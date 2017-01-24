include tinfo.inc
include ctype.inc
include string.inc

	.data

	;----------------------------------------------------------------------
	; Output syntax color
	;----------------------------------------------------------------------

ST_COUNT	equ 9

S_STYLE		STRUC
st_line		dd ?	; current line index
st_bp		dd ?	; current line adress
st_boff		dd ?	; offset start of visible line
st_bend		dd ?	; end of visible line
st_wbuf		dd ?	; screen buffer (int *)
st_type		db ?	; current type
st_attr		db ?	; current attrib
st_slen		dd ?	; length of line
st_string	dd ?	; offset of first word
st_begin	dd ?	; offset of Begin word
st_tinfo	dd ?
S_STYLE		ENDS

format_label	dd tidoattrib	; 1. A Attrib
		dd tidocontrol	; 2. O Control
		dd tidoquote	; 3. Q Quote
		dd tidonumber	; 4. D Digit
		dd tidochar	; 5. C Char
		dd tidostring	; 6. S String
		dd tidostart	; 7. B Begin
		dd tidoword	; 8. W Word
		dd tidonested	; 9. N Nested

	.code

	ASSUME	ebp : PTR S_STYLE
	OPTION	PROC: PRIVATE

getnexttoken PROC ; "1",0,"2",0,"n",0,0
	xor	eax,eax
	.repeat
		cmp	al,[esi]
		lea	esi,[esi+1]
	.until	ZERO?
	cmp	al,[esi]
	ret
getnexttoken ENDP

tisetat PROC USES eax ebx

	mov	eax,edi
	dec	eax			; = offset in text line

	.if	eax >= [ebp].st_boff
		.if	eax > [ebp].st_bend
			stc
		.else
			sub	eax,[ebp].st_boff
			add	eax,eax
			add	eax,[ebp].st_wbuf	; = offset in screen line (*int)
			mov	bl,[ebp].st_attr
			mov	[eax+1],bl		; set attrib for this char
			clc
		.endif
	.else
		clc
	.endif
	ret
tisetat ENDP

strisquote PROC USES esi edi ebx ecx line, string
	mov	edi,line
lupe:
	xor	esi,esi
	xor	ebx,ebx			; current quote
	mov	eax,string
	sub	eax,edi
	jle	toend
	memquote( edi, eax )
	mov	esi,eax			; first offset of quote
	jz	toend
	or	bl,[eax]
	lea	edi,[eax+1]
@@:
	cmp	edi,string
	jae	toend
	mov	ecx,string
	sub	ecx,edi
	memchr( edi, ebx, ecx )
	jz	toend
	lea	edi,[eax+1]
	cmp	bl,'"'
	jne	lupe
	cmp	byte ptr [eax-1],'\'	; "case \"quoted text\""
	jne	lupe
	cmp	byte ptr [eax-2],'\'	; case "C:\\"
	je	lupe
	jmp	@B
toend:
	mov	eax,esi		; return offset first quote
	test	ebx,ebx		; set ZF to result
	ret
strisquote ENDP

	;----------------------------------------------------------------------
	; 1. A Attrib
	;----------------------------------------------------------------------

tidoattrib PROC
	mov	al,[esi-1]
	mov	ebx,[ebp].st_tinfo
	mov	BYTE PTR [ebx+1].S_TINFO.ti_stat,al
	mov	al,[esi]
	.if	al
		mov	BYTE PTR [ebx].S_TINFO.ti_stat,al
	.endif
	ret
tidoattrib ENDP

	;----------------------------------------------------------------------
	; 5. C Char
	;----------------------------------------------------------------------

tidochar PROC

	;----------------------------
	; timeit_start 5, "tidochar"
	;----------------------------

	mov	eax,[ebp].st_boff
	cmp	eax,[ebp].st_begin
	jae	toend

ifdef __SSE__

	.data
	ALIGN	4
	tidochar_p dd _rtl_tidochar

	.code

	jmp	tidochar_p

