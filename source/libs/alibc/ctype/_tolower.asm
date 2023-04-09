; _TOLOWER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc

    .code

_tolower proc c:int_t

    mov eax,edi
    sub al,'A'
    add al,'a'
    ret

_tolower endp

    end
