; _TOLOWER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include ctype.inc

    .code

    OPTION PROLOGUE:NONE, EPILOGUE:NONE

_tolower proc char:SINT

    movzx eax,cl
    sub al,'A'
    add al,'a'
    ret

_tolower ENDP

    END