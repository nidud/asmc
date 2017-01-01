include stdio.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

feof	PROC stream:LPFILE
	mov	eax,[rcx].S_FILE.iob_flag
	and	rax,_IOEOF
	ret
feof	ENDP

	END
