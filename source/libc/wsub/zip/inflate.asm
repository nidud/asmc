; INFLATE.ASM--
;
;  inflate.c -- by Mark Adler
;  explode.c -- by Mark Adler
;
; Change history:
; 2012-09-08 - Modified for DZ32
; 03/31/2010 - Removed 386 instructions
; ../../1997 - Modified for Doszip

include iost.inc
include alloc.inc
include string.inc
include zip.inc
include errno.inc

OSIZE	equ 8000h
BMAX	equ 16		; Maximum bit length of any code (16 for explode)
N_MAX	equ 288		; Maximum number of codes in any set
;
; Huffman code lookup table entry--this entry is four bytes for machines
;   that have 16-bit pointers (e.g. PC's in the small or medium model).
;   Valid extra bits are 0..13.	 e == 15 is EOB (end of block), e == 16
;   means that v is a literal, 16 < e < 32 means that v is a pointer to
;   the next table, which codes e - 16 bits, and lastly e == 99 indicates
;   an unused code.  If a code with e == 99 is looked up, this implies an
;   error in the data.
;
HUFT	STRUC
e	db ?		; number of extra bits or operation
b	db ?		; number of bits in this code or subcode
 UNION
  n	dw ?		; literal, length base, or distance base
  t	dd ?		; pointer to next level of table
 ENDS
eight	dw ?
HUFT	ENDS

	.data

fixed_bd	dd 0
fixed_bl	dd 0
fixed_td	dd 0
fixed_tl	dd 0

border		dw 16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15
cplens		dw 3,4,5,6,7,8,9,10,11,13,15,17,19,23,27,31,35,43,51
		dw 59,67,83,99,115,131,163,195,227,258,0,0
cplext		dw 0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5
		dw 5,5,5,0,99,99
cpdist		dw 1,2,3,4,5,7,9,13,17,25,33,49,65,97,129,193,257
		dw 385,513,769,1025,1537,2049,3073,4097,6145,8193
		dw 12289,16385,24577
cpdext		dw 0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9
		dw 10,10,11,11,12,12,13,13
zlbits		dd 9
zdbits		dd 6
cplen2		dw 2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17
		dw 18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34
		dw 35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51
		dw 52,53,54,55,56,57,58,59,60,61,62,63,64,65
cplen3		dw 3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18
		dw 19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35
		dw 36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52
		dw 53,54,55,56,57,58,59,60,61,62,63,64,65,66
exextra		dw 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		dw 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		dw 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		dw 8
cpdist4		dw 1,65,129,193,257,321,385,449,513,577,641,705
		dw 769,833,897,961,1025,1089,1153,1217,1281,1345,1409,1473
		dw 1537,1601,1665,1729,1793,1857,1921,1985,2049,2113,2177
		dw 2241,2305,2369,2433,2497,2561,2625,2689,2753,2817,2881
		dw 2945,3009,3073,3137,3201,3265,3329,3393,3457,3521,3585
		dw 3649,3713,3777,3841,3905,3969,4033
cpdist8		dw 1,129,257,385,513,641,769,897,1025,1153,1281
		dw 1409,1537,1665,1793,1921,2049,2177,2305,2433,2561,2689
		dw 2817,2945,3073,3201,3329,3457,3585,3713,3841,3969,4097
		dw 4225,4353,4481,4609,4737,4865,4993,5121,5249,5377,5505
		dw 5633,5761,5889,6017,6145,6273,6401,6529,6657,6785,6913
		dw 7041,7169,7297,7425,7553,7681,7809,7937,8065
		ALIGN	4
bmask		dd 00000000h,00000001h,00000003h,00000007h
		dd 0000000Fh,0000001Fh,0000003Fh,0000007Fh
		dd 000000FFh,000001FFh,000003FFh,000007FFh
		dd 00000FFFh,00001FFFh,00003FFFh,00007FFFh
		dd 0000FFFFh
bk		dd 0
bb		dd 0

	.code

	OPTION	PROC: PRIVATE

;-------------------------------------------------------------------------
; Inflate and Explode
;-------------------------------------------------------------------------

getbits PROC
	mov	ecx,eax
	cmp	bk,eax		; AL = count
	jb	@F
	mov	eax,bmask[eax*4]
	and	eax,bb		; bits to EAX
	test	ecx,ecx		; set ZF flag
	ret
@@:				; add a byte to bb
	mov	eax,STDI.ios_i
	cmp	eax,STDI.ios_c
	je	read
	inc	STDI.ios_i
	add	eax,STDI.ios_bp
	movzx	eax,BYTE PTR [eax]
	push	ecx
	mov	cl,BYTE PTR bk
	shl	eax,cl
	or	bb,eax
	add	bk,8
	pop	eax
	jmp	getbits
read:
	push	ecx
	ioread( addr STDI )
	pop	ecx
	jnz	@B
	xor	eax,eax
	ret
getbits ENDP

;
; Free the malloc'ed tables built by huft_build(), which makes a linked
; list of the tables it made, with the links in a dummy first entry of
; each table.
;
huft_free PROC huft
	mov	eax,huft
@@:
	test	eax,eax
	jz	@F
	sub	eax,SIZE HUFT
	free  ( eax )
	mov	eax,[eax].HUFT.t
	jmp	@B
@@:
	ret
huft_free ENDP

huft_build PROC USES esi edi ebx \
	b,			; code lengths in bits (all assumed <= BMAX)
	n,			; number of codes (assumed <= N_MAX)
	s,			; number of simple-valued codes (0..s-1)
	d,			; list of base values for non-simple codes
	e,			; list of extra bits for non-simple codes
	t,			; result: starting table
	m			; maximum lookup bits, returns actual

  local z,			; number of entries in current table
	y,			; number of dummy codes added
	w,			; bits before this table == (l * h)
	p,			; pointer into c[], b[], or v[]
	l,			; stack of bits per table
	k,			; number of bits in current code
	i,			; counter, current code
	g,			; maximum code length
	el,			; length of EOB code (value 256)
	a,			; counter for codes of length k
	q,			; points to current table
	r:HUFT,			; table entry for structure assignment
	x[BMAX+1]:WORD,		; bit offsets, then code stack
	lx[BMAX+1]:WORD,	; memory for l[-1..BMAX-1]
	_c[BMAX+1]:WORD,	; bit length count table
	u[BMAX]:PTR HUFT,	; table stack
	v[N_MAX]:WORD		; values in order of bit length

	mov	ecx,ebp
	lea	edi,v
	sub	ecx,edi
	sub	eax,eax
	rep	stosb
	;--------------------------------------------------------------------
	; Generate counts for each bit length
	;--------------------------------------------------------------------
	lea	eax,lx[2]
	mov	l,eax
	mov	ecx,n
	mov	edi,b
	mov	eax,BMAX	; set length of EOB code, if any
	cmp	ecx,256
	jbe	@F
	mov	ax,[edi+512]
@@:
	mov	el,eax
	xor	eax,eax
	lea	edx,_c
@@:
	mov	ax,[edi]
	add	edi,2
	inc	WORD PTR [edx+eax*2]
	dec	ecx
	jnz	@B
@@:
	mov	eax,n
	cmp	[edx],ax
	jne	@F
	xor	eax,eax		; null input -- all zero length codes
	mov	edx,t
	mov	[edx],eax
	mov	[edx+4],ax
	mov	edx,m
	mov	[edx],eax
	jmp	toend
@@:
	;--------------------------------------------------------------------
	; Find minimum and maximum length, bound *m by those
	;--------------------------------------------------------------------
	mov	edi,1
	xor	eax,eax
@@:
	cmp	edi,BMAX
	ja	@F
	cmp	[edx+edi*2],ax
	jne	@F
	inc	edi
	jmp	@B
@@:
	mov	k,edi		; minimum code length
	mov	eax,m
	cmp	[eax],edi
	jnb	@F
	mov	[eax],edi
@@:
	mov	ecx,BMAX
	xor	eax,eax
@@:
	cmp	[edx+ecx*2],ax
	jne	@F
	dec	ecx
	jnz	@B
@@:
	mov	g,ecx		; maximum code length
	mov	eax,m
	cmp	[eax],ecx
	jna	@F
	mov	[eax],ecx
@@:
	;--------------------------------------------------------------------
	; Adjust last length count to fill out codes, if needed
	;--------------------------------------------------------------------
	mov	esi,ecx
	mov	ecx,edi
	mov	eax,1
	shl	eax,cl
	mov	ecx,eax
@@:
	cmp	edi,esi
	jnb	@F
	sub	cx,[edx+edi*2]
	jl	erzip		; bad input: more codes than bits
	add	ecx,ecx
	inc	edi
	jmp	@B
@@:
	lea	ebx,[edx+edi*2]
	sub	cx,[ebx]
	jl	erzip
	add	[ebx],cx
	mov	y,ecx
	;--------------------------------------------------------------------
	; Generate starting offsets into the value table for each length
	;--------------------------------------------------------------------
	xor	eax,eax
	lea	ebx,x[2]
	mov	[ebx],ax
	lea	edi,[edx+2]
	dec	esi		; i == g from above
	jz	l1
@@:
	add	ax,[edi]
	add	edi,2
	add	ebx,2
	mov	[ebx],ax
	dec	esi
	jnz	@B
l1:
	;--------------------------------------------------------------------
	; Make a table of values in order of bit lengths
	;--------------------------------------------------------------------
	xor	ecx,ecx
	mov	esi,b
	lea	ebx,x
	lea	edi,v
l2:
	movzx	eax,WORD PTR [esi]
	add	esi,2
	test	eax,eax
	jz	@F
	lea	edx,[ebx+eax*2]
	mov	ax,[edx]
	inc	WORD PTR [edx]
	mov	[edi+eax*2],cx
@@:
	inc	ecx
	cmp	ecx,n
	jb	l2
	;--------------------------------------------------------------------
	; Generate the Huffman codes and for each, make the table entries
	;--------------------------------------------------------------------
	xor	eax,eax
	mov	i,eax
	mov	x,ax
	mov	lx,ax
	mov	esi,-1
	lea	eax,v
	mov	p,eax
	jmp	loop_1
erzip:
	mov	eax,ER_ZIP
	jmp	toend
	;--------------------------------------------------------------------
	; compute minimum size table less than or equal to *m bits
	;--------------------------------------------------------------------
compute_table:
	mov	w,eax
	inc	esi
	mov	eax,g
	sub	eax,w
	mov	z,eax
	mov	edx,m
	mov	edx,[edx]
	cmp	eax,edx
	jna	@F
	mov	eax,edx
	mov	z,eax
@@:
	mov	eax,k
	sub	eax,w
	mov	edi,eax
	mov	ecx,eax
	mov	eax,1
	shl	eax,cl
	mov	ecx,eax
	mov	edx,a
	inc	edx
	cmp	eax,edx
	jna	@F
	sub	ecx,edx		; too few codes for k-w bit table
	mov	eax,k		; deduct codes from patterns left
	lea	ebx,_c[eax*2]
l3:
	mov	eax,z
	inc	edi
	cmp	di,ax
	jae	@F
	add	ecx,ecx
	mov	eax,ecx
	add	ebx,2
	cmp	ax,[ebx]
	jbe	@F
	movzx	eax,WORD PTR [ebx]
	sub	ecx,eax
	jmp	l3
@@:
	mov	edx,el
	mov	eax,w
	add	eax,edi
	cmp	eax,edx
	jna	@F
	mov	eax,edx
	cmp	w,eax
	jnb	@F
	sub	eax,w
	mov	edi,eax		; make EOB code end at table
@@:
	mov	eax,1
	mov	ecx,edi
	shl	eax,cl
	mov	z,eax		; table entries for j-bit table
	mov	edx,l
	mov	[edx+esi*2],di	; set table size in stack
	inc	eax
	shl	eax,3
	malloc( eax )
	jnz	link
	test	esi,esi
	jz	@F
	huft_free( u )
@@:
	mov	eax,ER_MEM
	jmp	toend
link:
	;--------------------------------------------------------------------
	; link to list for huft_free()
	;--------------------------------------------------------------------
	mov	ebx,t
	add	eax,SIZE HUFT
	mov	q,eax
	mov	[ebx],eax
	sub	eax,SIZE HUFT - 2
	mov	t,eax
	xor	ebx,ebx
	mov	[eax],ebx
	lea	ebx,u[esi*4]
	mov	eax,q
	mov	[ebx],eax
	mov	eax,esi
	test	eax,eax
	jz	loop_3		; connect to last table, if there is one
	add	eax,eax
	lea	ebx,x		; save patteen for backing up
	mov	edx,i
	mov	[ebx+eax],dx
	mov	ebx,l		; bits to dump before this table
	movzx	ecx,WORD PTR [ebx+eax-2]
	mov	r.b,cl		; bits in this table
	mov	ebx,eax		;
	lea	eax,[edi+16]
	mov	r.e,al
	mov	eax,q		; pointer to this table
	mov	r.t,eax
	mov	eax,w
	sub	eax,ecx
	mov	edx,eax
	mov	eax,w
	mov	eax,bmask[eax*4]
	mov	ecx,i
	and	ecx,eax
	mov	eax,ecx
	mov	ecx,edx
	shr	eax,cl
	shl	eax,3
	mov	edx,eax
	mov	eax,esi
	dec	eax
	mov	eax,u[eax*4]	; connect to last table
	add	eax,edx
	mov	ebx,eax
	mov	ax,WORD PTR r
	mov	[ebx],ax
	mov	eax,r.t
	mov	[ebx].HUFT.t,eax
	;-----------------------------------------------------------
	; here i is the Huffman code of length k bits for value *p
	; make tables up to required level
	;-----------------------------------------------------------
loop_3:
	mov	eax,l
	movzx	eax,WORD PTR [eax+esi*2]
	add	eax,w
	cmp	k,eax
	jg	compute_table
	mov	eax,k		; set up table entry in r
	sub	eax,w
	mov	r.b,al
	mov	eax,n
	lea	eax,v[eax*2]
	mov	ebx,p
	cmp	ebx,eax
	jb	@F
	mov	r.e,99		; out of values--invalid code
	jmp	l5
@@:
	movzx	eax,WORD PTR [ebx]
	add	p,2
	cmp	eax,s
	jnb	@F
	mov	r.e,16
	cmp	eax,256		; 256 is end-of-block code
	jb	l4
	mov	r.e,15
	jmp	l4
@@:
	sub	eax,s
	mov	ebx,e
	mov	dl,[ebx+eax*2]
	mov	r.e,dl
	mov	ebx,d
	mov	ax,[ebx+eax*2]
l4:
	mov	r.n,ax
l5:
	mov	ecx,k		; fill code-like entries with r
	sub	ecx,w
	mov	eax,1
	shl	eax,cl
	mov	edi,eax
	mov	ecx,w
	mov	eax,i
	shr	eax,cl
	mov	ecx,eax
	mov	ebx,q
@@:
	cmp	ecx,z
	jnb	@F
	mov	ax,WORD PTR r
	mov	[ebx+ecx*8],ax
	mov	eax,r.t
	mov	[ebx+ecx*8].HUFT.t,eax
	add	ecx,edi
	jmp	@B
@@:
	mov	ecx,k		; backwards increment the k-bit code i
	dec	ecx
	mov	eax,1
	shl	eax,cl
	mov	ecx,eax
	mov	edi,i
@@:
	test	edi,ecx
	jz	@F
	xor	edi,ecx
	shr	ecx,1
	jmp	@B
@@:
	xor	edi,ecx
	mov	i,edi
@@:				; backup over finished tables
	mov	eax,w
	mov	eax,bmask[eax*4]
	mov	edx,edi
	and	edx,eax
	lea	eax,x
	cmp	dx,[eax+esi*2]
	je	loop_2
	dec	esi		; don't need to update q
	mov	eax,l
	movzx	eax,WORD PTR [eax+esi*2]
	sub	w,eax
	jmp	@B
loop_2:
	mov	eax,a
	dec	a
	test	ax,ax
	jnz	loop_3
	inc	k
loop_1:
	mov	eax,k
	cmp	eax,g
	jg	@F
	lea	edx,_c
	movzx	eax,WORD PTR [edx+eax*2]
	mov	a,eax
	jmp	loop_2
@@:
	mov	eax,l
	movzx	eax,WORD PTR [eax]
	mov	edx,m
	mov	[edx],eax	; return actual size of base table
	mov	eax,1		; Return true (1) --warning error--
	cmp	y,0
	je	@F
	cmp	g,eax
	jne	toend
@@:
	dec	eax		; if we were given an incomplete table
toend:
	ret
huft_build ENDP

;************** Explode an imploded compressed stream

; Get the bit lengths for a code representation from the compressed
; stream. If gettree() returns 4, then there is an error in the data.
; Otherwise zero is returned.

ex_b	equ [ebp-04]
ex_io	equ [ebp-08]
ex_s	equ [ebp-12]
ex_bd	equ [ebp-16]
ex_bl	equ [ebp-20]
ex_bb	equ [ebp-24]
ex_td	equ [ebp-28]
ex_tl	equ [ebp-32]
ex_tb	equ [ebp-36]
ex_l	equ [ebp-548]

get_tree PROC
	mov	edi,eax
	call	ogetc
	inc	eax
	push	eax
	xor	esi,esi
lupe:
	call	ogetc
	mov	edx,eax
	and	eax,000Fh
	mov	ecx,eax
	inc	ecx
	and	edx,00F0h
	shr	edx,4
	inc	edx
	mov	eax,edx
	add	eax,esi
	cmp	eax,edi
	ja	e2
	lea	eax,ex_l
@@:
	mov	[eax+esi*2],cx
	inc	esi
	dec	edx
	jnz	@B
	pop	eax
	dec	eax
	jz	e1
	push	eax
	jmp	lupe
e1:
	cmp	esi,edi
	jne	toend
	ret
e2:
	pop	eax
toend:
	mov	eax,4
	test	eax,eax
	ret
get_tree ENDP

explode_init PROC
	xor	eax,eax
	mov	bk,eax
	mov	bb,eax
	mov	ex_io,eax
	mov	eax,zip_local.lz_fsize
	mov	ex_s,eax
	ret
explode_init ENDP

decode_huft PROC
	mov	edx,bmask[eax*4]
	call	getbits
lup:
	not	eax
	and	eax,edx
	shl	eax,3
	add	ebx,eax
	mov	cl,[ebx].HUFT.b
	sub	BYTE PTR bk,cl
	shr	bb,cl
	movzx	eax,[ebx].HUFT.e
	mov	esi,eax
	mov	al,0
	cmp	esi,16
	jna	toend
	inc	eax
	cmp	esi,99
	je	toend
	sub	esi,16
	mov	eax,esi
	mov	edx,bmask[eax*4]
	call	getbits
	mov	ebx,[ebx].HUFT.t
	jmp	lup
toend:
	test	eax,eax
	ret
decode_huft ENDP

explode_docopy PROC
	mov	eax,ex_b
	call	getbits
	sub	BYTE PTR bk,cl
	shr	bb,cl
	mov	edi,eax
	mov	ebx,ex_td
	mov	eax,ex_bd
	call	decode_huft
	jnz	toend
	movzx	edx,[ebx].HUFT.n
	mov	eax,STDO.ios_i
	sub	eax,edi
	sub	eax,edx
	mov	edi,eax
	mov	eax,ex_bl
	mov	ebx,ex_tl
	call	decode_huft
	jnz	toend
	mov	eax,esi
	movzx	esi,[ebx].HUFT.n
	test	eax,eax
	jz	@F
	mov	eax,8
	call	getbits
	sub	BYTE PTR bk,cl
	shr	bb,cl
	add	esi,eax
@@:
	xor	eax,eax
	mov	edx,ex_s
	mov	ex_s,eax
	mov	eax,esi
	cmp	edx,eax
	jbe	l1
	sub	edx,eax
	mov	ex_s,edx
l1:
	and	edi,OSIZE-1
	mov	eax,edi
	cmp	eax,STDO.ios_i
	ja	@F
	mov	eax,STDO.ios_i
@@:
	mov	ecx,OSIZE
	sub	ecx,eax
	cmp	ecx,esi
	jb	@F
	mov	ecx,esi
@@:
	sub	esi,ecx
	mov	eax,STDO.ios_i
	add	STDO.ios_i,ecx
	push	esi
	mov	esi,edi
	add	edi,ecx
	push	edi
	mov	ebx,STDO.ios_bp
	mov	edi,ebx
	add	edi,eax
	add	ebx,esi
	cmp	eax,esi
	mov	esi,ebx
	jbe	l4
l2:
	rep	movsb
l3:
	pop	edi
	pop	esi
	cmp	STDO.ios_i,OSIZE
	jae	flush
lup:
	test	esi,esi
	jnz	l1
	sub	eax,eax
toend:
	ret
l4:
	mov	al,ex_io
	test	al,al
	jnz	l2
	rep	stosb
	jmp	l3
flush:
	ioflush( addr STDO )
	mov	ex_io,al
	jnz	lup
	mov	eax,ER_DISK
	ret
explode_docopy ENDP

; Decompress the imploded data using coded literals and a sliding
; window (of size 2^(6+bdl) bytes).

explode_lit PROC
	call	explode_init
lup:
	mov	eax,ex_s
	test	eax,eax
	jz	explode_flush
	mov	eax,1
	call	getbits
	sub	BYTE PTR bk,cl
	shr	bb,cl
	test	al,al
	jz	docopy
	dec	DWORD PTR ex_s
	mov	ebx,ex_tb
	mov	eax,ex_bb
	call	decode_huft
	jnz	toend
	mov	ax,[ebx].HUFT.n
	call	oputc
	jz	explode_eof
	cmp	eax,STDO.ios_i
	jbe	lup
	mov	ex_io,al
	jmp	lup
docopy:
	call	explode_docopy
	test	eax,eax
	jz	lup
toend:
	ret
explode_lit ENDP

explode_flush PROC
	ioflush( addr STDO )
	dec	eax
	ret
explode_flush ENDP

explode_eof PROC  ; Out of space..
	dec	eax
	ret
explode_eof ENDP

; Decompress the imploded data using uncoded literals and a sliding
; window (of size 2^(6+bdl) bytes).

explode_nolit PROC
	call	explode_init
lup:
	mov	eax,ex_s
	test	eax,eax
	jz	explode_flush
	mov	eax,1
	call	getbits
	sub	BYTE PTR bk,cl
	shr	bb,cl
	test	al,al
	jz	docopy
	dec	DWORD PTR ex_s
	mov	eax,8
	call	getbits
	sub	BYTE PTR bk,cl
	shr	bb,cl
	call	oputc
	jz	explode_eof
	cmp	eax,STDO.ios_i
	jbe	lup
	mov	ex_io,al
	jmp	lup
docopy:
	call	explode_docopy
	test	eax,eax
	jz	lup
	ret
explode_nolit ENDP

;************** Decompress the codes in a compressed block

inflatecode PROC
	call	getbits
	lea	ebx,[ebx+eax*8]
	movzx	eax,[ebx].HUFT.e
	mov	esi,eax
	cmp	al,16
	ja	@F
	mov	cl,[ebx].HUFT.b
	sub	BYTE PTR bk,cl
	shr	bb,cl
	sub	eax,eax
	ret
@@:
	cmp	al,99
	je	@F
	mov	cl,[ebx].HUFT.b
	sub	BYTE PTR bk,cl
	shr	bb,cl
	sub	esi,16
	mov	eax,esi
	call	getbits
	mov	ebx,[ebx].HUFT.t
	lea	ebx,[ebx+eax*8]
	movzx	eax,[ebx].HUFT.e
	mov	esi,eax
	cmp	al,16
	ja	@B
	mov	cl,[ebx].HUFT.b
	sub	BYTE PTR bk,cl
	shr	bb,cl
	xor	eax,eax
@@:
	test	eax,eax
	ret
inflatecode ENDP

inflate_codes PROC USES esi edi tl, td, wl, wd
	;
	; do until end of block
	;
continue:
	mov	ebx,tl
	mov	eax,wl
	call	inflatecode
	jnz	toend
	cmp	esi,15
	je	toend
	cmp	esi,16
	jne	@F
	mov	ax,[ebx].HUFT.n
	call	oputc
	jnz	continue
	jmp	disk_full
@@:
	mov	eax,esi
	call	getbits
	sub	BYTE PTR bk,cl
	shr	bb,cl
	add	ax,[ebx].HUFT.n
	mov	edi,eax
	mov	ebx,td
	mov	eax,wd
	call	inflatecode
	jnz	toend
	movzx	eax,[ebx].HUFT.n
	push	eax
	mov	eax,esi
	call	getbits
	sub	BYTE PTR bk,cl
	shr	bb,cl
	mov	edx,eax
	mov	eax,STDO.ios_i
	pop	ebx
	sub	eax,ebx
	sub	eax,edx
	mov	ebx,eax
while_1:
	and	ebx,OSIZE-1
	mov	ecx,OSIZE
	mov	eax,ebx
	cmp	eax,STDO.ios_i
	ja	@F
	mov	eax,STDO.ios_i
@@:
	sub	ecx,eax
	cmp	ecx,edi
	jbe	@F
	mov	ecx,edi
@@:
	sub	edi,ecx
	mov	eax,STDO.ios_i
	add	STDO.ios_i,ecx
	mov	edx,edi
	mov	edi,STDO.ios_bp
	mov	esi,STDO.ios_bp
	add	edi,eax
	add	esi,ebx
	add	ebx,ecx
	add	eax,ecx
	rep	movsb
	mov	edi,edx
	cmp	eax,OSIZE
	jae	flush_codes
untildiz:
	test	edi,edi
	jnz	while_1
	jmp	continue
toend:
	ret
flush_codes:
	ioflush( addr STDO )
	jnz	untildiz
disk_full:
	mov	eax,ER_DISK
	jmp	toend
inflate_codes ENDP

;************** Decompress an inflated type 1 (fixed Huffman codes) block

inflate_fixed PROC USES edi

  local l[288]:WORD		; length list for huft_build

	lea	edi,l
	xor	eax,eax
	cmp	fixed_tl,eax
	jne	decompress

	mov	ebx,edi
	mov	ecx,144		; literal table
	mov	eax,8
	rep	stosw
	mov	ecx,112
	mov	eax,9
	rep	stosw
	mov	ecx,24
	mov	eax,7
	rep	stosw		; make a complete, but wrong code set
	mov	ecx,8
	mov	eax,8
	rep	stosw
	mov	edi,ebx
	mov	fixed_bl,7
	huft_build( edi, 288, 257, addr cplens, addr cplext, addr fixed_tl, addr fixed_bl )
	test	eax,eax
	jnz	error1
	mov	edx,edi		; make an incomplete code set
	mov	ecx,30
	mov	eax,5
	rep	stosw
	mov	fixed_bd,5
	mov	edi,edx
	huft_build( edi, 30, 0, addr cpdist, addr cpdext, addr fixed_td, addr fixed_bd )
	test	eax,eax
	jnz	error2

decompress:
	;
	; decompress until an end-of-block code
	;
	inflate_codes( fixed_tl, fixed_td, fixed_bl, fixed_bd )
	test	eax,eax
	jz	toend
	mov	eax,1
toend:
	ret
error1:
	mov	fixed_tl,0
	jmp	toend
error2:
	cmp	eax,1
	je	decompress
	push	eax
	huft_free( fixed_tl )
	mov	fixed_tl,0
	pop	eax
	jmp	toend
inflate_fixed ENDP

;************** Decompress an inflated type 2 (dynamic Huffman codes) block

inflate_dynamic PROC USES esi edi

  local nd,		; number of distance codes
	nl,		; number of literal/length codes
	nb,		; number of bit length codes
	tl,		; literal/length code table
	td,		; distance code table
	wl,		; lookup bits for tl (bl)
	wd,		; lookup bits for td (bd)
	n,		; number of lengths to get
	ll[320]:WORD	; literal/length and distance code lengths

	mov	eax,5
	call	getbits
	sub	BYTE PTR bk,cl
	shr	bb,cl
	add	eax,257
	mov	nl,eax		; number of literal/length codes
	mov	eax,5
	call	getbits
	sub	BYTE PTR bk,cl
	shr	bb,cl
	inc	eax
	mov	nd,eax		; number of distance codes
	mov	eax,4
	call	getbits
	sub	BYTE PTR bk,cl
	shr	bb,cl
	add	eax,4
	mov	nb,eax		; number of bit length codes

	cmp	nl,288		; PKZIP_BUG_WORKAROUND
	ja	return_1
	cmp	nd,32
	ja	return_1

	xor	esi,esi
	lea	edi,ll
@@:
	cmp	esi,nb
	jnb	@F
	mov	eax,3
	call	getbits
	sub	BYTE PTR bk,cl
	shr	bb,cl
	movzx	edx,border[esi*2]
	mov	[edi+edx*2],ax
	inc	esi
	jmp	@B
@@:
	cmp	esi,19
	jnb	@F
	movzx	eax,border[esi*2]
	mov	WORD PTR [edi+eax*2],0
	inc	esi
	jmp	@B
@@:
	mov	wl,7
	huft_build( edi, 19, 19, 0, 0, addr tl, addr wl )
	cmp	wl,0
	je	free_1		; no bit lengths
	test	eax,eax
	jnz	free?		; incomplete code set
	mov	eax,nl
	add	eax,nd
	mov	n,eax
	xor	esi,esi
	xor	edi,edi
lupe:
	cmp	esi,n
	jnb	break

	mov	eax,tl
	mov	td,eax
	mov	eax,wl
	call	getbits
	shl	eax,3
	add	td,eax
	mov	ebx,td
	mov	cl,[ebx].HUFT.b
	sub	BYTE PTR bk,cl
	shr	bb,cl
	movzx	eax,[ebx].HUFT.n

	cmp	eax,16
	ja	l1
	jb	l2

	mov	eax,2
	call	getbits
	sub	BYTE PTR bk,cl
	shr	bb,cl
	add	eax,3
	mov	edx,eax
	add	eax,esi
	cmp	eax,n
	ja	return_1
	jmp	while_edx
l1:
	cmp	eax,17
	je	@F
	mov	eax,7
	call	getbits
	sub	BYTE PTR bk,cl
	shr	bb,cl
	add	eax,11
	jmp	@2
@@:
	mov	eax,3
	call	getbits
	sub	BYTE PTR bk,cl
	shr	bb,cl
	add	eax,3
@2:
	mov	edx,eax
	add	eax,esi
	cmp	eax,n
	ja	return_1
	xor	edi,edi
while_edx:
	test	edx,edx
	jz	lupe
	lea	eax,ll
@@:
	mov	[eax+esi*2],di
	inc	esi
	dec	edx
	jnz	@B
	jmp	lupe
l2:
	mov	edi,eax
	lea	eax,ll
	mov	[eax+esi*2],di
	inc	esi
	jmp	lupe
break:
	huft_free( tl )
	mov	eax,zlbits
	mov	wl,eax
	huft_build( addr ll, nl, 257, addr cplens, addr cplext, addr tl, addr wl )
	cmp	wl,0
	je	free_1
	test	eax,eax
	jnz	free?
	mov	eax,zdbits
	mov	wd,eax
	lea	edx,ll
	add	edx,nl
	add	edx,nl
	huft_build( edx, nd, 0, addr cpdist, addr cpdext, addr td, addr wd )
	cmp	wd,0
	jne	@F
	cmp	nl,257
	jbe	free_1
@@:
	cmp	eax,1
	jne	@F
	xor	eax,eax
@@:
	test	eax,eax
	jnz	freehuft
	inflate_codes( tl, td, wl, wd )
	push	eax
	huft_free( td )
	pop	eax
	test	eax,eax
	jz	freehuft
free_1:
	mov	eax,1
freehuft:
	push	eax
	huft_free( tl )
	pop	eax
toend:
	ret
return_1:
	mov	eax,1
	jmp	toend
free?:
	cmp	eax,1
	je	freehuft
	jmp	toend
inflate_dynamic ENDP

;****** Decompress an inflated type 0 (stored) block.

inflate_stored PROC USES esi
	mov	bk,0
	mov	eax,16
	call	getbits
	sub	BYTE PTR bk,cl
	shr	bb,cl
	mov	esi,eax ; number of bytes in block
	mov	eax,16
	call	getbits
	sub	BYTE PTR bk,cl
	shr	bb,cl
	not	ax
	cmp	ax,si
	jne	error_data
	test	ax,ax
	jz	break
      while_rsi:	; read and output the compressed data
	mov	eax,8
	call	getbits
	jz	error_data
	sub	BYTE PTR bk,cl
	shr	bb,cl
	call	oputc
	jz	error_disk
	dec	esi
	jnz	while_rsi
      break:
	xor	eax,eax
      @@:
	ret
error_data:
	mov	eax,1	; error in compressed data
	jmp	@B
error_disk:
	mov	eax,ER_DISK
	jmp	@B
inflate_stored ENDP

;-------------------------------------------------------------------------
	OPTION	PROC: PUBLIC
;-------------------------------------------------------------------------

zip_explode PROC USES esi edi ebx

  local exb:  DWORD	; -04
  local exio: DWORD	; -08
  local exs:  DWORD	; -12
  local exbd: DWORD	; -16
  local exbl: DWORD	; -20
  local exbb: DWORD	; -24
  local extd: DWORD	; -28
  local extl: DWORD	; -32
  local extb: DWORD	; -36
  local exl[256]: WORD	; -548

	mov	eax,7
	mov	exbl,eax
	cmp	zip_local.lz_csize,200000
	jbe	@F
	inc	eax
@@:
	mov	exbd,eax
	xor	eax,eax
	mov	extb,eax
	test	zip_local.lz_flag,4
	jz	l1

	mov	exbb,9
	mov	eax,256
	call	get_tree
	test	eax,eax
	jnz	toend

	huft_build( addr exl, 256, 256, 0, 0, addr extb, addr exbb )
	test	eax,eax
	jz	@F
	cmp	eax,1
	je	freetb
	jmp	toend
@@:
	mov	eax,64
	call	get_tree
	test	eax,eax
	jnz	freetb
	mov	edx,offset cplen3
	jmp	l2
l1:
	mov	eax,64
	call	get_tree
	test	eax,eax
	jnz	toend
	mov	edx,offset cplen2
l2:
	huft_build( addr exl, 64, 0, edx, addr exextra, addr extl, addr exbl )
	test	eax,eax
	jz	@F
	cmp	eax,1
	je	freetl
	jmp	freetb
@@:
	mov	eax,64
	call	get_tree
	test	eax,eax
	jnz	freetl

	mov	exb,6
	mov	edx,offset cpdist4
	test	zip_local.lz_flag,2
	jz	@F
	mov	edx,offset cpdist8
	inc	exb
@@:
	huft_build( addr exl, 64, 0, edx, addr exextra, addr extd, addr exbd )
	test	eax,eax
	jz	@F
	cmp	eax,1
	je	freetd
	jmp	freetb
@@:
	cmp	extb,eax
	jne	@F
	call	explode_nolit
	jmp	freetd
@@:
	call	explode_lit
freetd:
	push	eax
	huft_free( extd )
	pop	eax
freetl:
	push	eax
	huft_free( extl )
	pop	eax
freetb:
	push	eax
	huft_free( extb )
	pop	eax
toend:
	ret
zip_explode ENDP

zip_inflate PROC USES esi edi ebx
	xor	eax,eax
	mov	bb,eax
	mov	bk,eax
while_0:
	mov	eax,1
	call	getbits
	sub	BYTE PTR bk,cl
	shr	bb,cl
	mov	edi,eax
	mov	eax,2
	call	getbits
	sub	BYTE PTR bk,cl
	shr	bb,cl
	test	eax,eax
	je	stored
	cmp	eax,1
	je	fixed
	cmp	eax,2
	mov	eax,ER_ZIP
	jne	continue
dynamic:
	call	inflate_dynamic
continue:
	mov	esi,eax
	test	eax,eax
	jne	@F
	test	edi,edi
	jz	while_0
	ioflush( addr STDO )
	jnz	@F
	mov	esi,ER_USERABORT
	test	STDO.ios_flag,IO_ERROR
	jz	@F
	mov	esi,ER_DISK
@@:
	xor	eax,eax
	cmp	fixed_tl,eax
	je	@F
	huft_free( fixed_td )
	huft_free( fixed_tl )
	xor	eax,eax
	mov	fixed_td,eax
	mov	fixed_tl,eax
@@:
	mov	eax,esi
toend:
	ret
fixed:
	call	inflate_fixed
	jmp	continue
stored:
	call	inflate_stored
	jmp	continue
zip_inflate ENDP

	END
