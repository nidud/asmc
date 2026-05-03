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
ifdef __UNIX__
define __USE_GNU
include ucontext.inc
endif

    .code

__crtPrintContext proc uses rsi rdi rbx

    mov rcx,__pxcptinfoptrs()
ifdef __UNIX__
    assume rbx:ptr mcontext_t
    lea rbx,[rcx+ucontext_t.uc_mcontext]
else
    mov rbx,[rcx].EXCEPTION_POINTERS.ContextRecord
    mov rsi,[rcx].EXCEPTION_POINTERS.ExceptionRecord
endif

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
            "\tRIP: %p %p\n"
            "\t     %p %p\n\n"
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

ifdef __UNIX__
    mov rax,[rbx].gregs[REG_EFL*size_t]
else
    mov eax,[rbx].CONTEXT.EFlags
endif
    mov ecx,16
    .repeat
        shr eax,1
        adc byte ptr [rdi+rcx+sizeof(@CStr(0))-43],0
    .untilcxz

if defined(__UNIX__) and defined(_AMD64_)

    mov rcx,[rbx].gregs[REG_RIP*8]
    mov rdx,[rcx]
    mov r10,[rcx-8]
    mov r11,[rcx+8]
    xor esi,esi

    printf( rdi,
            rsi, rsi,
            [rbx].gregs[REG_RAX*8], [rbx].gregs[REG_R8*8],
            [rbx].gregs[REG_RBX*8], [rbx].gregs[REG_R9*8],
            [rbx].gregs[REG_RCX*8], [rbx].gregs[REG_R10*8],
            [rbx].gregs[REG_RDX*8], [rbx].gregs[REG_R11*8],
            [rbx].gregs[REG_RSI*8], [rbx].gregs[REG_R12*8],
            [rbx].gregs[REG_RDI*8], [rbx].gregs[REG_R13*8],
            [rbx].gregs[REG_RBP*8], [rbx].gregs[REG_R14*8],
            [rbx].gregs[REG_RSP*8], [rbx].gregs[REG_R15*8],
            rcx, rdx, r10, r11 )

elseifdef __UNIX__

    mov edx,[ebx].gregs[REG_EIP*4]
    mov ecx,[edx]
    xor esi,esi

    printf( edi,
            esi, esi,
            [ebx].gregs[REG_EAX*4], [ebx].gregs[REG_EDX*4],
            [ebx].gregs[REG_EBX*4], [ebx].gregs[REG_ECX*4],
            [ebx].gregs[REG_ESI*4], [ebx].gregs[REG_EDI*4],
            [ebx].gregs[REG_ESP*4], [ebx].gregs[REG_EBP*4],
            edx, [edx+4], ecx )

elseifdef _WIN64

    mov rdx,[rbx].CONTEXT._Rip
    mov rcx,[rdx]
    mov r10,[rdx-8]
    mov r11,[rdx+8]

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
            rdx, rcx, r10, r11 )
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
