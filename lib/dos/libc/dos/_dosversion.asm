; _DOSVERSION.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include dos.inc

.data
 _dosversion label word
 _dosmajor   db 0
 _dosminor   db 0

.code

_init_dosversion proc private uses bx

    mov ah,0x30
    int 0x21
    mov _dosversion,ax
    ret

_init_dosversion endp

.pragma init(_init_dosversion, 40)

    end
