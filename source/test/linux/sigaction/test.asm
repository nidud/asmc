; TEST.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Change history:
; 2022-07-11 - added exception info to Linux64
;
include stdio.inc

define __USE_GNU
include signal.inc
include ucontext.inc

    .data
     canary dw 0
    .code

    assume rbx:ptr mcontext_t

myhandle proc uses rbx sig:int_t, info:ptr siginfo_t, context:ptr ucontext_t

    mov rbx,context
    add rbx,ucontext_t.uc_mcontext
    lea rdi,@CStr(
            "\n"
            "This message is created due to unrecoverable error\n"
            "and may contain data necessary to locate it.\n"
            "\n"
            "Code:\t%08X\n"
            "Errno:  %08X\n"
            "\n"
            "\tRAX: %016llX R8:  %016llX\n"
            "\tRBX: %016llX R9:  %016llX\n"
            "\tRCX: %016llX R10: %016llX\n"
            "\tRDX: %016llX R11: %016llX\n"
            "\tRSI: %016llX R12: %016llX\n"
            "\tRDI: %016llX R13: %016llX\n"
            "\tRBP: %016llX R14: %016llX\n"
            "\tRSP: %016llX R15: %016llX\n"
            "\tRIP: %016llX %016llX\n\n"
            "\tEFL: 0000000000000000\n"
            "\t     r n oditsz a p c\n\n")

    mov rax,[rbx].gregs[REG_EFL*8]
    mov ecx,16
    .repeat
        shr eax,1
        adc byte ptr [rdi+rcx+sizeof(@CStr(0))-43],0
    .untilcxz

    mov rcx,[rbx].gregs[REG_RIP*8]
    mov rdx,[rcx]
    mov canary,dx

    printf( rdi,
            [rsi].siginfo_t.si_code,
            [rsi].siginfo_t.si_errno,
            [rbx].gregs[REG_RAX*8], [rbx].gregs[REG_R8*8],
            [rbx].gregs[REG_RBX*8], [rbx].gregs[REG_R9*8],
            [rbx].gregs[REG_RCX*8], [rbx].gregs[REG_R10*8],
            [rbx].gregs[REG_RDX*8], [rbx].gregs[REG_R11*8],
            [rbx].gregs[REG_RSI*8], [rbx].gregs[REG_R12*8],
            [rbx].gregs[REG_RDI*8], [rbx].gregs[REG_R13*8],
            [rbx].gregs[REG_RBP*8], [rbx].gregs[REG_R14*8],
            [rbx].gregs[REG_RSP*8], [rbx].gregs[REG_R15*8],
            rcx, rdx )

    add [rbx].gregs[REG_RIP*8],0x02
    ret

myhandle endp


main proc argc:int_t, argv:array_t

   .new action:sigaction_t
    mov action.sa_sigaction,&myhandle
    mov action.sa_flags,SA_SIGINFO

    sigaction(SIGSEGV, &action, NULL)

    printf("create a segfault..\n")

    mov r8d,8
    mov r9d,9
    xor eax,eax
    mov [rax],eax ; crash...

    printf("still here..\n")

    ; Disassemble the code at RIP

    .new fp:ptr FILE = fopen("diasm.asm", "wt")
    .if ( fp )
        fprintf(fp, ".code\ndw 0x%X\nend\n", canary)
        fclose( fp )
    .endif
    .return( 0 )

main endp

    end
