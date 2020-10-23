; __SHRO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

u128 struct
l64_l dd ?
l64_h dd ?
h64_l dd ?
h64_h dd ?
u128 ends

    .code

    assume esi:ptr u128

__shro proc uses esi edi ebx val:ptr, count:int_t, bits:int_t

    mov esi,val
    mov ecx,count

    mov eax,[esi].l64_l
    mov edx,[esi].l64_h
    mov ebx,[esi].h64_l
    mov edi,[esi].h64_h

    .if ( ecx >= 128 ) || ( ecx >= 64 && bits < 128 )

        xor edi,edi
        xor ebx,ebx
        xor edx,edx
        xor eax,eax

    .elseif bits == 128

        .while ecx > 32

            mov eax,edx
            mov edx,ebx
            mov ebx,edi
            xor edi,edi
            sub ecx,32
        .endw

        shrd eax,edx,cl
        shrd edx,ebx,cl
        shrd ebx,edi,cl
        shr edi,cl

    .else

        .if eax == -1 && bits == 32

            xor edx,edx
        .endif

        .if ecx < 32

            shrd eax,edx,cl
            shr edx,cl
        .else

            mov eax,edx
            xor edx,edx
            and cl,32-1
            shr eax,cl
        .endif
    .endif

    mov [esi].l64_l,eax
    mov [esi].l64_h,edx
    mov [esi].h64_l,ebx
    mov [esi].h64_h,edi
    mov eax,esi
    ret

__shro endp

    end
