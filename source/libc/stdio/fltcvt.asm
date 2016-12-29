include stdio.inc
include crtl.inc

XAM_INVALID	EQU 0001h
XAM_DENORMAL	EQU 0002h
XAM_ZERODIVIDE	EQU 0004h
XAM_OVERFLOW	EQU 0008h
XAM_UNDERFLOW	EQU 0010h
XAM_PRECISION	EQU 0020h
XAM_STACKFAULT	EQU 0040h
XAM_INTREQUEST	EQU 0080h
XAM_C0		EQU 0100h
XAM_C1		EQU 0200h
XAM_C2		EQU 0400h
XAM_TOP		EQU 3800h
XAM_C3		EQU 4000h
XAM_BUSY	EQU 8000h
XAM_CMASK	EQU 4700h

externdef	output_proctab:DWORD

BUFFERSIZE	equ 512		; ANSI-specified minimum is 509
FLAG_SIGNED	equ 0040h	; signed data given
FLAG_NEGATIVE	equ 0100h	; value is negative
FLAG_LONG	equ 0400h	; long value given
FLAG_LONGDOUBLE equ 0800h	; long double

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

	.data

int10		dd 10
control		dw ?
state		dw ?
BCD_MAX		dq 1.0E18
BCD_E17		dq 1.0E17
convbuf		db 64 dup(?)
BCD		dt ?
tempw		dw ?
sign		dd ?
exponent	dd ?

	.code

	ASSUME	ebp: ptr S_OUTPUT
;
; EDI: precision
; DL:  format char
;
output_formatEU PROC
	mov	[ebp].OP_capitalize,1	; capitalize exponent
	add	dl,('a' - 'A')		; convert format char to lower
output_formatEU ENDP

output_formatE PROC
	or	esi,FLAG_SIGNED		; floating point is signed conversion
	lea	eax,[ebp].OP_buffer	; put result in buffer
	mov	[ebp].OP_text,eax
	cmp	edi,0			; compute the precision value
	jnl	@F
	mov	edi,6			; default precision: 6
@@:
	jne	@F
	cmp	dl,'g'
	jne	@F
	mov	edi,1			; ANSI specified
@@:
	mov	ecx,[ebp].OP_arglist
	add	[ebp].OP_arglist,8
	fld	QWORD PTR [ecx]
	mov	sign,0
	fxam				; Test real
	fstsw	state			; Store FPU status word
	movsx	eax,state
	test	eax,XAM_C1		; check FXAM flags
	jz	@F
	inc	sign
@@:
	and	eax,XAM_CMASK		; Condition flag
	cmp	eax,XAM_C2		; +normal
	je	@F
	cmp	eax,XAM_C1 or XAM_C2	; -normal
	jne	fpu_fault
@@:
	fabs				; force number positive
	fxtract				; extract exponent
	fxch	st(1)			; put exponent on top
	fldlg2				; form power of 10
	fmulp	st(1),st(0)
	fld	st(0)
	frndint
	fist	tempw
	movsx	eax,tempw
	mov	exponent,eax

	fsubp	st(1),st(0)		; find fractional part of
	fldl2t				; load log2(10)
	fmulp	st(1),st(0)		; log2(10) * argument
	fld	st(0)			; duplicate product
	frndint				; get int part of product
	fld	st(0)			; duplicate integer part
	fxch	st(2)			; get original product
	fsubrp	st(1),st(0)		; find fractional part
	fld1
	fchs
	fxch	st(1)			; scale fractional part
	fscale
	fstp	st(1)			; discard coprocessor junk
	f2xm1				; raise 2 to power-1
	fld1
	faddp	st(1),st(0)		; correct for the -1
	fmul	st(0),st(0)		; square result
	fscale				; scale by int part
	fstp	st(1)			; discard coprocessor junk
	fmulp	st(1),st(0)		; find fractional part of
	fmul	BCD_MAX			; then times mantissa
	frndint				; zap any remaining fraction
@@:
	fcom	BCD_E17			; is mantissa < 1.0e17?
	fstsw	tempw
	mov	ax,tempw
	sahf
	ja	@F			; no, proceed
	fimul	int10			; yes, mantissa * 10
	dec	exponent		; and decrement exponent
	jmp	@B
