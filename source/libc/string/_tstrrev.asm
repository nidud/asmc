; _STRREV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include tmacro.inc

    .code

_tcsrev proc uses rbx string:LPTSTR

    ldr rcx,string

    .for ( rdx = rcx : TCHAR ptr [rdx] : rdx+=TCHAR )
    .endf

    .for ( rdx-=TCHAR : rdx > rcx : rdx-=TCHAR, rcx+=TCHAR )

        mov __a,[rcx]
        mov __b,[rdx]
        mov [rcx],__b
        mov [rdx],__a
    .endf
    .return( string )

_tcsrev endp

    end
