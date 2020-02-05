; STRSTART.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strlib.inc

    .code

    option stackbase:esp

strstart proc string:LPSTR

    mov eax,string
    .repeat

        add eax,1
        .continue(0) .if byte ptr [eax-1] == ' '
        .continue(0) .if byte ptr [eax-1] == 9
    .until 1
    sub eax,1
    ret

strstart endp

    END
