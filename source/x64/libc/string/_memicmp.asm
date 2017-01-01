include string.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

_memicmp PROC s1:LPSTR, s2:LPSTR, l:SIZE_T
	mov	r9,rdx
@@:
	test	r8,r8
	jz	@F
	sub	r8,1
	mov	al,[rcx]
	cmp	al,[r9]
	lea	rcx,[rcx+1]
	lea	r9,[r9+1]
	je	@B
	mov	dl,[r9-1]
	mov	ah,dl
	sub	ax,'AA'
	cmp	al,'Z'-'A' + 1
	sbb	dl,dl
	and	dl,'a'-'A'
	cmp	ah,'Z'-'A' + 1
	sbb	dh,dh
	and	dh,'a'-'A'
	add	ax,dx
	add	ax,'AA'
	cmp	al,ah
	je	@B
	sbb	r8,r8
	sbb	r8,-1
@@:
	mov	rax,r8
	ret
_memicmp ENDP

	END
