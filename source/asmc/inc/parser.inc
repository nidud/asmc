; PARSER.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Parser items
;
.pragma list(push, 1)
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

insa macro tok, string, first, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, flags, vex, evex
if first eq 1
    @CatStr(<T_>,@SubStr(<tok>,2)),
endif
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
undef insa
undef avxins

VEX_START equ T_VBROADCASTSS ; first VEX encoded item


; queue of symbols

.template symbol_queue
    head asym_t ?
    tail asym_t ?
   .ends


.enumt queue_type : symbol_queue {
   TAB_UNDEF,
   TAB_EXT,     ; externals (EXTERNDEF, EXTERN, COMM, PROTO )
   TAB_SEG,     ; SEGMENT items
   TAB_GRP,     ; GROUP items
   TAB_PROC,    ; PROC items
   TAB_ALIAS    ; ALIAS items
   }

define TAB_LAST 6

; several lists, see enum queue_type above
externdef SymTables:symbol_queue

SegTable    equ <SymTables[TAB_SEG].head>
ExtTable    equ <SymTables[TAB_EXT].head>
AliasTable  equ <SymTables[TAB_ALIAS].head>
ProcTable   equ <SymTables[TAB_PROC].head>

; values for <rm_info> (3 bits)
; 000             -> has rm_byte with w-, d- and/or s-bit in opcode
; 001( no_RM    ) -> no rm_byte - may have w-bit
; 010( no_WDS   ) -> has rm_byte, but w-bit, d-bit, s-bit of opcode are absent
; 011( R_in_OP  ) -> no rm_byte, reg field (if any) is included in opcode

.enum rm_info {
    no_RM   = 0x1,
    no_WDS  = 0x2,
    R_in_OP = 0x3,
    }

; values for <allowed_prefix> (3 bits)

.enum allowed_prefix {
    ; AP_NO_PREFIX= 0x00, ; value 0 means "normal"
    AP_LOCK     = 0x01,
    AP_REP      = 0x02,
    AP_REPxx    = 0x03,
    AP_FWAIT    = 0x04,
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
    SFR_SIZMSK  = 0x7F,  ; size in bits 0-4
    SFR_IREG    = 0x80,
    SFR_SSBASED = 0x100, ; v2.11: added
    }


; operand classes. this table is defined in reswords.c.
; index into this array is member opclsidx in instr_item.
; v2.06: data removed from struct instr_item.

opnd_class      STRUC
opnd_type       dd 2 dup(?)
opnd_type_3rd   db ?    ; operand 3
opnd_class      ENDS

; instr_item is the structure used to store instructions
; in InstrTable (instruct.h).
; Most compilers will use unsigned type for enums, just OW
; allows to use the smallest size possible.

II_ALLOWED_PREFIX equ 0x07 ; 3 - allowed prefix
II_FIRST        equ 0x08 ; 1 - 1=opcode's first entry
II_RM_INFO      equ 0x70 ; 3 - info on r/m byte
II_OPND_DIR     equ 0x80 ; 1 - operand direction

; special_item is the structure used to store directives and
; other reserved words in SpecialTable (special.h).

if sizeof(special_item) ne 16
.err @CatStr(%@FileName,<(>,%@Line,<): >, <special_item need to 16 byte!!!!>)
endif

ifdef _WIN64
GetInstrTable proto watcall :dword {
        lea r11,optable_idx
        mov ax,[r11+rax*2-SPECIAL_LAST*2]
        lea rax,[r12+rax*8+SPECIAL_LAST*special_item]
        }
GetSpecialTable proto watcall :dword {
        add eax,eax
        lea rax,[r12+rax*8]
        }
GetRegNo proto watcall :dword {
        add eax,eax
        retm<[r12+rax*8].special_item.bytval>
        }
GetSflagsSp proto watcall :dword {
        add eax,eax
        retm<[r12+rax*8].special_item.sflags>
        }
