include string.inc
include stdio.inc
include crtl.inc

	.data

_divI	label dword
	dq	-1,	1,	-1,	0
	dq	13,	10,	1,	3
	dq	100,	10,	10,	0
	dq	100007, 100000, 1,	7
_divIend label dword

_shrI	label dword
	dq 0000000000000000h, 0000000000000000h, 0
	dq 0000000000000001h, 0000000000000000h, 1
	dq 0000000000000010h, 0000000000000008h, 1
	dq 0000000000000020h, 0000000000000010h, 1
	dq 0000000000000040h, 0000000000000002h, 5
	dq 8000000000000000h,0FFFFFFFF00000000h, 31
	dq 8000000000000000h,0FFFFFFFFFFFFFFF8h, 60
	dq 0800000000000000h, 0000000000000080h, 52
	dq 4000000000000000h, 0000000000000000h, 64
_shrIend label dword

_shrU	label dword
	dq 0000000000000000h, 0000000000000000h, 0
	dq 0000000000000001h, 0000000000000000h, 1
	dq 8000000000000001h, 0000000000000000h, 64
	dq 8000000000000001h, 0000000000000001h, 63
_shrUend label dword

_shl	label dword
	dd 00000000h,	00000000h,	0,	00000000h,	00000000h
	dd 00000001h,	00000000h,	16,	00010000h,	00000000h
	dd 00000001h,	00000000h,	32,	00000000h,	00000001h
	dd 00000000h,	00000001h,	32,	00000000h,	00000000h
	dd 00008000h,	00000000h,	48,	00000000h,	80000000h
	dd 80000000h,	00000080h,	1,	00000000h,	00000101h
	dd 00000001h,	00000000h,	63,	00000000h,	80000000h
	dd 00000001h,	00000000h,	64,	00000000h,	00000000h
_shlend label dword


nerror	dd 0

	.code

test_divI:
	lea	esi,_divI
@@:
	cmp	esi,offset _divIend
	jae	@F
	mov	eax,[esi]
	mov	edx,[esi+4]
	mov	ebx,[esi+8]
	mov	ecx,[esi+12]
	call	_I8D
	cmp	eax,[esi+16]
	jne	error_divI
	cmp	edx,[esi+20]
	jne	error_divI
	cmp	ebx,[esi+24]
	jne	error_divI
	add	esi,4*8
	jmp	@B
@@:
	xor	eax,eax
	inc	eax
	ret
error_divI:
	printf("\n\n_div64I() - %I64d.%d\n",edx,eax,ecx)
	inc	nerror
	xor	eax,eax
	ret

test_shrU:
	lea	esi,_shrU
@@:
	cmp	esi,offset _shrUend
	jae	@F
	mov	eax,[esi]
	mov	edx,[esi+4]
	mov	ecx,[esi+16]
	call	__ullshr
	cmp	eax,[esi+8]
	jne	error_shrU
	cmp	edx,[esi+12]
	jne	error_shrU
	add	esi,3*8
	jmp	@B
@@:
	xor	eax,eax
	inc	eax
	ret
error_shrU:
	invoke	printf("\n\n_shr64U() - %08X%08X\n",edx,eax)
	inc	nerror
	xor	eax,eax
	ret

test_shrI:
	lea	esi,_shrI
@@:
	cmp	esi,offset _shrIend
	jae	@F
	mov	eax,[esi]
	mov	edx,[esi+4]
	mov	ecx,[esi+16]
	call	_allshr
	cmp	eax,[esi+8]
	jne	error_shrI
	cmp	edx,[esi+12]
	jne	error_shrI
	add	esi,3*8
	jmp	@B
@@:
	xor	eax,eax
	inc	eax
	ret
error_shrI:
	printf("\n\n_shr64I() - %08X%08X\n",edx,eax)
	inc	nerror
	xor	eax,eax
	ret

test_shl:
	lea	esi,_shl
@@:
	cmp	esi,offset _shlend
	jae	@F
	mov	eax,[esi]
	mov	edx,[esi+4]
	mov	ecx,[esi+8]
	call	__llshl
	cmp	eax,[esi+12]
	jne	error_shl
	cmp	edx,[esi+16]
	jne	error_shl
	add	esi,5*4
	jmp	@B
@@:
	xor	eax,eax
	inc	eax
	ret
error_shl:
	invoke	printf("\n\n_shl64() - %08X%08X\n",edx,eax)
	inc	nerror
	xor	eax,eax
	ret

main	PROC c
	call	test_shl
	call	test_shrU
	call	test_shrI
	call	test_divI
toend:
	mov	eax,nerror
	ret
main	ENDP

	END
