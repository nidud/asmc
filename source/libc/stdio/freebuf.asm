; FREEBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include malloc.inc

    .code

    assume rdx:LPFILE

_freebuf proc fp:LPFILE

    ldr rcx,fp

    mov rdx,rcx
    mov eax,[rdx]._flag
    .if ( eax & _IOREAD or _IOWRT or _IORW )

	.if ( eax & _IOMYBUF )

	    xor eax,eax
	    mov rcx,[rdx]._base
	    mov [rdx]._ptr,rax
	    mov [rdx]._base,rax
	    mov [rdx]._flag,eax
	    mov [rdx]._bufsiz,eax
	    mov [rdx]._cnt,eax
	    free( rcx )
	.endif
    .endif
    ret

_freebuf endp

    end
