; _TOUPPER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc

    .code

_toupper proc c:int_t

    mov eax,c
    sub al,'a'-'A'
    ret

_toupper endp

    end

