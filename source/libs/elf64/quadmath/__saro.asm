; __SARO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

    option win64:noauto

__saro proc val:ptr, count:int_t, bits:int_t

    mov ecx,esi
    mov esi,edx

    mov rax,[rdi]
    mov rdx,[rdi+8]

    .if ( ecx >= 64 && esi <= 64 )

        xor eax,eax
        xor edx,edx

    .elseif ( ecx >= 128 && esi == 128 )

        sar rdx,63
        mov rax,rdx

    .elseif ( esi == 128 )

        .while ( ecx > 64 )
            mov rax,rdx
            sar rdx,63
            sub ecx,64
        .endw
        shrd rax,rdx,cl
        sar rdx,cl

    .else

        .if ( rax == -1 && esi == 64 )

            xor edx,edx
        .endif

        .if ( ecx < 64 )

            shrd rax,rdx,cl
            sar rdx,cl
        .else
            mov rax,rdx
            sar rdx,63
            and cl,63
            sar rax,cl
        .endif
    .endif

    mov [rdi],rax
    mov [rdi+8],rdx
   .return( rdi )

__saro endp

    end
