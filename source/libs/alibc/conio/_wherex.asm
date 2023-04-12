; _WHEREX.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_wherex proc

   _cursorxy()
   movzx eax,ax
   ret

_wherex endp

    end
