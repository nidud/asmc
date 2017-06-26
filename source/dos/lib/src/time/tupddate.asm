; TUPDDATE.ASM--
; Copyright (C) 2015 Doszip Developers

include time.inc
include mouse.inc
include conio.inc

.data
_day db 33

.code

tupddate PROC _CType PUBLIC
	.if console & CON_UDATE
	    mov ax,2A00h
	    int 21h
	    .if dl != _day
		mov _day,dl
		HideMouseCursor
		mov ax,_scrseg
		mov es,ax
		sub bx,bx
		mov bl,_scrcol
		sub bl,14
		.if console & CON_LTIME
		    sub bl,3
		.endif
		sub cx,2000
		.if console & CON_LDATE
		    sub bl,2
		    add bx,bx
		    mov BYTE PTR es:[bx],'2'
		    mov BYTE PTR es:[bx+2],'0'
		    add bx,4
		    mov al,cl
		    call wcputnum
		    add bx,6
		    mov BYTE PTR es:[bx-2],'-'
		    mov al,dh
		    call wcputnum
		    add bx,6
		    mov BYTE PTR es:[bx-2],'-'
		    mov al,dl
		    call wcputnum
		.else
		    add bx,bx
		    mov al,dl
		    call wcputnum
		    mov al,'.'
		    mov es:[bx+4],al
		    mov es:[bx+10],al
		    .if ah == '0'
			mov BYTE PTR es:[bx],' '
		    .endif
		    add bx,6
		    mov al,dh
		    call wcputnum
		    add bx,6
		    mov al,cl
		    call wcputnum
		.endif
		ShowMouseCursor
	    .endif
	.endif
	ret
tupddate ENDP

	END
