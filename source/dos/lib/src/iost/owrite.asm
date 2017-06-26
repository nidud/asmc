; OWRITE.ASM--
; Copyright (C) 2015 Doszip Developers

include iost.inc

	.code

owrite	PROC PUBLIC
	push si
	push di
	mov di,es
	mov si,bx
	mov dx,STDO.ios_i
	mov ax,STDO.ios_size
	sub ax,dx
	.if ax < cx
	    .repeat
		mov al,es:[si]
		call oputc
		mov es,di
		.break .if ZERO?
		inc si
	    .untilcxz
	    test ax,ax
	.else
	    add STDO.ios_i,cx
	    mov ax,WORD PTR STDO.ios_bp+2
	    add dx,WORD PTR STDO.ios_bp
	    push ds
	    mov ds,di
	    xchg di,dx
	    mov es,ax
	    cld?
	    rep movsb
	    mov es,dx
	    pop ds
	.endif
	mov bx,si
	pop di
	pop si
	ret
owrite	ENDP

	END
