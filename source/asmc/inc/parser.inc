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

; Flags used for instructions
; VEX flags is "general" for each instruction
; EVEX flags is set for all instruction variants
;
; EVEX.LZ.NDS.[128,256,512,LLIG].[66,F2,F3].0F/0F3A/0F38.[W0,W1,WIG] opcode [/r] [/ib]
;

.enum tuple_type {
    FV = 1,             ; Full Vector / Load+Op (Full Vector Dword/Qword)
    HV,                 ; Half Vector / Load+Op (Half Vector)
    FVM,                ; Full Mem / SubDword Convention
    T1S,                ; Tuple1 Scalar
    T1F,                ; Tuple1 Fixed 4/8 not affected by EVEX.W
    T2,                 ; Broadcast (2 elements)
    T4,                 ; Broadcast (4 elements)
    T8,                 ; Broadcast (8 elements)
    HVM,                ; Half Mem / SubQword Convention
    QVM,                ; QuarterMem
    OVM,                ; OctMem / SubWord Convention
    M128,               ; Mem128 / Shift count from memory
    DDUP,               ; VMOVDDUP
    T14X,               ; Tuple1_4X
    FV512,              ; Full Vector, 256 --> 512
    }

define LZ       0x10    ; VEX.LZ VEX-Encoded GPR instructions
define VSIB     0x20    ; /vsib Use VSIB memory addressing
define WIG      0x40    ; W ignored - same bit for VEX and EVEX
define W1       0x80    ; W set - same bit for VEX and EVEX
define MR       0x0100  ; Support {k1}
define BC       0x0200  ; Support /m32bcst /m64bcst {1tox} BCST
define SA       0x0400  ; Support {sae}
define ER       0x0800  ; Support {er} ({rx-sae})
define ZR       0x1000  ; Support {z}
define SZ       0x2000  ; Support {sae} for ZMM only
define EZ       0x4000  ; Support {er}  for ZMM only
define LLIG     0x8000  ; EVEX.L'L Ignored

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
    AP_NO_FWAIT = 0x05,
    AP_REX_W    = 0x06,
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


; instr_item is the structure used to store instructions
; in InstrTable (instruct.h).
; Most compilers will use unsigned type for enums, just OW
; allows to use the smallest size possible.

.template instr_item
    opclsidx    db ?        ; v2.06: index for opnd_clstab
    byte1_info  db ?        ; flags for 1st byte
    flags       db ?
    cpu         db ?
    evex        dw ?        ; flags for EVEX and VEX-Encoded GPR Instructions
    opcode      db ?        ; opcode byte
    rm_byte     db ?        ; mod_rm_byte
   .ends


; VEX, VEX2, VEX3, EVEX, and {evex} prefix -- not reserved words
;
; These may also be set by option avxencoding

define VEX_PREFIX 0x1F


.enum {
    REX_B       = 0x01,     ; regno 0-7 <-> 8-15 of ModR/M or SIB base
    REX_X       = 0x02,     ; regno 0-7 <-> 8-15 of SIB index
    REX_R       = 0x04,     ; regno 0-7 <-> 8-15 of ModR/M REG
    REX_W       = 0x08,     ; wide 32 <-> 64
    REX_B4      = 0x10,     ; REX2: regno 16-31 of ModR/M or SIB base
    REX_X4      = 0x20,     ; REX2: regno 16-31 of SIB index
    REX_R4      = 0x40,     ; REX2: regno 16-31 of ModR/M REG
    REX_M0      = 0x80
    }

.template ResWFlags
    record
     Disabled   db : 1 ?    ; keyword disabled
     IA32       db : 1 ?    ; keyword specific to IA32 mode
     X64        db : 1 ?    ; keyword specific to IA32+ mode
     VEX        db : 1 ?    ; keyword triggers VEX encoding
     EVEX       db : 1 ?    ; keyword triggers EVEX encoding
     DRIMM      db : 1 ?    ; reg,r/m,imm - VPSLLD/..
     SWAP       db : 1 ?    ; short version of VMOV*
     EVEX_W     db : 1 ?    ; used for EVEX encoding
    ends
   .ends

.template VexFlags
    record
     L          db : 1 ?    ; Support 256/512 Vectors
     NND        db : 1 ?    ; VEX.NDS/NDD not supported
     DST        db : 1 ?    ; VEX.NDD (if op3 is an immediate)
     IMM        db : 1 ?    ; no VEX.NDS if op3 is an immediate
     NMEM       db : 1 ?    ; no VEX.NDS if op1 is a mem ref (vmovs[d|s], vmov[h|l]p[d|s] )
     HALF       db : 1 ?    ; op2 is half-sized
     WIgnored   db : 1 ?    ; no REX.W bit
     W          db : 1 ?    ; set REX.W bit
    ends
   .ends

.template Instruction
    opclsidx    db ?        ; v2.06: index for opnd_clstab
    byte1_info  db ?        ; flags for 1st byte
    record
     prefix     db : 3 ?    ; allowed prefix
     first      db : 1 ?    ; 1=opcode's first entry
     rm_info    db : 3 ?    ; info on r/m byte
     opnd_dir   db : 1 ?    ; operand direction
    ends
    cpu         CPU <>
    record Evex
     Tuple      dw : 4 ?    ; Tuple type
     vgpr       dw : 1 ?    ; Support VEX.LZ VEX instructions using 3 registers (BMI)
     vsib       dw : 1 ?    ; Support VSIB memory addressing /vsib
     WIgnored   dw : 1 ?    ; EVEX.W bit ignored
     W          dw : 1 ?    ; EVEX.W=1
     Mask       dw : 1 ?    ; Support {k1}
     Broadcast  dw : 1 ?    ; Support BCST / {1tox} /m32bcst /m64bcst
     Suppress   dw : 1 ?    ; Support {sae} Suppress All Exceptions
     Rounding   dw : 1 ?    ; Support {rx-sae} {er}
     Zeroing    dw : 1 ?    ; Support {z} Zeroing/Merging
     SuppressZ  dw : 1 ?    ; Support {sae} for ZMM only
     RoundingZ  dw : 1 ?    ; Support {rx-sae} {er} for ZMM only
     LIgnored   dw : 1 ?    ; LLIG
    ends
    opcode      db ?        ; opcode byte
    rm_byte     db ?        ; mod_rm_byte
   .ends
    instr_t     typedef ptr Instruction

