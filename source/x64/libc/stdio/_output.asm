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

STATE_NORMAL	equ 0
STATE_PERCENT	equ 1
STATE_FLAGS	equ 2
STATE_WIDTH	equ 3
STATE_DOT	equ 4
STATE_PRECISION equ 5
STATE_SIZE	equ 6
STATE_TYPE	equ 7

S_OUTPUT	STRUC
OP_filep	dq ?
OP_format	dq ?
OP_charsout	dq ?
OP_hexoff	dq ?
OP_state	dq ?
OP_curadix	dq ?
OP_prefix	db 2 dup(?)
OP_count	dq ?
OP_prefixlen	dq ?
OP_no_output	dq ?
OP_fldwidth	dq ?
OP_padding	dq ?
OP_text		dq ?
OP_capitalize	dq ?
OP_number	dq ?
OP_buffer	db BUFFERSIZE dup(?)
OP_STACK	dq ? ; [(E)BP]
OP_CSIP		dq ?
OP_ARGfile	dq ?
OP_ARGformat	dq ?
OP_arglist	dq ?
S_OUTPUT	ENDS

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
		ALIGN	8
output_flush	dq 0

output_proctab	dq output_b
		dq output_c
		dq output_d
		dq output_e
		dq output_e
		dq output_e
		dq output_d
		dq output_n
		dq output_o
		dq output_p
		dq output_s
		dq output_u
		dq output_x
		dq output_eu
		dq output_eu
		dq output_xu


	.code

	OPTION	WIN64:2, STACKBASE:rsp
	ASSUME	rbp: PTR S_OUTPUT

_output PROC USES rdx rcx rsi rdi rbx rbp,
	filep:	LPFILE,
	format: LPSTR,
	args:	PVOID
local	OP:	S_OUTPUT

	lea	rbp,OP
	mov	[rbp].OP_filep,rcx
	mov	[rbp].OP_format,rdx
	mov	[rbp].OP_arglist,r8

	xor	rax,rax
	mov	[rbp].OP_count,rax
	mov	[rbp].OP_charsout,rax
	mov	[rbp].OP_state,rax

	.while	1

		mov	rax,[rbp].OP_format
		inc	[rbp].OP_format
		movzx	rax,BYTE PTR [rax]
		mov	rdx,rax

		.break .if !rax
		.break .if [rbp].OP_charsout > INT_MAX

		lea	r8,cl_table
		.if	al >= ' ' && al <= 'x'
			mov	al,[r8+rax-32]
			and	al,15
		.else
			xor	rax,rax
		.endif

		shl	rax,3
		add	rax,[rbp].OP_state
		mov	al,[r8+rax]
		shr	rax,4
		and	rax,0Fh
		mov	[rbp].OP_state,rax

		.switch al

		  .case STATE_NORMAL
			mov	al,dl
			call	output_PUTC
			.endc

		  .case STATE_PERCENT
			xor	rax,rax
			mov	[rbp].OP_no_output,rax
			mov	[rbp].OP_fldwidth,rax
			mov	[rbp].OP_prefixlen,rax
			mov	[rbp].OP_capitalize,rax
			mov	rsi,rax ; bufferiswide (default)
			mov	rdi,rax ; precision
			dec	rdi
			.endc

		  .case STATE_FLAGS
			.switch dl
			  .case '+': or esi,FLAG_SIGN	   : .endc ; '+' force sign indicator
			  .case ' ': or esi,FLAG_SIGNSP	   : .endc ; ' ' force sign or space
			  .case '#': or esi,FLAG_ALTERNATE : .endc ; '#' alternate form
			  .case '-': or esi,FLAG_LEFT	   : .endc ; '-' left justify
			  .case '0': or esi,FLAG_LEADZERO  : .endc ; '0' pad with leading zeros
			.endsw
			.endc

		  .case STATE_WIDTH
			.if	dl == '*'
				mov	rax,[rbp].OP_arglist
				add	[rbp].OP_arglist,8
				mov	rax,[rax]
				mov	[rbp].OP_fldwidth,rax
				.if	SQWORD PTR rax < 0
					or	esi,4
					neg	rax
					mov	[rbp].OP_fldwidth,rax
				.endif
			.else
				movsx	rax,dl
				push	rax
				mov	rax,[rbp].OP_fldwidth
				mov	rdx,10
				imul	rdx
				pop	rdx
				add	rdx,rax
				add	rdx,-48
				mov	[rbp].OP_fldwidth,rdx
			.endif
			.endc

		  .case STATE_DOT
			xor	edi,edi
			.endc

		  .case STATE_PRECISION
			.if	dl == '*'
				mov	rax,[rbp].OP_arglist
				add	[rbp].OP_arglist,8
				mov	rax,[rax]
				mov	edi,eax
				.if	SDWORD PTR eax < 0
					mov	edi,-1
				.endif
			.else
				movsx	rax,dl
				push	rax
				mov	rax,rdi
				mov	rdx,10
				imul	rdx
				pop	rdx
				add	rdx,rdi
				add	rdx,-48
				mov	rdi,rdx
			.endif
			.endc

		  .case STATE_SIZE
			.switch dl
			  .case 'l'
				or esi,FLAG_LONG
				.endc
			  .case 'L'
				or esi,FLAG_LONG or FLAG_LONGDOUBLE
				.endc
			  .case 'I'
				mov	rax,[rbp].OP_format
				mov	dx,[rax]
				.if	dx == '46'
					or  esi,FLAG_I64
					add rax,2
					mov [rbp].OP_format,rax
				.endif
				.endc
			.endsw
			.endc

		  .case STATE_TYPE
			lea	r8,formchar
			mov	ecx,sizeof(formchar)
			xor	rax,rax
			.repeat
				.if	dl == [r8+rax]
					lea	r8,output_proctab
					mov	rax,[r8+rax*8]
					call	rax
					.break
				.endif
				add	rax,1
			.untilcxz
			call	OUTPUT
			.endc

		.endsw
	.endw

	mov	rax,[rbp].OP_charsout
	ret
