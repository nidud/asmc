include consx.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

getkey	PROC
	call	ReadEvevnt
	call	PopEvent
	ret
getkey	ENDP

	END
