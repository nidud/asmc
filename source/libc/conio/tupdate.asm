; TUPDATE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.data
 tupdate DPROC 0

.code

_initupdate proc update:DPROC

    ldr rcx,update
    mov rax,tupdate
    mov tupdate,rcx
    ret

_initupdate endp

_tupdate proc

    .if ( tupdate )

        tupdate()
    .endif
    ret

_tupdate endp

    end
