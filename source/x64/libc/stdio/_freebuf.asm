include stdio.inc
include alloc.inc

	.code

	OPTION	WIN64:3, STACKBASE:rsp

_freebuf PROC fp:LPFILE

	mov	eax,[rcx].S_FILE.iob_flag
	.if	eax & _IOREAD or _IOWRT or _IORW
		.if	eax & _IOMYBUF
			free( [rcx].S_FILE.iob_base )
			xor	eax,eax
			mov	rcx,fp
			mov	[rcx].S_FILE.iob_ptr,rax
			mov	[rcx].S_FILE.iob_base,rax
			mov	[rcx].S_FILE.iob_flag,eax
			mov	[rcx].S_FILE.iob_bufsize,eax
			mov	[rcx].S_FILE.iob_cnt,eax
		.endif
	.endif
	ret
_freebuf ENDP

	END
