; RCINSIDE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .code

rcinside proc rc1, rc2
    xor eax,eax
    mov cx,word ptr rc1+2
    mov dx,word ptr rc2+2
    .if dh > ch || dl > cl
        mov eax,5
    .else
        add cx,word ptr rc1
        add dx,word ptr rc2
        .if ch < dh
            inc eax
        .elseif cl < dl
            mov eax,4
        .else
            mov cx,word ptr rc1
            mov dx,word ptr rc2
            .if ch > dh
                mov eax,2
            .elseif cl > dl
                mov eax,3
            .endif
        .endif
    .endif
    ret
rcinside endp

    END
