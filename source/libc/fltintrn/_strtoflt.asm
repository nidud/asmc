include ltype.inc
include fltintrn.inc
include crtl.inc

MAX_DIGITS  equ 19
MAX_SIG_DIG equ 32

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

setflags proc

    xor edi,edi
    mov flt.exponent,edi
    mov ebx,flt.string

    .repeat

	movzx eax,BYTE PTR [ebx]
	inc ebx
	test al,al
	jz case_zero
    .until !(_ltype[eax+1] & _SPACE)

    dec ebx
    .if al == '+'
	inc ebx
	or  edi,_ST_SIGN
    .endif
    .if al == '-'
	inc ebx
	or  edi,_ST_SIGN or _ST_NEGNUM
    .endif

    mov ax,[ebx]
    inc ebx
    test al,al
    jz case_zero

    or	eax,2020h
    cmp al,'n'
    je	case_NaN
    cmp al,'i'
    je	case_INF

    .if ax == 'x0'
	or edi,_ST_ISHEX
	add ebx,2
    .endif
    dec ebx

toend:
    mov flt.flags,edi
    mov flt.string,ebx
    mov eax,edi
    ret

case_NaN:

    mov ax,[ebx]
    inc ebx
    test al,al
    jz case_zero

    or	ax,2020h
    cmp ax,'na'
    jne case_INVALID
    or	edi,_ST_ISNAN
    inc ebx
    movzx eax,BYTE PTR [ebx]

    .if al == '('
	lea edx,[ebx+1]
	movzx eax,BYTE PTR [edx]
	.while al == '_' || _ltype[eax+1] & _DIGIT or _UPPER or _LOWER
	    inc edx
	    mov al,[edx]
	.endw
	.if al == ')'
	    lea ebx,[edx+1]
	.endif
    .endif

return_NAN:
    xor eax,eax
    mov ecx,80000000h
    jmp return_NANINF

case_INF:
    mov ax,[ebx]
    inc ebx
    or	ax,2020h
    cmp ax,'fn'
    jne case_INVALID
    or	edi,_ST_ISINF
    inc ebx
    xor eax,eax
    xor ecx,ecx

return_NANINF:
    mov edx,flt.mantissa
    mov [edx],eax
    mov [edx+4],ecx
    mov WORD PTR [edx+8],7FFFh
    .if edi & _ST_NEGNUM
	or WORD PTR [edx+8],8000h
    .endif
    jmp toend

case_INVALID:
    dec ebx
    or	edi,_ST_INVALID
    jmp toend

case_zero:
    dec ebx
    or	edi,_ST_ISZERO
    xor eax,eax
    mov edx,flt.mantissa
    mov [edx],eax
    mov [edx+4],eax
    mov [edx+8],ax
    jmp toend
setflags ENDP

parsedes PROC
    ;
    ; Parse the mantissa
    ;
    .while 1
	movzx eax,BYTE PTR [ebx]
	inc ebx
	.break .if !eax
	.if al == '.'
	    .break .if edi & _ST_DOT
	    or edi,_ST_DOT
	.else
	    .break .if !(_ltype[eax+1] & _DIGIT)
	    .if edi & _ST_DOT
		inc ecx
	    .endif
	    or edi,_ST_DIGITS
	    or edx,eax
	    .continue .if edx == '0' ; if a significant digit
	    .if esi < MAX_SIG_DIG
		mov buffer[esi],al
	    .endif
	    inc esi
	.endif
    .endw
    ;
    ; Parse the optional exponent
    ;
    xor edx,edx
    .if edi & _ST_DIGITS

	push esi
	push ecx

	xor esi,esi ; exponent
	.if al == 'e' || al == 'E'
	    mov al,[ebx]
	    lea edx,[ebx-1]
	    .if al == '+'
		inc ebx
	    .endif
	    .if al == '-'
		inc ebx
		or  edi,_ST_NEGEXP
	    .endif
	    and edi,not _ST_DIGITS
	    .while 1

		movzx eax,BYTE PTR [ebx]
		.break .if !(_ltype[eax+1] & _DIGIT)

		.if esi < 2000

		    lea ecx,[esi*8]
		    lea esi,[esi*2+ecx-'0']
		    add esi,eax
		.endif

		or  edi,_ST_DIGITS
		inc ebx
	    .endw
	    .if edi & _ST_NEGEXP

		neg esi
	    .endif
	    .if !(edi & _ST_DIGITS)
		mov ebx,edx
	    .endif
	.else
	    dec ebx ; digits found, but no e or E
	.endif

	mov edx,esi
	pop ecx
	pop esi

	sub edx,ecx
	.if esi > MAX_DIGITS

	    lea edx,[edx+esi-MAX_DIGITS]
	    mov esi,MAX_DIGITS
	.endif
	.while 1

	    .break .ifs esi <= 0
	    .break .if buffer[esi-1] != '0'
	    inc edx
	    dec esi
	.endw
    .else
	mov ebx,flt.string
    .endif
    mov flt.string,ebx
    ret
parsedes ENDP

