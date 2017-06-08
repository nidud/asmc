include consx.inc

	.code

getkey	PROC
	ReadEvent()
	PopEvent()
	ret
getkey	ENDP

	END
