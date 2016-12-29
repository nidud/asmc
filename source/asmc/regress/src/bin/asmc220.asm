	.486
	.model	flat, stdcall

foo	macro count
	local string
	string	equ <typedef proto :dword>
	exitm	<string>
	endm

pr1	 foo(1)

bar	macro const:req
	local string, quotes
	quotes INSTR <const>, <">
	string equ <>
	forc q, <const>
		string catstr <q>, string
		endm
	exitm	<string>
	endm

	.code

	.if	edx
	.elseif eax == bar(".dll")
	.endif

	END
