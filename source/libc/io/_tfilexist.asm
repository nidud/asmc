; _TFILEXIST.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include tchar.inc

.code

_tfilexist proc file:LPTSTR

    _tgetfattr( ldr(file) )
    inc eax
    .ifnz
        dec eax             ; 1 = file
        and eax,_A_SUBDIR   ; 2 = subdir
        shr eax,4
        inc eax
    .endif
    ret

_tfilexist endp

    end
