; _WCSICMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

_wcsicmp proc uses ebx s1:ptr wchar_t, s2:ptr wchar_t

    mov edx,s1
    mov ecx,s2
    mov eax,1

    .repeat

        .break .if !eax

        mov ax,[ecx]
        mov bx,[edx]
        add ecx,2
        add edx,2
        .continue(0) .if ax == bx

        and eax,0xFFDF
        and ebx,0xFFDF
        .continue(0) .if ebx == eax

        sbb ax,ax
        sbb ax,-1
    .until 1
    movsx eax,ax
    ret

_wcsicmp endp

    end
