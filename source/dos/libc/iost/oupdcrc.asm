; OUPDCRC.ASM--
; Copyright (C) 2015 Doszip Developers

include iost.inc

	.code

oupdcrc PROC PUBLIC
	push	ax
	push	di
	les	bx,[si]
	add	bx,dx		; update from read offset
ifdef __3__
	mov cx,ax		; size to update
	mov edx,[si].S_IOST.ios_bb ; current CRC value
	.while cx
	    movzx ax,dl
	    xor al,es:[bx]
	    shl ax,2
	    mov di,ax
	    shr edx,8
	    xor edx,[di+crctab]
	    inc bx
	    dec cx
	.endw
	mov [si].S_IOST.ios_bb,edx
else
	push si
	mov dx,WORD PTR [si].S_IOST.ios_bb
	mov cx,WORD PTR [si].S_IOST.ios_bb+2
	mov si,ax
	.while si
	    mov ah,0
	    mov al,dl
	    xor al,es:[bx]
	    shl ax,2
	    mov di,ax
	    mov dl,dh
	    mov dh,cl
	    mov cl,ch
	    mov ch,0
	    xor dx,WORD PTR [di+crctab]
	    xor cx,WORD PTR [di+crctab+2]
	    inc bx
	    dec si
	.endw
	pop si
	mov WORD PTR [si].S_IOST.ios_bb,dx
	mov WORD PTR [si].S_IOST.ios_bb+2,cx
endif
	pop di
	pop ax
	ret
oupdcrc ENDP

	END
