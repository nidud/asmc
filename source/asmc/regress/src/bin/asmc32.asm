	.486
	.model flat

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

	.while	eax == bar("abc")
		nop
	.endw
	.while	foo(eax)
		nop
	.endw
	.while	foo(eax) || ecx == bar("123")
		nop
	.endw

	.while	eax == bar("abc") || ( edx == bar("cba") && ecx == bar("123") )
		nop
	.endw
	.while	eax == bar("abc") && ( eax == bar("cba") || eax == bar("123") )
		nop
	.endw
	.while	foo(eax) || ( eax == bar("cba") && eax == bar("123") )
		nop
	.endw

	.while	eax == bar('abcd') && ecx
		nop
	.endw

	repeat	7
	.while	eax == bar('abcd')
		nop
	.endw
	endm

	.while	eax==bar(".hlp") || \
		eax==bar(".chm") || \
		eax==bar(".rtf") || \
		eax==bar(".com")
		nop
	.endw

	.if	edx
		nop
	.elseif eax==bar(".hlp") || \
		eax==bar(".chm") || \
		eax==bar(".rtf") || \
		eax==bar(".com")
		nop
	.endif

	end

