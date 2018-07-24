include crtl.inc

    .code

    OPTION PROLOGUE:NONE, EPILOGUE:NONE
	;
	; double[eax] to long double[edx]
	;
_iFDLD	proc
	mov	r10,rdx
	mov	edx,[rax+4]
	mov	eax,[rax]
	mov	r8d,edx
	shld	edx,eax,11
	shl	eax,11
	sar	r8d,20
	and	r8w,07FFh
	jz	L004
	cmp	r8w,07FFh
	je	@F
	add	r8w,3C00h
	jmp	L003
@@:
	or	r8d,00007F00h
	test	edx,7FFFFFFFh
	jnz	@F
	test	eax,eax
	jz	L003
@@:
;	int	3	  ; Invalid exception
	or	edx,40000000h
L003:
	or	edx,80000000h
	jmp	toend
L004:
	test	edx,edx
	jnz	@F
	test	eax,eax
	jz	toend
@@:
	or	r8d,00003C01h
	test	edx,edx
	jnz	@F
	xchg	edx,eax
	sub	r8d,32
@@:
	test	edx,edx
	js	toend
	add	eax,eax
	adc	edx,edx
	dec	r8d
	jmp	@B
toend:
	mov	[r10],eax
	mov	[r10+4],edx
	add	r8d,r8d
	rcr	r8w,1
	mov	[r10+8],r8w
	ret
_iFDLD	endp

	end
