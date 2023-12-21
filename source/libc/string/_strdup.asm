; _STRDUP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include string.inc

    .code

_strdup proc uses rbx string:LPSTR

    ldr rax,string
    .if rax

        mov rbx,rax
        .if malloc(&[strlen(rax)+1])

            strcpy(rax, rbx)
        .endif
    .endif
    ret

_strdup endp

    end
