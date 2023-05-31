; STRTRIM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

strtrim proc uses rbx string:string_t

    ldr rbx,string
    .for ( rcx = strlen(rbx), rcx += rbx : rax : rax-- )

        dec rcx
        .break .if byte ptr [rcx] > ' '

        mov byte ptr [rcx],0
    .endf
    ret

strtrim endp

    END