if sizeof(Instruction) ne 8
.err @CatStr(%@FileName,<(>,%@Line,<): >, <Instruction need to 8 byte!!!!>)
endif

; code_info describes the current instruction. It's the communication
; structure between parser and code generator.

.template code_info
    record Flags
     IsWide     db : 1 ?    ; 0=byte, 1=word/dword/qword
     IsDirect   db : 1 ?    ; 1=direct addressing mode
     IsFar      db : 1 ?    ; CALL/JMP far
     ConstFixed db : 1 ?    ; v2.01
     X86HUsed   db : 1 ?    ; AH,BH,CH,DH used
     X64LUsed   db : 1 ?    ; SPL,BPL,SIL,DIL used
     SymUndef   db : 1 ?    ; v2.06b: struct member is forward ref
     B_RIP      db : 1 ?    ; Base: RIP
    ends
    record Prefix
     Vex        db : 1 ?    ; VEX prefix 0x4* is to be emitted
     Vex2       db : 1 ?    ; VEX2 prefix 0xC5 is to be emitted
     Vex3       db : 1 ?    ; VEX3 prefix 0xC4 is to be emitted
     Evex       db : 1 ?    ; EVEX prefix 0x62 is to be emitted
     Rex2       db : 1 ?    ; REX2 prefix 0xD5 is to be emitted
     Osize      db : 1 ?    ; operand size prefix 0x66 is to be emitted
     Asize      db : 1 ?    ; address size prefix 0x67 is to be emitted
     Swap       db : 1 ?    ; Swap encoding
    ends
    record Rex
     B          db : 1 ?    ; Base  0-15 of ModR/M or SIB base
     X          db : 1 ?    ; Index 0-15 of SIB index
     R          db : 1 ?    ; Reg   0-15 of ModR/M REG
     W          db : 1 ?    ; wide  32/64
     Fixed      db : 2 ?    ; 0
     P64        db : 1 ?    ;
    ends
    record Rex2             ; High-16 registers used
     B          db : 1 ?    ; Rex: Base  0-15 of ModR/M or SIB base
     X          db : 1 ?    ; Rex: Index 0-15 of SIB index
     R          db : 1 ?    ; Rex: Reg   0-15 of ModR/M REG
     W          db : 1 ?    ; Rex: wide  32/64
     B4         db : 1 ?    ; Base  16-31 of ModR/M or SIB base
     X4         db : 1 ?    ; Index 16-31 of SIB index
     R4         db : 1 ?    ; Reg   16-31 of ModR/M REG
     M          db : 1 ?    ; map 0 (1-byte opcodes) or map 1 (2-byte opcodes, +0x0F)
    ends
    struct Evex             ; EVEX.P2 - User settings
     record P2
      Mask      db : 3 ?    ; Embedded opmask register specifier: {k1..k7}
      V         db : 1 ?    ; Combine with vvvv or when VSIB present
      b         db : 1 ?    ; Brodcast/RC/SAE Context: {1to2/4/8/16}
      L0        db : 1 ?    ; Vector length/RC - YMM
      L1        db : 1 ?    ; Vector length/RC - ZMM
      z         db : 1 ?    ; Zeroing/Merging: {z}
     ends
    ends
    record Modifier         ; Modifiers used:
     Broadcast  db : 1 ?    ; /bcst {1tox}
     Rounding   db : 1 ?    ; {rx-sae} Rounding control {er}
     Suppress   db : 1 ?    ; {sae} Suppress All Exceptions
     Zeroing    db : 1 ?    ; {z} Zeroing/Merging
     ZMMUsed    db : 1 ?    ; Rounding/Suppress only supported for ZMM
     BCShift    db : 3 ?    ; {1tox} value --> 2 << Shift
    ends
    Vex         VexFlags <> ; set by code_gen
    ResW        ResWFlags<> ; set by parser
    mem_type    db ?        ; byte / word / etc. NOT near/far
    Ofssize     db ?
    rm_byte     db ?
    sib         db ?
    opc_or      db ?
    rrm_ib      db ?
    vexregop    db ?        ; in based-1 format (0=empty)
    record VReg
     R_YMM      db : 1 ?    ; the reg-type in vexregop
     R_ZMM      db : 1 ?
     X_YMM      db : 1 ?    ; the reg-type in opc_or (VSIB index)
     X_ZMM      db : 1 ?
    ends
    HLE         db ?        ; Hardware Lock Elision Prefix Hints
    token       dd ?
    inst        int_t ?
    RegOverride int_t ?
    opnd        opnd_item MAX_OPND dup(<>)
    pinstr      instr_t ?
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
externdef SegOverride:asym_t

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
segm_override           proto __ccall :ptr expr, :ptr code_info
idata_fixup             proto __ccall :ptr code_info, :dword, :ptr expr

endif
.pragma list(pop)
