; STRNCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .code

strncpy::

    push rcx    ; returns dest, with the character copied there.

    .if r8d >= 8

        mov r10,0x8080808080808080
        mov r11,0x0101010101010101

        mov rax,[rdx]   ; read 8 bytes

        mov r9,rax      ; find null character in source
        sub r9,r11
        not rax
        and r9,rax
        and r9,r10

        .ifz    ; source >= 8 ?

            not rax         ; copy first 8 bytes
            mov [rcx],rax

            mov eax,ecx     ; align dest 8
            neg eax
            and eax,8-1
            .ifz
                add eax,8   ; continue if aligned
            .endif
            add rcx,rax
            add rdx,rax
            sub r8d,eax

            .if r8d >= 8

                .repeat

                    mov rax,[rdx]
                    mov r9,rax
                    sub r9,r11
                    not rax
                    and r9,rax
                    and r9,r10

                    .break .ifnz    ; null character found ?

                    not rax         ; copy 8 bytes
                    mov [rcx],rax
                    add rcx,8
                    add rdx,8
                    sub r8d,8
                .until r8d < 8
            .endif
        .endif
    .endif

    .repeat

        .break .if !r8d

        .repeat         ; while (count && (*dest++ = *source++))

            mov al,[rdx]
            mov [rcx],al

            dec r8d
            .break(1) .ifz

            inc rcx
            inc rdx
        .until !al

        mov rdx,rdi     ; dest is padded with null characters to length count.
        mov rdi,rcx
        mov rcx,r8
        rep stosb
        mov rdi,rdx
    .until 1
    pop rax
    ret

    END
