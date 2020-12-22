; __SARO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

    option win64:rsp noauto

__saro proc val:ptr, count:int_t, bits:int_t

    push rcx

    mov r10,rcx
    mov ecx,edx

    mov rax,[r10]
    mov rdx,[r10+8]

    .if ecx >= 64 && r8d <= 64

        xor eax,eax
        xor edx,edx

    .elseif ecx >= 128 && r8d == 128

        sar rdx,63
        mov rax,rdx

    .elseif r8d == 128

        .while ecx > 64
            mov rax,rdx
            sar rdx,63
            sub ecx,64
        .endw
        shrd rax,rdx,cl
        sar rdx,cl

    .else

        .if rax == -1 && r8d == 64

            xor edx,edx
        .endif

        .if ecx < 64

            shrd rax,rdx,cl
            sar rdx,cl
        .else

            mov rax,rdx
            sar rdx,63
            and cl,63
            sar rax,cl
        .endif
    .endif

    mov [r10],rax
    mov [r10+8],rdx
    pop rax
    ret

__saro endp

    end
