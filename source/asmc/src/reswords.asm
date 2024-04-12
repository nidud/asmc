; RESWORDS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; reserved word handling, including hash table access
;

include asmc.inc
include memalloc.inc
include parser.inc
include reswords.inc
include expreval.inc
include condasm.inc
include codegen.inc

public optable_idx
public opnd_clstab
public ResWordTable
public vex_flags

HASH_TABITEMS equ 4096

.pragma list(push, 0)

    .data?

; reserved words hash table

resw_table dw HASH_TABITEMS dup(?)

; define unary operand (LOW, HIGH, OFFSET, ...) type flags

include unaryop.inc

; v2.06: the following operand combinations are used
; inside InstrTable[] only, they don't need to be known
; by the parser.

.enum operand_sets {
    OP_R_MS      = ( OP_R or OP_MS ),
    OP_R8_M08    = ( OP_R8 or OP_M08 ),
    OP_RGT8_MS   = ( OP_RGT8 or OP_MS ),
    OP_RGT8_MGT8 = ( OP_RGT8 or OP_MGT8 ),
    OP_RMGT16    = ( OP_RGT16 or OP_MGT16 ),
    OP_RGT16_M08 = ( OP_RGT16 or OP_M08 ),
    OP_R16_R32   = ( OP_R16 or OP_R32 ),
    OP_R16_M16   = ( OP_R16 or OP_M16 ),
    OP_R32_M08   = ( OP_R32 or OP_M08 ),
    OP_R32_M16   = ( OP_R32 or OP_M16 ),
    OP_R32_M32   = ( OP_R32 or OP_M32 ),
    OP_R16_R64   = ( OP_R16 or OP_R64 ),
    OP_R64_M64   = ( OP_R64 or OP_M64 ),
    OP_M16_M64   = ( OP_M16 or OP_M64 ),
    OP_M16_M32   = ( OP_M16 or OP_M32 ),
    OP_MMX_M64   = ( OP_MMX or OP_M64 ),
    OP_XMM_M08   = ( OP_XMM or OP_M08 ),
    OP_YMM_M08   = ( OP_YMM or OP_M08 ),
    OP_ZMM_M08   = ( OP_ZMM or OP_M08 ),
    OP_XMM_M16   = ( OP_XMM or OP_M16 ),
    OP_YMM_M16   = ( OP_YMM or OP_M16 ),
    OP_ZMM_M16   = ( OP_ZMM or OP_M16 ),
    OP_XMM_M32   = ( OP_XMM or OP_M32 ),
    OP_XMM_M64   = ( OP_XMM or OP_M64 ),
    OP_XMM_M128  = ( OP_XMM or OP_M128 ),

; extended Masm syntax: sometimes Masm accepts 2 mem types
; for the memory operand, although the mem access will always
; be QWORD/OWORD.

    OP_MMX_M64_08  = ( OP_MMX or OP_M64  or OP_M08 ),
    OP_MMX_M64_16  = ( OP_MMX or OP_M64  or OP_M16 ),
    OP_MMX_M64_32  = ( OP_MMX or OP_M64  or OP_M32 ),

    OP_XMM_M128_08 = ( OP_XMM or OP_M128 or OP_M08 ),
    OP_XMM_M128_16 = ( OP_XMM or OP_M128 or OP_M16 ),
    OP_XMM_M128_32 = ( OP_XMM or OP_M128 or OP_M32 ),
    OP_XMM_M128_64 = ( OP_XMM or OP_M128 or OP_M64 ),

    OP_YMM_M256_08 = ( OP_YMM or OP_M256 or OP_M08 ),
    OP_YMM_M256_16 = ( OP_YMM or OP_M256 or OP_M16 ),
    OP_YMM_M256_32 = ( OP_YMM or OP_M256 or OP_M32 ),
    OP_YMM_M256_64 = ( OP_YMM or OP_M256 or OP_M64 ),

    OP_YMM_M256    = ( OP_YMM or OP_M256 ),
    OP_ZMM_M512    = ( OP_ZMM or OP_M512 ),
    OP_YMM_M32     = ( OP_YMM or OP_M32 ),
    OP_YMM_M64     = ( OP_YMM or OP_M64 ),
    OP_ZMM_M32     = ( OP_ZMM or OP_M32 ),
    OP_ZMM_M64     = ( OP_ZMM or OP_M64 ),
    OP_XMM_M256    = ( OP_XMM or OP_M256 ),
    OP_XMM_M_ANY   = ( OP_XMM or OP_M_ANY ),
    OP_XMM_M128_M32= ( OP_XMM or OP_M128 or OP_M32 ),
    OP_YMM_M256_M32= ( OP_YMM or OP_M256 or OP_M32 ),
    OP_ZMM_M512_M32= ( OP_ZMM or OP_M512 or OP_M32 ),
    OP_YMM_M128_M32= ( OP_YMM or OP_M128 or OP_M32 ),
    OP_ZMM_M128_M32= ( OP_ZMM or OP_M128 or OP_M32 ),
    OP_XMM_M128_M64= ( OP_XMM or OP_M128 or OP_M64 ),
    OP_YMM_M128_M64= ( OP_YMM or OP_M128 or OP_M64 ),
    OP_ZMM_M128_M64= ( OP_ZMM or OP_M128 or OP_M64 ),
    OP_YMM_M256_M64= ( OP_YMM or OP_M256 or OP_M64 ),
    OP_ZMM_M512_M64= ( OP_ZMM or OP_M512 or OP_M64 ),
    OP_YMM_M128    = ( OP_YMM or OP_M128 ),
    OP_ZMM_M128    = ( OP_ZMM or OP_M128 ),
    OP_ZMM_M256    = ( OP_ZMM or OP_M256 ),
    OP_M256_M128   = ( OP_M256 or OP_M128 ),
    OP_XMM_MXMM    = ( OP_XMM or OP_YMM or OP_M128 or OP_M256 or OP_M512 or OP_M64 or OP_M32 ),
    OP_XMM_YMM     = ( OP_XMM or OP_YMM ),
    OP_YMM_ZMM     = ( OP_YMM or OP_ZMM ),
    OP_M32_M64     = ( OP_M32 or OP_M64 ),
    OP_M32_M256    = ( OP_M32 or OP_M256 ),
    OP_M64_M256    = ( OP_M64 or OP_M256 ),
    OP_M32_M512    = ( OP_M32 or OP_M512 ),
    OP_M64_M512    = ( OP_M64 or OP_M512 ),
    OP_XYZMM       = ( OP_XMM or OP_YMM or OP_ZMM ),
    OP_XMM_MXQ     = ( OP_XMM or OP_M128 or OP_M64 ),
    OP_XMM_MXQD    = ( OP_XMM or OP_M128 or OP_M64 or OP_M32 ),
    OP_XMM_MXQDW   = ( OP_XMM or OP_M128 or OP_M64 or OP_M32 or OP_M16 ),
}

