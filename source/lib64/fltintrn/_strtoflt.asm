include ltype.inc
include fltintrn.inc
include crtl.inc

	.data

pow_table label DWORD
	dt 4002A000000000000000h	; 1e1
	dt 4005C800000000000000h	; 1e2
	dt 400C9C40000000000000h	; 1e4
	dt 4019BEBC200000000000h	; 1e8
	dt 40348E1BC9BF04000000h	; 1e16
	dt 40699DC5ADA82B70B59Eh	; 1e32
	dt 40D3C2781F49FFCFA6D5h	; 1e64
	dt 41A893BA47C980E98CE0h	; 1e128
	dt 4351AA7EEBFB9DF9DE8Eh	; 1e256
	dt 46A3E319A0AEA60E91C7h	; 1e512
	dt 4D48C976758681750C17h	; 1e1024
	dt 5A929E8b3B5DC53D5DE5h	; 1e2048
	dt 7525C46052028A20979Bh	; 1e4096
	dt 7FFF8000000000000000h	; infinity
_real	dt 0
buffer	db 64 dup(?)
flt	S_STRFLT <0,0,0,_real>
control dw 0
tmpcont dw 0
factor	REAL10 ?

	.code

	OPTION PROC:PRIVATE
	OPTION PROLOGUE:NONE, EPILOGUE:NONE

setflags PROC
	xor	edi,edi
	mov	flt.exponent,edi
	mov	rbx,flt.string
@@:
	movzx	eax,BYTE PTR [rbx]
	inc	rbx
	test	eax,eax
	jz	case_zero
	lea	r8,_ltype
	test	byte ptr [r8+rax+1],_SPACE
	jnz	@B
	dec	rbx
	cmp	eax,'+'
	jne	@F
	inc	rbx
	or	edi,_ST_SIGN
@@:
	cmp	eax,'-'
	jne	@F
	inc	rbx
	or	edi,_ST_SIGN or _ST_NEGNUM
@@:
	mov	ax,[rbx]
	inc	rbx
	test	al,al
	jz	case_zero
	or	eax,2020h
	cmp	al,'n'
	je	case_NaN
	cmp	al,'i'
	je	case_INF
	cmp	ax,'x0'
	jne	@F
	or	edi,_ST_ISHEX
	add	rbx,2
@@:
	dec	rbx
toend:
	mov	flt.flags,edi
	mov	flt.string,rbx
	mov	eax,edi
	ret
case_NaN:
	mov	ax,[rbx]
	inc	rbx
	test	al,al
	jz	case_zero
	or	ax,2020h
	cmp	ax,'na'
	jne	case_INVALID
	or	edi,_ST_ISNAN
	inc	rbx
	movzx	eax,BYTE PTR [rbx]
	cmp	eax,'('
	jne	return_NAN
	lea	rdx,[rbx+1]
@@:
	inc	rdx
	movzx	eax,BYTE PTR [rdx]
	cmp	eax,'_'
	je	@B
	lea	r8,_ltype
	test	byte ptr [r8+rax+1],_DIGIT or _UPPER or _LOWER
	jnz	@B
	cmp	eax,')'
	jne	return_NAN
	lea	rbx,[rdx+1]
return_NAN:
	xor	eax,eax
	mov	ecx,80000000h
	jmp	return_NANINF
case_INF:
	mov	ax,[rbx]
	inc	rbx
	or	ax,2020h
	cmp	ax,'fn'
	jne	case_INVALID
	or	edi,_ST_ISINF
	inc	rbx
	mov	eax,[rbx]
	or	eax,20202020h
	cmp	eax,'tini'
	jne	@F
	add	rbx,5
@@:
	xor	eax,eax
	xor	ecx,ecx
return_NANINF:
	mov	rdx,flt.mantissa
	mov	[rdx],eax
	mov	[rdx+4],ecx
	mov	WORD PTR [rdx+8],7FFFh
	test	edi,_ST_NEGNUM
	jz	toend
	or	WORD PTR [rdx+8],8000h
	jmp	toend
case_INVALID:
	dec	rbx
	or	edi,_ST_INVALID
	jmp	toend
