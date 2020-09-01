; _GETBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include malloc.inc

    .code

    option win64:rsp
    assume rdx:LPFILE

_getbuf proc fp:LPFILE

    malloc(_INTIOBUF)
    mov rdx,fp
    .if rax
	or  [rdx]._flag,_IOMYBUF
	mov [rdx]._bufsiz,_INTIOBUF
    .else
	or  [rdx]._flag,_IONBF
	mov [rdx]._bufsiz,4
	lea rax,[rdx]._charbuf
    .endif
    mov [rdx]._ptr,rax
    mov [rdx]._base,rax
    mov [rdx]._cnt,0
    ret
_getbuf endp

    END
