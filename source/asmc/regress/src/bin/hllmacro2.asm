	.386
	.model flat
	.code

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
	.while	eax == bar('abcd') && ecx
		nop
	.endw

	END
