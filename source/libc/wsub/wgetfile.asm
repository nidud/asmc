include string.inc
include io.inc
include iost.inc
include consx.inc
include stdlib.inc
include direct.inc
include wsub.inc

	.code

wgetfile PROC path:LPSTR, fmask:LPSTR, flag

	.if	flag & _WLOCAL

		_getcwd( path, _MAX_PATH )

	.else
		mov	eax,fmask
		add	eax,2

		.if	filexist( strfcat( path, _pgmpath, eax ) ) != 2

			strpath( path )
		.endif
	.endif

	.if	wdlgopen( path, fmask, flag )

		strcpy( path, eax )

		.if	flag & _WSAVE

			ogetouth( eax, M_WRONLY )
		.else
			openfile( eax, M_RDONLY, A_OPEN )
		.endif

		.if	eax == -1

			xor eax,eax
		.endif
	.endif
	ret

wgetfile ENDP

	END