_output ENDP

output_e:
output_eu:
	ret

output_b:
	mov	rax,[rbp].OP_arglist
	add	[rbp].OP_arglist,8

	mov	rdx,[rax]
	mov	rcx,32

	.repeat
		mov	rax,rdx
		shr	rax,cl
		.break .if CARRY?
	.untilcxz
	.if	!rcx
		inc	rcx
	.endif
	mov	[rbp].OP_count,rcx
	.repeat
		sub	rax,rax
		shr	rdx,1
		adc	al,'0'
		mov	[rbp].OP_buffer[rcx-1],al
	.untilcxz
	jmp	output_LDTEXT

output_c:
	call	output_getq
	mov	[rbp].OP_buffer,al
	mov	[rbp].OP_count,1

output_LDTEXT:
	lea	rax,[rbp].OP_buffer
	mov	[rbp].OP_text,rax
	ret

output_s:
	.if	!output_getq()
		lea	rax,nullstring
	.endif
	mov	[rbp].OP_text,rax
	mov	ecx,edi
	.if	edi == -1
		mov	ecx,7FFFh
	.endif
	mov	r8,rdi
	mov	rdi,rax
	xor	rax,rax
	repnz	scasb
	mov	rax,rdi
	mov	rdi,r8
	sub	rax,[rbp].OP_text
	mov	[rbp].OP_count,rax
	ret

output_n:
	mov	rax,[rbp].OP_arglist
	add	[rbp].OP_arglist,8
	mov	rdx,[eax-8]
	mov	rax,[rbp].OP_charsout
	mov	[rdx],rax
	.if	esi & FLAG_LONG
		mov [rbp].OP_no_output,1
	.endif
	ret

output_p:
	mov	edi,8

output_xu:
	mov	[rbp].OP_hexoff,'A'-'9'-1
	jmp	OPCOMMONHEX

output_x:
	mov	[rbp].OP_hexoff,'a'-'9'-1

OPCOMMONHEX:
	mov	[rbp].OP_curadix,16
	.if	esi & FLAG_ALTERNATE
		mov [rbp].OP_prefix,'0'
		mov [rbp].OP_prefix+1,'x'
		mov [rbp].OP_prefixlen,2
	.endif
	test	esi,FLAG_I64
	jnz	output_LONGINT
	cmp	[rbp].OP_fldwidth,2
	jne	output_SHORTINT
	call	output_getq
	and	rax,00FFh
	jmp	output_NUMBER

output_o:
	mov	[rbp].OP_curadix,8
	test	esi,FLAG_ALTERNATE
	jz	output_GENINT
	or	esi,FLAG_FORCEOCTAL
	jmp	output_GENINT

output_d:
	or	esi,FLAG_SIGNED

output_u:
	mov	[rbp].OP_curadix,10

output_GENINT:
	test	esi,FLAG_I64
	jz	output_SHORTINT

output_LONGINT:
	call	output_getq
	jmp	output_NUMBER

output_SHORTINT:
	call	output_getq
	if 0
	test	esi,FLAG_SIGNED
	jz	output_NUMBER
	cmp	eax,0
	jnl	output_NUMBER
	dec	edx
	endif

output_NUMBER:
	.if	esi & FLAG_SIGNED
		test	rax,rax
		.if	SIGN?
			neg	rax
			or	esi,FLAG_NEGATIVE
		.endif
	.endif

	mov	[rbp].OP_number,rax

	test	edi,edi
	.if	SIGN?
		mov	edi,1
	.else
		and	esi,-9
	.endif

	.if	!rax
		mov	[rbp].OP_prefixlen,rax
	.endif

	lea	rax,[rbp].OP_buffer+512-1
	mov	[rbp].OP_text,rax
	jmp	on_start

