; _TCREAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include share.inc
include fcntl.inc
include tchar.inc

    .code

_tcreat proc path:tstring_t, mode:int_t

    _tsopen( ldr(path), O_CREAT or O_TRUNC or O_RDWR, SH_DENYNO, ldr(mode) )
    ret

_tcreat endp

    end
