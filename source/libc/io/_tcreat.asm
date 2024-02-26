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

_tcreat proc path:LPTSTR, mode:SINT

    ldr rax,path
    ldr edx,mode

    _tsopen( rax, O_CREAT or O_TRUNC or O_RDWR, SH_DENYNO, edx )
    ret

_tcreat endp

    end
