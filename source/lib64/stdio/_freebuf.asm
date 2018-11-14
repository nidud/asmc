; _FREEBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include malloc.inc

    .code

    option win64:rsp

_freebuf proc fp:LPFILE

    mov eax,[rcx]._iobuf._flag
    .if eax & _IOREAD or _IOWRT or _IORW
	.if eax & _IOMYBUF
	    free([rcx]._iobuf._base)
	    xor eax,eax
	    mov rcx,fp
	    mov [rcx]._iobuf._ptr,rax
	    mov [rcx]._iobuf._base,rax
	    mov [rcx]._iobuf._flag,eax
	    mov [rcx]._iobuf._bufsiz,eax
	    mov [rcx]._iobuf._cnt,eax
	.endif
    .endif
    ret
_freebuf endp

    END
