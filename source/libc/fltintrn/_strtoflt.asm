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

	.code

	OPTION	PROC: PRIVATE

setflags PROC
	xor	edi,edi
	mov	flt.exponent,edi
	mov	ebx,flt.string
@@:
	movzx	eax,BYTE PTR [ebx]
	inc	ebx
	test	eax,eax
	jz	case_zero
	test	byte ptr _ltype[eax+1],_SPACE
	jnz	@B
	dec	ebx
	cmp	eax,'+'
	jne	@F
	inc	ebx
	or	edi,_ST_SIGN
@@:
	cmp	eax,'-'
	jne	@F
	inc	ebx
	or	edi,_ST_SIGN or _ST_NEGNUM
@@:
	mov	ax,[ebx]
	inc	ebx
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
	add	ebx,2
@@:
	dec	ebx
toend:
	mov	flt.flags,edi
	mov	flt.string,ebx
	mov	eax,edi
	ret
case_NaN:
	mov	ax,[ebx]
	inc	ebx
	test	al,al
	jz	case_zero
	or	ax,2020h
	cmp	ax,'na'
	jne	case_INVALID
	or	edi,_ST_ISNAN
	inc	ebx
	movzx	eax,BYTE PTR [ebx]
	cmp	eax,'('
	jne	return_NAN
	lea	edx,[ebx+1]
@@:
	inc	edx
	movzx	eax,BYTE PTR [edx]
	cmp	eax,'_'
	je	@B
	test	byte ptr _ltype[eax+1],_DIGIT or _UPPER or _LOWER
	jnz	@B
	cmp	eax,')'
	jne	return_NAN
	lea	ebx,[edx+1]
return_NAN:
	xor	eax,eax
	mov	ecx,80000000h
	jmp	return_NANINF
case_INF:
	mov	ax,[ebx]
	inc	ebx
	or	ax,2020h
	cmp	ax,'fn'
	jne	case_INVALID
	or	edi,_ST_ISINF
	inc	ebx
	mov	eax,[ebx]
	or	eax,20202020h
	cmp	eax,'tini'
	jne	@F
	add	ebx,5
@@:
	xor	eax,eax
	xor	ecx,ecx
return_NANINF:
	mov	edx,flt.mantissa
	mov	[edx],eax
	mov	[edx+4],ecx
	mov	WORD PTR [edx+8],7FFFh
	test	edi,_ST_NEGNUM
	jz	toend
	or	WORD PTR [edx+8],8000h
	jmp	toend
case_INVALID:
	dec	ebx
	or	edi,_ST_INVALID
	jmp	toend
case_zero:
	dec	ebx
	or	edi,_ST_ISZERO
	xor	eax,eax
	mov	edx,flt.mantissa
	mov	[edx],eax
	mov	[edx+4],eax
	mov	[edx+8],ax
	jmp	toend
setflags ENDP


parsedes PROC
	movzx	eax,BYTE PTR [ebx]
	inc	ebx
	test	eax,eax
	jz	parse
	cmp	eax,'.'
	je	dot
	test	byte ptr _ltype[eax+1],_DIGIT
	jz	parse
	test	edi,_ST_DOT
	jz	@F
	inc	ecx
@@:
	or	edi,_ST_DIGITS
	or	edx,eax
	cmp	edx,'0'
	je	parsedes
	cmp	esi,32
	jnb	parsedes
	mov	buffer[esi],al
	inc	esi
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
	push	esi
	push	ecx
	xor	esi,esi		; exponent
	cmp	al,'e'
	je	found
	cmp	al,'E'
	jne	notfound
found:
	mov	al,[ebx]
	lea	edx,[ebx-1]
	cmp	al,'+'
	jne	@F
	inc	ebx
@@:
	cmp	al,'-'
	jne	@F
	inc	ebx
	or	edi,_ST_NEGEXP
@@:
	and	edi,not _ST_DIGITS
lup:
	movzx	eax,BYTE PTR [ebx]
	test	byte ptr _ltype[eax+1],_DIGIT
	jz	end_lup
	cmp	esi,2000
	jnb	@F
	lea	ecx,[esi*8]
	lea	esi,[esi*2+ecx-'0']
	add	esi,eax
@@:
	or	edi,_ST_DIGITS
	inc	ebx
	jmp	lup
end_lup:
	test	edi,_ST_NEGEXP
	jz	@F
	neg	esi
@@:
	test	edi,_ST_DIGITS
	jnz	end_exp
	mov	ebx,edx
	jmp	end_exp
notfound:
	dec	ebx
end_exp:
	mov	edx,esi
	pop	ecx
	pop	esi
	sub	edx,ecx
	cmp	esi,32
	jna	@F
	lea	edx,[edx+esi-32]
	mov	esi,32
@@:
	cmp	esi,0
	jng	toend
	cmp	buffer[esi-1],'0'
	jne	toend
	inc	edx
	dec	esi
	jmp	@B
no_digits:
	mov	ebx,flt.string
toend:
	mov	flt.string,ebx
	ret
parsedes ENDP

parsehex PROC
	movzx	eax,BYTE PTR [ebx]
	inc	ebx
	test	eax,eax
	jz	parse
	cmp	eax,'.'
	je	dot
	test	byte ptr _ltype[eax+1],_HEX
	jz	parse
	test	edi,_ST_DOT
	jz	@F
	inc	ecx
@@:
	or	edi,_ST_DIGITS
	or	edx,eax
	cmp	edx,'0'
	je	parsehex
	cmp	esi,32
	jnb	parsehex
	mov	buffer[esi],al
	inc	esi
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
	push	esi
	push	ecx
	xor	esi,esi		; exponent
	cmp	al,'p'
	je	found
	cmp	al,'P'
	jne	notfound
