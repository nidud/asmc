; ASSERT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include stdlib.inc
include conio.inc

    .data

    _ax     dq 0
    _cx     dq 0
    _dx     dq 0

    regs    db "assert failed: %s",10
            db 10
            db 9,' regs:'
            db 9,   'RAX: %016llX R8:  %016llX',10
            db 9,9, 'RBX: %016llX R9:  %016llX',10
            db 9,9, 'RCX: %016llX R10: %016llX',10
            db 9,9, 'RDX: %016llX R11: %016llX',10
            db 9,9, 'RSI: %016llX R12: %016llX',10
            db 9,9, 'RDI: %016llX R13: %016llX',10
            db 9,9, 'RBP: %016llX R14: %016llX',10
            db 9,9, 'RSP: %016llX R15: %016llX',10
            db 9,9, 'RIP: %016llX',10
            db 10
            db 9,'flags:  '
    bits    db '0000000000000000',10
            db 9,9,'r n oditsz a p c',10,0

    .code

    option win64:rsp noauto

assert_exit proc

    mov _ax,rax
    mov _dx,rdx
    mov _cx,rcx

    lea rdx,bits
    pushfq
    pop rax
    mov rcx,16
    .repeat
        shr eax,1
        adc byte ptr [rdx+rcx-1],0
    .untilcxz

    mov rax,rsp
    pop rdx

    printf( &regs, rdx, _ax, r8, rbx, r9, _cx, r10, _dx, r11, rsi, r12, rdi, r13,
        rbp, r14, rax, r15, rdx )
    _getch()
    exit(1)
    ret

assert_exit endp

    end
