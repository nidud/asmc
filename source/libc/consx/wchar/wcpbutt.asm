include consx.inc

	.code

wcpbutt PROC USES esi edi ebx wp:PVOID, l, x, string:LPSTR
	mov	ecx,x
	mov	ah,at_background[B_PushButt]
	or	ah,at_foreground[F_Title]
	mov	al,' '
	mov	edi,wp
	mov	ebx,edi
	mov	edx,edi
	rep	stosw
	mov	eax,[edi]
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
	mov	esi,string
	mov	edi,ebx
	add	edi,4
lup:
	lodsb
	or	al,al
	jz	toend
	cmp	al,'&'
	jz	@F
	stosb
	inc	edi
	jmp	lup
@@:
	lodsb
	or	al,al
	jz	toend
	stosw
	jmp	lup
toend:
	mov	eax,wp
	ret
wcpbutt ENDP

	END
