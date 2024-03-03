; _STRREV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include tchar.inc

    .code

_tcsrev proc uses rbx string:LPTSTR

    ldr rcx,string

    .for ( rdx = rcx : TCHAR ptr [rdx] : rdx+=TCHAR )
    .endf

    .for ( rdx-=TCHAR : rdx > rcx : rdx-=TCHAR, rcx+=TCHAR )

        mov _tal,[rcx]
        mov _tbl,[rdx]
        mov [rcx],_tbl
        mov [rdx],_tal
    .endf
    .return( string )

_tcsrev endp

    end
