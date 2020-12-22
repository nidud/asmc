; __SHRO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

    option win64:rsp noauto

__shro proc val:ptr, count:int_t, bits:int_t

    push rcx

    mov r10,rcx
    mov ecx,edx
    mov rax,[r10]
    mov rdx,[r10+8]

    .if ( ecx >= 128 ) || ( ecx >= 64 && r8d < 128 )

        xor edx,edx
        xor eax,eax

    .elseif r8d == 128

        .while ecx > 64
            mov rax,rdx
            xor edx,edx
            sub ecx,32
        .endw
        shrd rax,rdx,cl
        shr rdx,cl

    .else

        .if eax == -1 && r8d == 32

            xor edx,edx
        .endif

        .if ecx < 64

            shrd rax,rdx,cl
            shr rdx,cl
        .else

            mov rax,rdx
            xor edx,edx
            and cl,64-1
            shr rax,cl
        .endif
    .endif

    mov [r10],rax
    mov [r10+8],rdx
    pop rax
    ret

__shro endp

    end
