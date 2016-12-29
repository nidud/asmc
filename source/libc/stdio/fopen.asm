include stdio.inc
include share.inc
include io.inc
include fcntl.inc
include errno.inc

extrn	_fmode:dword
extrn	_umaskval:dword

	.code

	option	switch:pascal, switch:notable

fopen	PROC USES esi edi ebx, fname:LPSTR, mode:LPSTR

	mov	ebx,mode
	movzx	eax,BYTE PTR [ebx]
	.switch eax
	  .case 'r':	mov esi,_IOREAD : mov edi,O_RDONLY
	  .case 'w':	mov esi,_IOWRT	: mov edi,O_WRONLY or O_CREAT or O_TRUNC
	  .case 'a':	mov esi,_IOWRT	: mov edi,O_WRONLY or O_CREAT or O_APPEND
	  .default
		xor	eax,eax
		mov	errno,EINVAL
		jmp	toend
	.endsw
	inc	ebx
	mov	al,[ebx]
	.while	eax
		.switch eax
		  .case '+'
			or	edi,O_RDWR
			and	edi,not (O_RDONLY or O_WRONLY)
			or	esi,_IORW
			and	esi,not (_IOREAD or _IOWRT)
		  .case 't':	or  edi,O_TEXT
		  .case 'b':	or  edi,O_BINARY
		  .case 'c':	or  esi,_IOCOMMIT
		  .case 'n':	and esi,not _IOCOMMIT
		  .case 'S':	or  edi,O_SEQUENTIAL
		  .case 'R':	or  edi,O_RANDOM
		  .case 'T':	or  edi,O_SHORT_LIVED
		  .case 'D':	or  edi,O_TEMPORARY
		  .default
			.break
		.endsw
		inc	ebx
		mov	al,[ebx]
	.endw
	.if	_getst()
		mov	ebx,eax
		.if	_sopen( fname, edi, SH_DENYNO, 0284h ) != -1
			mov	[ebx].S_FILE.iob_file,eax
			xor	eax,eax
			mov	[ebx].S_FILE.iob_cnt,eax
			mov	[ebx].S_FILE.iob_ptr,eax
			mov	[ebx].S_FILE.iob_base,eax
			mov	[ebx].S_FILE.iob_flag,esi
			or	eax,ebx
		.else
			xor	eax,eax
		.endif
	.endif
toend:
	ret
fopen	ENDP

	END