found:
	mov	al,[ebx]
	lea	edx,[ebx-1]
	cmp	al,'+'
	jne	@F
	inc	ebx
@@:
	cmp	al,'-'
	jne	@F
	inc	ebx
	or	edi,_ST_NEGEXP
@@:
	and	edi,not _ST_DIGITS
lupe:
	movzx	eax,BYTE PTR [ebx]
	test	BYTE PTR _ltype[eax+1],_DIGIT
	jz	end_lupx
	cmp	esi,10000
	jnb	@F
	lea	ecx,[esi*8]
	lea	esi,[esi*2+ecx-'0']
	add	esi,eax
@@:
	or	edi,_ST_DIGITS
	inc	ebx
	jmp	lupe
end_lupx:
	test	edi,_ST_NEGEXP
	jz	@F
	neg	esi
@@:
	test	edi,_ST_DIGITS
	jnz	end_exp
	mov	ebx,edx
	jmp	end_exp
notfound:
	dec	ebx
end_exp:
	mov	edx,esi
	shl	ecx,2
	sub	edx,ecx
	pop	ecx
	pop	esi
	cmp	esi,16
	jna	@F
	lea	edx,[edx+esi-16*4]
	mov	esi,16
@@:
	cmp	esi,0
	jng	toend
	cmp	buffer[esi-1],'0'
	jne	toend
	add	edx,4
	dec	esi
	jmp	@B
no_digits:
	mov	ebx,flt.string
toend:
	mov	flt.string,ebx
	ret
parsehex ENDP

strtold PROC USES esi edi ebx ebp
	push	edx
	mov	esi,eax
	xor	edx,edx
	xor	ecx,ecx
	xor	ebp,ebp
@@:
	movzx	eax,BYTE PTR [esi]
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
	movzx	eax,BYTE PTR [esi]
	and	eax,0000000Fh
	add	ebp,eax
	adc	ecx,0
	adc	edx,0
	inc	esi
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
	pop	ebx
	mov	[ebx],eax
	mov	[ebx+4],edx
	mov	[ebx+8],si
	ret
strtold ENDP

stxtold PROC USES edi
	mov	ebx,eax
	xor	edi,edi
	xor	edx,edx
@@:
	cmp	edi,8
	ja	@F
	test	esi,esi
	jz	@F
	dec	esi
	movzx	eax,BYTE PTR [ebx]
	inc	ebx
	and	eax,not 30h
	bt	eax,6
	sbb	ecx,ecx
	and	ecx,55
	sub	eax,ecx
	lea	ecx,[edi*4-28]
	neg	ecx
	shl	eax,cl
	or	edx,eax
	add	flt.exponent,4
	inc	edi
	jmp	@B
@@:
	push	edx
	xor	edi,edi
	xor	edx,edx
@@:
	cmp	edi,8
	ja	@F
	test	esi,esi
	jz	@F
	dec	esi
	movzx	eax,BYTE PTR [ebx]
	inc	ebx
	and	eax,not 30h
	bt	eax,6
	sbb	ecx,ecx
	and	ecx,55
	sub	eax,ecx
	lea	ecx,[edi*4-28]
	neg	ecx
	shl	eax,cl
	or	edx,eax
	add	flt.exponent,4
	inc	edi
	jmp	@B
@@:
	pop	eax
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
	mov	DWORD PTR _real[0],edx
	mov	DWORD PTR _real[4],eax
	mov	 WORD PTR _real[8],cx
	ret
stxtold ENDP

doscale PROC USES edi ebx
	mov	ebx,eax
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
	lea	edx,pow_table[edi]
	mov	eax,ebx
	call	_FLDM
@@:
	add	edi,10
	shr	esi,1
	jnz	lupe
toend:
	ret
doscale ENDP

scale10 PROC
  local control:WORD,
	tmpcont:WORD,
	factor:REAL10
	test	esi,esi
	jz	toend
	fstcw	control			; Store FPU control word
	mov	ax,control
	or	ax,0300h		; set 64 bits extended precision
	mov	tmpcont,ax
	fldcw	tmpcont
	lea	eax,factor
	mov	DWORD PTR [eax],00000000h
	mov	DWORD PTR [eax+4],80000000h
	mov	WORD PTR  [eax+8],3FFFh ; 1.0
	cmp	esi,0
	jnl	@F
	neg	esi
	call	doscale
	mov	eax,ebx
	lea	edx,factor
	call	_FLDD
	jmp	done
@@:
	call	doscale
	lea	edx,factor
	mov	eax,ebx
	call	_FLDM
done:
	fldcw	control			; restore control word
toend:
	ret
scale10 ENDP

scaleld PROC
	mov	esi,flt.exponent
	lea	ebx,_real
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

_strtoflt PROC USES esi edi ebx string:LPSTR

  local h, l, digits

	mov	eax,string
	mov	flt.string,eax
	call	setflags
;	int	3
	test	edi,_ST_ISZERO or _ST_ISNAN or _ST_ISINF or _ST_INVALID
	jnz	toend
	xor	ecx,ecx
	xor	edx,edx
	xor	esi,esi
	mov	ebx,flt.string
	test	edi,_ST_ISHEX
	jnz	@F
	call	parsedes
	jmp	end_parse
@@:
	call	parsehex
end_parse:
	mov	digits,esi
	test	esi,esi
	jnz	@F
	or	edi,_ST_ISZERO
	mov	edx,flt.mantissa
	mov	[edx],esi
	mov	[edx+4],esi
	mov	[edx+8],si
	jmp	toend
@@:
	mov	buffer[esi],0
	mov	flt.exponent,edx
	lea	eax,buffer
	lea	edx,_real
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
	add	eax,digits
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
	lea	eax,flt
	ret
_strtoflt ENDP

	END
