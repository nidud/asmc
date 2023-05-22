; _RCCLEAR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_rcclear proc uses rdi rc:TRECT, p:PCHAR_INFO, c:CHAR_INFO

    .if ( c.Char.UnicodeChar )

        movzx eax,rc.col
        mul   rc.row
        mov   ecx,eax
        mov   rdi,p
        mov   eax,c
        rep   stosd
    .else
        mov edx,rc
        mov dx,0
        _rcputa(rc, edx, p, c.Attributes )
    .endif
    ret

_rcclear endp

    end
