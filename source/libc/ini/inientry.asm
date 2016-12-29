include ini.inc

	.code

inientry PROC USES esi edi ebx edx section:LPSTR, entry:LPSTR
	mov	eax,cinifile
	test	eax,eax
	jz	toend
	lea	edi,[eax+INIMAXVALUE+4]
	mov	ecx,[edi-4]
	test	ecx,ecx
	jz	fail
	cmp	byte ptr [edi],'['
	jne	@00
	inc	edi
	jmp	@01
@00:
	mov	al,'['
	repne	scasb
	jne	fail
	cmp	byte ptr [edi-2],0Ah
	jne	@00
@01:
	mov	edx,edi
	mov	ebx,section
	lea	esi,[ecx+1]
@02:
	mov	al,[edx]
	mov	ah,[ebx]
	inc	edx
	inc	ebx
	dec	esi
	jz	fail
	or	ax,2020h
	cmp	al,ah
	je	@02
	sub	al,ah
	cmp	al,']'
	jne	@00
@03:
	mov	al,0Ah
	repne	scasb
	jne	fail
	mov	al,[edi]
	cmp	al,'['
	je	fail
	cmp	al,';'
	je	@03
@@:
	mov	al,[edi]
	cmp	ecx,3	; l=3
	jb	fail
	inc	edi
	dec	ecx
	cmp	al,9
	je	@B
	cmp	al,' '
	je	@B
	dec	edi
	inc	ecx
	cmp	al,';'
	je	@03
	mov	esi,entry
@@:
	mov	al,[edi]
	mov	ah,[esi]
	inc	esi
	inc	edi
	dec	ecx
	jz	fail
	test	ah,ah
	jz	@F
	or	ax,2020h
	cmp	al,ah
	je	@B
	jmp	@03
@@:
	sub	edi,2
	add	ecx,2
@@:
	inc	edi
	dec	ecx
	jz	fail
	mov	al,[edi]
	cmp	al,' '
	je	@B
	cmp	al,9
	je	@B
	cmp	al,'='
	jne	@03
@@:
	inc	edi
	dec	ecx
	jz	fail
	mov	al,[edi]
	cmp	al,' '
	je	@B
	cmp	al,9
	je	@B
	cmp	al,';'
	je	fail
	mov	edx,cinifile
	sub	eax,eax
	cmp	ecx,255
	jb	@04
	mov	ecx,255
@04:
	mov	al,[edi]
	cmp	al,'"'
	jne	@F
	xor	ah,1
@@:
	cmp	al,';'
	jne	@F
	test	ah,ah
	jz	@05
@@:
	cmp	al,0Dh
	je	@05
	cmp	al,0Ah
	je	@05
	test	al,al
	jz	@05
	mov	[edx],al
	inc	edi
	inc	edx
	dec	ecx
	jnz	@04
@05:
	mov	eax,' '
	mov	[edx],ah
	mov	ecx,cinifile
@@:
	dec	edx
	cmp	edx,ecx
	jb	@F
	cmp	[edx],al
	ja	@F
	mov	[edx],ah
	jmp	@B
@@:
	cmp	[ecx],ah
	je	fail
	mov	eax,ecx
toend:
	ret
fail:
	xor	eax,eax
	jmp	toend
inientry ENDP

	END
