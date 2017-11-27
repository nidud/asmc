; RESETPAL.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

resetpal PROC _CType PUBLIC
	push si
	xor si,si
	.repeat
	    invoke setpal,si,si
	    inc si
	.until si == 8
	mov si,56
	.repeat
	    mov ax,si
	    add ax,-48
	    invoke setpal,si,ax
	    inc si
	.until si == 64
	invoke setpal,0014h,0006h
	pop si
	ret
resetpal ENDP

	END
