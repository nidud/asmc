; TIDECX.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .code

    assume edx: ptr TEDIT

tidecx proc uses eax ecx ti:ptr TEDIT

    mov edx,ti
    mov eax,[edx].ti_boff
    add eax,[edx].ti_xoff

    .ifnz
        mov ecx,[edx].ti_boff
        mov eax,[edx].ti_xoff
        .if eax
            dec eax
            and edx,edx
            stc
        .else
            dec ecx
            test edx,edx
            clc
        .endif
        mov [edx].ti_xoff,eax
        mov [edx].ti_boff,ecx
    .endif
    ret

tidecx endp

tiincx proc uses eax ecx ti:ptr TEDIT

    mov edx,ti
    mov eax,[edx].ti_boff
    add eax,[edx].ti_xoff
    inc eax
    .if eax >= [edx].ti_bcol
        sub eax,eax
    .else
        mov ecx,[edx].ti_boff
        mov eax,[edx].ti_xoff
        inc eax
        .if eax >= [edx].ti_cols
            mov eax,[edx].ti_cols
            dec eax
            inc ecx
        .endif
        mov [edx].ti_xoff,eax
        mov [edx].ti_boff,ecx
    .endif
    ret

tiincx endp

    END
