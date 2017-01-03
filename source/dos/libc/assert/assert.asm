; ASSERT.ASM--
; Copyright (C) 2015 Doszip Developers
include stdio.inc
include stdlib.inc
include string.inc

	.data

_cs	dw ?
_ds	dw ?
_es	dw ?
_ss	dw ?
extrn	_dsstack:WORD
_ax	dw ?
_dx	dw ?
_bx	dw ?
_cx	dw ?
_ip	dw ?
_si	dw ?
_di	dw ?
_sp	dw ?
_st	dw ?
_bp	dw ?
_flag	dw ?

regs	db 10,10,9,' regs:'
	db 9,	'AX: %04X DX: %04X',10
	db 9,9, 'BX: %04X CX: %04X',10
	db 9,9, 'CS: %04X IP: %04X',10
	db 9,9, 'DS: %04X SI: %04X',10
	db 9,9, 'ES: %04X DI: %04X',10
	db 9,9, 'SS: %04X SP: %04X',10
	db 9,9, 'BP: %04X ST: %04X',10
	db 10
	db 9,'flags:  %016lb',10
	db 9,'        r n oditsz a p c',0
fassert db "assert failed:  %s",0

	.code

assert_exit PROC _CType PUBLIC
	mov	ss:_ds,ds
	push	ss
	pop	ds
	pushf
	mov	_es,es
	mov	_ss,ss
	mov	_ax,ax
	mov	ax,offset _dsstack
	mov	_st,ax
	pop	ax
	mov	_flag,ax
	mov	_dx,dx
	mov	_bx,bx
	mov	_cx,cx
	mov	_si,si
	mov	_di,di
	mov	_bp,bp
	mov	_sp,sp
	pop	ax
	mov	_ip,ax
ifdef __l__
	pop	dx
else
	mov	dx,cs
endif
	mov	_cs,dx
	invoke	_print,addr fassert,dx::ax
	invoke	_print,addr regs,_ax,_dx,_bx,_cx,_cs,_ip,_ds,_si,_es,_di,_ss,_sp,_bp,_st,_flag
	invoke	exit,1
	ret
assert_exit ENDP

debugmsg PROC _CType PUBLIC file:DWORD, line:size_t, expression:DWORD, doexit:size_t
	_print("\nDebug error\nFile: %s, line %2d, expression: (%s)\n", file, line, expression)
	.if doexit
	    invoke exit,doexit
	.endif
	ret
debugmsg ENDP

	END