parsehex PROC
    ;
    ; Parse the mantissa
    ;
    .while 1
	movzx eax,BYTE PTR [ebx]
	inc ebx
	.break .if !eax
	.if al == '.'
	    .break .if edi & _ST_DOT
	    or edi,_ST_DOT
	.else
	    .break .if !(_ltype[eax+1] & _HEX)
	    .if edi & _ST_DOT
		inc ecx
	    .endif
	    or edi,_ST_DIGITS
	    or edx,eax
	    .continue .if edx == '0' ; if a significant digit
	    .if esi < MAX_SIG_DIG
		mov buffer[esi],al
	    .endif
	    inc esi
	.endif
    .endw
    ;
    ; Parse the optional exponent
    ;
    xor edx,edx
    .if edi & _ST_DIGITS

	push esi
	push ecx

	xor esi,esi ; exponent
	.if al == 'p' || al == 'P'
	    mov al,[ebx]
	    lea edx,[ebx-1]
	    .if al == '+'
		inc ebx
	    .endif
	    .if al == '-'
		inc ebx
		or  edi,_ST_NEGEXP
	    .endif
	    and edi,not _ST_DIGITS
	    .while 1

		movzx eax,BYTE PTR [ebx]
		.break .if !(_ltype[eax+1] & _DIGIT)

		.if esi < 10000

		    lea ecx,[esi*8]
		    lea esi,[esi*2+ecx-'0']
		    add esi,eax
		.endif

		or  edi,_ST_DIGITS
		inc ebx
	    .endw
	    .if edi & _ST_NEGEXP

		neg esi
	    .endif
	    .if !(edi & _ST_DIGITS)
		mov ebx,edx
	    .endif
	.else
	    dec ebx ; digits found, but no e or E
	.endif

	mov edx,esi
	pop ecx
	pop esi
	shl ecx,2
	sub edx,ecx

	.if esi > 16

	    lea edx,[edx+esi-16*4]
	    mov esi,16
	.endif
	.while 1
	    .break .ifs esi <= 0
	    .break .if buffer[esi-1] != '0'
	    add edx,4
	    dec esi
	.endw
    .else
	mov ebx,flt.string
    .endif
    mov flt.string,ebx
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

    mov ebx,eax
    xor edi,edi
    .if esi >= 8192
	mov esi,8192	; set to infinity multiplier
    .endif
    .if esi
	.repeat
	    .if esi & 1
		lea edx,pow_table[edi]
		mov eax,ebx
		_FLDM()
	    .endif
	    add edi,10
	    shr esi,1
	.untilz
    .endif
    ret

doscale ENDP

scale10 proc
local control:WORD, tmpcont:WORD, factor:REAL10

    .if esi

	fstcw control		; Store FPU control word
	mov ax,control
	or  ax,0300h		; set 64 bits extended precision
	mov tmpcont,ax
	fldcw tmpcont
	lea eax,factor
	mov DWORD PTR [eax],00000000h
	mov DWORD PTR [eax+4],80000000h
	mov WORD PTR [eax+8],3FFFh	; 1.0

	.ifs esi < 0
	    neg esi
	    doscale()
	    mov eax,ebx
	    lea edx,factor
	    _FLDD()
	.else
	    doscale()
	    lea edx,factor
	    mov eax,ebx
	    _FLDM()
	.endif
	fldcw control			; restore control word
    .endif
    ret

scale10 ENDP

scaleld PROC
    mov esi,flt.exponent
    lea ebx,_real
    .ifs esi > 4096
	mov esi,4096
	scale10()
	mov esi,flt.exponent
	sub esi,4096
    .else
	.ifs esi < -4096
	    mov esi,-4096
	    scale10()
	    mov esi,flt.exponent
	    add esi,4096
	.endif
    .endif
    scale10()
    ret
scaleld ENDP

_strtoflt proc public uses esi edi ebx string:LPSTR

  local h, l, digits

    .repeat

	mov eax,string
	mov flt.string,eax
	setflags()
	.break .if edi & _ST_ISZERO or _ST_ISNAN or _ST_ISINF or _ST_INVALID

	xor ecx,ecx
	xor edx,edx
	xor esi,esi
	mov ebx,flt.string
	.if edi & _ST_ISHEX
	    parsehex()
	.else
	    parsedes()
	.endif

	mov digits,esi
	.if !esi
	    or	edi,_ST_ISZERO
	    mov edx,flt.mantissa
	    mov [edx],esi
	    mov [edx+4],esi
	    mov [edx+8],si
	    .break
	.endif

	mov buffer[esi],0
	mov flt.exponent,edx
	lea eax,buffer
	lea edx,_real

	.if edi & _ST_ISHEX
	    stxtold()
	.else
	    strtold()
	    .if flt.exponent != 0
		scaleld()
	    .endif
	.endif

	.if edi & _ST_NEGNUM
	    or WORD PTR _real[8],8000h
	.endif

	mov eax,flt.exponent
	add eax,digits
	dec eax
	.ifs eax > 4932
	    or edi,_ST_OVERFLOW
	.endif
	.ifs eax < -4932
	    or edi,_ST_UNDERFLOW
	.endif
    .until 1
    mov flt.flags,edi
    lea eax,flt
    ret

_strtoflt ENDP

	END
