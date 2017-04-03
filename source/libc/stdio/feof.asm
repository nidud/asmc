include stdio.inc

	.code

feof	PROC stream:LPFILE
	mov eax,stream
	mov eax,[eax]._iobuf._flag
	and eax,_IOEOF
	ret
feof	ENDP

	END
