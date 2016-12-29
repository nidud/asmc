include consx.inc

	.data

frametypes label BYTE
	db 'ÚÄ¿³ÀÙ'
	db 'ÉÍ»ºÈ¼'
	db 'ÂÄÂ³ÁÁ'
	db 'ÃÄ´³Ã´'

	.code

rcframe PROC USES esi edi ebx ecx edx rc, wstr:PVOID, lsize, ftype
local	tmp[16]:BYTE
	mov	eax,ftype		; AL = Type [0,6,12,18]
	and	eax,00FFh		; AH = Attrib
	add	eax,offset frametypes
	mov	esi,eax		;------------------------
	lodsw			; [BP-2] UL 'Ú'
	mov	[ebp-2],ax	; [BP-1] HL 'Ä'
	lodsw			; [BP-4] UR '¿'
	mov	[ebp-4],ax	; [BP-3] VL '³'
	lodsw			; [BP-6] LL 'À'
	mov	[ebp-6],ax	; [BP-5] LR 'Ù'
	mov	eax,lsize	;------------------------
	mov	ecx,eax		; line size - 80 on screen
	add	eax,eax
	movzx	edx,rc.S_RECT.rc_y
	mul	edx
	movzx	edx,rc.S_RECT.rc_x
	add	eax,edx
	add	eax,edx
	mov	edi,wstr
	add	edi,eax
	movzx	eax,rc.S_RECT.rc_col
	sub	al,2
	mov	ch,al
	add	eax,eax
	mov	[ebp-10],eax
	mov	eax,ftype
	mov	dl,rc.S_RECT.rc_row
	mov	esi,edx
	mov	dl,cl
	add	edx,edx
	mov	ebx,edi
	mov	cl,1
	mov	al,[ebp-2]	; Upper Left 'Ú'
	call	rcstosw
	mov	al,[ebp-1]	; Horizontal Line 'Ä'
	mov	cl,ch
	call	rcstosw
	inc	cl
	mov	al,[ebp-4]	; Upper Right '¿'
	call	rcstosw
	.if	esi > 1
		.if	esi != 2
			sub	esi,2
			.repeat
				add	ebx,edx
				mov	edi,ebx
				inc	cl
				mov	al,[ebp-3] ; Vertical Line '³'
				call	rcstosw
				add	edi,[ebp-10]
				inc	cl
				call	rcstosw
				dec	esi
			.until !esi
		.endif
		add	ebx,edx
		mov	edi,ebx
		mov	cl,1
		mov	al,[ebp-6] ; Lower Left 'À'
		call	rcstosw
		mov	al,[ebp-1] ; Horizontal Line 'Ä'
		mov	cl,ch
		call	rcstosw
		inc	cl
		mov	al,[ebp-5] ; Lower Right 'Ù'
		call	rcstosw
	.endif
	ret
rcstosw:
	.if	ah
		stosw
	.else
		stosb
		inc edi
	.endif
	dec	cl
	jnz	rcstosw
	retn
rcframe ENDP

	END
