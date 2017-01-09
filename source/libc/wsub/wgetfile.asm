include string.inc
include io.inc
include iost.inc
include consx.inc
include stdlib.inc
include wsub.inc

externdef IDD_DirectoryNotFound:dword

	.code

MakeDirectory PROC USES esi directory:LPSTR

	.if	filexist( directory ) != 2

		.if	rsopen( IDD_DirectoryNotFound )

			mov	esi,eax
			dlshow( eax )
			mov	ax,[esi+4]
			add	ax,0204h
			mov	dl,ah
			scpath( eax, edx, 22, directory )
			.if	dlmodal( esi )
				wsmkdir( directory )
				inc	eax
			.endif
		.endif
	.endif
	ret
MakeDirectory ENDP

	ALIGN	4

wgetfile PROC path:LPSTR, fmask:LPSTR, flag

	mov	eax,fmask
	add	eax,2

	.if	MakeDirectory( strfcat( path, _pgmpath, eax ) )

		.if	wdlgopen( path, fmask, flag )

			strcpy( path, eax )

			.if	flag == 2
				ogetouth( eax, M_WRONLY )
			.else
				openfile( eax, M_RDONLY, A_OPEN )
			.endif
			.if	eax == -1
				xor eax,eax
			.endif
		.endif
	.endif

	ret
wgetfile ENDP

	END
