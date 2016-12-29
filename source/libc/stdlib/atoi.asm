include stdlib.inc

	.code

atoi	PROC string:LPSTR
	atol( string )
	ret
atoi	ENDP

	END
