; THELP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.data
 thelp DPROC 0

.code

_inithelp proc help:DPROC

    ldr rcx,help
    mov rax,thelp
    mov thelp,rcx
    ret

_inithelp endp

_thelp proc

    .if ( thelp )

        thelp()
    .endif
    ret

_thelp endp

    END
