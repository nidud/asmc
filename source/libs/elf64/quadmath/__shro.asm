; __SHRO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

    option win64:noauto

__shro proc val:ptr, count:int_t, bits:int_t

    mov ecx,esi
    mov esi,edx
    mov rax,[rdi]
    mov rdx,[rdi+8]

    .if ( ( ecx >= 128 ) || ( ecx >= 64 && esi < 128 ) )

        xor edx,edx
        xor eax,eax

    .elseif ( esi == 128 )

        .while ecx > 64
            mov rax,rdx
            xor edx,edx
            sub ecx,32
        .endw
        shrd rax,rdx,cl
        shr rdx,cl

    .else

        .if ( eax == -1 && esi == 32 )

            xor edx,edx
        .endif

        .if ( ecx < 64 )

            shrd rax,rdx,cl
            shr rdx,cl
        .else
            mov rax,rdx
            xor edx,edx
            and cl,64-1
            shr rax,cl
        .endif
    .endif
    mov [rdi],rax
    mov [rdi+8],rdx
   .return( rdi )

__shro endp

    end
