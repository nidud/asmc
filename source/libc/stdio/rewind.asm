include io.inc
include stdio.inc

	.code

rewind	PROC fp:LPFILE
	fflush( fp )
	mov	ecx,fp
	mov	eax,[ecx].S_FILE.iob_flag
	and	eax,not (_IOERR or _IOEOF)
	.if	eax & _IORW
		and eax,not (_IOREAD or _IOWRT)
	.endif
	mov	[ecx].S_FILE.iob_flag,eax
	mov	eax,[ecx].S_FILE.iob_file
	and	_osfile[eax],not FH_EOF
	mov	eax,_osfhnd[eax*4]
	SetFilePointer( eax, 0, 0, SEEK_SET )
	ret
rewind	ENDP

	END
