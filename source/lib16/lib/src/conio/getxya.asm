; GETXYA.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

.code

getxya	PROC _CType PUBLIC x:size_t, y:size_t
	invoke getxyw,x,y
	mov al,ah
	mov ah,0
	ret
getxya	ENDP

	END
