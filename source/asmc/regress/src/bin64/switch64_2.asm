ifndef __ASMC64__
    .x64
    .model flat, fastcall
    option switch:REGAX
endif

    .enum Calc128 {
	ID_TEXT,
	ID_A,
	ID_B,
	ID_C,
	ID_D,
	ID_E,
	ID_F,
	ID_SHIFT_LEFT,
	ID_OP_BRACKET,
	ID_7,
	ID_4,
	ID_1,
	ID_NEG,
	ID_SHIFT_RIGHT,
	ID_CL_BRACKET,
	ID_8,
	ID_5,
	ID_2,
	ID_0,
	ID_MOD,
	ID_9,
	ID_6,
	ID_3,
	ID_DOT,
	ID_DIV,
	ID_MUL,
	ID_SUB,
	ID_ADD,
	ID_ENTER
	}

	.code

foo	proc

	.switch r8d
	.case ID_A
	.case ID_B
	.case ID_C
	.case ID_D
	.case ID_E
	.case ID_F
	    .endc
	.case ID_0
	.case ID_1
	.case ID_2
	.case ID_3
	.case ID_4
	.case ID_5
	.case ID_6
	.case ID_7
	.case ID_8
	.case ID_9
	    add r8d,'0'-1
	   .endc
	.case ID_SHIFT_LEFT
	.case ID_OP_BRACKET
	.case ID_NEG
	.case ID_SHIFT_RIGHT
	.case ID_CL_BRACKET
	.case ID_MOD
	.case ID_DIV
	.case ID_MUL
	.case ID_SUB
	.case ID_ADD
	.case ID_ENTER
	.endsw
	ret
foo	endp

	end

