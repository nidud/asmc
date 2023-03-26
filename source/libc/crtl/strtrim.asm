; STRTRIM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

strtrim proc string:string_t

    .for ( rcx = strlen(string), rcx += string : rax : rax-- )

        dec rcx
        .break .if byte ptr [rcx] > ' '

        mov byte ptr [rcx],0
    .endf
    ret

strtrim endp

    END
