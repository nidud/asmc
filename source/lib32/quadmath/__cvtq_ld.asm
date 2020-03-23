; __CVTQ_LD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

__cvtq_ld proc uses ebx x:ptr, q:ptr

    xor ecx,ecx
    mov eax,q
    mov cx,[eax+14]
    mov edx,[eax+10]
    mov ebx,ecx
    and ebx,LD_EXPMASK
    neg ebx
    mov ebx,[eax+6]
    rcr edx,1
    rcr ebx,1

    ; round result

    .ifc
        .if ebx == -1 && edx == -1
            xor ebx,ebx
            mov edx,0x80000000
            inc cx
        .else
            add ebx,1
            adc edx,0
        .endif
    .endif
    mov eax,x
    mov [eax],ebx
    mov [eax+4],edx
    .if eax == q
        mov [eax+8],ecx
        mov dword ptr [eax+12],0
    .else
        mov [eax+8],cx
    .endif
    ret

__cvtq_ld endp

    end
