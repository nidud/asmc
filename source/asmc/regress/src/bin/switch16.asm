	.186
	.model compact

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

	.switch
	.endsw

	.switch ax
	.endsw

	.switch mem8
	  .case al,ah,dl: .endc
	.endsw

	.switch al
	  .case 1
		.endc
	  .case 3..7
		nop
	  .case mem8
		.switch cx
		  .case 1,2,3,4,5,6,7,8,9: .endc
		.endsw
	  .default
		.endc .if !al	; == jz	 exit
		nop
	.endsw

	.switch p1( p1( 2 ) )
	  .case 2
		nop
	  .case 1
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
		nop
	  .case ax == 1
		nop
	.endsw

	.switch foo( ax )
	  .case bar( "a1" ) : nop : .endc
	  .case bar( "a2" ) : nop : .endc
	  .case bar( "a3" ) : nop : .endc
	  .case bar( "a4" ) : nop : .endc
	.endsw

	.switch
	  .case opt_1 : nop : .endc
	  .case opt_2 : nop : .endc
	  .case opt_3 : nop : .endc
	  .case opt_4 : nop : .endc
	  .case foo( cx )
	.endsw

define	equ 10
$label:
	.switch cx
	  .case 1
	  .case 10h
	  .case 's1'
	  .case "s2"
	  .case BYTE * 2
	  .case BYTE SHL WORD
	  .case $label - 1
	  .case offset $label
	  .case offset mem64
	  .case define
	  .case 4 XOR 1
	  .case ((NOT -7) + ('c' SHL 8))
	  .case 1..8
	  .case si
	  .case [di]
	  .case WORD PTR mem32
	  .case mem16
	  .default
	.endsw

	.switch
	  .case foo( ax ) == 2
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

	OPTION	SWITCH: REGAX

	.switch ax
	  .case 0	: .endc ; no table
	  .case 1	: .endc
	  .case 2
	.endsw

	.switch ax
	  .case 0	: .endc ; table - 8
	  .case 1	: .endc
	  .case 2	: .endc
	  .case 3	: .endc
	  .case 4	: .endc
	  .case 5	: .endc
	  .case 6	: .endc
	  .case 7
	.endsw

	.switch ax
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
	  .case 20000
	.endsw

	.switch ax
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
	.while	dx
		.switch cx
		  .case 0 : mov al,0 : .break
		  .case 1 : mov al,1 : .break
		  .case 2 : mov al,2 : .break
		.endsw
	.endw
	;
	; skip jump if .continue occure
	;
	.while	dx
		.switch cx
		  .case 0 : mov al,0 : .continue
		  .case 1 : mov al,1 : .continue
		  .case 2 : mov al,2 : .continue
		.endsw
	.endw
	;
	; jump...
	;
	.while	dx
		.switch cx
		  .case 0 : mov al,0
		  .case 1 : mov al,1
		  .case 2 : mov al,2
		.endsw
	.endw

	OPTION	SWITCH: C
	;
	; no jump...
	;
	.while	dx
		.switch cx
		  .case 0 : mov al,0
		  .case 1 : mov al,1
		  .case 2 : mov al,2
		.endsw
	.endw
	;
	; jump...
	;
	.while	dx
		.switch cx
		  .case 0 : mov al,0 : .endc
		  .case 1 : mov al,1 : .endc
		  .case 2 : mov al,2 : .endc
		.endsw
	.endw

	.switch cx
	  .case 0, 1, 2 : nop : .endc
	.endsw

	.switch cx
	  .case 0, 1, 2 : nop
	.endsw

	OPTION	SWITCH: NOTABLE
	;
	; no table
	;
	.switch cx
	  .case 0, 1, 2, 4 : nop
	.endsw

	OPTION	SWITCH: TABLE
	;
	; table
	;
	.switch cx
	  .case 0, 1, 2, 4 : nop
	.endsw

	.switch ax
	  .case 0: .repeat : movsb
	  .case 7: movsb
	  .case 6: movsb
	  .case 5: movsb
	  .case 4: movsb
	  .case 3: movsb
	  .case 2: movsb
	  .case 1: movsb : .untilcxz
	.endsw

	.switch ax
	  .case 1 : nop ; warning A7008: .case without .endc: assumed fall through
	  .case 2 : .endc
	.endsw

	.switch ax
	  .case $label - 1 : mov al,1 : .endc
	  .case $label - 2 : mov al,0 : .endc
	  .case $label	   : mov al,2 : .endc
	  .case $label + 1 : mov al,3 : .endc
	  .case $label + 2 : mov al,4 : .endc
	.endsw

	OPTION	SWITCH: PASCAL
	;
	; should generate the same code (no warning)
	;
	.switch ax
	  .case $label - 1 : mov al,1
	  .case $label - 2 : mov al,0
	  .case $label	   : mov al,2
	  .case $label + 1 : mov al,3
	  .case $label + 2 : mov al,4
	.endsw

	.switch al		; CBW
	  .case 1,0,2,3,4,5,6
	.endsw
	.switch dl		; MOV AL,DL + CBW
	  .case 1,0,2,3,4,5,6
	.endsw

	.386

	.switch al		; MOVSX AX,AL
	  .case 1,0,2,3,4,5,6
	.endsw
	.switch dl		; MOVSX AX,DL
	  .case 1,0,2,3,4,5,6
	.endsw

	end

