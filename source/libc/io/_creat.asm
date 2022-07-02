; _CREAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include share.inc
include fcntl.inc

    .code

_creat proc path:string_t, pmode:int_t

    _sopen( path, O_RDWR or O_CREAT or O_TRUNC, SH_DENYNO, pmode )
    ret

_creat endp

    end
