; _GETXYW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_getxyw proc x:int_t, y:int_t

  local Attrib:byte

    mov Attrib,_getxya(ecx, edx)
    _getxyc(x, y)
    mov ah,Attrib
    ret

_getxyw endp

    END
