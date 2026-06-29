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
public max_resw_len

.pragma list(push, 0)

.data?

; reserved words hash table
align size_t*2
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

    OP_MMX_M64_M08  = ( OP_MMX or OP_M64  or OP_M08 ),
    OP_MMX_M64_M16  = ( OP_MMX or OP_M64  or OP_M16 ),
    OP_MMX_M64_M32  = ( OP_MMX or OP_M64  or OP_M32 ),

    OP_XMM_M128_M08 = ( OP_XMM or OP_M128 or OP_M08 ),
    OP_XMM_M128_M16 = ( OP_XMM or OP_M128 or OP_M16 ),
    OP_XMM_M128_M32 = ( OP_XMM or OP_M128 or OP_M32 ),
    OP_XMM_M128_M64 = ( OP_XMM or OP_M128 or OP_M64 ),

    OP_YMM_M256_M08 = ( OP_YMM or OP_M256 or OP_M08 ),
    OP_YMM_M256_M32 = ( OP_YMM or OP_M256 or OP_M32 ),
    OP_YMM_M256_M64 = ( OP_YMM or OP_M256 or OP_M64 ),

    OP_XMM_MGT16   = ( OP_XMM or OP_M32 or OP_M64 ),
    OP_XMM_MXGT8   = ( OP_XMM or OP_M128 or OP_M16 or OP_M32 or OP_M64 ),
    OP_XMM_MXGT16  = ( OP_XMM or OP_M128 or OP_M32 or OP_M64 ),

    OP_YMM_M256    = ( OP_YMM or OP_M256 ),
    OP_ZMM_M512    = ( OP_ZMM or OP_M512 ),
    OP_YMM_M32     = ( OP_YMM or OP_M32 ),
    OP_YMM_M64     = ( OP_YMM or OP_M64 ),
    OP_ZMM_M32     = ( OP_ZMM or OP_M32 ),
    OP_ZMM_M64     = ( OP_ZMM or OP_M64 ),
    OP_XMM_M256    = ( OP_XMM or OP_M256 ),
    OP_XMM_M_ANY   = ( OP_XMM or OP_M_ANY ),

    OP_YMM_M128_M64= ( OP_YMM or OP_M128 or OP_M64 ),

    OP_ZMM_M512_M32= ( OP_ZMM or OP_M512 or OP_M32 ),
    OP_YMM_M128_M32= ( OP_YMM or OP_M128 or OP_M32 ),
    OP_ZMM_M128_M32= ( OP_ZMM or OP_M128 or OP_M32 ),
    OP_ZMM_M128_M64= ( OP_ZMM or OP_M128 or OP_M64 ),
    OP_ZMM_M512_M64= ( OP_ZMM or OP_M512 or OP_M64 ),
    OP_YMM_M128    = ( OP_YMM or OP_M128 ),
    OP_ZMM_M128    = ( OP_ZMM or OP_M128 ),
    OP_ZMM_M256    = ( OP_ZMM or OP_M256 ),
    OP_M256_M128   = ( OP_M256 or OP_M128 ),
    OP_XMM_YMM     = ( OP_XMM or OP_YMM ),
    OP_YMM_ZMM     = ( OP_YMM or OP_ZMM ),
    OP_M32_M64     = ( OP_M32 or OP_M64 ),
    OP_M32_M256    = ( OP_M32 or OP_M256 ),
    OP_M64_M256    = ( OP_M64 or OP_M256 ),
    OP_M32_M512    = ( OP_M32 or OP_M512 ),
    OP_M64_M512    = ( OP_M64 or OP_M512 ),
    OP_XMM_RMGT16  = ( OP_XMM or OP_RMGT16 ),
    OP_RMGT8       = ( OP_R16 or OP_R32 or OP_R64 or OP_M16 or OP_M32 or OP_M64 ),
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

intbuff char_t 256 dup(?)

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

OpCls macro op1, op2, op3
    exitm<OPC_&op1&&op2&&op3&>
    endm
