include consx.inc
include string.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

wcstrcpy PROC USES rsi rdi rbx cp:LPSTR, wc:PVOID, count
	mov	r8,rcx
	mov	rdi,rcx;cp
	mov	rsi,rdx;wc
	mov	ecx,r8d;count
	mov	bl,[rsi+1]
	and	bl,0Fh
@@:
	test	ecx,ecx
	jz	toend
	dec	ecx
	lodsw
	cmp	al,' '
	jbe	@B
	cmp	al,176
	ja	@B
	sub	rsi,2
	test	ecx,ecx
	jz	toend
lup:
	lodsw
	cmp	al,176
	ja	toend
	and	ah,0Fh
	cmp	ah,bl;13
	je	@F
	mov	ah,al
	mov	al,'&'
	stosb
	mov	al,ah
@@:
	stosb
	dec	ecx
	jnz	lup
toend:
	mov	BYTE PTR [rdi],0
	strtrim( r8 )
	ret
wcstrcpy ENDP

	END
