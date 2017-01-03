; RCSPRC.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

.code

rcsprc	PROC _CType PUBLIC rc:DWORD
	mov	al,_scrcol
	mul	rc.S_RECT.rc_y
	add	ax,ax
	xor	dx,dx
	mov	dl,rc.S_RECT.rc_x
	add	ax,dx
	add	ax,dx
	mov	dx,_scrseg
	ret
rcsprc	ENDP

	END
