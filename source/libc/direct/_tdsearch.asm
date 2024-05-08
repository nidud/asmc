; _TDSEARCH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include direct.inc
include string.inc
include tchar.inc

    .code

    assume rbx:PDIRENT

_dsearch proc uses rbx d:PDIRENT, name:LPTSTR

   .new i:int_t
    ldr rbx,d

    .for ( i = 0 : i < [rbx].count : i++ )

        imul eax,i,size_t
        add  rax,[rbx].fcb
        mov  rcx,[rax]

        .ifd ( !_tcscmp(name, [rcx].FILENT.name) )

            .return( i )
        .endif
    .endf
    .return( -1 )

_dsearch endp

    end
