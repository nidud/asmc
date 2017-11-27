include string.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

_strnicmp PROC s1:LPSTR, s2:LPSTR, count:SIZE_T

	mov	r9,rdx
	mov	al,-1
@@:
	test	al,al
	jz	@F
	xor	rax,rax
	test	r8,r8
	jz	toend
	mov	al,[r9]
	cmp	al,[rcx]
	lea	r9,[r9+1]
	lea	rcx,[rcx+1]
	lea	r8,[r8-1]
	je	@B
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
	je	@B

	sbb	al,al
	sbb	al,-1
@@:
	movsx	rax,al
toend:
	ret
_strnicmp ENDP

	END
