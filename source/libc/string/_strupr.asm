; _STRUPR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include string.inc
include ctype.inc

    .code

strupr::

_strupr proc uses rbx string:string_t

    ldr rbx,string
    .for ( : byte ptr [rbx] : rbx++ )

        movzx ecx,byte ptr [rbx]
        toupper(ecx)
        mov [rbx],al
    .endf
    .return(string)

_strupr endp

    end
