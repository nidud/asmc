; _WCSNICMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

_wcsnicmp proc uses esi edi s1:LPWSTR, s2:LPWSTR, count:SIZE_T

    mov esi,s1
    mov edi,s2
    mov ecx,count
    mov al,-1

    .repeat

        .break .if !ax

        xor eax,eax
        .break .if !ecx

        mov ax,[edi]
        dec ecx
        add edi,2
        add esi,2
        .continue(0) .if ax == [esi-2]

        mov dx,[esi-2]
        and eax,0xFFDF
        and edx,0xFFDF
        .continue(0) .if edx == eax

        sbb ax,ax
        sbb ax,-1
    .until 1
    movsx eax,ax
    ret

_wcsnicmp endp

    end
