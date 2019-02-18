	.486
	.model flat, c

foo	macro reg
	bswap reg
	exitm<reg>
	endm

bar	macro const:req
	local string
	string equ <>
	forc	q, <const>
		string catstr <q>, string
		endm
	exitm	<string>
	endm

	.data
dlabel	label dword
mem8	label byte
mem16	label word
mem32	label dword
mem64	label qword

opt_1	db 0
opt_2	db 0
opt_3	db 0
opt_4	db 0

; v2.27:
; - struct.proc_ptr(...)
; - [reg].struct.proc_ptr(...)
; - assume reg:ptr struct -- [reg].proc_ptr(...)

D0T	typedef proto
D1T	typedef proto :ptr
D2T	typedef proto :ptr, :ptr
D0	typedef ptr D0T
D1	typedef ptr D1T
D2	typedef ptr D2T

xx	struc
l1	D0 ?
l2	D1 ?
l3	D2 ?
xx	ends
x	xx <>

	.code

@@:	cmp	foo(eax),0
	jne	@B

@@:	.if	foo(eax)
		jmp @B
	.endif

clabel:
	call	ax
	call	eax
	call	dlabel
	call	clabel
	call	xlabel

	ax()
	eax()
	dlabel()
	clabel()
	xlabel()
	.if ax()
	.endif
	.if eax()
	.endif
	.if	dlabel()
	.elseif clabel()
	.elseif xlabel()
	.endif
	.while dlabel()
	.endw
	.while xlabel()
	.endw
xlabel:

p1	proc c arg
	ret
p1	endp
p2	proc stdcall a1, a2
	ret
p2	endp

	.while	p1( eax )
		nop
	.endw

	.while !( eax || edx ) && ecx
		nop
	.endw

	.while	al
		.break .if ZERO?
		.continue .if ZERO?
	.endw

	.if	eax
		nop
	.elseif foo( eax )
		nop
	.endif

_A_	equ 2
_B_	equ <foo>
_S_	equ sdword ptr

	.if	eax
		nop
	.elseif eax || eax == _A_
		nop
	.endif

	.if	eax && _A_
		nop
	.elseif foo(eax)
		nop
	.elseif _B_(eax)
		nop
	.endif

	.while	_S_ clabel() < 0
		nop
	.endw

	.if	_S_ ebx < 0
		nop
	.elseif _S_ ebx < 0
		nop
	.endif

	.while	p1( p1( 1 ) )
		nop
	.endw

m2	macro a
	invoke	p1,a
	mov	ebx,eax
	exitm  <ebx>
	endm

	.if	m2( 1 )
		.while	p1( p1( 1 ) ) || m2( 2 )
			nop
		.endw
	.endif

	invoke	p2, p1( 1 ), 2
	invoke	p2( ebx, "string\n" )
	p2( "if first token is a proc()", "invoke()\n" )

	invoke x.l1
	x.l1()
	x.l2(1)
	x.l3(1,2)

	[ebx].xx.l1()
	[ebx].xx.l2(1)
	[ebx].xx.l3(1,2)

	assume ebx:ptr xx
	[ebx].l1()
	[ebx].l2(1)
	[ebx].l3(1,2)

	.if [ebx].l2(0)
		nop
	.endif


	end

