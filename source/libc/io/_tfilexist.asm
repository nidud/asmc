; _TFILEXIST.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include direct.inc
include tchar.inc

.code

_tfilexist proc file:tstring_t

    .ifd ( _tgetfattr( ldr(file) ) == -1 )
        xor eax,eax
    .elseif ( eax & _F_SUBDIR )
        mov eax,2 ; 2 = subdir
    .else
        mov eax,1 ; 1 = file
    .endif
    ret

_tfilexist endp

    end
