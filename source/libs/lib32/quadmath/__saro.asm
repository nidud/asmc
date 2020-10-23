; __SARO.ASM--
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

__saro proc uses esi edi ebx val:ptr, count:int_t, bits:int_t

    mov esi,val
    mov ecx,count

    mov eax,[esi].l64_l
    mov edx,[esi].l64_h
    mov ebx,[esi].h64_l
    mov edi,[esi].h64_h

    .if ecx >= 64 && bits <= 64

        xor eax,eax
        xor edx,edx
        xor ebx,ebx
        xor edi,edi

    .elseif ecx >= 128 && bits == 128

        sar edi,31
        mov ebx,edi
        mov edx,edi
        mov eax,edi

    .elseif bits == 128

        .while ecx > 32

            mov eax,edx
            mov edx,ebx
            mov ebx,edi
            sar edi,31
            sub ecx,32
        .endw

        shrd eax,edx,cl
        shrd edx,ebx,cl
        shrd ebx,edi,cl
        sar edi,cl

    .else

        .if eax == -1 && bits == 32

            xor edx,edx
        .endif

        .if ecx < 32

            shrd eax,edx,cl
            sar edx,cl
        .else

            mov eax,edx
            sar edx,31
            and cl,32-1
            sar eax,cl
        .endif
    .endif

    mov [esi].l64_l,eax
    mov [esi].l64_h,edx
    mov [esi].h64_l,ebx
    mov [esi].h64_h,edi
    mov eax,esi
    ret

__saro endp

    end
