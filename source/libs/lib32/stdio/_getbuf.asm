; _GETBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include malloc.inc

    .code

    assume edx:LPFILE

_getbuf proc fp:LPFILE
    malloc(_INTIOBUF)
    mov edx,fp
    .ifnz
        or  [edx]._flag,_IOMYBUF
        mov [edx]._bufsiz,_INTIOBUF
    .else
        or  [edx]._flag,_IONBF
        mov [edx]._bufsiz,4
        lea eax,[edx]._charbuf
    .endif
    mov [edx]._ptr,eax
    mov [edx]._base,eax
    mov [edx]._cnt,0
    ret
_getbuf endp

    END
