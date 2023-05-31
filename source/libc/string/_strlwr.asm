; _STRLWR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include string.inc
include ctype.inc

    .code

_strlwr proc uses rbx string:string_t

    ldr rbx,string
    .for ( : byte ptr [rbx] : rbx++ )

        movzx ecx,byte ptr [rbx]
        tolower(ecx)
        mov [rbx],al
    .endf
    .return(string)

_strlwr endp

    end
