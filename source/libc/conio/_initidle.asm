; TIDLE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include winbase.inc

.data
 tidle DPROC 0

.code

_initidle proc idle:DPROC

    ldr rcx,idle
    mov rax,tidle
    mov tidle,rcx
    ret

_initidle endp

_tidle proc

    mov rax,tidle
    .if ( rax )

        rax()
    .else
ifdef __UNIX__
else
        Sleep( 4 )
endif
    .endif
    xor eax,eax
    ret

_tidle endp

    end
