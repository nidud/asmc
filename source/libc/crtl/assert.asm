; ASSERT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include stdlib.inc
include winnt.inc

    .data
     Context CONTEXT <>

    .code

assert_exit::

ifdef _WIN64
    mov Context._Rax,rax
    mov Context._Rcx,rcx
    mov Context._Rdx,rdx
    mov Context._Rbx,rbx
    mov Context._Rsp,rsp
    mov Context._Rbp,rbp
    mov Context._Rsi,rsi
    mov Context._Rdi,rdi
    mov Context._R8,r8
    mov Context._R9,r9
    mov Context._R10,r10
    mov Context._R11,r11
    mov Context._R12,r12
    mov Context._R13,r13
    mov Context._R14,r14
    mov Context._R15,r15
    mov rdx,[rsp]
    mov Context._Rip,rdx
    pushfq
else
    mov Context._Edi,edi
    mov Context._Esi,esi
    mov Context._Ebx,ebx
    mov Context._Edx,edx
    mov Context._Ecx,ecx
    mov Context._Eax,eax
    mov Context._Ebp,ebp
    mov Context._Esp,esp
    mov edx,[esp]
    mov Context._Eip,edx
    pushfd
endif
    pop rax
    mov Context.EFlags,eax

assertexit proc private

ifdef _WIN64

    lea rdi,@CStr(
            "assert failed: %s\n"
            "\n"
            "\tRAX: %p R8:  %p\n"
            "\tRBX: %p R9:  %p\n"
            "\tRCX: %p R10: %p\n"
            "\tRDX: %p R11: %p\n"
            "\tRSI: %p R12: %p\n"
            "\tRDI: %p R13: %p\n"
            "\tRBP: %p R14: %p\n"
            "\tRSP: %p R15: %p\n"
            "\tRIP: %p\n"
            "     EFlags: 0000000000000000\n"
            "\t     r n oditsz a p c\n\n" )
else

    lea edi,@CStr(
            "assert failed: %s\n"
            "\n"
            "\tEAX: %08X EDX: %08X\n"
            "\tEBX: %08X ECX: %08X\n"
            "\tESI: %08X EDI: %08X\n"
            "\tESP: %08X EBP: %08X\n"
            "\tEIP: %08X\n\n"
            "     EFlags: 0000000000000000\n"
            "\t     r n oditsz a p c\n\n" )
endif

    mov ecx,16
    .repeat
        shr eax,1
        adc byte ptr [rdi+rcx+sizeof(@CStr(0))-43],0
    .untilcxz

ifdef _WIN64

    printf( rdi, Context._Rip,
            Context._Rax, Context._R8,
            Context._Rbx, Context._R9,
            Context._Rcx, Context._R10,
            Context._Rdx, Context._R11,
            Context._Rsi, Context._R12,
            Context._Rdi, Context._R13,
            Context._Rbp, Context._R14,
            Context._Rsp, Context._R15,
            Context._Rip )
else

    printf( edi, Context._Eip,
            Context._Eax, Context._Edx,
            Context._Ebx, Context._Ecx,
            Context._Esi, Context._Edi,
            Context._Esp, Context._Ebp,
            Context._Eip )
endif

    exit( 1 )

assertexit endp

    end
