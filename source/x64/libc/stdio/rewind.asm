include io.inc
include stdio.inc

	.code

	OPTION	WIN64:3, STACKBASE:rsp

rewind	PROC fp:LPFILE
	fflush( rcx )
	mov	rcx,fp
	mov	eax,[rcx].S_FILE.iob_flag
	and	eax,not (_IOERR or _IOEOF)
	.if	eax & _IORW
		and eax,not (_IOREAD or _IOWRT)
	.endif
	mov	[rcx].S_FILE.iob_flag,eax
	mov	eax,[rcx].S_FILE.iob_file
	lea	rcx,_osfile
	and	BYTE PTR [rcx+rax],not FH_EOF
	lea	rcx,_osfhnd
	mov	rcx,[rcx+rax*8]
	SetFilePointer( rcx, 0, 0, SEEK_SET )
	ret
rewind	ENDP

	END
