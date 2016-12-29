include stdio.inc

	.code

setbuf	PROC fp:LPFILE, buf:LPSTR
	setvbuf( buf, fp, _IOFBF, _MINIOBUF )
	ret
setbuf	ENDP

	END
