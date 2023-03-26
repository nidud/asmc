; _STRUPR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include string.inc
include ctype.inc

    .code

strupr::

_strupr proc uses rsi string:string_t

    .for ( rsi = string : byte ptr [rsi] : rsi++ )

        movzx ecx,byte ptr [rsi]
        toupper(ecx)
        mov [rsi],al
    .endf
    .return(string)

_strupr endp

    end
