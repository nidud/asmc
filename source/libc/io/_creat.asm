; _CREAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include share.inc
include fcntl.inc

    .code

_creat proc path:string_t, mode:int_t

    ldr rax,path
    ldr edx,mode

    _sopen( rax, O_RDWR or O_CREAT or O_TRUNC, SH_DENYNO, edx )
    ret

_creat endp

    end
