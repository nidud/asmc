; _SCREADL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include malloc.inc

    .code

_scgetl proc x:int_t, y:int_t, l:int_t

   .new rc:TRECT = { dil, sil, dl, 1 }

    .ifs ( edx < 0 )

        not edx
        mov rc.col,1
        mov rc.row,dl
    .endif
    .if _rcalloc(rc, 0)
        _rcread(rc, rax)
    .endif
    ret

_scgetl endp

_scputl proc x:int_t, y:int_t, l:int_t, p:PCHAR_INFO

   .new rc:TRECT = { dil, sil, dl, 1 }

    .ifs ( edx < 0 )

        not edx
        mov rc.col,1
        mov rc.row,dl
    .endif
    _rcwrite(rc, rcx)
    free(p)
    ret

_scputl endp

    end
