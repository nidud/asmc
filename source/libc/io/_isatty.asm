; _ISATTY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc

    .code

_isatty proc handle:SINT

ifndef _WIN64
    mov ecx,handle
endif
    lea rax,_osfile
    mov al,[rax+rcx]
    and eax,FH_DEVICE
    ret

_isatty endp

    end
