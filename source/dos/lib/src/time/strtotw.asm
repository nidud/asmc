; STRTOTW.ASM--
; Copyright (C) 2015 Doszip Developers

include time.inc
include stdlib.inc

.code

strtotw PROC _CType PUBLIC USES bx si di string:DWORD
	sub ax,ax
	les bx,string
	.repeat
	    mov al,es:[bx]
	    inc bx
	.until al > '9' || al < '0'
	.if al
	    mov ax,WORD PTR string+2
	    push ax
	    push bx
	    push ax
	    push WORD PTR string
	    mov WORD PTR string,bx
	    call atol
	    mov si,ax
	    call atol
	    mov di,ax
	    les bx,string
	    sub ax,ax
	    .repeat
		mov al,es:[bx]
		inc bx
	    .until al > '9' || al < '0'
	    .if al
		push WORD PTR string+2
		    push bx
		call atol
		shr ax,1
		shl di,5
		shl si,11
		or ax,si
		or ax,di
	    .endif
	.endif
	ret
strtotw ENDP

	END