on_lupe:
	mov	rcx,[rbp].OP_curadix
	mov	rax,[rbp].OP_number
	xor	rdx,rdx
	div	rcx
	mov	rcx,rdx
	xor	rdx,rdx

	mov	[rbp].OP_number,rax
	add	cl,'0'
	cmp	cl,'9'
	jng	@F
	add	cl,BYTE PTR [rbp].OP_hexoff
@@:
	mov	rdx,[rbp].OP_text
	mov	[rdx],cl
	dec	[rbp].OP_text
on_start:
	mov	ecx,edi
	dec	edi
	test	ecx,ecx
	jg	on_lupe
	or	rax,[rbp].OP_number
	jnz	on_lupe

	lea	rax,[rbp].OP_buffer+512-1
	sub	rax,[rbp].OP_text
	mov	[rbp].OP_count,rax
	inc	[rbp].OP_text

	.if	esi & FLAG_FORCEOCTAL
		mov	rdx,[rbp].OP_text
		.if	BYTE PTR [rdx] != '0' || [rbp].OP_count == 0
			sub	rdx,1
			mov	[rbp].OP_text,rdx
			mov	BYTE PTR [rdx],'0'
			inc	[rbp].OP_count
		.endif
	.endif
	ret

OPST_normal:
	mov	al,dl

output_PUTC:
	mov	rdx,[rbp].OP_filep
	dec	[rdx]._iobuf._cnt
	jl	putc_flush
	inc	[rdx]._iobuf._ptr
	mov	rdx,[rdx]._iobuf._ptr
	mov	[rdx-1],al
putc_end:
	inc	[rbp].OP_charsout
	ret
putc_flush:
	sub	rsp,20h
	mov	rdx,[rbp].OP_filep
	movzx	rcx,al
	call	output_flush
	add	rsp,20h
	cmp	rax,-1
	jne	putc_end
	mov	[rbp].OP_charsout,rax
	ret

output_MULTI:
	push	rsi
	push	rdi
	movzx	rax,al
	mov	rsi,rax
	mov	rdi,rdx
	.while	SQWORD PTR rdi > 0
		mov	rax,rsi
		call	output_PUTC
		.break .if [rbp].OP_charsout == -1
		dec	rdi
	.endw
	pop	rdi
	pop	rsi
	ret

output_STRING:
	push	rsi
	push	rdi
	mov	rsi,rcx
	mov	rdi,rdx
	.while	SQWORD PTR rsi > 0
		mov	al,[rdi]
		call	output_PUTC
		.break .if [rbp].OP_charsout == -1
		inc	rdi
		dec	rsi
	.endw
	pop	rdi
	pop	rsi
	ret

OUTPUT:
	xor	rax,rax
	.if	rax == [rbp].OP_no_output
		.if	esi & FLAG_SIGNED
			.if	esi & FLAG_NEGATIVE
				mov	[rbp].OP_prefix,'-'
				mov	[rbp].OP_prefixlen,1
			.elseif esi & FLAG_SIGN
				mov	[rbp].OP_prefix,43
				mov	[rbp].OP_prefixlen,1
			.elseif esi & FLAG_SIGNSP
				mov	[rbp].OP_prefix,' '
				mov	[rbp].OP_prefixlen,1
			.endif
		.endif
		mov	rax,[rbp].OP_fldwidth
		sub	rax,[rbp].OP_count
		sub	rax,[rbp].OP_prefixlen
		mov	[rbp].OP_padding,rax
		.if	!(esi & FLAG_LEFT or FLAG_LEADZERO)
			mov	rdx,rax
			mov	rax,' '
			call	output_MULTI
		.endif
		lea	rdx,[rbp].OP_prefix
		mov	rcx,[rbp].OP_prefixlen
		call	output_STRING
		.if	esi & FLAG_LEADZERO
			.if	!(esi & FLAG_LEFT)
				mov	eax,'0'
				mov	rdx,[rbp].OP_padding
				call	output_MULTI
			.endif
		.endif
		mov	rcx,[rbp].OP_count
		.if	SQWORD PTR rcx > 0
			mov	rdx,[rbp].OP_text
			.while	SQWORD PTR rcx > 0
				movzx	rax,BYTE PTR [rdx]
				push	rdx
				push	rcx
				call	output_PUTC
				pop	rcx
				pop	rdx
				inc	rdx
				dec	rcx
			.endw
		.else
			mov	rdx,[rbp].OP_text
			call	output_STRING
		.endif
		.if	esi & FLAG_LEFT
			mov	rax,' '
			mov	rdx,[rbp].OP_padding
			call	output_MULTI
		.endif
	.endif
	ret

output_getq: ; Get QWORD from stack
	mov	rax,[rbp].OP_arglist
	add	[rbp].OP_arglist,8
	mov	rax,[rax]
	ret

	END
