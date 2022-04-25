; FGETS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

    assume rbx:ptr _iobuf

fgets proc uses rbx r12 r13 r14 buf:LPSTR, count:SINT, fp:LPFILE

    mov r13,rdi
    mov r12,rsi
    mov rbx,rdx
    mov r14,rdi
    xor eax,eax
    cmp r12,rax
    .return .ifng

    dec r12
    .ifnz
        .repeat
            dec [rbx]._cnt
            .ifl
                .ifd _filbuf(rbx) == -1
                    .break .if r13 != r14
                    .return 0
                .endif
            .else
                mov rcx,[rbx]._ptr
                inc [rbx]._ptr
                mov al,[rcx]
            .endif
            stosb
            .break .if al == 10
            dec r12
        .untilz
    .endif
    mov byte ptr [r13],0
    mov rax,r14
    ret

fgets endp

    END
