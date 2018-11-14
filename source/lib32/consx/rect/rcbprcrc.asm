; RCBPRCRC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .code

rcbprcrc proc uses ebx r1, r2, wbuf:PVOID, cols

    mov     eax,cols
    add     eax,eax
    mov     bx,word ptr r1
    add     bx,word ptr r2
    mul     bh
    movzx   ebx,bl
    add     eax,ebx
    add     eax,ebx
    add     eax,wbuf
    ret

rcbprcrc endp

    END
