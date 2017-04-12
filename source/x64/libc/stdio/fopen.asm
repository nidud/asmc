include stdio.inc
include share.inc
include io.inc
include fcntl.inc
include errno.inc

extrn	_fmode:dword
extrn	_umaskval:dword

	.code

	option	switch:pascal, switch:notable, win64:0

fopen	PROC USES rsi rdi rbx, fname:LPSTR, mode:LPSTR

	mov	al,[rdx]
	.switch al
	  .case 'r':	mov esi,_IOREAD : mov edi,O_RDONLY
	  .case 'w':	mov esi,_IOWRT	: mov edi,O_WRONLY or O_CREAT or O_TRUNC
	  .case 'a':	mov esi,_IOWRT	: mov edi,O_WRONLY or O_CREAT or O_APPEND
	  .default
		xor	eax,eax
		mov	errno,EINVAL
		jmp	toend
	.endsw
	inc	rdx
	mov	al,[rdx]
	.while	al
		.switch al
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
		inc	rdx
		mov	al,[rdx]
	.endw
	mov	rbx,rcx
	.if	_getst()
		mov	rcx,rbx
		mov	rbx,rax
		.if	_sopen( rcx, edi, SH_DENYNO, 0284h ) != -1
			mov	[rbx]._iobuf._file,eax
			xor	eax,eax
			mov	[rbx]._iobuf._cnt,eax
			mov	[rbx]._iobuf._ptr,rax
			mov	[rbx]._iobuf._base,rax
			mov	[rbx]._iobuf._flag,esi
			or	rax,rbx
		.else
			xor	eax,eax
		.endif
	.endif
toend:
	ret
fopen	ENDP

	END