case_zero:
	dec	rbx
	or	edi,_ST_ISZERO
	xor	eax,eax
	mov	rdx,flt.mantissa
	mov	[rdx],eax
	mov	[rdx+4],eax
	mov	[rdx+8],ax
	jmp	toend
setflags ENDP


parsedes PROC
	movzx	eax,BYTE PTR [rbx]
	inc	rbx
	test	eax,eax
	jz	parse
	cmp	eax,'.'
	je	dot
	lea	r8,_ltype
	test	byte ptr [r8+rax+1],_DIGIT
	jz	parse
	test	edi,_ST_DOT
	jz	@F
	inc	ecx
@@:
	or	edi,_ST_DIGITS
	or	edx,eax
	cmp	edx,'0'
	je	parsedes
	cmp	rsi,32
	jnb	parsedes
	lea	r8,buffer
	mov	[r8+rsi],al
	inc	rsi
	jmp	parsedes
dot:
	test	edi,_ST_DOT
	jnz	parse
	or	edi,_ST_DOT
	jmp	parsedes

parse:
	xor	edx,edx
	test	edi,_ST_DIGITS
	jz	no_digits
	push	rsi
	push	rcx
	xor	rsi,rsi		; exponent
	cmp	al,'e'
	je	found
	cmp	al,'E'
	jne	notfound
found:
	mov	al,[rbx]
	lea	rdx,[rbx-1]
	cmp	al,'+'
	jne	@F
	inc	rbx
@@:
	cmp	al,'-'
	jne	@F
	inc	rbx
	or	edi,_ST_NEGEXP
@@:
	and	edi,not _ST_DIGITS
lup:
	movzx	eax,BYTE PTR [rbx]
	lea	r8,_ltype
	test	byte ptr [r8+rax+1],_DIGIT
	jz	end_lup
	cmp	rsi,2000
	jnb	@F
	lea	rcx,[rsi*8]
	lea	rsi,[rsi*2+rcx-'0']
	add	rsi,rax
@@:
	or	edi,_ST_DIGITS
	inc	rbx
	jmp	lup
end_lup:
	test	edi,_ST_NEGEXP
	jz	@F
	neg	rsi
@@:
	test	edi,_ST_DIGITS
	jnz	end_exp
	mov	rbx,rdx
	jmp	end_exp
notfound:
	dec	rbx
end_exp:
	mov	rdx,rsi
	pop	rcx
	pop	rsi
	sub	rdx,rcx
	cmp	rsi,32
	jna	@F
	lea	rdx,[rdx+rsi-32]
	mov	rsi,32
@@:
	cmp	rsi,0
	jng	toend
	lea	r8,buffer
	cmp	byte ptr [r8+rsi-1],'0'
	jne	toend
	inc	rdx
	dec	rsi
	jmp	@B
no_digits:
	mov	rbx,flt.string
toend:
	mov	flt.string,rbx
	ret
parsedes ENDP

parsehex PROC
	movzx	eax,BYTE PTR [rbx]
	inc	rbx
	test	eax,eax
	jz	parse
	cmp	eax,'.'
	je	dot
	lea	r8,_ltype
	test	byte ptr [r8+rax+1],_HEX
	jz	parse
	test	edi,_ST_DOT
	jz	@F
	inc	ecx
@@:
	or	edi,_ST_DIGITS
	or	edx,eax
	cmp	edx,'0'
	je	parsehex
	cmp	rsi,32
	jnb	parsehex
	lea	r8,buffer
	mov	[r8+rsi],al
	inc	rsi
	jmp	parsehex
dot:
	test	edi,_ST_DOT
	jnz	parse
	or	edi,_ST_DOT
	jmp	parsehex
parse:
	xor	edx,edx
	test	edi,_ST_DIGITS
	jz	no_digits
	push	rsi
	push	rcx
	xor	rsi,rsi		; exponent
	cmp	al,'p'
	je	found
	cmp	al,'P'
	jne	notfound
found:
	mov	al,[rbx]
	lea	rdx,[rbx-1]
	cmp	al,'+'
	jne	@F
	inc	rbx
@@:
	cmp	al,'-'
	jne	@F
	inc	rbx
	or	edi,_ST_NEGEXP
@@:
	and	edi,not _ST_DIGITS
