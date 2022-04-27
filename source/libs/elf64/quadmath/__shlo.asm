; __SHLO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

    option win64:noauto

__shlo proc val:ptr, count:int_t, bits:int_t

    mov ecx,esi
    mov esi,edx
    mov rax,[rdi]
    mov rdx,[rdi+8]

    .if ( ( ecx >= 128 ) || ( ecx >= 64 && esi < 128 ) )

        xor eax,eax
        xor edx,edx

    .elseif ( esi == 128 )

        .while ( ecx >= 64 )

            mov rdx,rax
            xor eax,eax
            sub ecx,64
        .endw

        shld rdx,rax,cl
        shl rax,cl
    .else
        .if ( cl < 64 )

            shld rdx,rax,cl
            shl rax,cl
        .else
            and ecx,63
            mov rdx,rax
            xor eax,eax
            shl rdx,cl
        .endif
    .endif

    mov [rdi],rax
    mov [rdi+8],rdx
   .return( rdi )

__shlo endp

    end