; v2.06: operand types have been removed from InstrTable[], they
; are stored now in their own table, opnd_clstab[], below.
; This will allow to add a 4th operand ( AVX ) more effectively.

OpCls macro op1, op2, op3
    exitm<OPC_&op1&&op2&&op3&,>
    endm
.enum opnd_variants {
include opndcls.inc
}
undef OpCls

; the tables to handle "reserved words" are now generated:
; 1. InstrTable: contains info for instructions.
;    instructions may need multiple rows!
; 2. SpecialTable: contains info for reserved words which are
;    NOT instructions. One row each.
; 3. optable_idx: array of indices for InstrTable.
; 4. resw_strings: strings of reserved words. No terminating x'00'!
; 5. ResWordTable: array of reserved words (name, name length, flags).
;
; Each reserved word has a "token" value assigned, which is a short integer.
; This integer can be used as index for:
; - SpecialTable
; - optable_idx ( needs adjustment, better use macro IndexFromToken() )
; - ResWordTable


; create InstrTable.

    .data

OpCls macro op1, op2, op3
    exitm<OPC_&op1&&op2&&op3&>
    endm
InstFlags macro prefix, first, rm_info, op_dir
    exitm<prefix or (first shl 3) or (rm_info shl 4) or (op_dir shl 7)>
    endm
avxins macro alias, tok, string, cpu, flgs
    exitm<>
    endm
insa macro tok, string, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex
    exitm<instr_item { opcls, byte1_info, InstFlags(prefix, 1, rm_info, op_dir), evex, cpu, opcode, rm_byte }>
    endm
insx macro tok, string, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex, flgs
    exitm<instr_item { opcls, byte1_info, InstFlags(prefix, 1, rm_info, op_dir), evex, cpu, opcode, rm_byte }>
    endm
insv macro tok, string, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex, flgs, vex
    exitm<instr_item { opcls, byte1_info, InstFlags(prefix, 1, rm_info, op_dir), evex, cpu, opcode, rm_byte }>
    endm
insn macro tok, suffix, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex
    exitm<instr_item { opcls, byte1_info, InstFlags(prefix, 0, rm_info, op_dir), evex, cpu, opcode, rm_byte }>
    endm
insm macro tok, suffix, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex
    exitm<instr_item { opcls, byte1_info, InstFlags(prefix, 1, rm_info, op_dir), evex, cpu, opcode, rm_byte }>
    endm
InstrTable label instr_item
include instruct.inc
include instr64.inc
insa(NULL,0,OpCls(NONE,NONE,NONE),0,0,0,0,0,0,0,0) ; last entry - needed for its ".first" (=1) field
undef avxins
undef insm
undef insn
undef insx
undef insv
undef insa

; create SpecialTable.

SpecialTable special_item { 0, 0, 0, 0, 0 } ; dummy entry for T_NULL
res macro tok, string, type, value, bytval, flags, cpu, sflags
    special_item { value, sflags, cpu, bytval, type }
    endm
include special.inc
undef res
res macro tok, string, value, bytval, flags, cpu, sflags
    special_item { value, sflags, cpu, bytval, RWT_DIRECTIVE }
    endm
include directve.inc
undef res


; define symbolic indices for InstrTable[]

.enum res_idx {
avxins macro alias, tok, string, cpu, flgs
    endm
insa macro tok, string, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex
    exitm<T_&tok&_I,>
    endm
insx macro tok, string, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex, flgs
    exitm<T_&tok&_I,>
    endm
insv macro tok, string, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex, flgs, vex
    exitm<T_&tok&_I,>
    endm
insn macro tok, suffix, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex
    exitm<T_&tok&_&suffix&,>
    endm
insm macro tok, suffix, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex
    exitm<T_&tok&_&suffix&,>
    endm
include instruct.inc
undef insm
undef insn
undef insa
undef avxins
insa macro tok, string, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex
    exitm<T_&tok&_I64,>
    endm
insn macro tok, suffix, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex
    exitm<T_&tok&_&suffix&_I64,>
    endm
insm macro tok, suffix, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex
    exitm<T_&tok&_&suffix&_I64,>
    endm
include instr64.inc
undef insm
undef insn
undef insx
undef insv
undef insa
}

; create optable_idx, the index array for InstrTable.
; This is needed because instructions often need more than
; one entry in InstrTable.

optable_idx label word
insa macro tok, string, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex
    dw T_&tok&_I
    endm
insx macro tok, string, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex, flgs
    dw T_&tok&_I
    endm
insv macro tok, string, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex, flgs, vex
    dw T_&tok&_I
    endm
insn macro tok, suffix, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex
    endm
insm macro tok, suffix, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex
    endm
avxins macro alias, tok, string, cpu, flgs
    dw T_&alias&_I
    endm
include instruct.inc
undef insm
undef insn
undef insx
undef insv
undef insa
undef avxins
undef OpCls

; table of instruction operand classes

OpCls macro op1, op2, op3
    exitm<opnd_class { { OP_&op1&, OP_&op2& }, OP3_&op3& }>
    endm
opnd_clstab label opnd_class
include opndcls.inc
undef OpCls

; create the strings for all reserved words

MAX_RESW_LEN = 0 ; skip length > this..

.const

OpCls macro op1, op2, op3
    exitm<OPC_&op1&&op2&&op3&>
    endm

resw_strings label char_t
res macro tok, string, type, value, bytval, flags, cpu, sflags
if @SizeStr(string) gt MAX_RESW_LEN
    MAX_RESW_LEN = @SizeStr(string)
endif
    exitm<db "&string&">
    endm
include special.inc
undef res
res macro tok, string, value, bytval, flags, cpu, sflags
if @SizeStr(string) gt MAX_RESW_LEN
    MAX_RESW_LEN = @SizeStr(string)
endif
    exitm<db "&string&">
    endm
