; _WFOPEN.ASM--
; FILE *_wfopen(file, mode) - open a file
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

extrn	_fmode:dword
extrn	_umaskval:dword

	.code

	option	switch:pascal

_wfopen PROC USES esi edi ebx file:LPWSTR, mode:LPWSTR

	mov ebx,mode

	.repeat

		movzx eax,WORD PTR [ebx]
		add ebx,2
		.switch eax

		  .case 'r': mov esi,_IOREAD : mov edi,O_RDONLY
		  .case 'w': mov esi,_IOWRT  : mov edi,O_WRONLY or O_CREAT or O_TRUNC
		  .case 'a': mov esi,_IOWRT  : mov edi,O_WRONLY or O_CREAT or O_APPEND
		  .default
			xor eax,eax
			mov errno,EINVAL
			.break
		.endsw

		mov ax,[ebx]
		.while eax

			.switch eax
			  .case '+'
				or  edi,O_RDWR
				and edi,not (O_RDONLY or O_WRONLY)
				or  esi,_IORW
				and esi,not (_IOREAD or _IOWRT)

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

			add ebx,2
			mov ax,[ebx]
		.endw

		mov ebx,_getst()
		.break .if !eax

		.if _wsopen(file, edi, SH_DENYNO, 0284h) != -1

			mov [ebx]._iobuf._file,eax
			xor eax,eax
			mov [ebx]._iobuf._cnt,eax
			mov [ebx]._iobuf._ptr,eax
			mov [ebx]._iobuf._base,eax
			mov [ebx]._iobuf._flag,esi
			or  eax,ebx
		.else
			xor eax,eax
		.endif
	.until	1
	ret
_wfopen ENDP

	END
