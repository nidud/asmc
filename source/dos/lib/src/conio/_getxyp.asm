; _GETXYP.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include mouse.inc

.code

__getxypm PROC PUBLIC
	HideMouseCursor
__getxypm ENDP

__getxyp PROC PUBLIC	; x,y (AL,AH) to DX:AX
	mov	dl,al
	mov	al,_scrcol
	mul	ah
	add	ax,ax
	xor	dh,dh
	add	ax,dx
	add	ax,dx
	mov	dx,_scrseg
	ret
__getxyp ENDP

	END
