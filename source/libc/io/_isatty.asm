; _ISATTY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc

    .code

_isatty proc handle:SINT

    ldr ecx,handle
    lea rax,_osfile
    mov al,[rax+rcx]
    and eax,FDEV
    ret

_isatty endp

    end
