include consx.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

__wputs PROC		; EDI word buffer
	push	rsi	; ESI string
	push	rdi	; CL max byte output
	push	rbx	; CH attrib for &Text if set
	mov	rbx,rdi ; AH attrib or 0
	test	cl,cl	; EDX length of line (word count)
	jnz	putstr_loop
	dec	cl
	jmp	putstr_loop
    putstr_tab:
	add	rdi,8
	jmp	putstr_loop
    putstr_line:
	add	rbx,rdx
	mov	rdi,rbx
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
	inc	rdi
    putstr_next:
	dec	cl
	jnz	putstr_loop
    putstr_end:
	mov	rax,rsi
	pop	rbx
	pop	rdi
	pop	rsi
	sub	rax,rsi
	ret
    putstr_color:
	test	ch,ch
	jz	putstr_noat
	mov	[rdi+1],ch
	jmp	putstr_loop
__wputs ENDP

	END
