; _PUTWCH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include io.inc
include conio.inc

    .code

_putwch proc wc:wchar_t

    .if ( _conout == -1 )

        mov eax,WEOF
    .else
        ;
        ; write character to console file handle
        ;
        .new c:int_t = _wtoutf(wc)
        .if _write( _conout, &c, ecx )
            movzx eax,wc
        .else
            mov eax,WEOF
        .endif
    .endif
    ret

_putwch endp

    end