lupe:
	movzx	eax,BYTE PTR [rbx]
	lea	r8,_ltype
	test	BYTE PTR [r8+rax+1],_DIGIT
	jz	end_lupx
	cmp	rsi,10000
	jnb	@F
	lea	rcx,[rsi*8]
	lea	rsi,[rsi*2+rcx-'0']
	add	rsi,rax
@@:
	or	edi,_ST_DIGITS
	inc	rbx
	jmp	lupe
end_lupx:
	test	edi,_ST_NEGEXP
	jz	@F
	neg	rsi
@@:
	test	edi,_ST_DIGITS
	jnz	end_exp
	mov	rbx,rdx
	jmp	end_exp
notfound:
	dec	rbx
end_exp:
	mov	rdx,rsi
	shl	ecx,2
	sub	rdx,rcx
	pop	rcx
	pop	rsi
	cmp	rsi,16
	jna	@F
	lea	rdx,[rdx+rsi-16*4]
	mov	rsi,16
@@:
	cmp	rsi,0
	jng	toend
	lea	r8,buffer
	cmp	byte ptr [r8+rsi-1],'0'
	jne	toend
	add	rdx,4
	dec	rsi
	jmp	@B
no_digits:
	mov	rbx,flt.string
toend:
	mov	flt.string,rbx
	ret
parsehex ENDP

strtold PROC USES rsi rdi rbx rbp
	push	rdx
	mov	rsi,rax
	xor	edx,edx
	xor	ecx,ecx
	xor	ebp,ebp
@@:
	movzx	eax,BYTE PTR [rsi]
	test	eax,eax
	jz	@F
	mov	edi,edx
	mov	ebx,ecx
	mov	eax,ebp
	add	ebp,ebp
	adc	ecx,ecx
	adc	edx,edx
	add	ebp,ebp
	adc	ecx,ecx
	adc	edx,edx
	add	ebp,eax
	adc	ecx,ebx
	adc	edx,edi
	add	ebp,ebp
	adc	ecx,ecx
	adc	edx,edx
	movzx	eax,BYTE PTR [rsi]
	and	eax,0000000Fh
	add	ebp,eax
	adc	ecx,0
	adc	edx,0
	inc	rsi
	jmp	@B
@@:
	mov	eax,ecx
	mov	edi,16478
	mov	esi,eax
	or	esi,edx
	or	esi,ebp
	jz	toend
	test	edx,edx
	jnz	@F
	mov	edx,eax
	mov	eax,ebp
	xor	ebp,ebp
	sub	edi,32
	test	edx,edx
	jnz	@F
	mov	edx,eax
	mov	eax,ebp
	xor	ebp,ebp
	sub	edi,32
@@:
	test	edx,edx
	js	@F
	dec	edi
	add	ebp,ebp
	adc	eax,eax
	adc	edx,edx
	jmp	@B
@@:
	add	ebp,ebp
	adc	eax,0
	adc	edx,0
	jnc	@F
	rcr	edx,1
	inc	edi
@@:
	mov	esi,edi
toend:
	pop	rbx
	mov	[rbx],eax
	mov	[rbx+4],edx
	mov	[rbx+8],si
	ret
strtold ENDP

stxtold PROC USES rdi
	mov	rbx,rax
	xor	edi,edi
	xor	edx,edx
@@:
	cmp	edi,8
	ja	@F
	test	esi,esi
	jz	@F
	dec	esi
	movzx	eax,BYTE PTR [rbx]
	inc	rbx
	and	eax,not 30h
	bt	eax,6
	sbb	ecx,ecx
	and	ecx,55
	sub	eax,ecx
	lea	rcx,[rdi*4-28]
	neg	ecx
	shl	eax,cl
	or	edx,eax
	add	flt.exponent,4
	inc	edi
	jmp	@B
@@:
	push	rdx
	xor	edi,edi
	xor	edx,edx
@@:
	cmp	edi,8
	ja	@F
	test	esi,esi
	jz	@F
	dec	esi
	movzx	eax,BYTE PTR [rbx]
	inc	rbx
	and	eax,not 30h
	bt	eax,6
	sbb	ecx,ecx
	and	ecx,55
	sub	eax,ecx
	lea	rcx,[rdi*4-28]
	neg	rcx
	shl	eax,cl
	or	edx,eax
	add	flt.exponent,4
	inc	edi
	jmp	@B