_rtl_tidochar:
	mov	eax,tidochar_386
	.if	sselevel & SSE_SSE2
		mov	eax,tidochar_SSE2
	.endif
	mov	tidochar_p,eax
	jmp	eax

	ALIGN	4

tidochar_SSE2:

	mov	edi,[ebp].st_boff
	movzx	eax,BYTE PTR [esi]
	inc	esi
	test	al,al
	jz	toend
	cmp	al,"'"
	je	tidochar_SSE2
	cmp	al,'"'
	je	tidochar_SSE2

	imul	eax,eax,01010101h
	movd	xmm0,eax
	pshufd	xmm0,xmm0,0

	ALIGN	4
@@:
	movups	xmm1,[edi]
	movaps	xmm2,xmm0
	pcmpeqb xmm2,xmm1
	pcmpeqb xmm1,xmm2
	pmaxub	xmm1,xmm2
	pmovmskb eax,xmm1
	add	edi,16
	test	eax,eax
	jz	@B

	bsf	eax,eax
	lea	edi,[edi+eax-16]

	cmp	BYTE PTR [edi],0
	je	tidochar_SSE2
	cmp	edi,[ebp].st_begin
	jae	tidochar_SSE2

	inc	edi
	call	tisetat
	jnc	@B
	jmp	tidochar_SSE2

	ALIGN	4

tidochar_386:

endif

	strlen( esi )
	jz	toend
	mov	ebx,eax
	mov	edx,[ebp].st_bp
	xor	eax,eax
@@:
	mov	al,[edx]
	inc	edx
	test	al,al
	jz	toend
	test	__ctype[eax+1],_SPACE
	jnz	@B
	mov	edi,esi
	mov	ecx,ebx
	repne	scasb
	jne	@B
	mov	edi,edx
	cmp	edx,[ebp].st_begin
	ja	toend
	call	tisetat
	jnc	@B
toend:
	;-------------------------
	; timeit_end 5
	;-------------------------
	ret
tidochar ENDP

	;----------------------------------------------------------------------
	; 7. B Begin - XX string -- set color XX from string to end of line
	;----------------------------------------------------------------------

tidostart PROC

	;-------------------------
	; timeit_start 2, "tidostart"
	;-------------------------

dostart:
	mov	edi,edx
	movzx	ebx,BYTE PTR [esi]
	mov	bl,__ctype[ebx+1]
	memquote( edi, [ebp].st_slen )
	jz	do
	inc	bh
do:
	strstri( edi, esi )
	jnz	@F
	call	getnexttoken
	jnz	do
	ret
@@:
	lea	edi,[eax+1]
	test	ebx,_UPPER or _LOWER
	jz	test_quote

	cmp	eax,[ebp].st_bp
	je	test_end
	movzx	eax,BYTE PTR [eax-1]
	test	__ctype[eax+1],_SPACE
	jz	do
test_end:
	strlen( esi )
	movzx	eax,byte ptr [edi+eax-1]
	test	eax,eax
	jz	test_quote
	test	__ctype[eax+1],_SPACE
	jz	do

test_quote:
	test	ebx,0100h
	jz	no_quote
	cmp	BYTE PTR [esi],"'"
	je	no_quote
	lea	eax,[edi-1]
	strisquote( edx, eax )
	jnz	do

no_quote:

	lea	eax,[edi-1]
	cmp	eax,[ebp].st_begin
	ja	set_attrib
	mov	[ebp].st_begin,eax

set_attrib:
	call	tisetat
	jc	toend
	mov	al,[edi]
	inc	edi
	test	al,al
	jnz	set_attrib
toend:
	;-------------------------
	; timeit_end 2
	;-------------------------

	ret
tidostart ENDP

	;----------------------------------------------------------------------
	; 9. N Nested -- /* */
	;----------------------------------------------------------------------

