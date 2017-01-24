include string.inc

strstri PROTO :LPSTR, :LPSTR
strmove PROTO :LPSTR, :LPSTR

	.code

strxchg PROC USES esi edi ebx dst:LPSTR, old:LPSTR, new:LPSTR
	mov	edi,dst
	strlen( new )
	mov	esi,eax
	strlen( old )
	mov	ebx,eax
	.while	strstri( edi, old )	; find token
		mov	edi,eax		; EDI to start of token
		lea	ecx,[eax+esi]
		add	eax,ebx
		strmove( ecx, eax )	; move($ + len(new), $ + len(old))
		memmove( edi, new, esi ); copy($, new, len(new))
		inc	edi		; $++
	.endw
	mov	eax,dst
	ret
strxchg ENDP

	END
