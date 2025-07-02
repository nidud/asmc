; _TEROPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include tchar.inc

    .code

_eropen proc file:tstring_t

    _syserr("Error open file", "Can't open the file:\n%s", file)
    ret

_eropen endp

    end
