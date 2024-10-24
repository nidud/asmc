; _TUNLINK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; int _unlink(const char *filename);
; int _wunlink(const wchar_t *filename);
;
include io.inc
include tchar.inc

.code

_tunlink proc filename:tstring_t

    _tremove( ldr(filename) )
    ret

_tunlink endp

    end
