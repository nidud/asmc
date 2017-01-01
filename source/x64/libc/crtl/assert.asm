include stdio.inc
include stdlib.inc
include conio.inc

	.data

_ax	dq ?
_cx	dq ?
_dx	dq ?

regs	db "assert failed: %s",10
	db 10
	db 9,' regs:'
	db 9,	'RAX: %016X R8:  %016X',10
	db 9,9, 'RBX: %016X R9:  %016X',10
	db 9,9, 'RCX: %016X R10: %016X',10
	db 9,9, 'RDX: %016X R11: %016X',10
	db 9,9, 'RSI: %016X R12: %016X',10
	db 9,9, 'RDI: %016X R13: %016X',10
	db 9,9, 'RBP: %016X R14: %016X',10
	db 9,9, 'RSP: %016X R15: %016X',10
	db 9,9, 'RIP: %016X',10
	db 10
	db 9,'flags:  '
bits	db '0000000000000000',10
	db 9,9,'r n oditsz a p c',10,0

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

assert_exit proc
	mov	_ax,rax
	mov	_dx,rdx
	mov	_cx,rcx

	lea	rdx,bits
	pushfq
	pop	rax
	mov	rcx,16
	.repeat
		shr	eax,1
		adc	byte ptr [rdx+rcx-1],0
	.untilcxz
	mov	rax,rsp
	pop	rdx
	sub	rsp,@ReservedStack
	_print( addr regs, rdx,
		_ax, r8,
		rbx, r9,
		_cx, r10,
		_dx, r11,
		rsi, r12,
		rdi, r13,
		rbp, r14,
		rax, r15,
		rdx )
	_getch()
	exit( 1 )
	ret
assert_exit endp

	END
