	.386
	.model flat, c
	.code

foo	proto :dword

bar	macro const:req		; no code generated
	local string
	string equ <>
	forc	q, <const>
		string catstr <q>, string
		endm
	exitm	<string>
	endm
ifdef __ASMC__
	option asmc:on
endif
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
