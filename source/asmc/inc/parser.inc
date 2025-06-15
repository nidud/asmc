; PARSER.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Parser items
;
.pragma list(push, 0)
ifndef __PARSER_INC
define __PARSER_INC

include operands.inc
include fixup.inc

; define tokens for SpecialTable (registers, operators, ... )

.enum special_token {
    T_NULL,
res macro tok, string, type, value, bytval, flags, cpu, sflags
    @CatStr(<T_>,@SubStr(<tok>,2)),
    endm
include special.inc
undef res
; define tokens for SpecialTable (directives)
res macro token, string, value, bytval, flags, cpu, sflags
    @CatStr(<T_>,@SubStr(<token>,2)),
    endm
include directve.inc
undef res
    SPECIAL_LAST
}

insa macro tok, string, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex
    @CatStr(<T_>,@SubStr(<tok>,2)),
    endm
insx macro tok, string, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex, flgs
    @CatStr(<T_>,@SubStr(<tok>,2)),
    endm
insv macro tok, string, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex, flgs, rex
    @CatStr(<T_>,@SubStr(<tok>,2)),
    endm
insn macro tok, suffix, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex
    endm
insm macro tok, suffix, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex
    endm
avxins macro op, tok, string, cpu, flgs
    @CatStr(<T_>,@SubStr(<tok>,1)),
    endm
OpCls macro op1, op2, op3
    exitm<OPC_&op1&&op2&&op3&>
    endm
.enum instr_token {
    INS_FIRST_1 = SPECIAL_LAST - 1, ; to ensure tokens are unique
include instruct.inc
}
undef insm
undef insn
undef insx
undef insv
undef insa
undef avxins

VEX_START equ T_VBROADCASTSS ; first VEX encoded item


; queue of symbols

.template symbol_queue
    head asym_t ?
    tail asym_t ?
   .ends


.enum queue_type {
   TAB_UNDEF,
   TAB_EXT,	; externals (EXTERNDEF, EXTERN, COMM, PROTO )
   TAB_SEG,	; SEGMENT items
   TAB_GRP,	; GROUP items
   TAB_PROC,	; PROC items
   TAB_ALIAS,	; ALIAS items
   TAB_LAST	;
   }

; several lists, see enum queue_type above
externdef SymTables:symbol_queue

SegTable    equ <SymTables[TAB_SEG*symbol_queue].head>
ExtTable    equ <SymTables[TAB_EXT*symbol_queue].head>
AliasTable  equ <SymTables[TAB_ALIAS*symbol_queue].head>
ProcTable   equ <SymTables[TAB_PROC*symbol_queue].head>

; values for <rm_info> (3 bits)
; 000		  -> has rm_byte with w-, d- and/or s-bit in opcode
; 001( no_RM	) -> no rm_byte - may have w-bit
; 010( no_WDS	) -> has rm_byte, but w-bit, d-bit, s-bit of opcode are absent
; 011( R_in_OP ) -> no rm_byte, reg field (if any) is included in opcode

.enum rm_info {
    no_RM   = 0x1,
    no_WDS  = 0x2,
    R_in_OP = 0x3,
}

; values for <allowed_prefix> (3 bits)

.enum allowed_prefix {
    ; AP_NO_PREFIX= 0x00, ; value 0 means "normal"
    AP_LOCK	= 0x01,
    AP_REP	= 0x02,
    AP_REPxx	= 0x03,
    AP_FWAIT	= 0x04,
    AP_NO_FWAIT = 0x05
}

; values for field type in special_item.
; it should match order of T_REGISTER - T_RES_ID in token.h

.enum special_type {
    RWT_REG = 2,  ; same value as for T_REG
    RWT_DIRECTIVE,
    RWT_UNARY_OP,
    RWT_BINARY_OP,
    RWT_STYPE,
    RWT_RES_ID
}

; values for sflags if register
.enum op1_flags {
    SFR_SIZMSK	= 0x7F,	 ; size in bits 0-4
    SFR_IREG	= 0x80,
    SFR_SSBASED = 0x100, ; v2.11: added
}

.enum rex_bits {
    REX_B = 1,	; regno 0-7 <-> 8-15 of ModR/M or SIB base
    REX_X = 2,	; regno 0-7 <-> 8-15 of SIB index
    REX_R = 4,	; regno 0-7 <-> 8-15 of ModR/M REG
    REX_W = 8	; wide 32 <-> 64
}

; operand classes. this table is defined in reswords.c.
; index into this array is member opclsidx in instr_item.
; v2.06: data removed from struct instr_item.

opnd_class	STRUC
opnd_type	dd 2 dup(?)
opnd_type_3rd	db ?	; operand 3
opnd_class	ENDS

; instr_item is the structure used to store instructions
; in InstrTable (instruct.h).
; Most compilers will use unsigned type for enums, just OW
; allows to use the smallest size possible.

II_ALLOWED_PREFIX equ 0x07 ; 3 - allowed prefix
II_FIRST	equ 0x08 ; 1 - 1=opcode's first entry
II_RM_INFO	equ 0x70 ; 3 - info on r/m byte
II_OPND_DIR	equ 0x80 ; 1 - operand direction

