; _RCCLEAR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_rcclear proc _rc:TRECT, p:PCHAR_INFO, ci:CHAR_INFO

   .new c:CHAR_INFO = ci
   .new rc:TRECT = _rc

    .if ( c.Char.UnicodeChar )

        movzx eax,rc.col
        mul   rc.row
        mov   ecx,eax
        mov   rdi,p
        mov   eax,c
        rep   stosd
    .else
        mov eax,rc
        mov ax,0
        _rcputa(rc, eax, p, c.Attributes )
    .endif
    ret

_rcclear endp

    end
