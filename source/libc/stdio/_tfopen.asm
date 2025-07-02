; _TFOPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; FILE *[_w]fopen(file, mode) - open a file
;
; mode:
;  r  : read
;  w  : write
;  a  : append
;  z  : zip-stream rz/wx
;  r+ : read/write
;  w+ : open empty for read/write
;  a+ : read/append
;
; Append "t" or "b" for text and binary mode
;
; The c, n, R, S, t, T, and D mode options are
; Microsoft extensions for fopen and _wfopen and
; shouldn't be used when you want ANSI portability.
;
; To open a Unicode file, pass a ccs=encoding
; flag that specifies the desired encoding:
;
; fopen("file.txt", "rt+, ccs=UTF-8")
;
; UNICODE   : _O_WTEXT
; UTF-16LE  : _O_U16TEXT
; UTF-8     : _O_U8TEXT
;
; Change history:
; 2017-02-16 - _UNICODE
;
include stdio.inc
include share.inc
include tchar.inc

    .code

_tfopen proc file:tstring_t, mode:tstring_t

    .if _getst()

        _topenfile( file, mode, SH_DENYNO, rax )
    .endif
    ret

_tfopen endp

    end
