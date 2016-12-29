include consx.inc

	.code

GetScreenRect PROC

	mov eax,_scrcol
	mov ah,BYTE PTR _scrrow
	shl eax,16
	ret

GetScreenRect ENDP

	END
