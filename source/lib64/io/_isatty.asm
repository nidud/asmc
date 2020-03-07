; _ISATTY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc

    .code

    option win64:rsp noauto

_isatty proc handle:SINT

    lea rax,_osfile
    mov al,[rax+rcx]
    and eax,FH_DEVICE
    ret

_isatty endp

    end
