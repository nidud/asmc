	.486
	.model flat
	.code

	enumval = 1

res	macro tok, string, type, value, bytval, flags, cpu, sflags
%	echo @CatStr(@CatStr(@CatStr(<T_>,@SubStr(<tok>,2)),<	equ >),%enumval)
	enumval = enumval + 1
	endm

insa	macro tok, string, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex
%	echo @CatStr(@CatStr(@CatStr(<T_>,@SubStr(<tok>,2)),<	equ >),%enumval)
	enumval = enumval + 1
	endm

insx	macro tok, string, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex, flgs
%	echo @CatStr(@CatStr(@CatStr(<T_>,@SubStr(<tok>,2)),<	equ >),%enumval)
	enumval = enumval + 1
	endm

insv	macro tok, string, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex, flgs, rex
%	echo @CatStr(@CatStr(@CatStr(<T_>,@SubStr(<tok>,2)),<	equ >),%enumval)
	enumval = enumval + 1
	endm

insn	macro tok, suffix, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex
	endm

insm	macro tok, suffix, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex
	endm

avxins	macro op, tok, string, cpu, flgs
%	echo @CatStr(@CatStr(@CatStr(<T_>,@SubStr(<tok>,1)),<	equ >),%enumval)
	enumval = enumval + 1
	endm

OpCls	macro op1, op2, op3
	exitm<OPC_&op1&&op2&&op3&>
	endm

	echo .TITLE TOKEN.INC -- Auto made from mktok.asm
	echo .xlist
	echo ;
	echo T_NULL	equ 0
	echo ;
include ..\special.h
	echo ;
include directve.inc
%	echo SPECIAL_LAST	equ @CatStr(%enumval)
	echo ;
include ..\instruct.h
	echo ;
	echo VEX_START	equ T_VBROADCASTSS ; first VEX encoded item
	echo ;
	echo .list

	end
