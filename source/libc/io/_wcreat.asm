; _WCREAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include share.inc
include fcntl.inc

    .code

_wcreat proc path:LPWSTR, mode:SINT

    ldr rax,path
    ldr edx,mode

    _wsopen( rax, O_CREAT or O_TRUNC or O_RDWR, SH_DENYNO, edx )
    ret

_wcreat endp

    end
