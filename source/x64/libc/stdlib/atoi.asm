include stdlib.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

atoi	PROC string:LPSTR
	atol( rcx )
	ret
atoi	ENDP

	END
