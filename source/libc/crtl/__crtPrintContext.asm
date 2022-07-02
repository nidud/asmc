; PRINTCONTEXT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Change history:
; 2022-06-28 - added __pxcptinfoptrs()
; 2018-12-17 - format + "I64"
; 2018-12-17 - assign value <[rdx+8]=rax> (Asmc v2.28.15)
;

include stdio.inc
include signal.inc

    .code

__crtPrintContext proc uses rsi rdi rbx

    mov rcx,__pxcptinfoptrs()

    mov rbx,[rcx].EXCEPTION_POINTERS.ContextRecord
    mov rsi,[rcx].EXCEPTION_POINTERS.ExceptionRecord

ifdef _WIN64

    lea rdi,@CStr(
            "\n"
            "This message is created due to unrecoverable error\n"
            "and may contain data necessary to locate it.\n"
            "\n"
            "Code:\t%08X\n"
            "Flags:  %08X\n"
            "\n"
            "\tRAX: %p R8:  %p\n"
            "\tRBX: %p R9:  %p\n"
            "\tRCX: %p R10: %p\n"
            "\tRDX: %p R11: %p\n"
            "\tRSI: %p R12: %p\n"
            "\tRDI: %p R13: %p\n"
            "\tRBP: %p R14: %p\n"
            "\tRSP: %p R15: %p\n"
            "\tRIP: %p %p\n\n"
            "\tEFL: 0000000000000000\n"
            "\t     r n oditsz a p c\n\n" )
else

    lea edi,@CStr(
            "\n"
            "This message is created due to unrecoverable error\n"
            "and may contain data necessary to locate it.\n"
            "\n"
            "Code:\t%08X\n"
            "Flags:  %08X\n"
            "\n"
            "\tEAX: %p EDX: %p\n"
            "\tEBX: %p ECX: %p\n"
            "\tESI: %p EDI: %p\n"
            "\tESP: %p EBP: %p\n"
            "\tEIP: %p %p%p\n\n"
            "\tEFL: 0000000000000000\n"
            "\t     r n oditsz a p c\n\n" )
endif

    mov eax,[rbx].CONTEXT.EFlags
    mov ecx,16
    .repeat
        shr eax,1
        adc byte ptr [rdi+rcx+sizeof(@CStr(0))-43],0
    .untilcxz

ifdef _WIN64

    mov rdx,[rbx].CONTEXT._Rip
    mov rcx,[rdx]

    printf( rdi,
            [rsi].EXCEPTION_RECORD.ExceptionCode,
            [rsi].EXCEPTION_RECORD.ExceptionFlags,
            [rbx].CONTEXT._Rax, [rbx].CONTEXT._R8,
            [rbx].CONTEXT._Rbx, [rbx].CONTEXT._R9,
            [rbx].CONTEXT._Rcx, [rbx].CONTEXT._R10,
            [rbx].CONTEXT._Rdx, [rbx].CONTEXT._R11,
            [rbx].CONTEXT._Rsi, [rbx].CONTEXT._R12,
            [rbx].CONTEXT._Rdi, [rbx].CONTEXT._R13,
            [rbx].CONTEXT._Rbp, [rbx].CONTEXT._R14,
            [rbx].CONTEXT._Rsp, [rbx].CONTEXT._R15,
            rdx, rcx )
else

    mov edx,[ebx].CONTEXT._Eip
    mov ecx,[edx]

    printf( edi,
            [esi].EXCEPTION_RECORD.ExceptionCode,
            [esi].EXCEPTION_RECORD.ExceptionFlags,
            [ebx].CONTEXT._Eax, [ebx].CONTEXT._Edx,
            [ebx].CONTEXT._Ebx, [ebx].CONTEXT._Ecx,
            [ebx].CONTEXT._Esi, [ebx].CONTEXT._Edi,
            [ebx].CONTEXT._Esp, [ebx].CONTEXT._Ebp,
            edx, [edx+4], ecx )
endif
    ret

__crtPrintContext endp

    end
