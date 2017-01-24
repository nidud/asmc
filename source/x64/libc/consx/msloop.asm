include consx.inc

	.code

	OPTION	WIN64:0, STACKBASE:rsp

msloop	PROC
	.repeat
		mousep()
	.until	ZERO?
	ret
msloop	ENDP

	END
