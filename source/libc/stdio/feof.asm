include stdio.inc

	.code

feof	PROC stream:LPFILE
	mov	eax,stream
	mov	eax,[eax].S_FILE.iob_flag
	and	eax,_IOEOF
	ret
feof	ENDP

	END
