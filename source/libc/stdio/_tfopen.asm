; _WFOPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; FILE *_wfopen(file, mode) - open a file
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
; Change history:
; 2017-02-16 - _UNICODE
;
include stdio.inc
include share.inc
include tchar.inc

    .code

_tfopen proc file:LPTSTR, mode:LPTSTR

    .if _getst()

        _topenfile( file, mode, SH_DENYNO, rax )
    .endif
    ret

_tfopen endp

    end
