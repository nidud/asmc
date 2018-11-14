; _ISATTY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc

    .code

    OPTION PROLOGUE:NONE, EPILOGUE:NONE

_isatty PROC handle:SINT

    lea rax,_osfile
    mov al,[rax+rcx]
    and eax,FH_DEVICE
    ret

_isatty ENDP

    END
