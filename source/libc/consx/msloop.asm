include consx.inc

	.code

msloop	PROC
	.repeat
		mousep()
	.until	ZERO?
	ret
msloop	ENDP

	END
