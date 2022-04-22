; _FREEBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include malloc.inc

    .code

_freebuf proc fp:LPFILE

    mov eax,[rdi]._iobuf._flag

    .if ( eax & _IOREAD or _IOWRT or _IORW )

	.if ( eax & _IOMYBUF )

	    mov rcx,[rdi]._iobuf._base
	    xor eax,eax
	    mov [rdi]._iobuf._ptr,rax
	    mov [rdi]._iobuf._base,rax
	    mov [rdi]._iobuf._flag,eax
	    mov [rdi]._iobuf._bufsiz,eax
	    mov [rdi]._iobuf._cnt,eax
	    free(rcx)
	.endif
    .endif
    ret

_freebuf endp

    END
