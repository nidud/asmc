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

	OPTION	SWITCH: TABLE


p1	proc c arg
	ret
p1	endp

	.switch eax
	.endsw

	.switch al
	  .case 1
		.endc
	  .case 3..7
		nop
	  .default
		.endc .if !al	; == jz	 exit
		nop
	.endsw

	.switch p1( p1( 2 ) )
	  .case 2
		dec	eax
	  .case 1
	.endsw

	.switch
	.endsw

	.switch
	  .case al == 1
		.endc
	  .case al >= 3 && al <= 7
		nop
	  .default
		.endc .if !al
		nop
	.endsw

	.switch
	  .case p1( p1( 2 ) ) == 2
		dec	eax
	  .case eax == 1
		mov	edi,1
	.endsw

	.switch foo( eax )
	  .case bar( "arg1" ) : inc opt_1 : .endc
	  .case bar( "arg2" ) : inc opt_2 : .endc
	  .case bar( "arg3" ) : inc opt_3 : .endc
	  .case bar( "arg4" ) : inc opt_4 : .endc
	.endsw

	.switch
	  .case opt_1 : p1( "option 1 activated\n" ) : .endc
	  .case opt_2 : p1( "option 2 activated\n" ) : .endc
	  .case opt_3 : p1( "option 3 activated\n" ) : .endc
	  .case opt_4 : p1( "option 4 activated\n" ) : .endc
	  .case foo( ecx )
	.endsw

$label:

	.switch ecx
	  .case 1
	  .case 10h
	  .case 'st1'
	  .case "st2"
		.endc
	  .case BYTE * 2
		.endc
	  .case BYTE SHL WORD
		.endc
	  .case $label - 1
		.endc
	  .case offset $label
		.switch ecx
		  .case 10h
		  .case 'st1'
		  .case "st2"
		  .case BYTE
		  .case BYTE SHL WORD
			.endc
		  .case $label - 1
			.endc
		  .case offset $label
			mov	eax,$label
			.endc
		  .case offset mem64
;		  .case count
		  .case 4 XOR 1
		  .case ((NOT -7) + ('c' SHL 8))
		  .case 1..8
		  .case esi
		  .case [edi]
		  .case DWORD PTR mem32
		  .case mem32
			.endc
		  .default
		.endsw
		.endc
	  .case offset mem64
;	  .case count
	  .case 4 XOR 1
	  .case ((NOT -7) + ('c' SHL 8))
	  .case 1..8
	  .case esi
	  .case [edi]
	  .case DWORD PTR mem32
	  .case mem32
	  .default
	.endsw

if 1

	mov	ecx,10
	.switch cl
	enum  = 0
	count = 10
	repeat	count
%	  .case @CatStr(%enum)
		mov	eax,enum
		.endc
	enum = enum + 1
	endm
	.endsw

	.switch foo( eax )
	repeat	count
%	  .case @CatStr(%enum)
		mov	eax,enum
		.endc
	enum = enum + 1
	endm
	.endsw

	.switch ecx
	repeat	count