GetValueSp proto watcall :dword {
        add eax,eax
        retm<[r12+rax*8].special_item.value>
        }
GetMemtypeSp proto watcall :dword {
        add eax,eax
        retm<[r12+rax*8].special_item.bytval>
        }
GetCpuSp proto watcall :dword {
        add eax,eax
        retm<[r12+rax*8].special_item.cpu>
        }
else
GetInstrTable proto watcall :dword {
        mov ax,optable_idx[eax*2-SPECIAL_LAST*2]
        lea eax,InstrTable[eax*8]
        }
GetSpecialTable proto watcall :dword {
        add eax,eax
        lea eax,SpecialTable[eax*8]
        }
GetRegNo proto watcall :dword {
        add eax,eax
        retm<SpecialTable[eax*8].special_item.bytval>
        }
GetSflagsSp proto watcall :dword {
        add eax,eax
        retm<SpecialTable[eax*8].special_item.sflags>
        }
GetValueSp proto watcall :dword {
        add eax,eax
        retm<SpecialTable[eax*8].special_item.value>
        }
GetMemtypeSp proto watcall :dword {
        add eax,eax
        retm<SpecialTable[eax*8].special_item.bytval>
        }
GetCpuSp proto watcall :dword {
        add eax,eax
        retm<SpecialTable[eax*8].special_item.cpu>
        }
endif

; values for <value> if type == RWT_DIRECTIVE

