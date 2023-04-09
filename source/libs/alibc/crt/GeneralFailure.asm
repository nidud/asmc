; GENERALFAILURE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include stdlib.inc
include signal.inc
define __USE_GNU
include ucontext.inc

.code

__crtGeneralFailure proc signo:int_t

    .if ( edi != SIGTERM )

        assume rbx:ptr mcontext_t

        lea rdi,@CStr(
            "\n"
            "This message is created due to unrecoverable error\n"
            "and may contain data necessary to locate it.\n"
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


        mov rbx,rdx
        add rbx,ucontext_t.uc_mcontext
        mov rax,[rbx].gregs[REG_EFL*8]

        mov ecx,16
        .repeat
            shr eax,1
            adc byte ptr [rdi+rcx+sizeof(@CStr(0))-43],0
        .untilcxz

        mov rcx,[rbx].gregs[REG_RIP*8]
        mov rdx,[rcx]
        mov r10,[rcx-8]
        mov r11,[rcx+8]
        printf( rdi,
                [rbx].gregs[REG_RAX*8], [rbx].gregs[REG_R8*8],
                [rbx].gregs[REG_RBX*8], [rbx].gregs[REG_R9*8],
                [rbx].gregs[REG_RCX*8], [rbx].gregs[REG_R10*8],
                [rbx].gregs[REG_RDX*8], [rbx].gregs[REG_R11*8],
                [rbx].gregs[REG_RSI*8], [rbx].gregs[REG_R12*8],
                [rbx].gregs[REG_RDI*8], [rbx].gregs[REG_R13*8],
                [rbx].gregs[REG_RBP*8], [rbx].gregs[REG_R14*8],
                [rbx].gregs[REG_RSP*8], [rbx].gregs[REG_R15*8],
                rcx, rdx, r10, r11 )

    .endif
    exit(1)

__crtGeneralFailure endp

    end
