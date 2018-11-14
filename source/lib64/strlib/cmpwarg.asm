; CMPWARG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strlib.inc
include string.inc

    .code

    option win64:rsp nosave

cmpwarg proc path:LPSTR, wild:LPSTR

    xor eax,eax

    .while 1

        mov al,[rcx]
        mov ah,[rdx]
        inc rcx
        inc rdx

        .if ah == '*'

            .while 1

                mov ah,[rdx]
                .if !ah

                    mov eax,1
                    .break(1)
                .endif
                inc rdx
                .continue .if ah != '.'

                xor r8d,r8d
                .while al

                    .if al == ah

                        mov r8,rcx
                    .endif
                    mov al,[rcx]
                    inc rcx
                .endw

                mov rcx,r8
                .continue(1) .if r8

                mov ah,[rdx]
                inc rdx
                .continue .if ah == '*'

                test eax,eax
                mov  ah,0
                setz al
                .break(1)
            .endw

        .endif

        mov r8d,eax
        mov al,ah
        mov r9b,al
        xor eax,eax

        .if !r8b

            .break .if r8d
            inc eax
            .break
        .endif

        .break .if !r9b
        .continue .if r9b == '?'

        .if r9b == '.'

            .continue .if r8b == '.'
            .break
        .endif

        .break .if r8b == '.'

        or r8b,0x20
        or r9b,0x20
        .break .if r8b != r9b
    .endw
    ret

cmpwarg endp

cmpwargs proc uses rsi rdi path:LPSTR, wild:LPSTR

    mov rsi,rcx
    mov rdi,rdx

    .repeat

        .if strchr(rdi, ' ')

            mov rdi,rax
            mov byte ptr [rdi],0
            cmpwarg(rsi, rax)
            mov byte ptr [rdi],' '
            inc rdi
        .else
            cmpwarg(rsi, rdi)
            .break
        .endif
    .until eax
    ret

cmpwargs endp

    END
