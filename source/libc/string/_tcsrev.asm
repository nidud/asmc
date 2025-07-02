; _TCSREV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include tchar.inc

    .code

_tcsrev proc uses rbx string:tstring_t

    ldr rcx,string

    .for ( rdx = rcx : tchar_t ptr [rdx] : rdx+=tchar_t )
    .endf

    .for ( rdx-=tchar_t : rdx > rcx : rdx-=tchar_t, rcx+=tchar_t )

        mov _tal,[rcx]
        mov _tbl,[rdx]
        mov [rcx],_tbl
        mov [rdx],_tal
    .endf
    .return( string )

_tcsrev endp

    end
