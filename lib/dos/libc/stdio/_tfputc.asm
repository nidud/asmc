; FPUTWC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include stdio.inc
include io.inc
include tchar.inc

    .code

    assume bx:LPFILE

_fputtc proc uses bx c:int_t, fp:LPFILE

    lesl bx,fp

    dec esl[bx]._cnt
    .ifl
        _tflsbuf( c, rbx )
    .else
        mov ax,c
        inc word ptr esl[bx]._ptr
        lesl bx,esl[bx]._ptr
        mov esl[bx-1],al
    .endif
    ret

_fputtc endp

    end