include directve.inc
undef res
insa macro tok, string, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex
if @SizeStr(string) gt MAX_RESW_LEN
    MAX_RESW_LEN = @SizeStr(string)
endif
    exitm<db "&string&">
    endm
insx macro tok, string, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex, flgs
if @SizeStr(string) gt MAX_RESW_LEN
    MAX_RESW_LEN = @SizeStr(string)
endif
    exitm<db "&string&">
    endm
insv macro tok, string, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex, flgs, vex
if @SizeStr(string) gt MAX_RESW_LEN
    MAX_RESW_LEN = @SizeStr(string)
endif
    exitm<db "&string&">
    endm
insn macro tok, suffix, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex
    endm
insm macro tok, suffix, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex
    endm
avxins macro alias, tok, string, cpu, flgs
if @SizeStr(string) gt MAX_RESW_LEN
    MAX_RESW_LEN = @SizeStr(string)
endif
    exitm<db "&string&">
    endm
include instruct.inc
undef insx
undef insv
undef insm
undef insn
undef insa
undef avxins

size_resw_strings equ $ - resw_strings

; create the 'reserved words' table (ResWordTable).
; this table's entries will be used to create the instruction hash table.
; v2.11: RWF_SPECIAL flag removed:
; { 0, sizeof(#string)-1, RWF_SPECIAL or flags, NULL },

.data
align 16

ResWordTable ReservedWord { 0, 0, 0, NULL } ;; dummy entry for T_NULL
res macro tok, string, type, value, bytval, flags, cpu, sflags
    ReservedWord { 0, @SizeStr(string), flags, NULL }
    endm
include special.inc
undef res
res macro tok, string, value, bytval, flags, cpu, sflags
    ReservedWord { 0, @SizeStr(string), flags, NULL }
    endm
include directve.inc
undef res
insa macro tok,string, opcls, byte1_info,op_dir,rm_info,opcode,rm_byte,cpu,prefix,evex
    ReservedWord { 0, @SizeStr(string), 0, NULL }
    endm
insn macro tok, suffix, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex
    endm
insm macro tok, suffix, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex
    endm
insx macro tok, string, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex, flags
    ReservedWord { 0, @SizeStr(string), flags, NULL }
    endm
insv macro tok, string, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex, flags, vex
    ReservedWord { 0, @SizeStr(string), flags, NULL }
    endm
avxins macro alias, tok, string, rwf, flgs
    ReservedWord { 0, @SizeStr(string), rwf or RWF_VEX, NULL }
    endm
include instruct.inc
undef insx
undef insv
undef insm
undef insn
undef insa
undef avxins
ResWordCount equ ($ - ResWordTable) / ReservedWord

; these is a special 1-byte array for vex-encoded instructions.
; it could probably be moved to InstrTable[] (there is an unused byte),
; but in fact it's the wrong place, since the content of vex_flags[]
; are associated with opcodes, not with instruction variants.

vex_flags label byte

    ; flags for the AVX instructions in instruct.inc. The order must
    ; be equal to the one in instruct.h! ( this is to be improved.)
    ; For a description of the VX_ flags see codegen.inc

insa macro tok, string, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex
    endm
insn macro tok, suffix, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex
    endm
insm macro tok, suffix, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex
    endm
insx macro tok, string, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex, flags
    endm
insv macro tok,string, opcls, byte1_info,op_dir,rm_info,opcode,rm_byte,cpu,prefix,evex,flags,vex
    db vex
    endm
avxins macro alias, tok, string, cpu, flgs
    db flgs
    endm
include instruct.inc
undef insx
undef insv
undef insm
undef insn
undef insa
undef avxins

align 4

max_resw_len dd MAX_RESW_LEN

; keywords to be added for 64-bit
patchtab64 instr_token \
    T_SPL,              ; add x64 register part of special.h
    T_FRAME,            ; add x64 reserved word part of special.h
    T_DOT_ALLOCSTACK,   ; add x64 directive part of directve.h (win64)
    T_JRCXZ,            ; branch instructions must be grouped together
    T_CDQE,             ; add x64 part of instruct.h
    T_VPEXTRQ           ; add x64 part of instravx.h

; keywords to be removed for 64-bit
patchtab32 instr_token \
    T_TR3,              ; registers invalid for IA32+
    T_DOT_SAFESEH,      ; directives invalid for IA32+
    T_AAA,              ; instructions invalid for IA32+
    T_JCXZ,             ; 1. branch instructions invalid for IA32+
    T_LOOPW             ; 2. branch instructions invalid for IA32+


replace_ins struct
    tok     dw ?        ; is an optable_idx[] index
    idx32   res_idx ?
    idx64   res_idx ?
replace_ins ends

; keyword entries to be changed for 64-bit (see instr64.inc)
patchtabr replace_ins \
    { T_LGDT - SPECIAL_LAST, T_LGDT_I, T_LGDT_I64 },
    { T_LIDT - SPECIAL_LAST, T_LIDT_I, T_LIDT_I64 },
    { T_CALL - SPECIAL_LAST, T_CALL_I, T_CALL_I64 },
    { T_JMP  - SPECIAL_LAST, T_JMP_I,  T_JMP_I64  },
    { T_POP  - SPECIAL_LAST, T_POP_I,  T_POP_I64  }, ; v2.06: added
    { T_PUSH - SPECIAL_LAST, T_PUSH_I, T_PUSH_I64 }, ; v2.06: added
    { T_SLDT - SPECIAL_LAST, T_SLDT_I, T_SLDT_I64 }, ; with Masm, in 16/32-bit SLDTorSMSWorSTR accept a WORD argument only -
    { T_SMSW - SPECIAL_LAST, T_SMSW_I, T_SMSW_I64 }, ; in 64-bit (ML64), 32- and 64-bit registers are also accepted!
    { T_STR  - SPECIAL_LAST, T_STR_I,  T_STR_I64  },
    { T_VMREAD  - SPECIAL_LAST, T_VMREAD_I,   T_VMREAD_I64  },
    { T_VMWRITE - SPECIAL_LAST, T_VMWRITE_I,  T_VMWRITE_I64 }


align 8

renamed_keys qdesc { NULL, NULL }

; global queue of "disabled" reserved words.
; just indices of ResWordTable[] are used.

glqueue struct
Head    dw ?
Tail    dw ?
glqueue ends

Removed glqueue { 0, 0 }

b64bit int_t FALSE ; resw tables in 64bit mode?

.pragma list(pop)

define FNVPRIME 0x01000193
define FNVBASE  0x811c9dc5

    .code

ifdef _WIN64

    option win64:rsp noauto nosave

get_hash proc fastcall private token:string_t, len:byte

    xor     eax,eax
    test    edx,edx
    jz      .1
    mov     eax,FNVBASE
    mov     r8d,edx
.0:
    mov     rdx,0x2020202020202020
    or      rdx,[rcx]
    imul    eax,eax,FNVPRIME
    xor     al,dl
    dec     r8d
    jz      .1
    imul    eax,eax,FNVPRIME
    xor     al,dh
    dec     r8d
    jz      .1
    shr     rdx,16
    imul    eax,eax,FNVPRIME
    xor     al,dl
    dec     r8d
    jz      .1
    imul    eax,eax,FNVPRIME
    xor     al,dh
    dec     r8d
    jz      .1
    shr     rdx,16
    imul    eax,eax,FNVPRIME
    xor     al,dl
    dec     r8d
    jz      .1
    imul    eax,eax,FNVPRIME
    xor     al,dh
    dec     r8d
    jz      .1
    shr     rdx,16
    imul    eax,eax,FNVPRIME
    xor     al,dl
    dec     r8d
    jz      .1
    imul    eax,eax,FNVPRIME
    xor     al,dh
    add     rcx,8
    dec     r8d
    jnz     .0
.1:
    and     eax,HASH_TABITEMS-1
    ret

get_hash endp

; add reserved word to hash table

    assume r11:ptr ReservedWord
    assume r9: ptr ReservedWord

if sizeof(ReservedWord) ne 16
.err @CatStr(%@FileName,<(>,%@Line,<): >, <ReservedWord need to 16 byte!!!!>)
endif

AddResWord proc fastcall private token:int_t

    mov     r10d,ecx
    lea     r11,ResWordTable
    shl     ecx,4
    lea     r9,[r11+rcx]
    movzx   edx,[r9].len
    mov     rcx,[r9].name
    call    get_hash

    lea     rcx,resw_table
    lea     r8,[rcx+rax*2]
    xor     edx,edx

    ; sort the items of a line by length!

    movzx   ecx,word ptr [r8]
    shl     ecx,4
    jz      .1
    mov     al,[r9].len
.0:
    cmp     [r11+rcx].len,al
    ja      .1
    mov     edx,ecx
    movzx   ecx,[r11+rcx].next
    shl     ecx,4
    jnz     .0
.1:
    test    edx,edx
    jnz     .2
    mov     [r9].next,[r8]
    mov     [r8],r10w
    jmp     .3
.2:
    mov     [r9].next,[r11+rdx].next
    mov     [r11+rdx].next,r10w
.3:
    ret

AddResWord endp

    assume r9:nothing

; remove a reserved word from the hash table.

RemoveResWord proc fastcall token:int_t

    mov     r9d,ecx
    lea     r11,ResWordTable
    shl     ecx,4
    movzx   edx,[r11+rcx].len
    mov     rcx,[r11+rcx].name
    call    get_hash
    xor     edx,edx

    lea     rcx,resw_table
    lea     r8,[rcx+rax*2]
    movzx   ecx,word ptr [r8]
    test    ecx,ecx
    jz      .3
.0:
    cmp     ecx,r9d
    jne     .2
    shl     ecx,4
    shl     edx,4
    jz      .1
    mov     [r11+rdx].next,[r11+rcx].next
    mov     eax,TRUE
    jmp     .4
.1:
    mov     [r8],[r11+rcx].next
    mov     eax,TRUE
    jmp     .4
.2:
    mov     edx,ecx
    shl     ecx,4
    movzx   ecx,[r11+rcx].next
    test    ecx,ecx
    jnz     .0
.3:
    xor     eax,eax
.4:
    ret

RemoveResWord endp

rename_node struct
next        ptr rename_node ?
name        string_t ?  ; the original name in resw_strings[]
token       dw ?        ; is either enum instr_token or enum special_token
length      db ?
rename_node ends

; Rename a keyword - used by OPTION RENAMEKEYWORD.
; - token:  keyword to rename
; - name:   new name of keyword
; - length: length of new name

    assume r12:ptr rename_node
    assume rbx:ptr ReservedWord
    option win64:rbp auto save

RenameKeyword proc fastcall uses rsi rdi rbx r12 token:uint_t, name:string_t, length:byte

  local newname[64]:char_t ; added v2.26

    .for ( rdi = &newname, rsi = rdx :: )

        lodsb
        .break .if !al
        or al,0x20 ;; '@' --> 'ï'..
        stosb
    .endf
    stosb

    ; v2.11: do nothing if new name matches current name

    mov edi,ecx
    lea rbx,ResWordTable
    shl ecx,4
    add rbx,rcx

    .if ( [rbx].len == r8b )

        .return .ifd !tmemicmp( &newname, [rbx].name, r8d )
    .endif
    RemoveResWord( edi )

    ; if it is the first rename action for this keyword,
    ; the original name must be saved.

    lea rax,resw_strings
    lea rcx,[rax+size_resw_strings]
    mov rsi,[rbx].name

    .if ( rsi >= rax && rsi < rcx )

        mov r12,LclAlloc( sizeof( rename_node ) )
        mov [r12].next,NULL
        mov [r12].name,rsi
        mov [r12].token,di
        mov [r12].length,[rbx].len

        .if renamed_keys.head == NULL
            mov renamed_keys.head,r12
            mov renamed_keys.tail,r12
        .else
            mov rdx,renamed_keys.tail
            mov [rdx].rename_node.next,r12
            mov renamed_keys.tail,r12
        .endif

    .else

        ; v2.11: search the original name. if the "new" names matches
        ; the original name, restore the name pointer

        .for ( r12 = renamed_keys.head, rsi = NULL: r12: rsi = r12 )
            .if ( [r12].token == di )
                .if ( [r12].length == length )
                    .ifd !tmemcmp( &newname, [r12].name, length )
                        .if rsi
                            mov [rsi].rename_node.next,[r12].next
                        .else
                            mov renamed_keys.head,[r12].next
                        .endif
                        .if renamed_keys.tail == r12
                            mov renamed_keys.tail,rsi
                        .endif
                        mov [rbx].name,[r12].name
                        mov [rbx].len,[r12].length
                        AddResWord(edi)
                       .return
                    .endif
                .endif
                .break
            .endif
        .endf
    .endif

    movzx esi,length
    mov [rbx].len,sil
    mov [rbx].name,LclAlloc(esi)
    ; convert to lowercase?
    tmemcpy(rax, &newname, esi)
    AddResWord(edi)
    ret

RenameKeyword endp

    assume r12:nothing

; depending on 64bit on or off, some instructions must be added,
; some removed. Currently this is a bit hackish.

Set64Bit proc fastcall uses rsi rdi rbx r12 newmode:int_t

    .if ( ecx != b64bit )

        lea r12,ResWordTable

        .if ( ecx != FALSE )

            inc optable_idx[(T_INC-SPECIAL_LAST)*2] ; skip the one-byte register INC
            inc optable_idx[(T_DEC-SPECIAL_LAST)*2] ; skip the one-byte register DEC

            .for ( esi = 0: esi < lengthof(patchtab64): esi++ )

                lea  rcx,patchtab64
                mov  edi,[rcx+rsi*4]
                imul ebx,edi,ReservedWord
                add  rbx,r12

                .for ( : [rbx].flags & RWF_X64 : rbx+=ReservedWord, edi++ )
                    .if ( !( [rbx].flags & RWF_DISABLED ) )
                        AddResWord(edi)
                    .endif
                .endf
            .endf

            .for ( esi = 0: esi < lengthof(patchtab32): esi++ )

                lea  rcx,patchtab32
                mov  edi,[rcx+rsi*4]
                imul ebx,edi,ReservedWord
                add  rbx,r12

                .for ( : [rbx].flags & RWF_IA32 : rbx+=ReservedWord, edi++ )
                    .if ( !( [rbx].flags & RWF_DISABLED ) )
                        RemoveResWord(edi)
                    .endif
                .endf
            .endf

            .for ( r8 = &patchtabr,
                   r9 = &optable_idx,
                   edi = 0 : edi < sizeof(patchtabr) : edi+=replace_ins )
                movzx edx,[r8+rdi].replace_ins.tok
                mov eax,[r8+rdi].replace_ins.idx64
                mov [r9+rdx*2],ax
            .endf

        .else

            dec optable_idx[(T_INC - SPECIAL_LAST)*2] ;; restore the one-byte register INC
            dec optable_idx[(T_DEC - SPECIAL_LAST)*2] ;; restore the one-byte register DEC

            .for ( esi = 0: esi < lengthof(patchtab64): esi++ )

                lea  rcx,patchtab64
                mov  edi,[rcx+rsi*4]
                imul ebx,edi,ReservedWord
                add  rbx,r12

                .for ( : [rbx].flags & RWF_X64 : rbx+=ReservedWord, edi++ )
                    .if ( !( [rbx].flags & RWF_DISABLED ) )
                        RemoveResWord(edi)
                    .endif
                .endf
            .endf

            .for ( esi = 0: esi < lengthof(patchtab32): esi++ )

                lea  rcx,patchtab32
                mov  edi,[rcx+rsi*4]
                imul ebx,edi,ReservedWord
                add  rbx,r12

                .for ( : [rbx].flags & RWF_IA32 : rbx+=ReservedWord, edi++ )
                    .if ( !( [rbx].flags & RWF_DISABLED ) )
                        AddResWord(edi)
                    .endif
                .endf
            .endf

            .for ( r8 = &patchtabr,
                   r9 = &optable_idx,
                   edi = 0 : edi < sizeof(patchtabr): edi+=replace_ins )
                movzx edx,[r8+rdi].replace_ins.tok
                mov eax,[r8+rdi].replace_ins.idx32
                mov [r9+rdx*2],ax
            .endf

        .endif
        mov b64bit,newmode
    .endif
    ret

Set64Bit endp

DisableKeyword proc fastcall uses rdi rbx token:uint_t

    mov edi,ecx
    lea rbx,ResWordTable
    shl edi,4

    .if ( !( [rbx+rdi].flags & RWF_DISABLED ) )

        RemoveResWord(ecx)

        mov [rbx+rdi].next,0
        or  [rbx+rdi].flags,RWF_DISABLED
        shr edi,4
        .if Removed.Head == 0
            mov Removed.Head,di
        .else
            movzx ecx,Removed.Tail
            shl ecx,4
            mov [rbx+rcx].next,di
        .endif
        mov Removed.Tail,di
    .endif
    ret

DisableKeyword endp

;; check if a keyword is in the list of disabled words.

IsKeywordDisabled proc __ccall uses rdi rbx name:string_t, len:int_t

    movzx edi,Removed.Head
    .for ( : edi : )

        lea rbx,ResWordTable
        imul ecx,edi,ReservedWord
        add rbx,rcx
        mov rdx,[rbx].name
        mov r8d,len
        .if byte ptr [rdx+r8] == 0
            .return(TRUE) .ifd !tmemicmp( name, rdx, r8d )
        .endif
        mov di,[rbx].next
    .endf
    .return(FALSE)

IsKeywordDisabled endp


; get current name of a reserved word.
; max size is 255.

GetResWName proc __ccall resword:uint_t, buff:string_t

    .data?
    intbuff char_t 256 dup(?)
    .code

    lea     rax,intbuff
    test    rdx,rdx
    cmovnz  rax,rdx
    lea     r11,ResWordTable
    shl     ecx,4
    mov     r10,rdi
    mov     rdx,rsi
    mov     rdi,rax
    mov     rsi,[r11+rcx].name
    movzx   ecx,[r11+rcx].len
    rep     movsb
    mov     byte ptr [rdi],0

    mov     rsi,rdx
    mov     rdi,r10
    ret

GetResWName endp


;; ResWordsInit() initializes the reserved words hash array ( resw_table[] )
;; and also the reserved words string pointers ( ResWordTable[].name + ResWordTable[].len )

ResWordsInit proc __ccall uses rsi rdi rbx

    ; exit immediately if table is already initialized

    .return .if ResWordTable[ReservedWord].name

    ; clear hash table

    lea rdi,resw_table
    mov ecx,sizeof(resw_table)/4
    xor eax,eax
    rep stosd

    ; currently these flags must be set manually, since the
    ; RWF_ flags aren't contained in instravx.inc

    or ResWordTable[T_VPEXTRQ*ReservedWord].flags,RWF_X64
    or ResWordTable[T_VPINSRQ*ReservedWord].flags,RWF_X64

    ; initialize ResWordTable[].name and .len.
    ; add keyword to hash table ( unless it is 64-bit only ).
    ; v2.09: start with index = 1, since index 0 is now T_NULL

    .for ( rsi = &resw_strings,
           rbx = &ResWordTable,
           rbx += ReservedWord,
           edi = 1: edi < ResWordCount: edi++, rbx += ReservedWord )

        mov [rbx].name,rsi
        movzx eax,[rbx].len
        add rsi,rax
        .if ( !( [rbx].flags & RWF_X64 ) )
            AddResWord(edi)
        .endif
    .endf
    ret

ResWordsInit endp

; ResWordsFini() is called once per module
; it restores the resword table

    assume rsi:ptr rename_node
    assume rdi:ptr rename_node

ResWordsFini proc __ccall uses rsi rdi rbx

    ; restore renamed keywords.
    ; the keyword has to removed ( and readded ) from the hash table,
    ; since its position most likely will change.

    .for ( rdi = renamed_keys.head : rdi : rdi = rsi )

        mov rsi,[rdi].next
        movzx ebx,[rdi].token
        RemoveResWord(ebx)

        ; v2.06: this is the correct name to free

        imul ecx,ebx,ReservedWord
        mov [r11+rcx].name,[rdi].name
        mov [r11+rcx].len,[rdi].length

        AddResWord(ebx)
    .endf
    mov renamed_keys.head,NULL

    ; reenter disabled keywords

    lea rbx,ResWordTable
    movzx edi,Removed.Head
    .for ( : edi : di = si )

        imul ecx,edi,ReservedWord
        mov si,[rbx+rcx].next
        and [rbx+rcx].flags,not RWF_DISABLED
        .if ( !( [rbx+rcx].flags & RWF_X64 ) )
            AddResWord(edi)
        .endif
    .endf
    mov Removed.Head,0
    mov Removed.Tail,0
    ret

ResWordsFini endp

    option win64:rsp noauto nosave

    align 8

FindResWord proc fastcall name:string_t, size:uint_t

    test    edx,edx
    jz      .skip
    cmp     edx,max_resw_len
    ja      .skip
    cmp     byte ptr [rcx],'_'
    je      .skip

    movzx   eax,byte ptr [rcx]
    cmp     al,'_'
    je      .skip

    mov     r8,rcx
    mov     r9,rcx

    or      al,0x20
    xor     eax,( FNVPRIME * FNVBASE ) and 0xFFFFFFFF
    inc     r8
    mov     dh,dl
    dec     dh
    jz      .1
.0:
    mov     rcx,0x2020202020202020
    or      rcx,[r8]
    imul    eax,eax,FNVPRIME
    xor     al,cl
    dec     dh
    jz      .1
    imul    eax,eax,FNVPRIME
    xor     al,ch
    dec     dh
    jz      .1
    shr     rcx,16
    imul    eax,eax,FNVPRIME
    xor     al,cl
    dec     dh
    jz      .1
    imul    eax,eax,FNVPRIME
    xor     al,ch
    dec     dh
    jz      .1
    shr     rcx,16
    imul    eax,eax,FNVPRIME
    xor     al,cl
    dec     dh
    jz      .1
    imul    eax,eax,FNVPRIME
    xor     al,ch
    dec     dh
    jz      .1
    shr     rcx,16
    imul    eax,eax,FNVPRIME
    xor     al,cl
    dec     dh
    jz      .1
    imul    eax,eax,FNVPRIME
    xor     al,ch
    add     r8,8
    dec     dh
    jnz     .0
.1:
    and     eax,HASH_TABITEMS-1
    lea     r11,ResWordTable
    lea     r8,resw_table
    movzx   eax,word ptr [r8+rax*2]
    test    eax,eax
    jz      .done
.2:
    imul    ecx,eax,ReservedWord
    cmp     dl,[r11+rcx].len
    jne     .next
    mov     r8,[r11+rcx].name
    movzx   ecx,dl
if 0
.dd:
    test    ecx,-4
    jz      .db
    sub     ecx,4
    mov     r10d,[r9+rcx]
    cmp     r10d,[r8+rcx]
    je      .dd
    add     ecx,4
.db:
    test    ecx,ecx
    jz      .done
    dec     ecx
else
.db:
    dec     ecx
    jz      .done
endif
    mov     r10b,[r9+rcx]
    cmp     r10b,[r8+rcx]
    je      .db
    or      r10b,0x20
    cmp     r10b,[r8+rcx]
    je      .db
.next:
    shl     eax,4
    movzx   eax,[r11+rax].next
    test    eax,eax
    jnz     .2
.skip:
    xor     eax,eax
.done:
    ret

FindResWord endp

else

get_hash proc fastcall private token:string_t, len:byte

    xor     eax,eax
    test    edx,edx
    jz      .1
    mov     eax,FNVBASE
.0:
    mov     ebx,[ecx]
    or      ebx,0x20202020
    imul    eax,eax,FNVPRIME
    xor     al,bl
    dec     edx
    jz      .1
    imul    eax,eax,FNVPRIME
    xor     al,bh
    dec     edx
    jz      .1
    shr     ebx,16
    imul    eax,eax,FNVPRIME
    xor     al,bl
    dec     edx
    jz      .1
    imul    eax,eax,FNVPRIME
    xor     al,bh
    add     ecx,4
    dec     edx
    jnz     .0
.1:
    and     eax,HASH_TABITEMS-1
    ret

get_hash endp

; add reserved word to hash table

    assume esi:ptr ReservedWord

AddResWord proc fastcall private uses esi edi ebx token:int_t

    mov     edi,ecx
    lea     esi,ResWordTable
    movzx   edx,[esi+edi*8].len
    mov     ecx,[esi+edi*8].name
    call    get_hash
    lea     ebx,resw_table[eax*2]

    ; sort the items of a line by length!

    movzx   ecx,word ptr [ebx]
    shl     ecx,3
    jz      .1
    mov     al,[esi+edi*8].len
.0:
    cmp     [esi+ecx].len,al
    ja      .1
    mov     edx,ecx
    movzx   ecx,[esi+ecx].next
    shl     ecx,3
    jnz     .0
.1:
    test    edx,edx
    jnz     .2
    mov     [esi+edi*8].next,[ebx]
    mov     [ebx],di
    jmp     .3
.2:
    mov     [esi+edi*8].next,[esi+edx].next
    mov     [esi+edx].next,di
.3:
    ret

AddResWord endp

; remove a reserved word from the hash table.

RemoveResWord proc fastcall uses esi edi ebx token:int_t

    mov     edi,ecx
    lea     esi,ResWordTable
    movzx   edx,[esi+edi*8].len
    mov     ecx,[esi+edi*8].name
    call    get_hash
    lea     ebx,resw_table[eax*2]

    movzx   ecx,word ptr [ebx]
    test    ecx,ecx
    jz      .3
.0:
    cmp     ecx,edi
    jne     .2
    shl     edx,3
    jz      .1
    mov     [esi+edx].next,[esi+ecx*8].next
    mov     eax,TRUE
    jmp     .4
.1:
    mov     [ebx],[esi+ecx*8].next
    mov     eax,TRUE
    jmp     .4
.2:
    mov     edx,ecx
    movzx   ecx,[esi+ecx*8].next
    test    ecx,ecx
    jnz     .0
.3:
    xor     eax,eax
.4:
    ret

RemoveResWord endp

    assume esi:nothing

rename_node struct
next        ptr_t ?
name        string_t ?  ;  the original name in resw_strings[]
token       dw ?        ; is either enum instr_token or enum special_token
length      db ?
rename_node ends

; Rename a keyword - used by OPTION RENAMEKEYWORD.
; - token: keyword to rename
; - name: new name of keyword
; - length: length of new name

    assume edi:ptr rename_node

RenameKeyword proc uses esi edi ebx token:uint_t, name:string_t, length:byte

    local newname[64]:char_t ;; added v2.26

    .for ( edi = &newname, esi = name :: )

        lodsb
        .break .if !al
        or al,0x20 ;; '@' --> 'ï'..
        stosb
    .endf
    stosb

    ; v2.11: do nothing if new name matches current name
    mov ebx,token

    .if ( ResWordTable[ebx*8].len == length )

        .return .if !tmemicmp( &newname, ResWordTable[ebx*8].name, length )
    .endif

    RemoveResWord( ebx )

    ; if it is the first rename action for this keyword,
    ; the original name must be saved.

    lea eax,resw_strings
    lea ecx,[eax+size_resw_strings]
    mov esi,ResWordTable[ebx*8].name

    .if (  esi >= eax && esi < ecx )
        mov edi,LclAlloc( sizeof( rename_node ) )
        mov [edi].next,NULL
        mov [edi].name,esi
        mov [edi].token,bx
        mov [edi].length,ResWordTable[ebx*8].len

        .if renamed_keys.head == NULL
            mov renamed_keys.head,edi
            mov renamed_keys.tail,edi
        .else
            mov edx,renamed_keys.tail
            mov [edx].rename_node.next,edi
            mov renamed_keys.tail,edi
        .endif
    .else
        ; v2.11: search the original name. if the "new" names matches
        ; the original name, restore the name pointer
        .for ( edi = renamed_keys.head, esi = NULL: edi: esi = edi )
            .if ( [edi].token == bx )
                .if ( [edi].length == length )
                    .if !tmemcmp( &newname, [edi].name, length )
                        .if esi
                            mov [esi].rename_node.next,[edi].next
                        .else
                            mov renamed_keys.head,[edi].next
                        .endif
                        .if renamed_keys.tail == edi
                            mov renamed_keys.tail,esi
                        .endif
                        mov ResWordTable[ebx*8].name,[edi].name
                        mov ResWordTable[ebx*8].len,[edi].length
                        AddResWord(ebx)
                        .return
                    .endif
                .endif
                .break
            .endif
        .endf
    .endif
    movzx esi,length
    mov ResWordTable[ebx*8].name,LclAlloc(esi)
    ; convert to lowercase?
    tmemcpy(ResWordTable[ebx*8].name, &newname, esi)
    mov ResWordTable[ebx*8].len,length
    AddResWord(ebx)
    ret

RenameKeyword endp

; depending on 64bit on or off, some instructions must be added,
; some removed. Currently this is a bit hackish.

Set64Bit proc uses esi edi ebx newmode:int_t

    .if ( newmode != b64bit )
        .if ( newmode != FALSE )
            inc optable_idx[(T_INC-SPECIAL_LAST)*2] ; skip the one-byte register INC
            inc optable_idx[(T_DEC-SPECIAL_LAST)*2] ; skip the one-byte register DEC

            .for ( edi = 0: edi < lengthof(patchtab64): edi++ )
                .for( ebx = patchtab64[edi*4]: ResWordTable[ebx*8].flags & RWF_X64: ebx++ )
                    .if ( !( ResWordTable[ebx*8].flags & RWF_DISABLED ) )
                        AddResWord(ebx)
                    .endif
                .endf
            .endf
            .for ( edi = 0: edi < lengthof(patchtab32): edi++ )
                .for( ebx = patchtab32[edi*4]: ResWordTable[ebx*8].flags & RWF_IA32: ebx++ )
                    .if ( !( ResWordTable[ebx*8].flags & RWF_DISABLED ) )
                        RemoveResWord(ebx)
                    .endif
                .endf
            .endf
            .for ( edi = 0: edi < lengthof(patchtabr): edi++ )
                imul ecx,edi,replace_ins
                movzx edx,patchtabr[ecx].tok
                mov optable_idx[edx*2],patchtabr[ecx].idx64
            .endf
        .else
            dec optable_idx[(T_INC - SPECIAL_LAST)*2] ;; restore the one-byte register INC
            dec optable_idx[(T_DEC - SPECIAL_LAST)*2] ;; restore the one-byte register DEC

            .for ( edi = 0: edi < lengthof(patchtab64): edi++ )
                .for( ebx = patchtab64[edi*4]: ResWordTable[ebx*8].flags & RWF_X64: ebx++ )
                    .if ( !( ResWordTable[ebx*8].flags & RWF_DISABLED ) )
                        RemoveResWord(ebx)
                    .endif
                .endf
            .endf
            .for ( edi = 0: edi < lengthof( patchtab32 ): edi++ )
                .for( ebx = patchtab32[edi*4]: ResWordTable[ebx*8].flags & RWF_IA32: ebx++ )
                    .if ( !( ResWordTable[ebx*8].flags & RWF_DISABLED ) )
                        AddResWord(ebx)
                    .endif
                .endf
            .endf
            .for ( edi = 0: edi < lengthof(patchtabr): edi++ )
                imul ecx,edi,replace_ins
                movzx edx,patchtabr[ecx].tok
                mov optable_idx[edx*2],patchtabr[ecx].idx32
            .endf
        .endif
        mov b64bit,newmode
    .endif
    ret

Set64Bit endp

DisableKeyword proc uses ebx token:uint_t
    mov ebx,token
    .if ( !( ResWordTable[ebx*8].flags & RWF_DISABLED ) )
        RemoveResWord(ebx)
        mov ResWordTable[ebx*8].next,0
        or  ResWordTable[ebx*8].flags,RWF_DISABLED
        .if Removed.Head == 0
            mov Removed.Head,bx
            mov Removed.Tail,bx
        .else
            movzx ecx,Removed.Tail
            mov ResWordTable[ecx*8].next,bx
            mov Removed.Tail,bx
        .endif
    .endif
    ret

DisableKeyword endp

; check if a keyword is in the list of disabled words.

IsKeywordDisabled proc uses ebx name:string_t, len:int_t

    xor ebx,ebx
    .for ( bx = Removed.Head : ebx : bx = ResWordTable[ebx*8].next )
        mov ecx,ResWordTable[ebx*8].name
        mov eax,len
        .if byte ptr [ecx+eax] == 0
            .return(TRUE) .if !tmemicmp( name, ecx, eax )
        .endif
    .endf
    mov eax,FALSE
    ret

IsKeywordDisabled endp


; get current name of a reserved word.
; max size is 255.

GetResWName proc resword:uint_t, buff:string_t

    .data?
    intbuff char_t 256 dup(?)
    .code

    lea edx,intbuff
    .if buff
        mov edx,buff
    .endif

    push    edx
    mov     eax,resword
    movzx   ecx,ResWordTable[eax*8].len
    mov     eax,ResWordTable[eax*8].name
    xchg    eax,esi
    xchg    edx,edi
    rep     movsb
    mov     byte ptr [edi],0
    mov     esi,eax
    mov     edi,edx
    pop     eax
    ret

GetResWName endp


; ResWordsInit() initializes the reserved words hash array ( resw_table[] )
; and also the reserved words string pointers ( ResWordTable[].name + ResWordTable[].len )

ResWordsInit proc uses esi edi

    ; exit immediately if table is already initialized
    .return .if ResWordTable[1*8].name

    ; clear hash table
    lea edi,resw_table
    mov ecx,sizeof(resw_table)/4
    xor eax,eax
    rep stosd

    ; currently these flags must be set manually, since the
    ; RWF_ flags aren't contained in instravx.h
    or ResWordTable[T_VPEXTRQ*8].flags,RWF_X64
    or ResWordTable[T_VPINSRQ*8].flags,RWF_X64

    ; initialize ResWordTable[].name and .len.
    ; add keyword to hash table ( unless it is 64-bit only ).
    ; v2.09: start with index = 1, since index 0 is now T_NULL
    lea esi,resw_strings
    .for ( edi = 1: edi < ResWordCount: edi++ )
        mov ResWordTable[edi*8].name,esi
        movzx eax,ResWordTable[edi*8].len
        add esi,eax
        .if ( !( ResWordTable[edi*8].flags & RWF_X64 ) )
            AddResWord(edi)
        .endif
    .endf
    ret

ResWordsInit endp

; ResWordsFini() is called once per module
; it restores the resword table

ResWordsFini proc uses esi edi ebx

    assume esi:ptr rename_node
    assume edi:ptr rename_node

    ; restore renamed keywords.
    ; the keyword has to removed ( and readded ) from the hash table,
    ; since its position most likely will change.

    .for ( edi = renamed_keys.head: edi: )
        mov esi,[edi].next
        movzx ebx,[edi].token
        RemoveResWord(ebx)
        ; v2.06: this is the correct name to free
        mov ResWordTable[ebx*8].name,[edi].name
        mov ResWordTable[ebx*8].len,[edi].length
        AddResWord(ebx)
        mov edi,esi
    .endf
    mov renamed_keys.head,NULL

    ; reenter disabled keywords
    xor ebx,ebx
    .for ( bx = Removed.Head: ebx != 0: bx = si )
        mov si,ResWordTable[ebx*8].next
        and ResWordTable[ebx*8].flags,not RWF_DISABLED
        .if ( !( ResWordTable[ebx*8].flags & RWF_X64 ) )
            AddResWord(ebx)
        .endif
    .endf
    mov Removed.Head,0
    mov Removed.Tail,0
    ret

ResWordsFini endp

    align 8

FindResWord proc fastcall w_name:string_t, w_size:uint_t

    test    edx,edx
    jz      .skip
    cmp     edx,max_resw_len
    ja      .skip
    cmp     byte ptr [ecx],'_'
    je      .skip

    push    edi
    push    ebx

    mov     edi,ecx
    movzx   eax,byte ptr [ecx]
    cmp     al,'_'
    je      .false

    or      al,0x20
    xor     eax,( FNVPRIME * FNVBASE ) and 0xFFFFFFFF
    inc     ecx
    mov     dh,dl
    dec     dh
    jz      .1
.0:
    mov     ebx,[ecx]
    or      ebx,0x20202020
    imul    eax,eax,FNVPRIME
    xor     al,bl
    dec     dh
    jz      .1
    imul    eax,eax,FNVPRIME
    xor     al,bh
    dec     dh
    jz      .1
    shr     ebx,16
    imul    eax,eax,FNVPRIME
    xor     al,bl
    dec     dh
    jz      .1
    imul    eax,eax,FNVPRIME
    xor     al,bh
    add     ecx,4
    dec     dh
    jnz     .0
.1:
    and     eax,HASH_TABITEMS-1
    movzx   eax,resw_table[eax*2]
    test    eax,eax
    jz      .done
.2:
    cmp     dl,ResWordTable[eax*8].len
    jne     .4
    mov     ebx,ResWordTable[eax*8].name
    movzx   ecx,dl
.3:
    dec     ecx
    jz      .done
    mov     dh,[edi+ecx]
    cmp     dh,[ebx+ecx]
    je      .3
    or      dh,0x20
    cmp     dh,[ebx+ecx]
    je      .3
.4:
    mov     ax,ResWordTable[eax*8].next
    test    eax,eax
    jnz     .2
.done:
    pop     ebx
    pop     edi
    ret
.false:
    xor     eax,eax
    pop     ebx
    pop     edi
    ret
.skip:
    xor     eax,eax
    ret

FindResWord endp

endif

    end
