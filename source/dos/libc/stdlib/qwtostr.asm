; QWTOSTR.ASM--
; Copyright (C) 2015 Doszip Developers

include stdlib.inc
include string.inc

ifndef	__16__

	.code

qwtostr PROC _CType PUBLIC USES esi edi ebx odx:DWORD, oax:DWORD
local	result[128]:BYTE
	lea	di,result+40
	mov	result[40],0
	mov	edx,odx
	mov	eax,oax
    qwtostr_mul:
	push	edi
	mov	ebx,10
	test	edx,edx
	jnz	qwtostr_64
	div	ebx
	mov	ebx,edx
	sub	edx,edx
	jmp	qwtostr_break
    qwtostr_64:
	mov	ecx,64
	sub	esi,esi
	mov	edi,esi
    qwtostr_lup:
	shl	eax,1
	rcl	edx,1
	rcl	esi,1
	rcl	edi,1
	cmp	edi,0
	jb	qwtostr_next
	ja	qwtostr_sub
	cmp	esi,ebx
	jb	qwtostr_next
    qwtostr_sub:
	sub	esi,ebx
	sbb	edi,0
	inc	eax
    qwtostr_next:
	dec	ecx
	jnz	qwtostr_lup
	mov	ebx,esi
    qwtostr_break:
	pop	edi
	add	ebx,'0'
	dec	di
	mov	[di],bl
	lea	cx,result
	cmp	di,cx
	jbe	qwtostr_end
	mov	cx,dx
	or	cx,ax
	jnz	qwtostr_mul
    qwtostr_end:
	mov	ax,di
	mov	dx,ss
	ret
qwtostr ENDP

else

	.data

string_01	db '1',0
string_02	db '52',0
string_03	db '904',0
string_04	db '3556',0
string_05	db '758401',0
string_06	db '1277761',0
string_07	db '54534862',0
string_08	db '927694924',0
string_09	db '3767491786',0
string_10	db '777261159901',0
string_11	db '1444068129571',0
string_12	db '56017679474182',0
string_13	db '940737269953054',0
string_14	db '3972973049575027',0
string_15	db '796486064051292511',0
string_16	db '1615590737044764481',0

str_off		dw string_01
		dw string_02
		dw string_03
		dw string_04
		dw string_05
		dw string_06
		dw string_07
		dw string_08
		dw string_09
		dw string_10
		dw string_11
		dw string_12
		dw string_13
		dw string_14
		dw string_15
		dw string_16

	.code

qwtostr PROC _CType PUBLIC USES si di bx odx:DWORD, oax:DWORD
local	result[128]:BYTE
	mov	ax,ss
	mov	es,ax
	lea	di,result
	mov	cx,20
	mov	al,'0'
	cld?
	rep	stosb
	mov	dx,WORD PTR oax
	mov	ax,dx
	and	ax,15
	add	al,'0'
	lea	di,result
	cmp	al,'9'
	jle	@F
	add	al,246
	inc	result[1]
      @@:
	stosb
	call	DO_QWORD
	lea	dx,result
	mov	ax,3000h
	mov	cx,19
	mov	di,dx
	add	di,19
	std
      @@:
	cmp	[di],ah
	jne	@F
	stosb
	dec	cx
	jnz	@B
      @@:
	cld
	mov	si,di
	mov	di,dx
      @@:
	mov	al,[di]
	movsb
	mov	[si-1],al
	sub	si,2
	cmp	di,si
	jb	@B
	lea	ax,result
	mov	dx,ss
	ret
    DO_QWORD:
	mov	si,dx
	mov	dx,WORD PTR oax[2]
	mov	cx,0704h
	mov	bx,offset str_off
	call	DO_DWORD
	mov	cx,0800h
	mov	si,WORD PTR odx
	mov	dx,WORD PTR odx[2]
    DO_DWORD:
	mov	ax,si
	shr	ax,cl
	and	ax,15
	jz	DWORD_01
      @@:
	call	ADD_STRING
	dec	ax
	jnz	@B
    DWORD_01:
	add	cl,4
	cmp	cl,16
	jb	@F
	mov	si,dx
	xor	cl,cl
      @@:
	add	bx,2
	dec	ch
	jnz	DO_DWORD
	retn
    ADD_STRING:
	push	ax
	push	si
	push	cx
	mov	si,[bx]
	lea	di,result
	mov	cx,17
	add	BYTE PTR [di],6
	call	FIX_BYTE
	inc	di
      @@:
	lodsb
	test	al,al
	jz	@F
	add	al,-48
	add	[di],al
	call	FIX_BYTE
	inc	di
	dec	cx
	jnz	@B
      @@:
	call	FIX_BYTE
	pop	cx
	pop	si
	pop	ax
	retn
    FIX_BYTE:
	mov	ax,[di]
	cmp	al,'9'
	jle	@F
	add	al,246
	inc	ah
	mov	[di],ax
      @@:
	retn
qwtostr ENDP
endif
	END
