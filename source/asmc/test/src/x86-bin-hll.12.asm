
; v2.20 delayed expansion of macro

	.486
	.model flat, stdcall
	.code

foo	macro	reg		; generate codes
	bswap	reg
	exitm  <reg>
	endm

bar	macro const:req		; no code generated
	local string
	string equ <>
	forc	q, <const>
		string catstr <q>, string
		endm
	exitm	<string>
	endm

bar2	macro const:req
	local string
	string equ <>
	forc	q, <const>
		string catstr <q>, string
		endm
	exitm	<string>
	endm

bar3	macro const:req
	local string
	string equ <>
	forc	q, <const>
		string catstr <q>, string
		endm
	exitm	<string>
	endm

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

	.while	eax == bar2('abcd') && ecx
		nop
	.endw

	repeat	7
	.while	eax == bar3('abcd')
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

	END
