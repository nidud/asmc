; TUPDTIME.ASM--
; Copyright (C) 2015 Doszip Developers

include time.inc
include mouse.inc
include conio.inc

.data
_sec db 61

.code

tupdtime PROC _CType PUBLIC
	.if console & CON_UTIME
	    mov ax,2C00h
	    int 21h
	    .if dh != _sec
		mov _sec,dh
		HideMouseCursor
		mov ax,_scrseg
		mov es,ax
		sub bx,bx
		mov bl,_scrcol
		sub bl,5
		.if console & CON_LTIME
		    sub bl,3
		.endif
		add bx,bx
		mov al,ch
		call wcputnum
		mov al,':'
		mov es:[bx+4],al
		.if console & CON_LTIME
		    mov es:[bx+10],al
		.endif
		.if ah == '0'
		    mov BYTE PTR es:[bx],' '
		.endif
		add bx,6
		mov al,cl
		call wcputnum
		.if console & CON_LTIME
		    add bx,6
		    mov al,dh
		    call wcputnum
		.endif
		ShowMouseCursor
	    .endif
	.endif
	ret
tupdtime ENDP

	END
