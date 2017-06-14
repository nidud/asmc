include stdio.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

setbuf	PROC fp:LPFILE, buf:LPSTR
	xchg	rcx,rdx
	setvbuf( rcx, rdx, _IOFBF, _MINIOBUF )
	ret
setbuf	ENDP

	END
