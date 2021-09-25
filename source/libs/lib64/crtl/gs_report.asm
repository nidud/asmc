define _VCRT_ALLOW_INTERNALS
include vcruntime_internal.inc

STATUS_SECURITY_CHECK_FAILURE equ STATUS_STACK_BUFFER_OVERRUN

if defined(_CRT_APP) or defined(_M_ARM) or defined(_M_ARM64) or defined(_SCRT_ENCLAVE_BUILD)

PROCESSOR_FAST_FAIL_AVAILABLE equ 1

elseif defined(_M_IX86) or defined(_M_X64)

else

.err <Unsupported architecture>

endif

extern __security_cookie:UINT_PTR
extern __security_cookie_complement:UINT_PTR

.data
GS_ExceptionRecord      EXCEPTION_RECORD <>
GS_ContextRecord        CONTEXT <>
GS_ExceptionPointers    EXCEPTION_POINTERS { GS_ExceptionRecord, GS_ContextRecord }
ifdef _VCRT_BUILD
DebuggerWasPresent      BOOL 0
endif

.code

if not defined(PROCESSOR_FAST_FAIL_AVAILABLE) and defined(_M_X64)

    capture_current_context proc pContextRecord:ptr CONTEXT

      local ControlPc        : ULONG64
      local EstablisherFrame : ULONG64
      local ImageBase        : ULONG64
      local FunctionEntry    : PRUNTIME_FUNCTION
      local HandlerData      : PVOID

        RtlCaptureContext(rcx)

        mov rcx,pContextRecord
        mov ControlPc,[rcx].CONTEXT._Rip
        mov FunctionEntry,RtlLookupFunctionEntry(ControlPc, &ImageBase, NULL)

        .if rax

            RtlVirtualUnwind(
                UNW_FLAG_NHANDLER,
                ImageBase,
                ControlPc,
                FunctionEntry,
                pContextRecord,
                &HandlerData,
                &EstablisherFrame,
                NULL);
        .endif
        ret

    capture_current_context endp

    capture_previous_context proc pContextRecord:ptr CONTEXT

      local ControlPc        : ULONG64
      local EstablisherFrame : ULONG64
      local ImageBase        : ULONG64
      local FunctionEntry    : PRUNTIME_FUNCTION
      local HandlerData      : PVOID
      local frames           : int_t

        RtlCaptureContext(rcx)

        mov rcx,pContextRecord
        mov ControlPc,[rcx].CONTEXT._Rip

        .for frames = 0: frames < 2: ++frames

            .if RtlLookupFunctionEntry(ControlPc, &ImageBase, NULL)
                mov r9,rax
                RtlVirtualUnwind(
                    UNW_FLAG_NHANDLER,
                    ImageBase,
                    ControlPc,
                    r9,
                    pContextRecord,
                    &HandlerData,
                    &EstablisherFrame,
                    NULL)

            .else

                .break
            .endif
        .endf
        ret

    capture_previous_context endp

endif


ifndef PROCESSOR_FAST_FAIL_AVAILABLE

__raise_securityfailure proc exception_pointers:PEXCEPTION_POINTERS

        ifdef _VCRT_BUILD
        mov DebuggerWasPresent,IsDebuggerPresent()
        _CRT_DEBUGGER_HOOK(_CRT_DEBUGGER_GSFAILURE)
        endif

        SetUnhandledExceptionFilter(NULL)
        UnhandledExceptionFilter(exception_pointers)

        ifdef _VCRT_BUILD
        .if !DebuggerWasPresent

            _CRT_DEBUGGER_HOOK(_CRT_DEBUGGER_GSFAILURE)
        .endif
        endif

    TerminateProcess(GetCurrentProcess(), STATUS_SECURITY_CHECK_FAILURE)
    ret

__raise_securityfailure endp

endif

ifdef _M_IX86
    GSFAILURE_PARAMETER equ <>
elseifdef _M_X64
    GSFAILURE_PARAMETER equ <stack_cookie:ULONGLONG>
elseif defined(_M_ARM) or defined(_M_ARM64)
    GSFAILURE_PARAMETER equ <stack_cookie:uintptr_t>
else
    .err <Unsupported architecture>
endif

ifdef PROCESSOR_FAST_FAIL_AVAILABLE

    __report_gsfailure proc GSFAILURE_PARAMETER
        __fastfail(FAST_FAIL_STACK_COOKIE_CHECK_FAILURE)
        ret
    __report_gsfailure endp

