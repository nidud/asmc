include stdio.inc
include stdlib.inc
;include conio.inc

	.data

_ax	dd ?
_dx	dd ?
_bx	dd ?
_cx	dd ?
_ip	dd ?
_si	dd ?
_di	dd ?
_sp	dd ?
_st	dd ?
_bp	dd ?
_flag	dd ?

regs	db 10,10,9,' regs:'
	db 9,	'EAX: %08X EDX: %08X',10
	db 9,9, 'EBX: %08X ECX: %08X',10
	db 9,9, 'EIP: %08X ESI: %08X',10
	db 9,9, 'EBP: %08X EDI: %08X',10
	db 9,9, 'ESP: %08X EST: %08X',10
	db 10
	db 9,'flags:  '
bits	db '0000000000000000',10
	db 9,'        r n oditsz a p c',10,0
fassert db "assert failed:  %s",0

	.code

assert_exit proc
	mov	_ax,eax
	mov	eax,offset _flag + 4;_BSS
	mov	_st,eax
	pushfd
	pop	eax
	mov	_flag,eax
	mov	_dx,edx
	mov	_bx,ebx
	mov	_cx,ecx
	mov	_si,esi
	mov	_di,edi
	mov	_bp,ebp
	mov	_sp,esp
	mov	eax,30303030h
	lea	edx,bits
	mov	[edx],eax
	mov	[edx+4],eax
	mov	[edx+8],eax
	mov	[edx+12],eax
	mov	eax,_flag
	mov	ecx,16
	.repeat
		shr	eax,1
		adc	byte ptr [edx+ecx-1],0
	.untilcxz
	pop	eax
	mov	_ip,eax
	printf( addr fassert, eax )
	printf( addr regs, _ax, _dx, _bx, _cx, _ip, _si, _bp, _di, _sp, _st )
;	getch()
	exit( 1 )
	ret
assert_exit endp

	END
