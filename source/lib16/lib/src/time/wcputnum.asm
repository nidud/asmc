; WCPUTNUM.ASM--
; Copyright (C) 2015 Doszip Developers

include libc.inc

PUBLIC	wcputnum	; Output Number to WORD *

.code

wcputnum PROC
	aam		; AH := AL / 10
	add ax,3030h	; AL := AL mod 10
	mov es:[bx],ah	; AX := AX + '00'
	mov es:[bx+2],al
	ret
wcputnum ENDP

	END