instr_item	STRUC
opclsidx	db ?	; v2.06: index for opnd_clstab
byte1_info	db ?	; flags for 1st byte
flags		db ?
evex		db ?	; EVEX
cpu		dw ?
opcode		db ?	; opcode byte
rm_byte		db ?	; mod_rm_byte
instr_item	ENDS
instr_t		typedef ptr instr_item


; special_item is the structure used to store directives and
; other reserved words in SpecialTable (special.h).

special_item	STRUC
value		dd ?
sflags		dd ?
cpu		dw ?	; CPU type
bytval		db ?
type		db ?
special_item	ENDS

ifdef _WIN64
GetRegNo macro x
	 lea  r11,SpecialTable
	 imul eax,x,special_item
	 exitm<[r11+rax].special_item.bytval>
	 endm
GetSflagsSp macro x
	 lea  r11,SpecialTable
	 imul eax,x,special_item
	 exitm<[r11+rax].special_item.sflags>
	 endm
GetValueSp macro x
	 lea  r11,SpecialTable
	 imul eax,x,special_item
	 exitm<[r11+rax].special_item.value>
	 endm
GetMemtypeSp macro x
	 lea  r11,SpecialTable
	 imul eax,x,special_item
	 exitm<[r11+rax].special_item.bytval>
	 endm
GetCpuSp macro x
	 lea  r11,SpecialTable
	 imul eax,x,special_item
	 exitm<[r11+rax].special_item.cpu>
	 endm
else
GetRegNo macro x
	 imul eax,x,special_item
	 exitm<SpecialTable[eax].bytval>
	 endm
GetSflagsSp macro x
	 imul eax,x,special_item
	 exitm<SpecialTable[eax].sflags>
	 endm
GetValueSp macro x
	 imul eax,x,special_item
	 exitm<SpecialTable[eax].value>
	 endm
GetMemtypeSp macro x
	 imul eax,x,special_item
	 exitm<SpecialTable[eax].bytval>
	 endm
GetCpuSp macro x
	 imul eax,x,special_item
	 exitm<SpecialTable[eax].cpu>
	 endm
endif

; values for <value> if type == RWT_DIRECTIVE

.enum directive_flags {
    DF_CEXPR	= 0x01, ; avoid '<' being used as string delimiter (.IF, ...)
    DF_STRPARM	= 0x02, ; directive expects string param(s) (IFB, IFDIF, ...)
			; enclose strings in <> in macro expansion step
    DF_NOEXPAND = 0x04, ; don't expand params for directive (PURGE, FOR, IFDEF, ...)
    DF_LABEL	= 0x08, ; directive requires a label
    DF_NOSTRUC	= 0x10, ; directive not allowed inside structs/unions
    DF_NOCONCAT = 0x20, ; don't concat line
    DF_PROC	= 0x40, ; directive triggers prologue generation
    DF_STORE	= 0x80, ; directive triggers line store
    DF_CGEN	= 0x100 ; directive generates lines
}

; values for <bytval> if type == RWT_DIRECTIVE

res macro token, function
    DRT_&token&,
    exitm<>
    endm

.enum directive_type {
include dirtype.inc
}
undef res

MAX_OPND	equ 3

opnd_item	STRUC
type		uint_t ?
InsFixup	fixup_t ?
UNION
 STRUC
  data32l	int_t ?
  data32h	int_t ? ; needed for OP_I48 and OP_I64
 ENDS
 data64		uint64_t ?
ENDS
opnd_item	ENDS

; code_info describes the current instruction. It's the communication
; structure between parser and code generator.

; EVEX:
; P1: R.X.B.R1.0.0.m1.m2
; P2: W.v3.v2.v1.v0.1.p1.p0
; P3: z.L1.L0.b.V1.a2.a1.a0

VX1_R		equ 0x80
VX1_X		equ 0x40
VX1_B		equ 0x20
VX1_R1		equ 0x10
VX1_M1		equ 0x02
VX1_M2		equ 0x01

VX2_W		equ 0x80
VX2_V3		equ 0x40
VX2_V2		equ 0x20
VX2_V1		equ 0x10
VX2_V0		equ 0x08
VX2_1		equ 0x04
VX2_P1		equ 0x02
VX2_P0		equ 0x01

VX3_Z		equ 0x80 ; {z}
VX3_L1		equ 0x40
VX3_L0		equ 0x20
VX3_B		equ 0x10 ; {1to4} {1to8} {1to16}
VX3_V		equ 0x08
VX3_A2		equ 0x04 ; {k1..k7}
VX3_A1		equ 0x02
VX3_A0		equ 0x01

; vflags

VX_OP1V		equ 0x01 ; set if op1..3 is [z|y|x]mm16..31 register
VX_OP2V		equ 0x02
VX_OP3V		equ 0x04
VX_OP3		equ 0x08 ; more than 2 instruction args used
VX_ZMM		equ 0x10 ; ZMM used
VX_SAE		equ 0x20 ; {sae} used
VX_ZMM8		equ 0x40 ; zmm8..15 used
VX_ZMM24	equ 0x80 ; zmm24..31 used

