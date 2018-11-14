; GETXYS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .code

getxys proc x, y, b:LPSTR, l, bsize
    mov ah,1
    mov al,byte ptr l
    shl eax,16
    mov ah,byte ptr y
    mov al,byte ptr x
    dledit(b, eax, bsize, 0)
    ret
getxys endp

    END
