; _TWCTITLE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

wctitle proc p:PCHAR_INFO, l:int_t, string:LPTSTR

    _at BG_TITLE,FG_TITLE,' '
    wcputw(p, l, eax)
    wcenter(p, l, string)
    ret

wctitle endp

    END
