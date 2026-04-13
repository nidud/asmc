; _TINITEVENT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.data
 tgetevent DPROC 0

.code

_initevent proc event:DPROC
    ldr rcx,event
    mov rax,tgetevent
    mov tgetevent,rcx
    ret
    endp

__initevent proc private
    _initevent(&getevent)
    ret
    endp

.pragma init(__initevent, 50)


    END
