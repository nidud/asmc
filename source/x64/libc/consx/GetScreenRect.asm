include consx.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

GetScreenRect PROC
	mov	eax,_scrcol
	mov	ah,BYTE PTR _scrrow
	shl	eax,16
	ret
GetScreenRect ENDP

	END