@@:
	pop	rax
@@:
	bt	eax,31
	jc	@F
	shl	eax,1
	bt	edx,31
	sbb	ecx,ecx
	and	ecx,1
	or	eax,ecx
	shl	edx,1
	dec	flt.exponent
	jmp	@B
@@:
	dec	flt.exponent
	mov	ecx,flt.exponent
	add	ecx,00003FFFh
	lea	rbx,_real
	mov	DWORD PTR [rbx],edx
	mov	DWORD PTR [rbx+4],eax
	mov	 WORD PTR [rbx+8],cx
	ret
stxtold ENDP

doscale PROC USES rdi rbx
	mov	rbx,rax
	xor	edi,edi
	cmp	esi,8192
	jb	@F
	mov	esi,8192	; set to infinity multiplier
@@:
	test	esi,esi
	jz	toend
lupe:
	test	esi,1
	jz	@F
	lea	rdx,pow_table[rdi]
	mov	rax,rbx
	call	_FLDM
@@:
	add	edi,10
	shr	esi,1
	jnz	lupe
toend:
	ret
doscale ENDP

scale10 PROC
	test	esi,esi
	jz	toend
	fstcw	control			; Store FPU control word
	mov	ax,control
	or	ax,0300h		; set 64 bits extended precision
	mov	tmpcont,ax
	fldcw	tmpcont
	lea	rax,factor
	mov	DWORD PTR [rax],00000000h
	mov	DWORD PTR [rax+4],80000000h
	mov	WORD PTR  [rax+8],3FFFh ; 1.0
	cmp	esi,0
	jnl	@F
	neg	esi
	call	doscale
	mov	rax,rbx
	lea	rdx,factor
	call	_FLDD
	jmp	done
@@:
	call	doscale
	lea	rdx,factor
	mov	rax,rbx
	call	_FLDM
done:
	fldcw	control			; restore control word
toend:
	ret
scale10 ENDP

scaleld PROC
	mov	esi,flt.exponent
	lea	rbx,_real
	cmp	esi,4096
	jng	@F
	mov	esi,4096
	call	scale10
	mov	esi,flt.exponent
	sub	esi,4096
	jmp	done
@@:
	cmp	esi,-4096
	jnl	done
	mov	esi,-4096
	call	scale10
	mov	esi,flt.exponent
	add	esi,4096
done:
	call	scale10
	ret
scaleld ENDP

	OPTION	PROC: PUBLIC

_strtoflt PROC USES rsi rdi rbx r12 string:LPSTR

	mov	flt.string,rcx
	call	setflags
;	int	3
	test	edi,_ST_ISZERO or _ST_ISNAN or _ST_ISINF or _ST_INVALID
	jnz	toend
	xor	ecx,ecx
	xor	edx,edx
	xor	esi,esi
	mov	rbx,flt.string
	test	edi,_ST_ISHEX
	jnz	@F
	call	parsedes
	jmp	end_parse
@@:
	call	parsehex
end_parse:
	mov	r12d,esi
	test	esi,esi
	jnz	@F
	or	edi,_ST_ISZERO
	mov	rdx,flt.mantissa
	mov	[rdx],esi
	mov	[rdx+4],esi
	mov	[rdx+8],si
	jmp	toend
@@:
	lea	rax,buffer
	mov	byte ptr [rax+rsi],0
	mov	flt.exponent,edx
	lea	rdx,_real
	test	edi,_ST_ISHEX
	jz	@F
	call	stxtold
	jmp	done
@@:
	call	strtold
	cmp	flt.exponent,0
	je	done
	call	scaleld
done:
	test	edi,_ST_NEGNUM
	jz	@F
	or	WORD PTR _real[8],8000h
@@:
	mov	eax,flt.exponent
	add	eax,r12d
	dec	eax
	cmp	eax,4932
	jng	@F
	or	edi,_ST_OVERFLOW
@@:
	cmp	eax,-4932
	jnl	toend
	or	edi,_ST_UNDERFLOW

toend:
	mov	flt.flags,edi
	lea	rax,flt
	ret
_strtoflt ENDP

	END
