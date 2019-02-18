; STRTRIM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strlib.inc
include string.inc

    .code

strtrim proc string:LPSTR

    .for ( rcx = strlen(rcx), rcx += string : rax : rax-- )

        dec rcx
        .break .if byte ptr [rcx] > ' '

        mov byte ptr [rcx],0

    .endf
    ret

strtrim endp

    END
