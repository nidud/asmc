include stdio.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

feof	PROC stream:LPFILE
	mov	eax,[rcx]._iobuf._flag
	and	rax,_IOEOF
	ret
feof	ENDP

	END
