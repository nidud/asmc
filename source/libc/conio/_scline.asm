; _SCREADL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include malloc.inc

    .code

_scgetl proc x:int_t, y:int_t, l:int_t

   .new rc:TRECT = { x, y, l, 1 }
    ldr eax,l
    .ifs ( eax < 0 )

        not eax
        mov rc.col,1
        mov rc.row,al
    .endif
    .if _rcalloc(rc, W_UNICODE)

        _rcread(rc, rax)
    .endif
    ret

_scgetl endp

_scputl proc x:int_t, y:int_t, l:int_t, p:PCHAR_INFO

   .new rc:TRECT = { x, y, l, 1 }
    ldr eax,l
    .ifs ( eax < 0 )

        not eax
        mov rc.col,1
        mov rc.row,al
    .endif
    _rcwrite(rc, p)
    free(p)
    ret

_scputl endp

    end
