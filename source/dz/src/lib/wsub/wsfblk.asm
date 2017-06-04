include wsub.inc

	.code

wsfblk	PROC wsub:PTR S_WSUB, index
	mov	eax,index
	mov	edx,wsub
	cmp	[edx].S_WSUB.ws_count,eax
	jle	error
	shl	eax,2
	add	eax,[edx].S_WSUB.ws_fcb		; EDX wsub
	mov	eax,[eax]			; EAX fblk
	mov	ecx,[eax].S_FBLK.fb_flag	; ECX fblk.flag
toend:
	ret
error:
	xor	eax,eax
	jmp	toend
wsfblk	ENDP

	END
