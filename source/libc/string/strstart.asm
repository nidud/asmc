; STRSTART.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include ctype.inc

    .code

strstart proc uses rbx string:string_t

    ldr rbx,string
    .while( isspace([rbx]) )

        inc rbx
    .endw
    .return( rbx )

strstart endp

    end
