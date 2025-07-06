; FOPEN.D--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; FILE *fopen(file, mode) - open a file
;
; mode:
;  r  : read
;  w  : write
;  a  : append
;  r+ : read/write
;  w+ : open empty for read/write
;  a+ : read/append
;
; Append "t" or "b" for text and binary mode
;

include stdio.inc
include share.inc

    .code

fopen proc file:string_t, mode:string_t

    .if _getst()

        _openfile( file, mode, SH_DENYNO, ldr(ax) )
    .endif
    ret

fopen endp

    end
