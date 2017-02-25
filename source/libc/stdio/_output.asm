include stdio.inc
include limits.inc

PUBLIC		output_flush
PUBLIC		output_proctab

BUFFERSIZE	equ 512		; ANSI-specified minimum is 509

FLAG_SIGN	equ 0001h	; put plus or minus in front
FLAG_SIGNSP	equ 0002h	; put space or minus in front
FLAG_LEFT	equ 0004h	; left justify
FLAG_LEADZERO	equ 0008h	; pad with leading zeros
FLAG_I64	equ 0010h	; 64-bit value given
FLAG_SHORT	equ 0020h	; short value given
FLAG_SIGNED	equ 0040h	; signed data given
FLAG_ALTERNATE	equ 0080h	; alternate form requested
FLAG_NEGATIVE	equ 0100h	; value is negative
FLAG_FORCEOCTAL equ 0200h	; force leading '0' for octals
FLAG_LONG	equ 0400h	; long value given
FLAG_LONGDOUBLE equ 0800h	; long double

	.data

cl_table	db 06h, 00h, 00h, 06h, 00h, 01h, 00h, 00h ;  !"#$%&' 20 00
		db 10h, 00h, 03h, 06h, 00h, 06h, 02h, 10h ; ()*+,-./ 28 08
		db 04h, 45h, 45h, 45h, 05h, 05h, 05h, 05h ; 01234567 30 10
		db 05h, 35h, 30h, 00h, 50h, 00h, 00h, 00h ; 89:;<=>? 38 18
		db 00h, 20h, 28h, 38h, 50h, 58h, 07h, 08h ; @ABCDEFG 40 20
		db 00h, 37h, 30h, 30h, 57h, 50h, 07h, 00h ; HIJKLMNO 48 28
		db 00h, 20h, 20h, 08h, 00h, 00h, 00h, 00h ; PQRSTUVW 50 30
		db 08h, 60h, 60h, 60h, 60h, 60h, 60h, 00h ; XYZ[\]^_ 58 38
		db 00h, 70h, 78h, 78h, 78h, 78h, 78h, 08h ; `abcdefg 60 40
		db 07h, 08h, 00h, 00h, 07h, 00h, 08h, 08h ; hijklmno 68 48
		db 08h, 00h, 00h, 08h, 00h, 08h, 00h, 00h ; pqrstuvw 70 50
		db 08h					  ; xyz{|}~  78 58

formchar	db 'bcdefginopsuxEGX'
nullstring	db '(null)',0
output_flush	dd 0

		ALIGN	4
OPST_table	dd OPST_normal
		dd OPST_percent
		dd OPST_flag
		dd OPST_width
		dd OPST_dot
		dd OPST_precision
		dd OPST_size
		dd OPST_type

output_proctab	dd OUTPUT_b
		dd OUTPUT_c
		dd OUTPUT_d
		dd OUTPUT_e
		dd OUTPUT_e
		dd OUTPUT_e
		dd OUTPUT_d
		dd OUTPUT_n
		dd OUTPUT_o
		dd OUTPUT_p
		dd OUTPUT_s
		dd OUTPUT_u
		dd OUTPUT_x
		dd OUTPUT_eu
		dd OUTPUT_eu
		dd OUTPUT_xu

S_OUTPUT	STRUC
OP_filep	dd ?
OP_format	dd ?
OP_charsout	dd ?
OP_hexoff	dd ?
OP_state	dd ?
OP_curadix	dd ?
OP_prefix	db 2 dup(?)
OP_count	dd ?
OP_prefixlen	dd ?
OP_no_output	dd ?
OP_fldwidth	dd ?
OP_padding	dd ?
OP_text		dd ?
OP_capitalize	dd ?
OP_numeax	dd ?
OP_numedx	dd ?
OP_buffer	db BUFFERSIZE dup(?)
OP_STACK	dd ? ; [(E)BP]
OP_CSIP		dd ?
OP_ARGfile	dd ?
OP_ARGformat	dd ?
OP_arglist	dd ?
S_OUTPUT	ENDS

	.code

	OPTION	PROC:PRIVATE, SWITCH:PASCAL, SWITCH:NOTABLE
	ASSUME	ebp: PTR S_OUTPUT

output_getd:  ; Get DWORD from stack
	mov	eax,[ebp].OP_arglist
	add	[ebp].OP_arglist,4
	mov	eax,[eax]
	sub	edx,edx
	ret

output_getq:  ; Get QWORD from stack
	mov	eax,[ebp].OP_arglist
	add	[ebp].OP_arglist,8
	mov	edx,[eax+4]
	mov	eax,[eax]
	ret

OPST_percent:
	xor	eax,eax
	mov	[ebp].OP_no_output,eax
	mov	[ebp].OP_fldwidth,eax
	mov	[ebp].OP_prefixlen,eax
	mov	[ebp].OP_capitalize,eax
	mov	esi,eax ; bufferiswide (default)
	mov	edi,eax ; precision
	dec	edi
	ret

OPST_flag:
	movzx	eax,dl
	.switch eax
	  .case '+': or esi,FLAG_SIGN	   ; '+' force sign indicator
	  .case ' ': or esi,FLAG_SIGNSP	   ; ' ' force sign or space
	  .case '#': or esi,FLAG_ALTERNATE ; '#' alternate form
	  .case '-': or esi,FLAG_LEFT	   ; '-' left justify
	  .case '0': or esi,FLAG_LEADZERO  ; '0' pad with leading zeros
	.endsw
	ret

OPST_width:
	.if	dl == '*'
		call	output_getd
		mov	[ebp].OP_fldwidth,eax
		.if	SDWORD PTR eax < 0
			or	esi,4
			neg	eax
			mov	[ebp].OP_fldwidth,eax
		.endif
	.else
		movsx	eax,dl
		push	eax
		mov	eax,[ebp].OP_fldwidth
		mov	edx,10
		imul	edx
		pop	edx
		add	edx,eax
		add	edx,-48
		mov	[ebp].OP_fldwidth,edx
	.endif
	ret

OPST_dot:
	xor	edi,edi
	ret

OPST_precision:
	.if	dl == '*'
		call	output_getd
		mov	edi,eax
		.if	SDWORD PTR eax < 0
			mov	edi,-1
		.endif
	.else
		movsx	eax,dl
		push	eax
		mov	eax,edi
		mov	edx,10
		imul	edx
		pop	edx
		add	edx,eax
		add	edx,-48
		mov	edi,edx
	.endif
	ret

OPST_size:
	.switch edx
	  .case 'l':	or esi,FLAG_LONG
	  .case 'L':	or esi,FLAG_LONG or FLAG_LONGDOUBLE
	  .case 'I'
		mov	eax,[ebp].OP_format
		mov	edx,[eax]
		.if	dx == '46'
			or  esi,FLAG_I64
			add eax,2
			mov [ebp].OP_format,eax
		.endif
	.endsw
	ret

OPST_type:
	xor	eax,eax
	mov	ecx,sizeof(formchar)
	.repeat
		.if	dl == formchar[eax]
			call  output_proctab[eax*4]
			.break
		.endif
		add	eax,1
	.untilcxz
	jmp	OUTPUT

OUTPUT_e:
OUTPUT_eu:
	ret

OUTPUT_b:
	call	output_getd
	mov	ecx,32
	mov	edx,eax
	.repeat
		mov	eax,edx
		shr	eax,cl
		.break .if CARRY?
	.untilcxz
	.if	!ecx
		inc	ecx
	.endif
	mov	[ebp].OP_count,ecx
	.repeat
		sub	eax,eax
		shr	edx,1
		adc	al,'0'
		mov	[ebp].OP_buffer[ecx-1],al
	.untilcxz
	jmp	OUTPUT_LDTEXT

OUTPUT_c:
	call	output_getd
	mov	[ebp].OP_buffer,al
	mov	[ebp].OP_count,1

OUTPUT_LDTEXT:
	lea	eax,[ebp].OP_buffer
	mov	[ebp].OP_text,eax
	ret

OUTPUT_s:
	.if	!output_getd()
		lea	eax,nullstring
	.endif
	mov	[ebp].OP_text,eax
	.if	edi == -1
		mov	ecx,7FFFh
	.else
		mov	ecx,edi
	.endif
	.repeat
		.break .if BYTE PTR [eax] == 0
		inc	eax
	.untilcxz
	sub	eax,[ebp].OP_text
	mov	[ebp].OP_count,eax
	ret

OUTPUT_n:
	mov	eax,[ebp].OP_arglist
	add	[ebp].OP_arglist,4
	mov	edx,[eax-4]
	mov	eax,[ebp].OP_charsout
	mov	[edx],eax
	.if	esi & FLAG_LONG
		mov [ebp].OP_no_output,1
	.endif
	ret

OUTPUT_p:
	mov	edi,8

OUTPUT_xu:
	mov	[ebp].OP_hexoff,'A'-'9'-1
	jmp	OPCOMMONHEX

OUTPUT_x:
	mov	[ebp].OP_hexoff,'a'-'9'-1

OPCOMMONHEX:
	mov	[ebp].OP_curadix,16
	.if	esi & FLAG_ALTERNATE
		mov [ebp].OP_prefix,'0'
		mov [ebp].OP_prefix+1,'x'
		mov [ebp].OP_prefixlen,2
	.endif
	test	esi,FLAG_I64
	jnz	OUTPUT_LONGINT
	cmp	[ebp].OP_fldwidth,2
	jne	OUTPUT_SHORTINT
	call	output_getd
	and	eax,00FFh
	jmp	OUTPUT_NUMBER

OUTPUT_o:
	mov	[ebp].OP_curadix,8
	test	esi,FLAG_ALTERNATE
	jz	OUTPUT_GENINT
	or	esi,FLAG_FORCEOCTAL
	jmp	OUTPUT_GENINT

OUTPUT_d:
	or	esi,FLAG_SIGNED

OUTPUT_u:
	mov	[ebp].OP_curadix,10

OUTPUT_GENINT:
	test	esi,FLAG_I64
	jz	OUTPUT_SHORTINT

OUTPUT_LONGINT:
	call	output_getq
	jmp	OUTPUT_NUMBER

OUTPUT_SHORTINT:
	call	output_getd
	test	esi,FLAG_SIGNED
	jz	OUTPUT_NUMBER
	cmp	eax,0
	jnl	OUTPUT_NUMBER
	dec	edx

OUTPUT_NUMBER PROC
	.if	esi & FLAG_SIGNED
		test	edx,edx
		.if	SIGN?
			neg	eax
			neg	edx
			sbb	edx,0
			or	esi,FLAG_NEGATIVE
		.endif
	.endif

	mov	[ebp].OP_numeax,eax
	mov	[ebp].OP_numedx,edx

	test	edi,edi
	.if	SIGN?
		mov	edi,1
	.else
		and	esi,-9
	.endif

	.if	!eax && !edx
		mov	[ebp].OP_prefixlen,eax
	.endif

	lea	eax,[ebp].OP_buffer+512-1
	mov	[ebp].OP_text,eax
	jmp	@06
lupe:
	mov	ecx,[ebp].OP_curadix
	mov	eax,[ebp].OP_numeax
	mov	edx,[ebp].OP_numedx
	test	edx,edx
	jz	DIV00
	test	ecx,ecx
	jnz	DIV01
DIV00:
	div	ecx
	mov	ecx,edx
	xor	edx,edx
	jmp	DIV06
DIV01:
	push	esi
	push	edi
	mov	ebx,ecx
	mov	ecx,64
	xor	esi,esi
	xor	edi,edi
DIV02:
	shl	eax,1
	rcl	edx,1
	rcl	esi,1
	rcl	edi,1
	cmp	edi,0
	jb	DIV04
	ja	DIV03
	cmp	esi,ebx
	jb	DIV04
DIV03:
	sub	esi,ebx
	sbb	edi,0
	inc	eax
DIV04:
	dec	ecx
	jnz	DIV02
	mov	ebx,esi
DIV05:
	mov	ecx,ebx
	pop	edi
	pop	esi
DIV06:
	mov	[ebp].OP_numeax,eax
	mov	[ebp].OP_numedx,edx
	add	ecx,'0'
	cmp	ecx,'9'
	jng	@F
	add	ecx,[ebp].OP_hexoff
@@:
	mov	edx,[ebp].OP_text
	mov	[edx],cl
	dec	[ebp].OP_text
@06:
	mov	ecx,edi
	dec	edi
	test	ecx,ecx
	jg	lupe
	or	eax,[ebp].OP_numedx
	jnz	lupe

	lea	eax,[ebp].OP_buffer+512-1
	sub	eax,[ebp].OP_text
	mov	[ebp].OP_count,eax
	inc	[ebp].OP_text
	.if	esi & FLAG_FORCEOCTAL
		mov	edx,[ebp].OP_text
		.if	BYTE PTR [edx] != '0' || [ebp].OP_count == 0
			sub	edx,1
			mov	[ebp].OP_text,edx
			mov	BYTE PTR [edx],'0'
			inc	[ebp].OP_count
		.endif
	.endif
toend:
	ret
OUTPUT_NUMBER ENDP

OPST_normal:
	mov	al,dl

OUTPUT_PUTC PROC
	mov	edx,[ebp].OP_filep
	dec	[edx]._iobuf._cnt
	jl	flush
	inc	[edx]._iobuf._ptr
	mov	edx,[edx]._iobuf._ptr
	mov	[edx-1],al
toend:
	inc	[ebp].OP_charsout
	ret
flush:
	push	[ebp].OP_filep
	push	eax
	call	output_flush
	cmp	eax,-1
	jne	toend
	mov	[ebp].OP_charsout,eax
	ret
OUTPUT_PUTC ENDP

OUTPUT_MULTI PROC USES esi edi
	movzx	eax,al
	mov	esi,eax
	mov	edi,edx
	.while	SDWORD PTR edi > 0
		mov	eax,esi
		call	OUTPUT_PUTC
		.break .if [ebp].OP_charsout == -1
		dec	edi
	.endw
	ret
OUTPUT_MULTI ENDP

OUTPUT_STRING PROC USES esi edi
	mov	esi,ecx
	mov	edi,edx
	.while	SDWORD PTR esi > 0
		mov	al,[edi]
		call	OUTPUT_PUTC
		.break .if [ebp].OP_charsout == -1
		inc	edi
		dec	esi
	.endw
	ret
OUTPUT_STRING ENDP

OUTPUT	PROC
	xor	eax,eax
	.if	eax == [ebp].OP_no_output
		.if	esi & FLAG_SIGNED
			.if	esi & FLAG_NEGATIVE
				mov	[ebp].OP_prefix,'-'
				mov	[ebp].OP_prefixlen,1
			.elseif esi & FLAG_SIGN
				mov	[ebp].OP_prefix,43
				mov	[ebp].OP_prefixlen,1
			.elseif esi & FLAG_SIGNSP
				mov	[ebp].OP_prefix,' '
				mov	[ebp].OP_prefixlen,1
			.endif
		.endif
		mov	eax,[ebp].OP_fldwidth
		sub	eax,[ebp].OP_count
		sub	eax,[ebp].OP_prefixlen
		mov	[ebp].OP_padding,eax
		.if	!(esi & FLAG_LEFT or FLAG_LEADZERO)
			mov	edx,eax
			mov	eax,' '
			call	OUTPUT_MULTI
		.endif
		lea	edx,[ebp].OP_prefix
		mov	ecx,[ebp].OP_prefixlen
		call	OUTPUT_STRING
		.if	esi & FLAG_LEADZERO
			.if	!(esi & FLAG_LEFT)
				mov	eax,'0'
				mov	edx,[ebp].OP_padding
				call	OUTPUT_MULTI
			.endif
		.endif
		mov	ecx,[ebp].OP_count
		.if	SDWORD PTR ecx > 0
			mov	edx,[ebp].OP_text
			.while	SDWORD PTR ecx > 0
				movzx	eax,BYTE PTR [edx]
				push	edx
				push	ecx
				call	OUTPUT_PUTC
				pop	ecx
				pop	edx
				inc	edx
				dec	ecx
			.endw
		.else
			mov	edx,[ebp].OP_text
			call	OUTPUT_STRING
		.endif
		.if	esi & FLAG_LEFT
			mov	eax,' '
			mov	edx,[ebp].OP_padding
			call	OUTPUT_MULTI
		.endif
	.endif
	ret
OUTPUT	ENDP

	OPTION	PROC: PUBLIC
	ALIGN	4

_output PROC USES edx ecx esi edi ebx,
	filep:	LPFILE,
	format: LPSTR,
	args:	PVOID
local	OP:	S_OUTPUT

	mov	eax,filep
	mov	ecx,format
	mov	edx,args
	mov	OP.OP_arglist,edx
	push	ebp
	lea	ebp,OP
	mov	[ebp].OP_format,ecx
	mov	[ebp].OP_filep,eax
	sub	eax,eax
	mov	[ebp].OP_count,eax
	mov	[ebp].OP_charsout,eax
	mov	[ebp].OP_state,eax
	.repeat
		mov	eax,[ebp].OP_format
		inc	[ebp].OP_format
		movzx	eax,BYTE PTR [eax]
		mov	edx,eax
		.break .if !eax
		.break .if [ebp].OP_charsout > INT_MAX
		.if	eax >= ' ' && eax <= 'x'
			mov	al,cl_table[eax-32]
			and	eax,15
		.else
			xor	eax,eax
		.endif
		shl	eax,3
		add	eax,[ebp].OP_state
		mov	al,cl_table[eax]
		shr	eax,4
		and	eax,0Fh
		mov	[ebp].OP_state,eax
		.if	eax <= 7
			call	OPST_table[eax*4]
		.endif
	.until	0
	mov	eax,[ebp].OP_charsout
	pop	ebp
	ret
_output ENDP

	END
