include consx.inc

	.code

wcpbutt PROC USES rsi rdi rbx wp:PVOID, l, x, string:LPSTR
	mov	rdi,rcx
	mov	ecx,x
	mov	ah,at_background[B_PushButt]
	or	ah,at_foreground[F_Title]
	mov	al,' '
	mov	rbx,rdi
	mov	rdx,rdi
	rep	stosw
	mov	eax,[rdi]
	mov	al,'Ü'
	and	ah,11110000B
	or	ah,at_foreground[F_PBShade]
	stosw
	add	edx,l
	add	edx,l
	add	edx,2
	mov	edi,edx
	mov	ecx,x
	mov	al,'ß'
	rep	stosw
	mov	ah,at_background[B_PushButt]
	or	ah,at_foreground[F_TitleKey]
	mov	rsi,string
	mov	rdi,rbx
	add	rdi,4
lup:
	lodsb
	or	al,al
	jz	toend
	cmp	al,'&'
	jz	@F
	stosb
	inc	rdi
	jmp	lup
@@:
	lodsb
	or	al,al
	jz	toend
	stosw
	jmp	lup
toend:
	mov	rax,wp
	ret
wcpbutt ENDP

	END