else

    __report_gsfailure proc GSFAILURE_PARAMETER

        local cookie[2]:UINT_PTR

        .if IsProcessorFeaturePresent(PF_FASTFAIL_AVAILABLE)

            __fastfail(FAST_FAIL_STACK_COOKIE_CHECK_FAILURE)
        .endif

        ifdef _M_IX86

        else

        capture_previous_context(&GS_ContextRecord)

        mov GS_ContextRecord._Rip,               _ReturnAddress()
        mov GS_ExceptionRecord.ExceptionAddress, rax
        add _AddressOfReturnAddress(),8
        mov GS_ContextRecord._Rsp,               rax
        mov GS_ContextRecord._Rcx,               stack_cookie

        endif

        mov GS_ExceptionRecord.ExceptionCode,           STATUS_SECURITY_CHECK_FAILURE
        mov GS_ExceptionRecord.ExceptionFlags,          EXCEPTION_NONCONTINUABLE
        mov GS_ExceptionRecord.NumberParameters,        1
        mov GS_ExceptionRecord.ExceptionInformation[0], FAST_FAIL_STACK_COOKIE_CHECK_FAILURE

        mov cookie[0],__security_cookie
        mov cookie[8],__security_cookie_complement

        __raise_securityfailure(&GS_ExceptionPointers)
        ret

    __report_gsfailure endp

endif



ifdef PROCESSOR_FAST_FAIL_AVAILABLE


    __report_securityfailureEx proc failure_code:ULONG, parameter_count:ULONG, parameters:ptr ptr

        __fastfail(failure_code)
        ret

    __report_securityfailureEx endp

else

    __report_securityfailureEx proc failure_code:ULONG, parameter_count:ULONG, parameters:ptr ptr

        .if IsProcessorFeaturePresent(PF_FASTFAIL_AVAILABLE)

            __fastfail(failure_code)
        .endif

        ifdef _M_IX86

        else

        capture_current_context(&GS_ContextRecord)
        mov GS_ContextRecord._Rip,_ReturnAddress()
        mov GS_ExceptionRecord.ExceptionAddress,rax
        add _AddressOfReturnAddress(),8
        mov GS_ContextRecord._Rsp,rax

        endif

        mov GS_ExceptionRecord.ExceptionCode,STATUS_SECURITY_CHECK_FAILURE
        mov GS_ExceptionRecord.ExceptionFlags,EXCEPTION_NONCONTINUABLE

        .if (parameter_count > 0 && parameters == NULL)

            mov parameter_count,0
        .endif

        .if (parameter_count > EXCEPTION_MAXIMUM_PARAMETERS - 1)

            dec parameter_count
        .endif

        mov eax,parameter_count
        inc eax
        mov GS_ExceptionRecord.NumberParameters,eax
        mov GS_ExceptionRecord.ExceptionInformation[0],failure_code

        .for rdx = parameters, ecx = 0: ecx < parameter_count: ecx++

            mov rax,[rdx+rcx*8]
            mov GS_ExceptionRecord.ExceptionInformation[rcx*8+8],rax
        .endf

        __raise_securityfailure(&GS_ExceptionPointers)
        ret

    __report_securityfailureEx endp

endif


ifdef PROCESSOR_FAST_FAIL_AVAILABLE

    __report_securityfailure proc failure_code:ULONG

        __fastfail(failure_code)
        ret

    __report_securityfailure endp

else

    __report_securityfailure proc failure_code:ULONG

        .if IsProcessorFeaturePresent(PF_FASTFAIL_AVAILABLE)

            __fastfail(failure_code)
        .endif

        ifdef _M_IX86

        else

        capture_current_context(&GS_ContextRecord)
        mov GS_ContextRecord._Rip, _ReturnAddress()
        mov GS_ExceptionRecord.ExceptionAddress,rax
        add _AddressOfReturnAddress(),8
        mov GS_ContextRecord._Rsp,rax

        endif

        mov GS_ExceptionRecord.ExceptionCode,  STATUS_SECURITY_CHECK_FAILURE
        mov GS_ExceptionRecord.ExceptionFlags, EXCEPTION_NONCONTINUABLE

        mov GS_ExceptionRecord.NumberParameters,1
        mov GS_ExceptionRecord.ExceptionInformation[0],failure_code

        __raise_securityfailure(&GS_ExceptionPointers)
        ret

    __report_securityfailure endp

endif

__report_rangecheckfailure proc

    __report_securityfailure(FAST_FAIL_RANGE_CHECK_FAILURE)
    ret

__report_rangecheckfailure endp

    end
