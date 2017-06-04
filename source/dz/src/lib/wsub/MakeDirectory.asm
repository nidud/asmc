include io.inc
include consx.inc
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

	END