InstFlags macro prefix, first, rm_info, op_dir
    exitm<prefix or ((first and 1) shl 3) or (rm_info shl 4) or (op_dir shl 7)>
    endm
avxins macro alias, tok, string, cpu, flgs
    exitm<>
    endm
insa macro tok, string, first, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, flags, vex, evex
    exitm<instr_item { opcls, byte1_info, InstFlags(prefix, first, rm_info, op_dir), cpu, evex, opcode, rm_byte }>
    endm
InstrTable label instr_item
include instruct.inc
include instr64.inc
insa(NULL,0,1,OpCls(NONE,NONE,NONE),0,0,0,0,0,0,0,0,0,0) ; last entry - needed for its ".first" (=1) field
undef insa

; define symbolic indices for InstrTable[]

.enum res_idx {
insa macro tok, string, first, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, flags, vex, evex
if first eq 1
    exitm<T_&tok&_I,>
else
    exitm<T_&tok&_&string&,>
endif
    endm
include instruct.inc
undef insa
undef avxins
insa macro tok, string, first, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, flags, vex, evex
if first eq 1
    exitm<T_&tok&_I64,>
else
    exitm<T_&tok&_&string&_I64,>
endif
    endm
include instr64.inc
undef insa
}

; create optable_idx, the index array for InstrTable.
; This is needed because instructions often need more than one entry in InstrTable.

optable_idx label word
insa macro tok, string, first, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, flags, vex, evex
if first eq 1
    dw T_&tok&_I
endif
    endm
avxins macro alias, tok, string, cpu, flgs
    dw T_&alias&_I
    endm
include instruct.inc
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

insa macro tok, string, first, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, flags, vex, evex
if first eq 1
if @SizeStr(string) gt MAX_RESW_LEN
    MAX_RESW_LEN = @SizeStr(string)
endif
    exitm<db "&string&">
endif
    endm
avxins macro alias, tok, string, cpu, flgs
if @SizeStr(string) gt MAX_RESW_LEN
    MAX_RESW_LEN = @SizeStr(string)
endif
    exitm<db "&string&">
    endm
include instruct.inc
undef insa
undef avxins

size_resw_strings equ $ - resw_strings

