; FPUTC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include io.inc

    .code

    assume bx:LPFILE

fputc proc uses bx c:int_t, fp:LPFILE

    ldr bx,fp
    dec esl[bx]._cnt
    .ifl
        _flsbuf( c, ldr(bx) )
    .else
        mov ax,c
        inc word ptr esl[bx]._ptr
        ldr bx,esl[bx]._ptr
        mov esl[bx-1],al
    .endif
    ret

fputc endp

    end
