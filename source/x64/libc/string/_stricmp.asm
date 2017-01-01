include string.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

_stricmp PROC dst:LPSTR, src:LPSTR
	mov	r10,rdx
	mov	rax,-1
	ALIGN	16
lupe:
	test	al,al
	jz	toend

	mov	al,[r10]
	cmp	al,[rcx]
	lea	r10,[r10+1]
	lea	rcx,[rcx+1]
	je	lupe

	mov	ah,[rcx-1]
	sub	ax,'AA'
	cmp	al,'Z'-'A'+1
	sbb	dl,dl
	and	dl,'a'-'A'
	cmp	ah,'Z'-'A'+1
	sbb	dh,dh
	and	dh,'a'-'A'
	add	ax,dx
	add	ax,'AA'
	cmp	ah,al
	je	lupe
	sbb	al,al
	sbb	al,-1
toend:
	movsx	rax,al
	ret
_stricmp ENDP

	END
