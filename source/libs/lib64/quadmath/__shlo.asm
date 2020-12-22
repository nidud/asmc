; __SHLO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

    option win64:rsp noauto

__shlo proc val:ptr, count:int_t, bits:int_t

    push rcx
    mov r10,rcx
    mov ecx,edx

    mov rax,[r10]
    mov rdx,[r10+8]

    .if ( ecx >= 128 ) || ( ecx >= 64 && r8d < 128 )

        xor eax,eax
        xor edx,edx

    .elseif r8d == 128

        .while ecx >= 64

            mov rdx,rax
            xor eax,eax
            sub ecx,64
        .endw

        shld rdx,rax,cl
        shl rax,cl

    .else

        .if cl < 64

            shld rdx,rax,cl
            shl rax,cl
        .else

            and ecx,63
            mov rdx,rax
            xor eax,eax
            shl rdx,cl
        .endif
    .endif

    mov [r10],rax
    mov [r10+8],rdx
    pop rax
    ret

__shlo endp

    end
