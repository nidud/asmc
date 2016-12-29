	.model compact
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

	OPTION	CSTACK: ON

cstack	PROC STDCALL USES si di bx arg
	sub	sp,arg
	ret
cstack	ENDP

	OPTION	CSTACK: OFF

astack	PROC STDCALL USES si di bx arg
	sub	sp,arg
	ret
astack	ENDP

	.while	ax == bar("ab")
		nop
	.endw
	.while	foo(ax)
		nop
	.endw
	.while	foo(ax) || cx == bar("12")
		nop
	.endw

	.while	ax == bar("ab") || ( dx == bar("cb") && cx == bar("12") )
		nop
	.endw
	.while	ax == bar("ab") && ( ax == bar("ba") || ax == bar("12") )
		nop
	.endw
	.while	foo(ax) || ( ax == bar("ba") && ax == bar("12") )
		nop
	.endw

	.while	ax == bar('ab') && cx
		nop
	.endw

	repeat	7
	.while	ax == bar('ab')
		nop
	.endw
	endm

	.while	ax==bar(".h") || \
		ax==bar(".c") || \
		ax==bar(".r") || \
		ax==bar(".c")
		nop
	.endw

	.if	dx
		nop
	.elseif ax==bar(".h") || \
		ax==bar(".c") || \
		ax==bar(".r") || \
		ax==bar(".c")
		nop
	.endif

	end

