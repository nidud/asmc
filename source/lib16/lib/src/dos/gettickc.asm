; GETTICKC.ASM--
; Copyright (C) 2015 Doszip Developers

include dos.inc

	.code

GetTickCount PROC _CType PUBLIC
	mov ax,0040h
	mov es,ax
	mov ax,es:[006Ch]	; TIMER TICKS SINCE MIDNIGHT
	mov dx,es:[006Eh]
	ret
GetTickCount ENDP

	END

