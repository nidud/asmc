	.model compact, c
	.286

foo	macro reg
	inc   reg
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

dlabel	label word
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

@@:	cmp	foo(ax),0
	jne	@B

@@:	.if	foo(ax)
		jmp @B
	.endif

clabel:
	call	ax
	call	clabel
	call	dlabel
	call	xlabel

	ax()
	clabel()
	dlabel()
	xlabel()
	.if ax()
	.endif
	.if clabel()
	.elseif xlabel()
	.endif
	.while xlabel()
	.endw
xlabel:

p1	proc c arg
	ret
p1	endp
p2	proc stdcall a1, a2
	ret
p2	endp

	.while	p1( ax )
		nop
	.endw

	.while !( ax || dx ) && cx
		nop
	.endw

	.while	al
		.break .if ZERO?
		.continue .if ZERO?
	.endw

	.if	ax
		nop
	.elseif foo( ax )
		nop
	.endif

_A_	equ 2
_B_	equ <foo>
_S_	equ sword ptr

	.if	ax
		nop
	.elseif ax || ax == _A_
		nop
	.endif

	.if	ax && _A_
		nop
	.elseif foo(ax)
		nop
	.elseif _B_(ax)
		nop
	.endif

	.while	_S_ clabel() < 0
		nop
	.endw

	.if	_S_ bx < 0
		nop
	.elseif _S_ bx < 0
		nop
	.endif

	.while	p1( p1( 1 ) )
		nop
	.endw

m2	macro a
	invoke	p1,a
	mov	bx,ax
	exitm  <bx>
	endm

	.if	m2( 1 )
		.while	p1( p1( 1 ) ) || m2( 2 )
			nop
		.endw
	.endif

	invoke	p2, p1( 1 ), 2
	invoke	p2( bx, "string\n" )
	p2( "if first token is a proc()", "invoke()\n" )

	invoke x.l1
	x.l1()
	x.l2(1)
	x.l3(1,2)

	[bx].xx.l1()
	[bx].xx.l2(1)
	[bx].xx.l3(1,2)

	assume bx:ptr xx
	[bx].l1()
	[bx].l2(1)
	[bx].l3(1,2)

	.if [bx].l2(0)
		nop
	.endif


	end

