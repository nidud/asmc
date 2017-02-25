; FOPEN.ASM--
; FILE *fopen(file, mode) - open a file
;
; mode:
;  r  : read
;  w  : write
;  a  : append
;  r+ : read/write
;  w+ : open empty for read/write
;  a+ : read/append
;
; Append "t" or "b" for text and binary mode
;
; Change history:
; 2017-02-16 - _UNICODE
;
include stdio.inc
include share.inc
include io.inc
include fcntl.inc
include errno.inc
IFDEF	_UNICODE
FOPEN	equ <_wfopen>
SOPEN	equ <_wsopen>
ELSE
FOPEN	equ <fopen>
SOPEN	equ <_sopen>
ENDIF
MGETCHAR MACRO
IFDEF	_UNICODE
	movzx	eax,WORD PTR [ebx]
	add	ebx,2
ELSE
	movzx	eax,BYTE PTR [ebx]
	add	ebx,1
ENDIF
	EXITM<eax>
	ENDM

extrn	_fmode:dword
extrn	_umaskval:dword

	.code

	option	switch:pascal

FOPEN	PROC USES esi edi ebx file:LPTSTR, mode:LPTSTR

	mov	ebx,mode

	.repeat

		.switch MGETCHAR()

		  .case 'r':	mov esi,_IOREAD : mov edi,O_RDONLY
		  .case 'w':	mov esi,_IOWRT	: mov edi,O_WRONLY or O_CREAT or O_TRUNC
		  .case 'a':	mov esi,_IOWRT	: mov edi,O_WRONLY or O_CREAT or O_APPEND
		  .default
			xor	eax,eax
			mov	errno,EINVAL
			.break
		.endsw

		.while	MGETCHAR()

			.switch eax
			  .case '+'
				or	edi,O_RDWR
				and	edi,not (O_RDONLY or O_WRONLY)
				or	esi,_IORW
				and	esi,not (_IOREAD or _IOWRT)

			  .case 't': or	 edi,O_TEXT
			  .case 'b': or	 edi,O_BINARY
			  .case 'c': or	 esi,_IOCOMMIT
			  .case 'n': and esi,not _IOCOMMIT
			  .case 'S': or	 edi,O_SEQUENTIAL
			  .case 'R': or	 edi,O_RANDOM
			  .case 'T': or	 edi,O_SHORT_LIVED
			  .case 'D': or	 edi,O_TEMPORARY
			  .default
				.break
			.endsw
		.endw

		mov	ebx,_getst()
		.break .if !eax

		.if	SOPEN( file, edi, SH_DENYNO, 0284h ) != -1

			mov	[ebx]._iobuf._file,eax
			xor	eax,eax
			mov	[ebx]._iobuf._cnt,eax
			mov	[ebx]._iobuf._ptr,eax
			mov	[ebx]._iobuf._base,eax
			mov	[ebx]._iobuf._flag,esi
			or	eax,ebx
		.else
			xor	eax,eax
		.endif
	.until	1
	ret
FOPEN	ENDP

	END