tidonested PROC

	;------------------------------
	; timeit_start 9, "tidonested"
	;------------------------------

	mov	edi,edx		; find start condition
	mov	eax,[ebp].st_line
	test	eax,eax
	jz	find_arg1	; first line..

	call	find_token	; seek back to last first arg (/*)
	jz	find_arg1
	mov	ebx,eax		; EBX first arg
	call	getnexttoken	; ESI to next token
	jz	@F		; start, no end - ok
	call	find_token	; find end */
	jz	@F		; start, no end
	cmp	eax,ebx		; end > start ?
	ja	find_arg1
@@:
	inc	edi
	mov	ecx,[ebp].st_slen
	jmp	find_arg2

find_arg1:
	mov	esi,[ebp].st_string
	mov	ecx,[ebp].st_slen
	mov	eax,edi
	sub	eax,[ebp].st_bp
	sub	ecx,eax
	jle	toend
	mov	al,[esi]
	repne	scasb
	jne	toend
	inc	esi
	xor	eax,eax
	xor	ebx,ebx
@@:
	inc	ebx
	xor	al,[esi+ebx-1]
	jz	@F
	sub	al,[edi+ebx-1]
	jz	@B
	jmp	find_arg1
@@:
	strisquote( edx, edi )
	jnz	find_arg1
@@:
	call	tisetat
	jc	toend
	inc	edi
	mov	al,[esi]
	inc	esi
	test	al,al
	jz	find_arg2
	dec	ecx
	jnz	@B
	call	tisetat

find_arg2:
	test	ecx,ecx
	jz	toend
	mov	ax,[esi]
	test	al,al
	jz	clear_ECX
@@:
	call	tisetat
	jc	toend
	dec	ecx
	jz	toend
	inc	edi
	cmp	al,[edi-2]
	jne	@B
	test	ah,ah
	jz	find_arg1
	cmp	ah,[edi-1]
	jne	@B
	strisquote( edx, edi )
	jnz	find_arg2
	xor	eax,eax
	xor	ebx,ebx
@@:
	call	tisetat
	jc	toend
	dec	ecx
	jz	toend
	inc	edi
	inc	ebx
	xor	al,[esi+ebx+2]
	jz	find_arg1
	sub	al,[edi+ebx-1]
	jz	@B
	call	tisetat
	jmp	find_arg2

clear_ECX:
	inc	edi
	call	tisetat
	jc	toend
	dec	ecx
	jnz	clear_ECX
	jmp	find_arg1

toend:
	;-------------------------
	; timeit_end 9
	;-------------------------
	ret

arg2_not_found:
	dec	edi
	mov	eax,edi
	sub	eax,[ebp].st_bp
	mov	ecx,[ebp].st_slen
	sub	ecx,eax
	jg	clear_ECX
	jmp	toend

	;--------------------------------------
	; seek back to get offset of /* and */
	;--------------------------------------

find_token:
	push	edi
	push	ebx
	push	edx

	strlen( esi )
	mov	ebx,eax
	jz	end_find

	mov	eax,[ebp].st_tinfo
	mov	edi,[eax].S_TINFO.ti_flp
	mov	edx,[eax].S_TINFO.ti_bp
	mov	eax,edi
	sub	eax,edx
	jz	end_find
	dec	edi

token_loop:
	movzx	eax,BYTE PTR [esi]
	mov	ecx,edi
	sub	ecx,edx
	memrchr( edx, eax, ecx )
	jz	end_find

	mov	edi,eax
	strncmp( esi, edi, ebx )
	jnz	token_loop
	;
	; token found, now find start of line to make
	; sure EDI is not indside " /* quotes */ "
	;
	mov	ecx,edi
	sub	ecx,edx
	memrchr( edx, 10, ecx )
	lea	eax,[eax+1]
	jnz	@F
	mov	eax,edx
@@:
	strisquote( eax, edi )
	jz	token_found
	;
	; ' is found but /* it's maybe a fake */
	;
	streol( edi )	; get end of line
	cmp	eax,edi
	je	token_found
	sub	eax,edi
	jz	end_find
	memquote( edi, eax )
	jnz	token_loop
token_found:
	mov	eax,edi
	inc	ebx
end_find:
	pop	edx
	pop	ebx
	pop	edi
	retn
tidonested ENDP

	;----------------------------------------------------------------------
	; 8. W Word - match on all equal words
	;----------------------------------------------------------------------

tidoword PROC

	;----------------------------
	; timeit_start 8, "tidoword"
	;----------------------------

ifdef __SSE__

	.data
	ALIGN	4
	tidoword_p dd _rtl_tidoword
	  doword_p dd doword_386


	.code

	jmp	tidoword_p

_rtl_tidoword:
	mov	eax,tidoword_386
	mov	ecx,doword_386
	.if	sselevel & SSE_SSE2
		mov	eax,tidoword_SSE2
		mov	ecx,doword_SSE2
	.endif
	mov	tidoword_p,eax
	mov	doword_p,ecx
	jmp	eax

	ALIGN	4

tidoword_SSE2:

	mov	eax,20202020h	; preset SIMD values
	movd	xmm3,eax
	pshufd	xmm3,xmm3,0
	pxor	xmm4,xmm4

	jmp	tidoword_386

doword_SSE2:

	;---------------------------
	; strchr(edi, [esi])
	;---------------------------
	movzx	eax,BYTE PTR [esi]
	or	eax,20h
	imul	eax,eax,01010101h
	movd	xmm2,eax
	pshufd	xmm2,xmm2,0
	push	edi
	push	edx
	mov	edx,edi
SSECHR:
	;---------------------------
	; skip if already painted
	;---------------------------
	cmp	edx,[ebp].st_begin
	jae	SSECHR_DONE
	movdqu	xmm0,[edx]
	movdqa	xmm1,xmm0
	pcmpeqb xmm1,xmm4
	pmovmskb ecx,xmm1
	orps	xmm0,xmm3
	pcmpeqb xmm0,xmm2
	pmovmskb eax,xmm0
	lea	edx,[edx+16]
	or	ecx,eax
	jz	SSECHR
	;---------------------------
	; char or zero found
	;---------------------------
	bsf	ecx,ecx
	lea	edx,[edx+ecx-16]
	cmp	BYTE PTR [edx],0
	je	SSECHR_DONE
	cmp	edx,[ebp].st_begin
	jae	SSECHR_DONE
	;---------------------------
	; compare string
	;---------------------------
	mov	edi,edx
	inc	edx
	xor	ecx,ecx
	lea	eax,[esi+1]
  SSECHR_COMPARE:
	xor	cl,[eax]
	jz	SSECHR_FOUND
	mov	ch,[edx]
	or	cx,2020h
	sub	cl,ch
	jnz	SSECHR
	inc	eax
	inc	edx
	jmp	SSECHR_COMPARE
  SSECHR_FOUND:
	mov	ecx,eax
	mov	eax,edi
	sub	ecx,esi
	test	eax,eax
	pop	edx
	pop	edi
	jmp	set_attrib

  SSECHR_DONE:
	pop	edx
	pop	edi
	jmp	get_next_word

tidoword_386:

endif
	cmp	edx,[ebp].st_begin
	jae	toend

doword:
	mov	edi,edx

find_next_word:
	cmp	edi,[ebp].st_begin
	jae	get_next_word
	cmp	edi,[ebp].st_bend
	ja	get_next_word
	cmp	BYTE PTR [edi],0
	je	get_next_word
ifdef __SSE__

	jmp	doword_p

doword_386:

endif
	strlen( esi )
	push	eax
	push	eax
	strlen( edi )
	pop	ecx
	memstri( edi, eax, esi, ecx )
	pop	ecx
	jz	get_next_word
	cmp	eax,[ebp].st_begin
	jb	set_attrib

get_next_word:
	call	getnexttoken
	jnz	doword
toend:
	;
	; timeit_end 8
	;
	ret

set_attrib:
	;
	; first char or !X in front
	; end is !X or end of line
	; X: UPPER | LOWER | DIGIT | '_'
	;
	cmp	eax,[ebp].st_bp
	lea	edi,[eax+1]
	je	@F
	;
	; then test char in front
	;
	movzx	eax,BYTE PTR [edi-2]
	test	__ctype[eax+1],_UPPER or _LOWER or _DIGIT
	jnz	find_next_word
	cmp	al,'_'
	je	find_next_word
     @@:
	;
	; test last char + one
	;
	movzx	eax,BYTE PTR [edi+ecx-1]
	test	__ctype[eax+1],_UPPER or _LOWER or _DIGIT
	jnz	find_next_word
	cmp	al,'_'
	je	find_next_word
     @@:
	call	tisetat
	jc	get_next_word
	inc	edi
	dec	ecx
	jnz	@B
	jmp	find_next_word
tidoword ENDP

	;----------------------------------------------------------------------
	; 2. O Control - match on all control chars
	;----------------------------------------------------------------------

tidocontrol PROC
	;
	; timeit_start 2, "tidocontrol"
	;
	mov	edi,[ebp].st_boff
	xor	eax,eax
	.if	edi < [ebp].st_begin
		.repeat
			mov	al,[edi]
			inc	edi
			.break .if !al
			.if	__ctype[eax+1] & _CONTROL
				.if	al != 9
					mov	ebx,[ebp].st_tinfo
					.if	[ebx].S_TINFO.ti_flag & _T_SHOWTABS
						call	tisetat
						.break .if CARRY?
					.endif
				.endif
			.endif
		.until	edi >= [ebp].st_bend
	.endif
	;
	; timeit_end 2
	;
	ret
tidocontrol ENDP

	;----------------------------------------------------------------------
	; 6. S String - match on all equal strings if not inside quote
	;----------------------------------------------------------------------

tidostring PROC
	;
	; timeit_start 6, "tidostring"
	;
	.repeat
		mov	edi,edx
		.repeat
			strstr( edi, esi )
			.break .if ZERO?
			lea	edi,[eax+1]
			mov	ecx,esi
			.while	edi < [ebp].st_begin
				call	tisetat
				.if	CARRY?
					xor	eax,eax
					.break
				.endif
				inc	edi
				inc	ecx
				.break .if BYTE PTR [ecx] < 1
			.endw
		.until	ZERO?
		call	getnexttoken
	.until	ZERO?
	;
	; timeit_end 6
	;
	ret
tidostring ENDP

	;----------------------------------------------------------------------
	; 3. Q Quote - match on '"' and "'"
	;----------------------------------------------------------------------

tidoquote PROC
	;
	; timeit_start 3, "tidoquote"
	;
	mov	edi,edx
	mov	eax,[ebp].st_slen
doquote:
	memquote( edi, eax )
	jz	toend
	lea	edi,[eax+1]
	mov	bl,[eax]	; save quote in BL
@@:
	cmp	edi,[ebp].st_begin
	ja	toend
	call	tisetat
	jc	toend
	mov	al,[edi]
	inc	edi
	test	al,al
	jz	done
	cmp	al,bl
	jne	@B
	cmp	al,'"'		; case C string \"
	jne	@F
	cmp	BYTE PTR [edi-2],'\'
	jne	@F
	cmp	byte ptr [edi-3],'\'	; case "C:\\"
	jne	@B
@@:
	call	tisetat
	jc	toend
	strlen( edi )
	jnz	doquote
toend:
	;
	; timeit_end 3
	;
	ret
done:
	call	tisetat
	jmp	toend
tidoquote ENDP

	;----------------------------------------------------------------------
	; 4. D Digit - match on 0x 0123456789ABCDEF and Xh
	;----------------------------------------------------------------------

tidonumber PROC
	;
	; timeit_start 4, "tidonumber"
	;
	mov	edi,[ebp].st_boff
	xor	eax,eax
donumber:
	cmp	edi,[ebp].st_begin
	jae	toend
	mov	al,[edi]
	inc	edi
	test	al,al
	jz	toend
	test	__ctype[eax+1],_DIGIT
	jnz	digit
next:
	cmp	edi,[ebp].st_bend
	jb	donumber
toend:
	;
	; timeit_end 4
	;
	ret
digit:
	lea	ecx,[edi-1]
	cmp	ecx,[ebp].st_bp
	je	@F
	movzx	ecx,BYTE PTR [ecx-1]
	cmp	ecx,'_'
	je	next
	test	ecx,ecx
	jz	next
	test	__ctype[ecx+1],_UPPER or _LOWER or _DIGIT
	jnz	next
@@:
	mov	esi,edi
	cmp	al,'0'
	jne	@F
	mov	al,[esi]
	inc	esi
	or	al,20h
	cmp	al,'x'
	je	@F
	dec	esi
@@:
	mov	al,[esi]
	inc	esi
	test	al,al
	jz	setat
	test	__ctype[eax+1],_HEX
	jnz	@B
	or	al,20h
	cmp	al,'u'		; 0x00000000UL
	je	@B
	cmp	al,'i'		; 0x8000000000000000i64
	je	@B
	cmp	al,'l'		; 0x00000000UL[L]
	je	@B
	inc	esi
	cmp	al,'h'		; 80000000h
	je	setat
	dec	esi
@@:
	mov	al,[esi-1]
	test	__ctype[eax+1],_UPPER or _LOWER
	jnz	next
setat:
	sub	esi,edi
@@:
	call	tisetat
	inc	edi
	dec	esi
	jnz	@B
	jmp	next
tidonumber ENDP

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	ASSUME	ebp : NOTHING
	OPTION	PROC: PUBLIC

tistyle PROC USES esi edi ebx,
	ti:		PTINFO,
	line_id:	DWORD,
	line_ptr:	LPSTR,
	line_size:	DWORD,
	out_buffer:	PTR WORD

local	style:		S_STYLE
	;
	; timeit_start 1, "tistyle"
	;

	mov	esi,ti
	mov	ebx,line_id
	mov	eax,line_ptr
	mov	ecx,line_size
	mov	edx,out_buffer

	push	ebp
	lea	ebp,style

	mov	[ebp].S_STYLE.st_line,ebx	; line id
	mov	[ebp].S_STYLE.st_bp,eax		; pointer to line
	mov	[ebp].S_STYLE.st_wbuf,edx	; output buffer *WORD
	mov	[ebp].S_STYLE.st_slen,ecx	; length of line
	mov	[ebp].S_STYLE.st_tinfo,esi

	add	eax,[esi].S_TINFO.ti_boff	; start of line
	mov	[ebp].S_STYLE.st_boff,eax
	mov	edx,eax
	add	eax,ecx
	add	edx,TIMAXSCRLINE

	.if	eax >= edx
		mov	eax,edx
		dec	eax
	.endif

	mov	[ebp].S_STYLE.st_bend,eax	; end of line
	mov	[ebp].S_STYLE.st_begin,eax

	mov	esi,[esi].S_TINFO.ti_style	; ESI style

	.if	esi

		.while	1

			xor	eax,eax
			lodsw
			mov	[ebp].S_STYLE.st_attr,ah
			mov	[ebp].S_STYLE.st_type,al

			.break .if !al

			mov	ah,0
			dec	eax
			.break .if al >= ST_COUNT

			mov	[ebp].S_STYLE.st_string,esi
			mov	edx,[ebp].S_STYLE.st_bp
			push	esi
			call	format_label[eax*4]
			pop	esi

			.repeat
				lodsb
				.continue .if al
				lodsb
			.until	!al
		.endw
	.endif
	pop	ebp
	;
	; timeit_end 1
	;
	ret
tistyle ENDP

	END
