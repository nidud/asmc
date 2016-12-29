include stdio.inc
include alloc.inc

	.code

_freebuf PROC fp:LPFILE
	mov	ecx,fp
	mov	eax,[ecx].S_FILE.iob_flag
	.if	eax & _IOREAD or _IOWRT or _IORW
		.if	eax & _IOMYBUF
			free( [ecx].S_FILE.iob_base )
			xor	eax,eax
			mov	ecx,fp
			mov	[ecx].S_FILE.iob_ptr,eax
			mov	[ecx].S_FILE.iob_base,eax
			mov	[ecx].S_FILE.iob_flag,eax
			mov	[ecx].S_FILE.iob_bufsize,eax
			mov	[ecx].S_FILE.iob_cnt,eax
		.endif
	.endif
	ret
_freebuf ENDP

	END
