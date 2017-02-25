include stdio.inc
include io.inc

	.code

	ASSUME	esi: LPFILE

_filwbuf PROC USES esi edi fp:LPFILE

	mov esi,fp
	mov edi,[esi]._flag

	.repeat
		or	eax,-1
		.switch
		  .case !( edi & _IOREAD or _IOWRT or _IORW )
		  .case edi & _IOSTRG
			.break
		  .case edi & _IOWRT
			or [esi]._flag,_IOERR
			.break
		.endsw

		or  edi,_IOREAD
		mov [esi]._flag,edi

		.if !( edi & _IOMYBUF or _IONBF or _IOYOURBUF )

			_getbuf( fp )
			mov edi,[esi]._flag
		.else
			mov eax,[esi]._base
			mov [esi]._ptr,eax
		.endif

		mov [esi]._cnt,_read([esi]._file, [esi]._base, [esi]._bufsiz)

		.ifs eax < 2

			.if eax
				mov eax,_IOERR
			.else
				mov eax,_IOEOF
			.endif

			or  [esi]._flag,eax
			xor eax,eax
			mov [esi]._cnt,eax
			dec eax
			.break
		.endif

		.if !( edi & _IOWRT or _IORW )

			lea eax,_osfile
			add eax,[esi]._file
			mov al,[eax]
			and al,FH_TEXT or FH_EOF
			.if al == FH_TEXT or FH_EOF

				or [esi]._flag,_IOCTRLZ
			.endif
		.endif

		mov eax,[esi]._bufsiz
		.if eax == _MINIOBUF && edi & _IOMYBUF && !( edi & _IOSETVBUF )

			mov [esi]._bufsiz,_INTIOBUF
		.endif

		sub [esi]._cnt,2
		add [esi]._ptr,2
		mov esi,[esi]._ptr
		movzx eax,word ptr [esi-2]
	.until	1
	ret

_filwbuf ENDP

	END