.enum directive_flags {
    DF_CEXPR    = 0x01, ; avoid '<' being used as string delimiter (.IF, ...)
    DF_STRPARM  = 0x02, ; directive expects string param(s) (IFB, IFDIF, ...)
                        ; enclose strings in <> in macro expansion step
    DF_NOEXPAND = 0x04, ; don't expand params for directive (PURGE, FOR, IFDEF, ...)
    DF_LABEL    = 0x08, ; directive requires a label
    DF_NOSTRUC  = 0x10, ; directive not allowed inside structs/unions
    DF_NOCONCAT = 0x20, ; don't concat line
    DF_PROC     = 0x40, ; directive triggers prologue generation
    DF_STORE    = 0x80, ; directive triggers line store
    DF_CGEN     = 0x100 ; directive generates lines
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

MAX_OPND        equ 3

opnd_item       STRUC
type            uint_t ?
InsFixup        fixup_t ?
UNION
 STRUC
  data32l       int_t ?
  data32h       int_t ? ; needed for OP_I48 and OP_I64
 ENDS
 data64         uint64_t ?
ENDS
opnd_item       ENDS

; code_info describes the current instruction. It's the communication
; structure between parser and code generator.

.template instr_item
    opclsidx    db ?        ; v2.06: index for opnd_clstab
    byte1_info  db ?        ; flags for 1st byte
    flags       db ?
    evex        db ?
    cpu         dw ?
    opcode      db ?        ; opcode byte
    rm_byte     db ?        ; mod_rm_byte
   .ends
    instr_t     typedef ptr instr_item

; VEX, VEX2, VEX3, EXEX, and {evex} prefix -- not reserved words
;
; These may also be set by option avxencoding

.enum {

    V_W0                = 0x01,     ; no REX.W bit
    V_W1                = 0x02,     ; set REX.W bit
    V_NDS               = 0x04,     ; set if NDS register supported
    V_SIB               = 0x08,     ; set if VSIB memory addressing supported
    V_R1                = 0x10,     ; set if High-16 registers supported
    V_B                 = 0x20,     ; set if Next-8 base register supported
    V_X                 = 0x40,     ; set if Next-8 index register supported
    V_R                 = 0x80,     ; set if Next-8 register supported
    V_RXB               = 0xE0,     ;

    REX_B               = 0x01,     ; regno 0-7 <-> 8-15 of ModR/M or SIB base
    REX_X               = 0x02,     ; regno 0-7 <-> 8-15 of SIB index
    REX_R               = 0x04,     ; regno 0-7 <-> 8-15 of ModR/M REG
    REX_W               = 0x08,     ; wide 32 <-> 64
    REX_B4              = 0x10,     ; REX2: regno 16-31 of ModR/M or SIB base
    REX_X4              = 0x20,     ; REX2: regno 16-31 of SIB index
    REX_R4              = 0x40,     ; REX2: regno 16-31 of ModR/M REG
    REX_M0              = 0x80,

    APX_B_H             = 0x01,     ; GPR ModR/M or SIB base is regno 16-31
    APX_X_H             = 0x02,     ; GPR SIB index is regno 16-31
    APX_R_H             = 0x04,     ; GPR ModR/M REG is regno 16-31

    V_OP1_H             = 0x01,     ; Vector op1 is regno 16-31
    V_OP2_H             = 0x02,     ; Vector op2 is regno 16-31
    V_OP3_H             = 0x04,     ; Vector op3 is regno 16-31
    V_OP3_USED          = 0x08,
    V_ZMM_USED          = 0x10,
    V_SAE_USED          = 0x20,
    V_Z08_USED          = 0x40,
    V_Z24_USED          = 0x80,

    VEX_P0_MMMMM        = 0x1F,
    VEX_P0_B            = 0x20,
    VEX_P0_X            = 0x40,
    VEX_P0_R            = 0x80,

    VEX_P1_P0           = 0x01,
    VEX_P1_P1           = 0x02,
    VEX_P1_PP           = 0x03,
    VEX_P1_L            = 0x04,
    VEX_P1_VVVV         = 0x78,
    VEX_P1_W            = 0x80,

    VEX2_P0_PP          = 0x03,
    VEX2_P0_L           = 0x04,
    VEX2_P0_VVVV        = 0x78,
    VEX2_P0_R           = 0x80,

    EVEX_P0_M0          = 0x01,
    EVEX_P0_M1          = 0x02,
    EVEX_P0_MM          = 0x03,
    EVEX_P0_RESERVED    = 0x0C,
    EVEX_P0_R1          = 0x10,
    EVEX_P0_B           = 0x20,
    EVEX_P0_X           = 0x40,
    EVEX_P0_R           = 0x80,

    EVEX_P1_P0          = 0x01,
    EVEX_P1_P1          = 0x02,
    EVEX_P1_PP          = 0x03,
    EVEX_P1_FIXED       = 0x04,
    EVEX_P1_V0          = 0x08,
    EVEX_P1_V1          = 0x10,
    EVEX_P1_V2          = 0x20,
    EVEX_P1_V3          = 0x40,
    EVEX_P1_VVVV        = 0x78,
    EVEX_P1_W           = 0x80,

    EVEX_P2_A0          = 0x01,
    EVEX_P2_A1          = 0x02,
    EVEX_P2_A2          = 0x04,
    EVEX_P2_MASK        = 0x07,
    EVEX_P2_V           = 0x08,
    EVEX_P2_B           = 0x10,
    EVEX_P2_L0          = 0x20,
    EVEX_P2_L1          = 0x40,
    EVEX_P2_L           = 0x60,
    EVEX_P2_Z           = 0x80,
    }

.template code_info
    record Flags
     IsWide             db : 1 ?    ; 0=byte, 1=word/dword/qword
     IsDirect           db : 1 ?    ; 1=direct addressing mode
     IsFar              db : 1 ?    ; CALL/JMP far
     ConstSizeFixed     db : 1 ?    ; v2.01
     X86HUsed           db : 1 ?    ; AH,BH,CH,DH used
     X64LUsed           db : 1 ?    ; SPL,BPL,SIL,DIL used
     SymUndefined       db : 1 ?    ; v2.06b: struct member is forward ref
     B_RIP              db : 1 ?    ; Base:     RIP
    ends
    record Prefix
     Osize              db : 1 ?    ; 0x66
     Asize              db : 1 ?    ; 0x67
     Vex                db : 1 ?    ; 0x4*
     Vex2               db : 1 ?    ; 0xC5
     Vex3               db : 1 ?    ; 0xC4
     Evex               db : 1 ?    ; 0x62
     Rex2               db : 1 ?    ; 0xD5
    ends
    record Rex
     B                  db : 1 ?    ; Base  0-15 of ModR/M or SIB base
     X                  db : 1 ?    ; Index 0-15 of SIB index
     R                  db : 1 ?    ; Reg   0-15 of ModR/M REG
     W                  db : 1 ?    ; wide  32/64
     B4                 db : 1 ?    ; Base  16-31 of ModR/M or SIB base
     X4                 db : 1 ?    ; Index 16-31 of SIB index
     R4                 db : 1 ?    ; Reg   16-31 of ModR/M REG
     M0                 db : 1 ?
    ends
    record Apx
     B_High             db : 1 ?    ; Base:     GPR 16-31
     X_High             db : 1 ?    ; Index:    GPR 16-31
     R_High             db : 1 ?    ; Register: GPR 16-31 (REX2)
    ends
    record Vector
     Op1_High           db : 1 ?    ; Operand1: xMM 16-31
     Op2_High           db : 1 ?    ; Operand2: xMM 16-31
     Op3_High           db : 1 ?    ; Operand3: xMM 16-31
     Op3_Used           db : 1 ?    ; more than 2 operands used
     ZMM_Used           db : 1 ?    ; ZMM used
     SAE_Used           db : 1 ?    ; {sae}
     V08_Used           db : 1 ?    ; xMM  8-15 used
     V24_Used           db : 1 ?    ; xMM 24-31 used
    ends
    record EvexP2                   ; Payload byte 2
     Mask               db : 3 ?    ; Embedded opmask register specifier: {k1..k7}
     V                  db : 1 ?    ; Combine with vvvv or when VSIB present
     b                  db : 1 ?    ; Brodcast/RC/SAE Context: {1to4} {1to8} {1to16}
     L                  db : 2 ?    ; Vector length/RC
     z                  db : 1 ?    ; Zeroing/Merging: {z}
    ends
    mem_type            db ?        ; byte / word / etc. NOT near/far
    Ofssize             db ?
    rm_byte             db ?
    sib                 db ?
    opc_or              db ?
    vexregop            db ?        ; in based-1 format (0=empty)
    token               dd ?
    inst                int_t ?
    RegOverride         int_t ?
    opnd                opnd_item MAX_OPND dup(<>)
    pinstr              instr_t ?
   .ends

.enum { OPND1, OPND2, OPND3 }

define OPNI2 (OPND2 * sizeof(opnd_item))
define OPNI3 (OPND3 * sizeof(opnd_item))

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
    cmp     [s].Ofssize,0
    setnz   al
    cmp     [s].Prefix.Osize,0
    setne   ah
    xor     al,ah
    exitm   <al>
    endm

; globals

externdef InstrTable:instr_item         ; instruction table
externdef optable_idx:ushort_t          ; helper, access thru IndexFromToken() only

SizeFromMemtype         proto fastcall :uchar_t, :int_t, :asym_t
MemtypeFromSize         proto fastcall :int_t, :ptr uchar_t
SizeFromRegister        proto fastcall :int_t
GetLangType             proto __ccall :ptr int_t, :token_t, :ptr uchar_t
sym_add_table           proto fastcall :ptr symbol_queue, :asym_t
sym_remove_table        proto fastcall :ptr symbol_queue, :asym_t
sym_ext2int             proto __ccall :asym_t
OperandSize             proto fastcall :int_t, :ptr code_info
set_frame               proto fastcall :asym_t
set_frame2              proto fastcall :asym_t
ParseLine               proto __ccall :token_t
ProcessFile             proto __ccall :token_t
WritePreprocessedLine   proto __ccall :string_t
parsevex                proto fastcall :string_t, :ptr uchar_t

endif
.pragma list(pop)
