; WCTITLE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .code

wctitle proc p:PVOID, l:dword, string:LPSTR

    mov al,' '
    mov ah,at_background[B_Title]
    or  ah,at_foreground[F_Title]
    wcputw(p, l, eax)
    wcenter(p, l, string)
    ret

wctitle endp

    END
