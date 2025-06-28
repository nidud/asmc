; EXIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

externdef _CRTFINI_S:ptr
externdef _CRTFINI_E:ptr

.code

exit proc retval:int_t

    _initterm(&_CRTFINI_S, &_CRTFINI_E)
    mov ax,retval
    mov ah,0x4C
    int 0x21

exit endp

    end