; create the 'reserved words' table (ResWordTable).
; this table's entries will be used to create the instruction hash table.
; v2.11: RWF_SPECIAL flag removed:
; { 0, sizeof(#string)-1, RWF_SPECIAL or flags, NULL },

.data
align size_t*2
ResWordTable ReservedWord 0 dup(<>)

    ReservedWord { 0, 0, 0, 0 } ;; dummy entry for T_NULL
res macro tok, string, type, value, bytval, flags, cpu, sflags
    ReservedWord { 0, @SizeStr(string), flags, HASH(string) }
    endm
include special.inc
undef res
res macro tok, string, value, bytval, flags, cpu, sflags
    ReservedWord { 0, @SizeStr(string), flags, HASH(string) }
    endm
include directve.inc
undef res

insa macro tok, string, first, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, flags, vex, evex
if first eq 1
    ReservedWord { 0, @SizeStr(string), flags, HASH(string) }
endif
    endm
avxins macro alias, tok, string, rwf, flgs
    ReservedWord { 0, @SizeStr(string), rwf, HASH(string) }
    endm
include instruct.inc
undef insa
undef avxins
ResWordCount equ ($ - ResWordTable) / ReservedWord

.data?
align size_t*2
ResWordNames string_t ResWordCount dup(?)

.data
align size_t*2

; these is a special 1-byte array for vex-encoded instructions.
; it could probably be moved to InstrTable[] (there is an unused byte),
; but in fact it's the wrong place, since the content of vex_flags[]
; are associated with opcodes, not with instruction variants.

vex_flags VexFlags 0 dup(<?>)

    ; flags for the AVX instructions in instruct.inc. The order must
    ; be equal to the one in instruct.h! ( this is to be improved.)
    ; For a description of the VX_ flags see codegen.inc

insa macro tok, string, first, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, flags, vex, evex
if first eq 1
if flags and ( RWF_VEX or RWF_EVEX )
    db vex
endif
endif
    endm
avxins macro alias, tok, string, cpu, flgs
    db flgs
    endm
include instruct.inc
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


masmkeywords instr_token T_NAME, T_TITLE, T_PAGE, T_SIZE, T_LENGTH, T_THIS, T_MASK, T_WIDTH, T_TYPE, T_HIGH, T_LOW, 0

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

ResWordInitialized int_t FALSE

.pragma list(pop)

.code


FindResWord proc fastcall _name:string_t, size:uint_t
ifdef _WIN64
    mov     r10,rbx
    define  rqs <r8>
    define  rgn <r9>
else
    push    esi
    push    edi
    push    ebx
    define  rqs <esi>
    define  rgn <edi>
endif
    test    edx,edx
    jz      .6
    cmp     edx,max_resw_len
    ja      .6
    mov     rgn,rcx
    mov     rqs,rcx
    movzx   eax,byte ptr [rgn]
    cmp     al,'_'
    je      .6
    mov     ebx,edx
    or      al,0x20
    xor     eax,( FNVPRIME * FNVBASE ) and 0xFFFFFFFF
    dec     edx
    jz      .1
    inc     rgn
.0:
    mov     ecx,[rgn]
    or      ecx,0x20202020
    imul    eax,eax,FNVPRIME
    xor     al,cl
    dec     edx
    jz      .1
    imul    eax,eax,FNVPRIME
    xor     al,ch
    dec     edx
    jz      .1
    shr     ecx,16
    imul    eax,eax,FNVPRIME
    xor     al,cl
    dec     edx
    jz      .1
    imul    eax,eax,FNVPRIME
    xor     al,ch
    add     rgn,4
    dec     edx
    jnz     .0
.1:
    mov     edx,eax
    and     eax,HASH_TABITEMS-1
ifdef _WIN64
    lea     rcx,ResWordTable
    lea     rgn,resw_table
    movzx   eax,word ptr [rgn+rax*2]
    test    eax,eax
    jz      .7
.3:
    cmp     bl,[rcx+rax*8].ReservedWord.len
    jne     .5
    cmp     edx,[rcx+rax*8].ReservedWord.hash
    je      .7
.5:
    movzx   eax,[rcx+rax*8].ReservedWord.next
else
    movzx   eax,resw_table[eax*2]
    test    eax,eax
    jz      .7
.3:
    cmp     bl,ResWordTable[eax*8].len
    jne     .5
    cmp     edx,ResWordTable[eax*8].hash
    je      .7
.5:
    movzx   eax,ResWordTable[eax*8].next
endif
    test    eax,eax
    jnz     .3
.6:
    xor     eax,eax
.7:
ifdef _WIN64
    mov     rbx,r10
else
    pop     ebx
    pop     edi
    pop     esi
endif
    ret
    endp

; add reserved word to hash table

AddResWord proc fastcall private token:int_t
ifdef _WIN64
    mov     r9d,ecx
    lea     r10,ResWordTable
    mov     eax,[r10+rcx*8].ReservedWord.hash
    and     eax,HASH_TABITEMS-1
    lea     rcx,resw_table
    lea     r11,[rcx+rax*2]
    xor     edx,edx

    ; sort the items of a line by length!

    movzx   ecx,word ptr [r11]
    test    ecx,ecx
    jz      .1
    mov     al,[r10+r9*8].ReservedWord.len
.0:
    cmp     al,[r10+rcx*8].ReservedWord.len
    jbe     .1
    mov     edx,ecx
    movzx   ecx,[r10+rcx*8].ReservedWord.next
    test    ecx,ecx
    jnz     .0
.1:
    mov     ecx,r9d
    test    edx,edx
    jnz     .2
    mov     [r10+rcx*8].ReservedWord.next,[r11]
    mov     [r11],r9w
    jmp     .3
.2:
    mov     [r10+rcx*8].ReservedWord.next,[r10+rdx*8].ReservedWord.next
    mov     [r10+rdx*8].ReservedWord.next,r9w
.3:
else
    push    esi
    push    edi
    mov     esi,ecx
    mov     eax,ResWordTable[ecx*8].ReservedWord.hash
    and     eax,HASH_TABITEMS-1
    lea     edi,resw_table[eax*2]
    xor     edx,edx

    ; sort the items of a line by length!

    movzx   ecx,word ptr [edi]
    test    ecx,ecx
    jz      .1
    mov     al,ResWordTable[esi*8].len
.0:
    cmp     al,ResWordTable[ecx*8].len
    jbe     .1
    mov     edx,ecx
    movzx   ecx,ResWordTable[ecx*8].next
    test    ecx,ecx
    jnz     .0
.1:
    mov     ecx,esi
    test    edx,edx
    jnz     .2
    mov     ResWordTable[ecx*8].next,[edi]
    mov     [edi],si
    jmp     .3
.2:
    mov     ResWordTable[ecx*8].next,ResWordTable[edx*8].next
    mov     ResWordTable[edx*8].next,si
.3:
    pop     edi
    pop     esi
endif
    ret
    endp


; remove a reserved word from the hash table.

RemoveResWord proc fastcall token:int_t
ifdef _WIN64
    mov     r9d,ecx
    lea     r10,ResWordTable
    mov     eax,[r10+rcx*8].ReservedWord.hash
    and     eax,HASH_TABITEMS-1
    lea     rcx,resw_table
    xor     edx,edx
    lea     r11,[rcx+rax*2]
    movzx   ecx,word ptr [r11]
    test    ecx,ecx
    jz      .3
.0:
    cmp     ecx,r9d
    jne     .2
    test    edx,edx
    jz      .1
    mov     [r10+rdx*8].ReservedWord.next,[r10+rcx*8].ReservedWord.next
    mov     eax,TRUE
    jmp     .4
.1:
    mov     [r11],[r10+rcx*8].ReservedWord.next
    mov     eax,TRUE
    jmp     .4
.2:
    mov     edx,ecx
    movzx   ecx,[r10+rcx*8].ReservedWord.next
    test    ecx,ecx
    jnz     .0
.3:
    xor     eax,eax
.4:
else
    push    esi
    push    edi
    mov     esi,ecx
    mov     eax,ResWordTable[ecx*8].hash
    and     eax,HASH_TABITEMS-1
    xor     edx,edx
    lea     edi,resw_table[eax*2]
    movzx   ecx,word ptr [edi]
    test    ecx,ecx
    jz      .3
.0:
    cmp     ecx,esi
    jne     .2
    test    edx,edx
    jz      .1
    mov     ResWordTable[edx*8].next,ResWordTable[ecx*8].next
    mov     eax,TRUE
    jmp     .4
.1:
    mov     [edi],ResWordTable[ecx*8].next
    mov     eax,TRUE
    jmp     .4
.2:
    mov     edx,ecx
    movzx   ecx,ResWordTable[ecx*8].next
    test    ecx,ecx
    jnz     .0
.3:
    xor     eax,eax
.4:
    pop     edi
    pop     esi
endif
    ret
    endp


rename_node struct
next        ptr rename_node ?
name        string_t ?  ; the original name in resw_strings[]
hash        dd ?
token       dw ?        ; is either enum instr_token or enum special_token
length      db ?
rename_node ends

; Rename a keyword - used by OPTION RENAMEKEYWORD.
; - token:  keyword to rename
; - name:   new name of keyword
; - length: length of new name

    assume rbx:ptr ReservedWord

RenameKeyword proc __ccall uses rsi rdi rbx token:uint_t, name:string_t, length:byte

   .new nameptr:string_t
   .new newname[64]:char_t ; added v2.26
   .new hash:dword

    ldr ecx,token
    ldr rdx,name

    .for ( ebx = FNVBASE, rdi = &newname, rsi = rdx :: )
        lodsb
        .break .if !al
        imul ebx,ebx,FNVPRIME
        or al,0x20 ;; '@' --> 'ï'..
        xor bl,al
        stosb
    .endf
    stosb
    mov hash,ebx

    ; v2.11: do nothing if new name matches current name

    mov edi,ecx
    lea rax,ResWordTable
    lea rdx,ResWordNames
    lea rbx,[rax+rcx*8]
    lea rsi,[rdx+rcx*string_t]
    movzx ecx,length
    .if ( cl == [rbx].len )
        .return .ifd !tmemicmp( &newname, [rsi], ecx )
    .endif
    RemoveResWord( edi )

    ; if it is the first rename action for this keyword,
    ; the original name must be saved.

    lea rax,resw_strings
    lea rcx,[rax+size_resw_strings]
    mov rdx,[rsi]
    .if ( rdx >= rax && rdx < rcx )
        mov rcx,LclAlloc( sizeof( rename_node ) )
        mov [rcx].rename_node.name,[rsi]
        mov [rcx].rename_node.token,di
        mov [rcx].rename_node.hash,[rbx].hash
        mov [rcx].rename_node.length,[rbx].len
        .if renamed_keys.head == NULL
            mov renamed_keys.head,rcx
            mov renamed_keys.tail,rcx
        .else
            mov rdx,renamed_keys.tail
            mov [rdx].rename_node.next,rcx
            mov renamed_keys.tail,rcx
        .endif
    .else

        ; v2.11: search the original name. if the "new" names matches
        ; the original name, restore the name pointer
        ;
        ; v2.17: fixed infinite loop ( curr wasn't changed )

        mov nameptr,rsi
        assume rdi:ptr rename_node
        .for ( rdi = renamed_keys.head, rsi = NULL : rdi : rsi = rdi, rdi = [rdi].next )
            mov eax,token
            .if ( ax == [rdi].token )
                .if ( [rdi].length == length )
                    .ifd !tmemcmp( &newname, [rdi].name, length )
                        .if rsi
                            mov [rsi].rename_node.next,[rdi].next
                        .else
                            mov renamed_keys.head,[rdi].next
                        .endif
                        .if renamed_keys.tail == rdi
                            mov renamed_keys.tail,rsi
                        .endif
                        mov rdx,nameptr
                        mov [rdx],[rdi].name
                        mov [rbx].hash,[rdi].hash
                        mov [rbx].len,[rdi].length
                        AddResWord(token)
                       .return
                    .endif
                .endif
                .break
            .endif
        .endf
        mov rsi,nameptr
        assume rdi:nothing
    .endif
    mov [rbx].hash,hash
    movzx ecx,length
    mov [rbx].len,cl
    mov edi,ecx
    mov rcx,LclAlloc(ecx)
    mov [rsi],rax
    ; convert to lowercase?
    tmemcpy(rcx, &newname, edi)
    AddResWord(token)
    ret
    endp

; ResWordsInit() initializes the reserved words hash array ( resw_table[] )
; and also the reserved words string pointers ( ResWordNames[] + ResWordTable[].len )

ResWordsInit proc uses rsi rdi rbx

    ; exit immediately if table is already initialized

    .if ( !ResWordInitialized )

        inc ResWordInitialized

        ; clear hash table

        lea rdi,resw_table
        mov ecx,sizeof(resw_table)/4
        xor eax,eax
        rep stosd
        mov ResWordNames,rax

        ; currently these flags must be set manually, since the
        ; RWF_ flags aren't contained in instravx.inc

        ; or ResWordTable[T_VPEXTRQ*ReservedWord].flags,RWF_X64
        ; or ResWordTable[T_VPINSRQ*ReservedWord].flags,RWF_X64

        ; initialize ResWordTable[].name and .len.
        ; add keyword to hash table ( unless it is 64-bit only ).
        ; v2.09: start with index = 1, since index 0 is now T_NULL

        .for ( rsi = &resw_strings,
               rbx = &ResWordTable[ReservedWord],
               edi = 1 : edi < ResWordCount : edi++, rbx += ReservedWord )

            lea rcx,ResWordNames
            mov [rcx+rdi*string_t],rsi
            movzx eax,[rbx].len
            add rsi,rax
            .if ( !( [rbx].flags & RWF_X64 ) )
                AddResWord(edi)
            .endif
        .endf
    .endif
    ret
    endp

; ResWordsFini() is called once per module
; it restores the resword table

ResWordsFini proc uses rsi rdi rbx

    ; restore renamed keywords.
    ; the keyword has to removed ( and readded ) from the hash table,
    ; since its position most likely will change.

    assume rdi:ptr rename_node
    .for ( rdi = renamed_keys.head : rdi : rdi = rbx )

        mov rbx,[rdi].next
        movzx esi,[rdi].token
        RemoveResWord(esi)

        ; v2.06: this is the correct name to free

        lea rdx,ResWordTable
        lea rcx,ResWordNames
        mov [rcx+rsi*string_t],[rdi].name
        mov [rdx+rsi*8].ReservedWord.len,[rdi].length
        mov [rdx+rsi*8].ReservedWord.hash,[rdi].hash
        AddResWord(esi)
    .endf
    mov renamed_keys.head,NULL
    assume rdi:nothing

    ; reenter disabled keywords

    lea rbx,ResWordTable
    movzx edi,Removed.Head
    .for ( : edi : di = si )
        mov si,[rbx+rdi*8].next
        and [rbx+rdi*8].flags,not RWF_DISABLED
        .if !( [rbx+rdi*8].flags & RWF_X64 )
            AddResWord(edi)
        .endif
    .endf
    mov Removed.Head,0
    mov Removed.Tail,0
    ret
    endp


DisableKeyword proc fastcall uses rsi rbx token:uint_t

    mov  esi,ecx
    lea  rbx,ResWordTable
    .if !( [rbx+rsi*8].flags & RWF_DISABLED )
        RemoveResWord(ecx)
        mov [rbx+rsi*8].next,0
        or  [rbx+rsi*8].flags,RWF_DISABLED
        .if Removed.Head == 0
            mov Removed.Head,si
        .else
            movzx ecx,Removed.Tail
            mov [rbx+rcx*8].next,si
        .endif
        mov Removed.Tail,si
    .endif
    ret
    endp


EnableKeyword proc fastcall uses rsi rdi rbx token:uint_t

    lea rbx,ResWordTable
    .if ( ( [rbx+rcx*8].flags & RWF_DISABLED ) )
        .if ( Removed.Head == cx )
            mov Removed.Head,[rbx+rcx*8].next
        .else
            movzx edi,Removed.Head
            .for ( : edi : edi = esi )
                movzx esi,[rbx+rdi*8].next
                .if esi == ecx
                    mov [rbx+rdi*8].next,[rbx+rcx*8].next
                   .break
                .endif
            .endf
        .endif
        .if Removed.Tail == cx
            mov Removed.Tail,Removed.Head
        .endif
        and [rbx+rcx*8].flags,not RWF_DISABLED
        AddResWord(ecx)
    .endif
    ret
    endp


; check if a keyword is in the list of disabled words.

IsKeywordDisabled proc fastcall uses rsi rdi rbx _name:string_t, len:int_t
    mov rbx,rcx
    mov esi,edx
    movzx edi,Removed.Head
    .while ( edi )
        lea rdx,ResWordTable
        mov ecx,edi
        mov di,[rdx+rcx*8].ReservedWord.next
        lea rax,ResWordNames
        mov rdx,[rax+rcx*string_t]
        .if ( byte ptr [rdx+rsi] == 0 )
            .ifd !tmemicmp( rbx, rdx, esi )
                .return( TRUE )
            .endif
        .endif
    .endw
    .return( FALSE )
    endp

; depending on 64bit on or off, some instructions must be added,
; some removed. Currently this is a bit hackish.

Set64Bit proc __ccall uses rsi rdi rbx newmode:int_t

    ldr ecx,newmode

    .if ( ecx != b64bit )

        .if ( ecx != FALSE )

            inc optable_idx[(T_INC-SPECIAL_LAST)*2] ; skip the one-byte register INC
            inc optable_idx[(T_DEC-SPECIAL_LAST)*2] ; skip the one-byte register DEC

            .for ( esi = 0 : esi < lengthof(patchtab64) : esi++ )
                .for ( rcx = &patchtab64, rbx = &ResWordTable, edi = [rcx+rsi*4] : [rbx+rdi*8].flags & RWF_X64 : edi++ )
                    .if ( !( [rbx+rdi*8].flags & RWF_DISABLED ) )
                        AddResWord(edi)
                    .endif
                .endf
            .endf
            .for ( esi = 0 : esi < lengthof(patchtab32) : esi++ )
                .for ( rcx = &patchtab32, edi = [rcx+rsi*4] : [rbx+rdi*8].flags & RWF_IA32 : edi++ )
                    .if ( !( [rbx+rdi*8].flags & RWF_DISABLED ) )
                        RemoveResWord(edi)
                    .endif
                .endf
            .endf
            assume rbx:nothing
            .for ( rbx = &patchtabr, rcx = &optable_idx, edi = 0 : edi < sizeof(patchtabr) : edi+=replace_ins )
                movzx edx,[rbx+rdi].replace_ins.tok
                mov eax,[rbx+rdi].replace_ins.idx64
                mov [rcx+rdx*2],ax
            .endf

        .else

            dec optable_idx[(T_INC - SPECIAL_LAST)*2] ;; restore the one-byte register INC
            dec optable_idx[(T_DEC - SPECIAL_LAST)*2] ;; restore the one-byte register DEC

            assume rbx:ptr ReservedWord
            .for ( esi = 0 : esi < lengthof(patchtab64) : esi++ )
                .for ( rcx = &patchtab64, rbx = &ResWordTable, edi = [rcx+rsi*4] : [rbx+rdi*8].flags & RWF_X64 : edi++ )
                    .if ( !( [rbx+rdi*8].flags & RWF_DISABLED ) )
                        RemoveResWord(edi)
                    .endif
                .endf
            .endf
            .for ( esi = 0 : esi < lengthof(patchtab32) : esi++ )
                .for ( rcx = &patchtab32, edi = [rcx+rsi*4] : [rbx+rdi*8].flags & RWF_IA32 : edi++ )
                    .if ( !( [rbx+rdi*8].flags & RWF_DISABLED ) )
                        AddResWord(edi)
                    .endif
                .endf
            .endf
            assume rbx:nothing
            .for ( rbx = &patchtabr, rcx = &optable_idx, edi = 0 : edi < sizeof(patchtabr) : edi+=replace_ins )
                movzx edx,[rbx+rdi].replace_ins.tok
                mov eax,[rbx+rdi].replace_ins.idx32
                mov [rcx+rdx*2],ax
            .endf
        .endif
        mov b64bit,newmode
    .endif
    ret
    endp

; get current name of a reserved word.
; max size is 255.

GetResWName proc fastcall uses rsi rdi resword:uint_t, buff:string_t
    lea     rdi,intbuff
    test    rdx,rdx
ifdef __P686__
    cmovnz  rdi,rdx
else
    jz      @F
    mov     rdi,rdx
@@:
endif
    lea     rax,ResWordTable
    lea     rdx,ResWordNames
    mov     rsi,[rdx+rcx*string_t]
    movzx   ecx,[rax+rcx*8].ReservedWord.len
    mov     rax,rdi
    rep     movsb
    mov     byte ptr [rdi],0
    ret
    endp

; option masm:on|off

SetMasmKeywords proc fastcall uses rsi enable:int_t
    lea rsi,masmkeywords
    lodsd
    .if ( ecx )
        .while eax
            EnableKeyword( eax )
            lodsd
        .endw
    .else
        .while eax
            DisableKeyword( eax )
            lodsd
        .endw
    .endif
    ret
    endp

    end