%	  .case @CatStr(%enum)
		mov	eax,enum
		.endc
	enum = enum + 3
	endm
	.endsw

	.switch
	  .case foo( eax ) == 2
		.endc
	  .case ax == 1
		mov	di,1
	  .case al == 1
		.endc
	  .case al >= 3 && al <= 7
		nop
	  .default
		.endc .if !al
		nop
	.endsw

	.switch eax
	  .case 0	: .endc ; no table
	  .case 1	: .endc
	  .case 2
	.endsw

	.switch eax
	  .case 0	: .endc ; table - 8
	  .case 1	: .endc
	  .case 2	: .endc
	  .case 3	: .endc
	  .case 4	: .endc
	  .case 5	: .endc
	  .case 6	: .endc
	  .case 7
	.endsw

	.switch eax
	  .case 0	: .endc
	  .case 1000	: .endc ; -> table - 10
	  .case 1001	: .endc
	  .case 1002	: .endc
	  .case 1003	: .endc
	  .case 1004	: .endc
	  .case 1005	: .endc
	  .case 1006	: .endc
	  .case 1007	: .endc
	  .case 1008	: .endc
	  .case 1009	: .endc ; <-
	  .case 10000	: .endc
	  .case 100000
	.endsw

	.switch eax
	  .case 0	: .endc ; *
	  .case 100	: .endc ; -> table - 5
	  .case 101	: .endc
	  .case 102	: .endc
	  .case 103	: .endc
	  .case 104	: .endc ; <-
	  .case 1000	: .endc ; -> table - 7
	  .case 1001	: .endc
	  .case 1002	: .endc
	  .case 1003	: .endc
	  .case 1004	: .endc
	  .case 1005	: .endc
	  .case 1006	: .endc ; <-
	  .case 10000	: .endc ; *
	  .case 30000	: .endc ; *
	.endsw

	.switch al	; extended table
	  .case 'e'	; stack used
	  .case 'z'
	  .case 'c'
	  .case 's'
	  .case 'p'
	  .case 'o':	ret
	  .case 'n':	ret
	  .case 'a':	.endc
	  .case 'b':	.endc
	  .case 'g':	.endc
	  .case 'l':	.endc
	  .default
		ret
	.endsw

	OPTION	SWITCH: PASCAL
	;
	; skip jump if .break occure
	;
	.while	edx
		.switch ecx
		  .case 0 : mov al,0 : .break
		  .case 1 : mov al,1 : .break
		  .case 2 : mov al,2 : .break
		.endsw
	.endw
	;
	; skip jump if .continue occure
	;
	.while	edx
		.switch ecx
		  .case 0 : mov al,0 : .continue
		  .case 1 : mov al,1 : .continue
		  .case 2 : mov al,2 : .continue
		.endsw
	.endw
	;
	; jump...
	;
	.while	edx
		.switch ecx
		  .case 0 : mov al,0
		  .case 1 : mov al,1
		  .case 2 : mov al,2
		.endsw
	.endw

	OPTION	SWITCH: C
	;
	; no jump...
	;
	.while	edx
		.switch ecx
		  .case 0 : mov al,0
		  .case 1 : mov al,1
		  .case 2 : mov al,2
		.endsw
	.endw
	;
	; jump...
	;
	.while	edx
		.switch ecx
		  .case 0 : mov al,0 : .endc
		  .case 1 : mov al,1 : .endc
		  .case 2 : mov al,2 : .endc
		.endsw
	.endw

	.switch ecx
	  .case 0, 1, 2 : mov al,3 : .endc
	.endsw

	.switch ecx
	  .case 0, 1, 2 : mov al,3
	.endsw

	OPTION	SWITCH: NOTABLE
	;
	; no table
	;
	.switch ecx
	  .case 0, 1, 2, 4 : mov al,4
	.endsw

	OPTION	SWITCH: TABLE
	;
	; forced table
	;
	.switch ecx
	  .case 0,1,2,4 : mov al,4
	.endsw

	.switch eax
	  .case 0: .repeat : movsb
	  .case 7: movsb
	  .case 6: movsb
	  .case 5: movsb
	  .case 4: movsb
	  .case 3: movsb
	  .case 2: movsb
	  .case 1: movsb : .untilcxz
	.endsw

	.switch eax
	  .case 1 : mov al,1	; warning A7008: .case without .endc: assumed fall through
	  .case 2 : .endc
	.endsw

	OPTION	SWITCH:C

	.switch eax
	  .case $label - 1 : mov al,1 : .endc
	  .case $label - 2 : mov al,0 : .endc
	  .case $label	   : mov al,2 : .endc
	  .case $label + 1 : mov al,3 : .endc
	  .case $label + 2 : mov al,4 : .endc
	.endsw
endif
	OPTION	SWITCH:PASCAL
	;
	; should generate the same code (no warning)
	;
	.switch eax
	  .case $label - 1 : mov al,1
	  .case $label - 2 : mov al,0
	  .case $label	   : mov al,2
	  .case $label + 1 : mov al,3
	  .case $label + 2 : mov al,4
	.endsw

	OPTION	SWITCH:C

	.switch eax
	  .case 'A','C','D','E','F','G','H','I'
	  .default
	.endsw

	OPTION SWITCH:PASCAL, SWITCH:TABLE

	.switch eax
	  .case 'A','C','D','E','F','G','H','I'
	  .default
	.endsw

	OPTION SWITCH:REGAX

	.switch jmp eax
	  .case 'A','C','D','E','F','G','H','I'
	  .default
	.endsw

	.switch al
	  .case 'A','C','D','E','F','G','H','I'
	  .default
	.endsw

	.switch jmp al
	  .case 'A','C','D','E','F','G','H','I'
	  .default
	.endsw

	end

