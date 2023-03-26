; _STRLWR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include string.inc
include ctype.inc

    .code

_strlwr proc uses rsi string:string_t

    .for ( rsi = string : byte ptr [rsi] : rsi++ )

        movzx ecx,byte ptr [rsi]
        tolower(ecx)
        mov [rsi],al
    .endf
    .return(string)

_strlwr endp

    end
