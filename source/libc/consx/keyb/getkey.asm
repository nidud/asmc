include consx.inc

	.code

getkey	PROC
	ReadEvevnt()
	PopEvent()
	ret
getkey	ENDP

	END