; pinstr->evex

VX_RXB		equ 0x0F ; P1: R.X.B.R1
VX_XMMI		equ 0x08 ; XMM register used as index
VX_NV0		equ 0x04 ; P2: V0=0
VX_W1		equ 0x02 ; P2: W=1

; VEX, VEX2, VEX3, EXEX, and {evex} prefix -- not reserved words
;
; These may also be set by option avxencoding

define PREFIX_VEX	0x01 ; Encode an AVX instruction using a VEX prefix
define PREFIX_VEX2	0x02 ; Encode an AVX instruction using a 2-byte VEX prefix
define PREFIX_VEX3	0x04 ; Encode an AVX instruction using a 3-byte VEX prefix
define PREFIX_EVEX	0x08 ; Encode an AVX instruction using an EVEX prefix

code_info	STRUC
inst		int_t ?
RegOverride	int_t ?
rex		db ?
adrsiz		db ?	; address size prefix 0x67 is to be emitted
opsiz		db ?	; operand size prefix 0x66 is to be emitted
prefix		db ?	; VEX prefix to be emitted
evexP3		db ?
vflags		db ?
token		dw ?
opnd		opnd_item MAX_OPND dup(<>)
pinstr		instr_t ?
mem_type	db ?	; byte / word / etc. NOT near/far
rm_byte		db ?
sib		db ?
Ofssize		db ?
opc_or		db ?
vexregop	db ?	; in based-1 format (0=empty)
union
 flags		db ?
 record
  iswide	db :1 ? ; 0=byte, 1=word/dword/qword
  isdirect	db :1 ? ; 1=direct addressing mode
  isfar		db :1 ? ; CALL/JMP far
  constsizefixed db :1 ? ; v2.01
  x86hi_used	db :1 ? ; AH,BH,CH,DH used
  x64lo_used	db :1 ? ; SPL,BPL,SIL,DIL used
  undef_sym	db :1 ? ; v2.06b: struct member is forward ref
  base_rip	db :1 ?
 ends
ends
code_info	ENDS

OPND1		equ 0
OPND2		equ 1
OPND3		equ 2
OPNI2		equ OPND2 * sizeof(opnd_item)
OPNI3		equ OPND3 * sizeof(opnd_item)

; branch instructions are still sorted:
; CALL, JMP, Jcc, J[e|r]CXZ, LOOP, LOOPcc

IS_CALL macro inst
    exitm<(inst == T_CALL)>
    endm
IS_JMPCALL macro inst
    exitm<(inst == T_CALL || inst ==  T_JMP)>
    endm
IS_JMP macro inst
    exitm<(inst !>= T_JMP && inst !< T_LOOP)>
    endm
IS_JCC macro inst
    exitm<(inst !> T_JMP && inst !< T_JCXZ)>
    endm
IS_BRANCH macro inst
    exitm<(inst !>= T_CALL && inst !< T_LOOP)>
    endm
IS_ANY_BRANCH macro inst
    exitm<(inst !>= T_CALL && inst !<= T_LOOPNZW)>
    endm
IS_XCX_BRANCH macro inst
    exitm<(inst !>= T_JCXZ && inst !< T_LOOPNZW)>
    endm
IS_OPER_32 macro s
    xor eax,eax
    cmp [s].Ofssize,al
    setz al
    exitm<[s].opsiz == al>
    endm


; globals

externdef InstrTable:instr_item		; instruction table
externdef SpecialTable:special_item	; rest of res words
externdef optable_idx:ushort_t		; helper, access thru IndexFromToken() only

IndexFromToken_imm macro tok
    exitm<optable_idx[(tok-SPECIAL_LAST)*2]>
    endm
ifdef _WIN64
IndexFromToken_dword proto watcall tok:uint_t {
    sub eax,SPECIAL_LAST
    lea rcx,optable_idx
    retm<word ptr [rcx+rax*2]>
    }
else
IndexFromToken_dword macro tok
    sub tok,SPECIAL_LAST
    exitm<optable_idx[tok*2]>
    endm
endif

IndexFromToken macro tok
%   exitm<typeid(IndexFromToken_,tok)(tok)>
    endm

SizeFromMemtype		proto fastcall :uchar_t, :int_t, :asym_t
MemtypeFromSize		proto fastcall :int_t, :ptr uchar_t
SizeFromRegister	proto fastcall :int_t
GetLangType		proto __ccall :ptr int_t, :token_t, :ptr uchar_t
sym_add_table		proto fastcall :ptr symbol_queue, :asym_t
sym_remove_table	proto fastcall :ptr symbol_queue, :asym_t
sym_ext2int		proto __ccall :asym_t
OperandSize		proto fastcall :int_t, :ptr code_info
set_frame		proto fastcall :asym_t
set_frame2		proto fastcall :asym_t
ParseLine		proto __ccall :token_t
ProcessFile		proto __ccall :token_t
WritePreprocessedLine	proto __ccall :string_t
parsevex		proto fastcall :string_t, :ptr uchar_t

endif
.pragma list(pop)
