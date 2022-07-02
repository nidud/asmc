; _STRREV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

_wcsrev proc uses rbx string:wstring_t

ifndef _WIN64
    mov ecx,string
endif

    .for ( rdx = rcx : word ptr [rdx] : rdx += 2 )
    .endf
    .for ( rdx -= 2 : rdx > rcx : rdx -= 2, rcx += 2 )

        mov ax,[rcx]
        mov bx,[rdx]
        mov [rcx],bx
        mov [rdx],ax
    .endf
    .return( string )

_wcsrev endp

    end
