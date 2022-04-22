; _ISATTY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc

    .code

_isatty proc handle:SINT

    lea rax,_osfile
    mov al,[rax+rdi]
    and eax,FH_DEVICE
    ret

_isatty endp

    end
