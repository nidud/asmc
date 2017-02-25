include stdio.inc
include io.inc
include alloc.inc
include crtl.inc
IFDEF	_UNICODE
OFLUSH	equ <woutput_flush>
ELSE
OFLUSH	equ <output_flush>
ENDIF
extrn	_stdbuf:dword
extrn	OFLUSH:dword

	.code

_stbuf	PROC USES esi edi fp:LPFILE

	mov	esi,fp
	assume	esi:ptr _iobuf

	.repeat
		;
		; exit if not a tty device
		;
		.break .if !_isatty( [esi]._file )

		xor	eax,eax ; return 0
		xor	edi,edi ; _stdbuf index
		;
		; is stream stdout or stderr ?
		;
		.if esi != offset stdout

			.break .if esi != offset stderr
			inc	edi
		.endif
		;
		; already buffered ?
		;
		mov	ecx,[esi]._flag
		and	ecx,_IOMYBUF or _IONBF or _IOYOURBUF
		.breaknz

		or	ecx,_IOWRT or _IOYOURBUF or _IOFLRTN
		mov	[esi]._flag,ecx
		shl	edi,2
		add	edi,offset _stdbuf
		mov	eax,[edi]
		mov	ecx,_INTIOBUF

		.if	!eax

			mov	[edi],malloc(ecx)
			mov	ecx,_INTIOBUF

			.if	!eax

				lea eax,[esi]._charbuf
				mov ecx,4
			.endif
		.endif

		mov	[esi]._ptr,eax
		mov	[esi]._base,eax
		mov	[esi]._bufsiz,ecx
		mov	eax,1

	.until	1
	ret

_stbuf	ENDP

__STDIO:
	mov eax,_flsbuf
	mov OFLUSH,eax
	ret

pragma_init __STDIO, 2

	END
