; _WPUTS.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

__wputs PROC PUBLIC	; ES:DI word buffer (or screen)
	push	si	; DS:SI string
	push	di	; CL max byte output
	cld?		; CH attrib for &Text if set
	test	cl,cl	; DX length of line (word count)
	jnz	putstr_loop
	dec	cl	; AH attrib or 0
	jmp	putstr_loop
    putstr_tab:
	add	di,16
	and	di,not 15
	jmp	putstr_loop
    putstr_line:
	pop	di
	add	di,dx
	push	di
    putstr_loop:
	lodsb
	test	al,al
	jz	putstr_end
	cmp	al,10
	je	putstr_line
	cmp	al,9
	je	putstr_tab
	cmp	al,'&'
	je	putstr_color
	test	ah,ah
	jz	putstr_noat
	stosw
	jmp	putstr_next
    putstr_noat:
	stosb
	inc	di
    putstr_next:
	dec	cl
	jnz	putstr_loop
    putstr_end:
	mov	ax,si
	pop	di
	pop	si
	sub	ax,si
	ret
    putstr_color:
	test	ch,ch
	jz	putstr_noat
	mov	es:[di][1],ch
	jmp	putstr_loop
__wputs ENDP

	END