@@:
	fcom	BCD_MAX			; is mantissa < 1.0e18?
	fstsw	tempw
	mov	ax,tempw
	sahf
	jb	unload_BCD		; yes, proceed
	fidiv	int10			; yes, mantissa / 10
	inc	exponent		; and increment exponent
	jmp	@B

unload_BCD:

	fbstp	BCD			; unload BCD in mantissa
	lea	ebx,BCD			; convert BCD byte to ASCII
	mov	ecx,9
@@:
	mov	al,[ebx]
	mov	ah,al
	shr	al,4
	and	ah,0Fh
	add	ax,'00'
	mov	WORD PTR convbuf[ecx*2-2],ax
	inc	ebx
	dec	ecx
	jnz	@B

	mov	ebx,[ebp].OP_text
	cmp	sign,0
	je	@F
	mov	byte ptr [ebx],'-'
	inc	ebx
@@:
	mov	tempw,dx
	cmp	dl,'e'
	lea	edx,convbuf
	je	outex
	mov	ecx,exponent
	cmp	ecx,308
;	ja	infinity
	cmp	ecx,-308
;	jl	infinity
	cmp	ecx,7
	jnb	outex
	test	ecx,ecx
	jnz	@F
	mov	byte ptr [ebx],'0'
	inc	ebx
	jmp	ezero
@@:
	mov	al,[edx]
	mov	[ebx],al
	inc	edx
	inc	ebx
	dec	ecx
	jnz	@B
ezero:
	mov	byte ptr [ebx],'.'
	inc	ebx
	mov	ecx,edi
	mov	eax,edx
	sub	eax,offset convbuf
	add	eax,edi
	cmp	eax,18
	jb	@F
	mov	ecx,17
@@:
	mov	al,[edx]
	mov	[ebx],al
	inc	edx
	inc	ebx
	dec	ecx
	jnz	@B
	cmp	byte ptr tempw,'g'
	jne	alldone
	mov	eax,'0'
@@:
	cmp	[ebx-1],al
	jne	@F
	mov	[ebx-1],ah
	dec	ebx
	jmp	@B
@@:
	cmp	byte ptr [ebx-1],'.'
	jne	alldone
	mov	[ebx-1],ah
	dec	ebx
	jmp	alldone
fpu_fault:
	mov	eax,[ecx]
	add	eax,[ecx+4]
	jnz	infinity
	fldz
	mov	exponent,0
	jmp	unload_BCD
infinity:
	mov	eax,'FNI+'
	cmp	sign,0
	je	@F
	mov	al,'-'
@@:
	mov	ebx,[ebp].OP_text
	mov	[ebx],eax
	add	ebx,4
	jmp	toend
outex:
	mov	eax,'0'
	mov	ecx,edi
	cmp	exponent,0
	je	@F
	mov	al,[edx]
	inc	edx
	inc	exponent
@@:
	cmp	byte ptr tempw,'g'
	jne	use_dot
	mov	[ebx],al
	inc	ebx
	jmp	put_exp
use_dot:
	mov	ah,'.'
	mov	[ebx],ax
	add	ebx,2
@@:
	mov	al,[edx]
	mov	[ebx],al
	inc	edx
	inc	ebx
	dec	ecx
	jnz	@B
put_exp:
	mov	al,'e'		; store 'e' for exponent
	cmp	[ebp].OP_capitalize,0
	je	@F
	mov	al,'E'		; store 'E' for exponent
@@:
	mov	ecx,exponent	; test sign of exponent
	mov	ah,'+'
	or	ecx,ecx
	jns	@F		; jump, exponent positive
	mov	ah,'-'
	neg	ecx
@@:
	mov	[ebx],ax	; store sign of exponent
	add	ebx,2
	sub	ecx,2
	push	edi
	push	esi
if 0
	test	esi,FLAG_LONGDOUBLE
	mov	esi,4
	jnz	@F
	dec	esi
@@:
else
	mov	esi,3
endif
	mov	eax,ecx
	mov	ecx,esi
	mov	edi,10
@@:
	xor	edx,edx
	div	edi
	add	dl,'0'
	mov	[ebx+ecx-1],dl
	dec	ecx
	jnz	@B
	add	ebx,esi
	pop	esi
	pop	edi
alldone:
	cmp	convbuf,'-'
	jne	toend
	inc	[ebp].OP_text
	or	esi,FLAG_NEGATIVE
toend:
	sub	ebx,[ebp].OP_text
	mov	[ebp].OP_count,ebx
	ret
output_formatE ENDP

	END
