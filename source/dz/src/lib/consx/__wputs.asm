include consx.inc

	.code

__wputs PROC		; EDI word buffer
	push	esi	; ESI string
	push	edi	; CL max byte output
	push	ebx	; CH attrib for &Text if set
	mov	ebx,edi ; AH attrib or 0
	test	cl,cl	; EDX length of line (word count)
	jnz	putstr_loop
	dec	cl
	jmp	putstr_loop
    putstr_tab:
	add	edi,8
	jmp	putstr_loop
    putstr_line:
	add	ebx,edx
	mov	edi,ebx
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
	inc	edi
    putstr_next:
	dec	cl
	jnz	putstr_loop
    putstr_end:
	mov	eax,esi
	pop	ebx
	pop	edi
	pop	esi
	sub	eax,esi
	ret
    putstr_color:
	test	ch,ch
	jz	putstr_noat
	mov	[edi+1],ch
	jmp	putstr_loop
__wputs ENDP

	END
