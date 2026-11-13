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
    endp

_tidle proc
    mov rax,tidle
    .if ( rax )
        rax()
    .else
        Sleep( 4 )
    .endif
    xor eax,eax
    ret
    endp

    end
