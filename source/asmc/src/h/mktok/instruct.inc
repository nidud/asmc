;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Description: table of instructions. Other reserved words see special.h
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; The order of items for an opcode (ins + insn) is IMPORTANT!
; And op1 has a higher precedence than op2.
; operands with type OP_A should be before OP_Rx & OP_R
; operands with type OP_M should follow OP_Mx
; operands with type OP_R should follow OP_Rx
; operands with type OP_I should follow OP_Ix
;
;
; v1.96: the table needn't be sorted anymore, but
; "additional" (=insn) entries must still be located after the
; main (=ins) entry. These entries must have a <suffix> so that <tok> +
; <suffix> gives a unique identifier.
;
;
; branch instructions
; there are some macros in codegen.h which rely on the order of the
; branch tokens. To satisfy those make sure:
; - the branch instructions are in order CALL, JMP, Jcc, JeCXZ, LOOPcc
; - no other instruction between these
;
;
;   tok	  (suffix)		op1-3			   b1_inf op_dir rm_inf opcode	 rm_byte       cpu	prefix */
;
insa(CALL, call,		OpCls( I16,  NONE,  NONE  ), 0,	     0,	 no_RM,	 0E8h,	   000h,   P_86,	    0)
insn(CALL, 1,			OpCls( I32,  NONE,  NONE  ), 0,	     0,	 no_RM,	 0E8h,	   000h,   P_386,	    0)
insn(CALL, 2,			OpCls( RGT8, NONE,  NONE  ), 0,	     0,	 no_WDS, 0FFh,	   010h,   P_86,	    0)
insn(CALL, 3,			OpCls( M32,  NONE,  NONE  ), F_32,   0,	 no_WDS, 0FFh,	   010h,   P_386,	    0)
insn(CALL, 4,			OpCls( M16,  NONE,  NONE  ), F_16,   0,	 no_WDS, 0FFh,	   010h,   P_86,	    0)
;
; start entries for FAR call
;
insm(CALL, 6,			OpCls( I32,  NONE,  NONE  ), F_16,   0,	 no_RM,	 09Ah,	   0,	   P_86,	    0)
insn(CALL, 7,			OpCls( I48,  NONE,  NONE  ), F_32,   0,	 no_RM,	 09Ah,	   0,	   P_386,	    0)
insn(CALL, 8,			OpCls( M32,  NONE,  NONE  ), F_16,   0,	 no_WDS, 0FFh,	   018h,   P_86,	    0)
insn(CALL, 9,			OpCls( M48,  NONE,  NONE  ), F_32,   0,	 no_WDS, 0FFh,	   018h,   P_386,	    0)
insa(JMP, jmp,			OpCls( I8,   NONE,  NONE  ), 0,	     0,	 no_RM,	 0EBh,	   0,	   P_86,	    0)
insn(JMP, 1,			OpCls( I16,  NONE,  NONE  ), 0,	     0,	 no_RM,	 0E9h,	   0,	   P_86,	    0)
insn(JMP, 2,			OpCls( I32,  NONE,  NONE  ), 0,	     0,	 no_RM,	 0E9h,	   0,	   P_386,	    0)
insn(JMP, 3,			OpCls( RGT8, NONE,  NONE  ), 0,	     0,	 no_WDS, 0FFh,	   020h,   P_86,	    0)
insn(JMP, 4,			OpCls( M32,  NONE,  NONE  ), F_32,   0,	 no_WDS, 0FFh,	   020h,   P_386,	    0)
insn(JMP, 5,			OpCls( M16,  NONE,  NONE  ), F_16,   0,	 no_WDS, 0FFh,	   020h,   P_86,	    0)
;
; entries for FAR jmp
;
insm(JMP, 7,			OpCls( I32,  NONE,  NONE  ), F_16,   0,	 no_RM,	 0EAh,	   00h, P_86,  0)
insn(JMP, 8,			OpCls( I48,  NONE,  NONE  ), F_32,   0,	 no_RM,	 0EAh,	   00h, P_386, 0)
insn(JMP, 9,			OpCls( M32,  NONE,  NONE  ), F_16,   0,	 no_WDS, 0FFh,	   28h, P_86,  0)
insn(JMP, 10,			OpCls( M48,  NONE,  NONE  ), F_32,   0,	 no_WDS, 0FFh,	   28h, P_386, 0)
;
; for conditional jumps, the SHORT version must always be first!
;
jcc	macro cond, dist, condlc
	insa(J&cond&, j&condlc&, OpCls(I8, NONE, NONE), 0, 0, no_RM, 0x70+dist, 0, P_86, 0)
	insn(J&cond&, 1, OpCls( I, NONE, NONE ), F_0F, 0, no_RM, 80h+dist, 0, P_386, 0)
	endm

jcc A,	 07h,	 a
jcc AE,	 03h,	ae
jcc B,	 02h,	 b
jcc BE,	 06h,	be
jcc C,	 02h,	 c
jcc E,	 04h,	 e
jcc G,	 0fh,	 g
jcc GE,	 0dh,	ge
jcc L,	 0ch,	 l
jcc LE,	 0eh,	le
jcc NA,	 06h,	na
jcc NAE, 02h,  nae
jcc NB,	 03h,	nb
jcc NBE, 07h,  nbe
jcc NC,	 03h,	nc
jcc NE,	 05h,	ne
jcc NG,	 0eh,	ng
jcc NGE, 0ch,  nge
jcc NL,	 0dh,	nl
jcc NLE, 0fh,  nle
jcc NO,	 01h,	no
jcc NP,	 0bh,	np
jcc NS,	 09h,	ns
jcc NZ,	 05h,	nz
jcc O,	 00h,	 o
jcc P,	 0ah,	 p
jcc PE,	 0ah,	pe
jcc PO,	 0bh,	po
jcc S,	 08h,	 s
jcc Z,	 04h,	 z


insx(JCXZ,   jcxz,	OpCls( I8,   NONE,  NONE  ), F_16A,  0,	 no_RM,	 0E3h, 0, P_86,	    0, RWF_IA32)
insa(JECXZ,  jecxz,	OpCls( I8,   NONE,  NONE  ), F_32A,  0,	 no_RM,	 0E3h, 0, P_386,    0)
insx(JRCXZ,  jrcxz,	OpCls( I8,   NONE,  NONE  ), 0,	     0,	 no_RM,	 0E3h, 0, P_64,	    0, RWF_X64)
insa(LOOP,   loop,	OpCls( I8,   NONE,  NONE  ), 0,	     0,	 no_RM,	 0E2h, 0, P_86,	    0)
insa(LOOPE,  loope,	OpCls( I8,   NONE,  NONE  ), 0,	     0,	 no_RM,	 0E1h, 0, P_86,	    0)
insa(LOOPZ,  loopz,	OpCls( I8,   NONE,  NONE  ), 0,	     0,	 no_RM,	 0E1h, 0, P_86,	    0)
insa(LOOPNE, loopne,	OpCls( I8,   NONE,  NONE  ), 0,	     0,	 no_RM,	 0E0h, 0, P_86,	    0)
insa(LOOPNZ, loopnz,	OpCls( I8,   NONE,  NONE  ), 0,	     0,	 no_RM,	 0E0h, 0, P_86,	    0)
insa(LOOPD,  loopd,	OpCls( I8,   NONE,  NONE  ), F_32A,  0,	 no_RM,	 0E2h, 0, P_386,    0)
insa(LOOPED, looped,	OpCls( I8,   NONE,  NONE  ), F_32A,  0,	 no_RM,	 0E1h, 0, P_386,    0)
insa(LOOPZD, loopzd,	OpCls( I8,   NONE,  NONE  ), F_32A,  0,	 no_RM,	 0E1h, 0, P_386,    0)
insa(LOOPNED,loopned,	OpCls( I8,   NONE,  NONE  ), F_32A,  0,	 no_RM,	 0E0h, 0, P_386,    0)
insa(LOOPNZD,loopnzd,	OpCls( I8,   NONE,  NONE  ), F_32A,  0,	 no_RM,	 0E0h, 0, P_386,    0)
insx(LOOPW,  loopw,	OpCls( I8,   NONE,  NONE  ), F_16A,  0,	 no_RM,	 0E2h, 0, P_86,	    0, RWF_IA32)
insx(LOOPEW, loopew,	OpCls( I8,   NONE,  NONE  ), F_16A,  0,	 no_RM,	 0E1h, 0, P_86,	    0, RWF_IA32)
insx(LOOPZW, loopzw,	OpCls( I8,   NONE,  NONE  ), F_16A,  0,	 no_RM,	 0E1h, 0, P_86,	    0, RWF_IA32)
insx(LOOPNEW,loopnew,	OpCls( I8,   NONE,  NONE  ), F_16A,  0,	 no_RM,	 0E0h, 0, P_86,	    0, RWF_IA32)
insx(LOOPNZW,loopnzw,	OpCls( I8,   NONE,  NONE  ), F_16A,  0,	 no_RM,	 0E0h, 0, P_86,	    0, RWF_IA32)

; arith instructions. Masm v6 encodes operand types R,R differently
; (direction bit is NOT set). JWasm does like Masm v8+.


ari	macro name, namelc, c_id, lock
	insa(name, namelc, OpCls( RGT8, I8,    NONE  ), 0, 0, no_WDS, 83h,   c_id, P_86, 0)
	insn(name, 1,		OpCls( R,    R_MS,  NONE  ), 0, 1, 0,	   c_id+2, 0, P_86, 0)
	insn(name, 3,		OpCls( A,    I,	    NONE  ), 0, 0, no_RM,  c_id+4, 0, P_86, 0)
	insn(name, 4,		OpCls( R,    I,	    NONE  ), 0, 0, 0,	   80h,	  c_id, P_86, 0)
	insn(name, 6,		OpCls( MGT8, I8,    NONE  ), 0, 0, no_WDS, 83h,	  c_id, P_86, lock)
	insn(name, 7,		OpCls( MS,   R,	    NONE  ), 0, 0, 0,	   c_id,   0, P_86, lock)
	insn(name, 8,		OpCls( MS,   I,	    NONE  ), 0, 0, 0,	   80h,	  c_id, P_86, lock)
	endm

; v2.02: entries 5+6 replaced by 6
; v2.06: entries 1+2 replaced by 1
; v2.11: added AP_LOCK argument, because CMP isn't supposed to accept this prefix

ari ADD, add, 00h, AP_LOCK
ari  OR,  or, 08h, AP_LOCK
ari ADC, adc, 10h, AP_LOCK
ari SBB, sbb, 18h, AP_LOCK
ari AND, and, 20h, AP_LOCK
ari SUB, sub, 28h, AP_LOCK
ari XOR, xor, 30h, AP_LOCK
ari CMP, cmp, 38h, 0

; std bitshift instructions

bsi	macro name, namelc, c_id
	insa(name, namelc, OpCls( R_MS, CL_ONLY, NONE ), 0, 0, 0, 0xD2, c_id, P_86,  0)
	insn(name, 1,		OpCls( R_MS,  I_1,     NONE ), 0, 0, 0, 0xD0, c_id, P_86,  0)
	insn(name, 2,		OpCls( R_MS,  I8_U,    NONE ), 0, 0, 0, 0xC0, c_id, P_186, 0)
	endm

bsi RCL, rcl, 0x10
bsi RCR, rcr, 0x18
bsi ROL, rol, 0x00
bsi ROR, ror, 0x08
bsi SAL, sal, 0x20
bsi SAR, sar, 0x38
bsi SHL, shl, 0x20
bsi SHR, shr, 0x28

; string instructions

insa(CMPS, cmps,		OpCls( MS,	 MS,	     NONE ), 0,	     0,	 no_RM,	 0xA6,	   0,	   P_86,	    AP_REPxx)
insa(CMPSB, cmpsb,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xA6,	   0,	   P_86,	    AP_REPxx)
insn(CMPSB, 1,			OpCls( M08,	 M08,	     NONE ), 0,	     0,	 no_RM,	 0xA6,	   0,	   P_86,	    AP_REPxx)
insa(CMPSW, cmpsw,		OpCls( NONE,	 NONE,	     NONE ), F_16,   0,	 no_RM,	 0xA7,	   0,	   P_86,	    AP_REPxx)
insn(CMPSW, 1,			OpCls( M16,	 M16,	     NONE ), F_16,   0,	 no_RM,	 0xA7,	   0,	   P_86,	    AP_REPxx)
insa(CMPSD, cmpsd,		OpCls( NONE,	 NONE,	     NONE ), F_32,   0,	 no_RM,	 0xA7,	   0,	   P_386,	    AP_REPxx)
insn(CMPSD, 1,			OpCls( M32,	 M32,	     NONE ), F_32,   0,	 no_RM,	 0xA7,	   0,	   P_386,	    AP_REPxx)
insn(CMPSD, 2,			OpCls( XMM,	 XMM_M64,    I8_U ), F_F20F, 1,	 no_WDS, 0xC2,	   0,	   P_686|P_SSE2,0)
insa(INS, ins,		OpCls( MS,	 DX_ONLY,    NONE ), 0,	     0,	 no_RM,	 0x6C,	   0,	   P_186,	    AP_REP)
insa(INSB, insb,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0x6C,	   0,	   P_186,	    AP_REP)
insn(INSB,  1,			OpCls( M08,	 DX_ONLY,    NONE ), 0,	     0,	 no_RM,	 0x6C,	   0,	   P_186,	    AP_REP)
insa(INSW, insw,		OpCls( NONE,	 NONE,	     NONE ), F_16,   0,	 no_RM,	 0x6D,	   0,	   P_186,	    AP_REP)
insn(INSW,  1,			OpCls( M16,	 DX_ONLY,    NONE ), F_16,   0,	 no_RM,	 0x6D,	   0,	   P_186,	    AP_REP)
insa(INSD, insd,		OpCls( NONE,	 NONE,	     NONE ), F_32,   0,	 no_RM,	 0x6D,	   0,	   P_386,	    AP_REP)
insn(INSD,  1,			OpCls( M32,	 DX_ONLY,    NONE ), F_32,   0,	 no_RM,	 0x6D,	   0,	   P_386,	    AP_REP)
insa(LODS, lods,		OpCls( MS,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xAC,	   0,	   P_86,	    AP_REP)
insa(LODSB, lodsb,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xAC,	   0,	   P_86,	    AP_REP)
insn(LODSB, 1,			OpCls( M08,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xAC,	   0,	   P_86,	    AP_REP)
insa(LODSW, lodsw,		OpCls( NONE,	 NONE,	     NONE ), F_16,   0,	 no_RM,	 0xAD,	   0,	   P_86,	    AP_REP)
insn(LODSW, 1,			OpCls( M16,	 NONE,	     NONE ), F_16,   0,	 no_RM,	 0xAD,	   0,	   P_86,	    AP_REP)
insa(LODSD, lodsd,		OpCls( NONE,	 NONE,	     NONE ), F_32,   0,	 no_RM,	 0xAD,	   0,	   P_386,	    AP_REP)
insn(LODSD, 1,			OpCls( M32,	 NONE,	     NONE ), F_32,   0,	 no_RM,	 0xAD,	   0,	   P_386,	    AP_REP)
insa(MOVS, movs,		OpCls( MS,	 MS,	     NONE ), 0,	     0,	 no_RM,	 0xA4,	   0,	   P_86,	    AP_REP)
insa(MOVSB, movsb,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xA4,	   0,	   P_86,	    AP_REP)
insn(MOVSB, 1,			OpCls( M08,	 M08,	     NONE ), 0,	     0,	 no_RM,	 0xA4,	   0,	   P_86,	    AP_REP)
insa(MOVSW, movsw,		OpCls( NONE,	 NONE,	     NONE ), F_16,   0,	 no_RM,	 0xA5,	   0,	   P_86,	    AP_REP)
insn(MOVSW, 1,			OpCls( M16,	 M16,	     NONE ), F_16,   0,	 no_RM,	 0xA5,	   0,	   P_86,	    AP_REP)
insa(MOVSD, movsd,		OpCls( NONE,	 NONE,	     NONE ), F_32,   0,	 no_RM,	 0xA5,	   0,	   P_386,	    AP_REP)
insn(MOVSD, 1,			OpCls( M32,	 M32,	     NONE ), F_32,   0,	 no_RM,	 0xA5,	   0,	   P_386,	    AP_REP)
insn(MOVSD, 2,			OpCls( XMM,	 XMM_M64,    NONE ), F_F20F, 1,	 no_WDS, 0x10,	   0,	   P_686|P_SSE2,0)
insn(MOVSD, 3,			OpCls( M64,	 XMM,	     NONE ), F_F20F, 0,	 no_WDS, 0x11,	   0,	   P_686|P_SSE2,0)
insa(OUTS, outs,		OpCls( DX_ONLY,	 MS,	     NONE ), 0,	     0,	 no_RM,	 0x6E,	   0,	   P_186,	    AP_REP)
insa(OUTSB, outsb,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0x6E,	   0,	   P_186,	    AP_REP)
insn(OUTSB, 1,			OpCls( DX_ONLY,	 M08,	     NONE ), 0,	     0,	 no_RM,	 0x6E,	   0,	   P_186,	    AP_REP)
insa(OUTSW, outsw,		OpCls( NONE,	 NONE,	     NONE ), F_16,   0,	 no_RM,	 0x6F,	   0,	   P_186,	    AP_REP)
insn(OUTSW, 1,			OpCls( DX_ONLY,	 M16,	     NONE ), F_16,   0,	 no_RM,	 0x6F,	   0,	   P_186,	    AP_REP)
insa(OUTSD, outsd,		OpCls( NONE,	 NONE,	     NONE ), F_32,   0,	 no_RM,	 0x6F,	   0,	   P_386,	    AP_REP)
insn(OUTSD, 1,			OpCls( DX_ONLY,	 M32,	     NONE ), F_32,   0,	 no_RM,	 0x6F,	   0,	   P_386,	    AP_REP)
insa(SCAS, scas,		OpCls( MS,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xAE,	   0,	   P_86,	    AP_REPxx)
insa(SCASB, scasb,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xAE,	   0,	   P_86,	    AP_REPxx)
insn(SCASB, 1,			OpCls( M08,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xAE,	   0,	   P_86,	    AP_REPxx)
insa(SCASW, scasw,		OpCls( NONE,	 NONE,	     NONE ), F_16,   0,	 no_RM,	 0xAF,	   0,	   P_86,	    AP_REPxx)
insn(SCASW, 1,			OpCls( M16,	 NONE,	     NONE ), F_16,   0,	 no_RM,	 0xAF,	   0,	   P_86,	    AP_REPxx)
insa(SCASD, scasd,		OpCls( NONE,	 NONE,	     NONE ), F_32,   0,	 no_RM,	 0xAF,	   0,	   P_386,	    AP_REPxx)
insn(SCASD, 1,			OpCls( M32,	 NONE,	     NONE ), F_32,   0,	 no_RM,	 0xAF,	   0,	   P_386,	    AP_REPxx)
insa(STOS, stos,		OpCls( MS,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xAA,	   0,	   P_86,	    AP_REP)
insa(STOSB, stosb,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xAA,	   0,	   P_86,	    AP_REP)
insn(STOSB, 1,			OpCls( M08,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xAA,	   0,	   P_86,	    AP_REP)
insa(STOSW, stosw,		OpCls( NONE,	 NONE,	     NONE ), F_16,   0,	 no_RM,	 0xAB,	   0,	   P_86,	    AP_REP)
insn(STOSW, 1,			OpCls( M16,	 NONE,	     NONE ), F_16,   0,	 no_RM,	 0xAB,	   0,	   P_86,	    AP_REP)
insa(STOSD, stosd,		OpCls( NONE,	 NONE,	     NONE ), F_32,   0,	 no_RM,	 0xAB,	   0,	   P_386,	    AP_REP)
insn(STOSD, 1,			OpCls( M32,	 NONE,	     NONE ), F_32,   0,	 no_RM,	 0xAB,	   0,	   P_386,	    AP_REP)

; instructions invalid for IA32+

insx(AAA, aaa,			OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0x37,	   0,	   P_86,	    0, RWF_IA32 )
insx(AAD, aad,			OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD5,	   0x0A,       P_86,	    0, RWF_IA32 )
insx(AAM, aam,			OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD4,	   0x0A,       P_86,	    0, RWF_IA32 )
insx(AAS, aas,			OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0x3F,	   0,	   P_86,	    0, RWF_IA32 )
insx(DAA, daa,			OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0x27,	   0,	   P_86,	    0, RWF_IA32 )
insx(DAS, das,			OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0x2F,	   0,	   P_86,	    0, RWF_IA32 )
insx(LDS, lds,			OpCls( RGT8,	 MFPTR,	     NONE ), 0,	     1,	 no_WDS, 0xC5,	   0,	   P_86,	    0, RWF_IA32 )
insx(LES, les,			OpCls( RGT8,	 MFPTR,	     NONE ), 0,	     1,	 no_WDS, 0xC4,	   0,	   P_86,	    0, RWF_IA32 )
insx(POPA,  popa,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0x61,	   0,	   P_186,	    0, RWF_IA32 )
insx(POPAD, popad,		OpCls( NONE,	 NONE,	     NONE ), F_32,   0,	 no_RM,	 0x61,	   0,	   P_386,	    0, RWF_IA32 )
insx(POPAW, popaw,		OpCls( NONE,	 NONE,	     NONE ), F_16,   0,	 no_RM,	 0x61,	   0,	   P_186,	    0, RWF_IA32 )
insx(POPFD, popfd,		OpCls( NONE,	 NONE,	     NONE ), F_32,   0,	 no_RM,	 0x9D,	   0,	   P_386,	    0, RWF_IA32 )
insx(PUSHA,  pusha,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0x60,	   0,	   P_186,	    0, RWF_IA32 )
insx(PUSHAD, pushad,		OpCls( NONE,	 NONE,	     NONE ), F_32,   0,	 no_RM,	 0x60,	   0,	   P_386,	    0, RWF_IA32 )
insx(PUSHAW, pushaw,		OpCls( NONE,	 NONE,	     NONE ), F_16,   0,	 no_RM,	 0x60,	   0,	   P_186,	    0, RWF_IA32 )
insx(PUSHFD, pushfd,		OpCls( NONE,	 NONE,	     NONE ), F_32,   0,	 no_RM,	 0x9C,	   0,	   P_386,	    0, RWF_IA32 )
insx(PUSHD,  pushd,		OpCls( I8,	 NONE,	     NONE ), F_32,   0,	 no_RM,	 0x6A,	   0,	   P_386,	    0, RWF_IA32 )
insn(PUSHD,  1,			OpCls( I32,	 NONE,	     NONE ), F_32,   0,	 no_RM,	 0x68,	   0,	   P_386,	    0)
insn(PUSHD,  2,			OpCls( R32,	 NONE,	     NONE ), 0,	     0,	 R_in_OP,0x50,	   0,	   P_386,	    0)
insn(PUSHD,  3,			OpCls( SR86,	 NONE,	     NONE ), 0,	     1,	 R_in_OP,0x06,	   0,	   P_86,	    0)
insn(PUSHD,  4,			OpCls( SR,	 NONE,	     NONE ), F_0F,   1,	 R_in_OP,0x80,	   0,	   P_386,	    0)
insn(PUSHD,  5,			OpCls( M32,	 NONE,	     NONE ), 0,	     0,	 0,	 0xFF,	   0x30,       P_386,	    0)
; unlike their names suggest, RETD/RETW will always create a 32-/16-bit far ret
insx(RETD, retd,		OpCls( I16,	 NONE,	     NONE ), F_32,   0,	 no_RM,	 0xCA,	   0,	   P_386,	    0, RWF_IA32 )
insn(RETD, 1,			OpCls( NONE,	 NONE,	     NONE ), F_32,   0,	 no_RM,	 0xCB,	   0,	   P_386,	    0)
insx(RETW, retw,		OpCls( I16,	 NONE,	     NONE ), F_16,   0,	 no_RM,	 0xCA,	   0,	   P_86,	    0, RWF_IA32 )
insn(RETW, 1,			OpCls( NONE,	 NONE,	     NONE ), F_16,   0,	 no_RM,	 0xCB,	   0,	   P_86,	    0)

; protected-mode instructions
; some (i.e. SMSW) also work with 32bit register as first operand, but Masm won't accept.
; to make JWasm accept, change OP_R16 to OP_RGT8
;

insa(ARPL, arpl,		OpCls( R16_M16,	 R16,	   NONE ), 0,	    0,	no_WDS, 0x63,	  0,	      P_286,	   0)
insa(LLDT, lldt,		OpCls( R16_M16,	 NONE,	   NONE ), F_0FNO66,0,	no_WDS, 0,	  0x10,	      P_286p,	   0)
insa(LMSW, lmsw,		OpCls( R16_M16,	 NONE,	   NONE ), F_0FNO66,0,	no_WDS, 0x01,	  0x30,	      P_286p,	   0)
insa(LTR, ltr,			OpCls( R16_M16,	 NONE,	   NONE ), F_0FNO66,0,	no_WDS, 0,	  0x18,	      P_286p,	   0)
insa(SLDT, sldt,		OpCls( R16_M16,	 NONE,	   NONE ), F_0FNO66,0,	no_WDS, 0,	  0,	      P_286,	   0)
insa(SMSW, smsw,		OpCls( R16_M16,	 NONE,	   NONE ), F_0FNO66,0,	no_WDS, 0x01,	  0x20,	      P_286,	   0)
insa(STR, str,			OpCls( R16_M16,	 NONE,	   NONE ), F_0FNO66,0,	no_WDS, 0,	  0x08,	      P_286,	   0)
insa(VERR, verr,		OpCls( R16_M16,	 NONE,	   NONE ), F_0FNO66,0,	no_WDS, 0,	  0x20,	      P_286,	   0)
insa(VERW, verw,		OpCls( R16_M16,	 NONE,	   NONE ), F_0FNO66,0,	no_WDS, 0,	  0x28,	      P_286,	   0)

; one-operand register/memory instructions

insa(DIV, div,			OpCls( R,	 NONE,	     NONE ), 0,	     0,	 0,	 0xF6,	   0x30,       P_86,	    0)
insn(DIV, 1,			OpCls( M08,	 NONE,	     NONE ), 0,	     0,	 0,	 0xF6,	   0x30,       P_86,	    0)
insn(DIV, 2,			OpCls( MGT8,	 NONE,	     NONE ), 0,	     0,	 0,	 0xF7,	   0x30,       P_86,	    0)
insa(IDIV, idiv,		OpCls( R,	 NONE,	     NONE ), 0,	     0,	 0,	 0xF6,	   0x38,       P_86,	    0)
insn(IDIV, 1,			OpCls( M08,	 NONE,	     NONE ), 0,	     0,	 0,	 0xF6,	   0x38,       P_86,	    0)
insn(IDIV, 2,			OpCls( MGT8,	 NONE,	     NONE ), 0,	     0,	 0,	 0xF7,	   0x38,       P_86,	    0)
insa(MUL, mul,			OpCls( R,	 NONE,	     NONE ), 0,	     0,	 0,	 0xF6,	   0x20,       P_86,	    0)
insn(MUL, 1,			OpCls( M08,	 NONE,	     NONE ), 0,	     0,	 0,	 0xF6,	   0x20,       P_86,	    0)
insn(MUL, 2,			OpCls( MGT8,	 NONE,	     NONE ), 0,	     0,	 0,	 0xF7,	   0x20,       P_86,	    0)
insa(NEG, neg,			OpCls( R,	 NONE,	     NONE ), 0,	     0,	 0,	 0xF6,	   0x18,       P_86,	    0)
insn(NEG, 1,			OpCls( M08,	 NONE,	     NONE ), 0,	     0,	 0,	 0xF6,	   0x18,       P_86,	    AP_LOCK)
insn(NEG, 2,			OpCls( MGT8,	 NONE,	     NONE ), 0,	     0,	 0,	 0xF7,	   0x18,       P_86,	    AP_LOCK)
insa(NOT, not,			OpCls( R,	 NONE,	     NONE ), 0,	     0,	 0,	 0xF6,	   0x10,       P_86,	    0)
insn(NOT, 1,			OpCls( M08,	 NONE,	     NONE ), 0,	     0,	 0,	 0xF6,	   0x10,       P_86,	    AP_LOCK)
insn(NOT, 2,			OpCls( MGT8,	 NONE,	     NONE ), 0,	     0,	 0,	 0xF7,	   0x10,       P_86,	    AP_LOCK)

; prefixes. must start with LOCK, end with REPZ and be consecutive
insa(LOCK, lock,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xF0,	   0,	       P_86,	    AP_LOCK)
insa(REP, rep,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xF3,	   0,	       P_86,	    AP_REP)
insa(REPE, repe,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xF3,	   0,	       P_86,	    AP_REPxx)
insa(REPNE, repne,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xF2,	   0,	       P_86,	    AP_REPxx)
insa(REPNZ, repnz,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xF2,	   0,	       P_86,	    AP_REPxx)
insa(REPZ, repz,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xF3,	   0,	       P_86,	    AP_REPxx)

; BTx

insa(BT, bt,			OpCls( RGT8,	 RGT8,	     NONE ), F_0F,   0,	 no_WDS, 0xA3,	   0,	   P_386,	    0)
insn(BT,   1,			OpCls( RGT8,	 I8_U,	     NONE ), F_0F,   0,	 no_WDS, 0xBA,	   0x20,       P_386,	    0)
insn(BT,   2,			OpCls( MGT8,	 RGT8,	     NONE ), F_0F,   0,	 no_WDS, 0xA3,	   0,	   P_386,	    0)
insn(BT,   3,			OpCls( MGT8,	 I8_U,	     NONE ), F_0F,   0,	 no_WDS, 0xBA,	   0x20,       P_386,	    0)
insa(BTC, btc,			OpCls( RGT8,	 RGT8,	     NONE ), F_0F,   0,	 no_WDS, 0xBB,	   0,	   P_386,	    0)
insn(BTC,  1,			OpCls( RGT8,	 I8_U,	     NONE ), F_0F,   0,	 no_WDS, 0xBA,	   0x38,       P_386,	    0)
insn(BTC,  2,			OpCls( MGT8,	 RGT8,	     NONE ), F_0F,   0,	 no_WDS, 0xBB,	   0,	   P_386,	    AP_LOCK)
insn(BTC,  3,			OpCls( MGT8,	 I8_U,	     NONE ), F_0F,   0,	 no_WDS, 0xBA,	   0x38,       P_386,	    AP_LOCK)
insa(BTR, btr,			OpCls( RGT8,	 RGT8,	     NONE ), F_0F,   0,	 no_WDS, 0xB3,	   0,	   P_386,	    0)
insn(BTR,  1,			OpCls( RGT8,	 I8_U,	     NONE ), F_0F,   0,	 no_WDS, 0xBA,	   0x30,       P_386,	    0)
insn(BTR,  2,			OpCls( MGT8,	 RGT8,	     NONE ), F_0F,   0,	 no_WDS, 0xB3,	   0,	   P_386,	    AP_LOCK)
insn(BTR,  3,			OpCls( MGT8,	 I8_U,	     NONE ), F_0F,   0,	 no_WDS, 0xBA,	   0x30,       P_386,	    AP_LOCK)
insa(BTS, bts,			OpCls( RGT8,	 RGT8,	     NONE ), F_0F,   0,	 no_WDS, 0xAB,	   0,	   P_386,	    0)
insn(BTS,  1,			OpCls( RGT8,	 I8_U,	     NONE ), F_0F,   0,	 no_WDS, 0xBA,	   0x28,       P_386,	    0)
insn(BTS,  2,			OpCls( MGT8,	 RGT8,	     NONE ), F_0F,   0,	 no_WDS, 0xAB,	   0,	   P_386,	    AP_LOCK)
insn(BTS,  3,			OpCls( MGT8,	 I8_U,	     NONE ), F_0F,   0,	 no_WDS, 0xBA,	   0x28,       P_386,	    AP_LOCK)

; set/reset flags

insa(CMC, cmc,			OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xF5,	   0,	   P_86,	    0)
insa(CLC, clc,			OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xF8,	   0,	   P_86,	    0)
insa(STC, stc,			OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xF9,	   0,	   P_86,	    0)
insa(CLI, cli,			OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xFA,	   0,	   P_86,	    0)
insa(STI, sti,			OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xFB,	   0,	   P_86,	    0)
insa(CLD, cld,			OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xFC,	   0,	   P_86,	    0)
insa(STD, std,			OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xFD,	   0,	   P_86,	    0)

; INC/DEC. (hack for 64-bit in reswords.c!)

insa(INC, inc,			OpCls( RGT8,	 NONE,	     NONE ), 0,	     0,	 R_in_OP,0x40,	   0,	   P_86,	    0)
insn(INC, 1,			OpCls( R,	 NONE,	     NONE ), 0,	     0,	 0,	 0xFE,	   0,	   P_86,	    0)
insn(INC, 2,			OpCls( M08,	 NONE,	     NONE ), 0,	     0,	 0,	 0xFE,	   0,	   P_86,	    AP_LOCK)
insn(INC, 3,			OpCls( MGT8,	 NONE,	     NONE ), 0,	     0,	 0,	 0xFF,	   0,	   P_86,	    AP_LOCK)
insa(DEC, dec,			OpCls( RGT8,	 NONE,	     NONE ), 0,	     0,	 R_in_OP,0x48,	   0,	   P_86,	    0)
insn(DEC, 1,			OpCls( R,	 NONE,	     NONE ), 0,	     0,	 0,	 0xFE,	   0x08,       P_86,	    0)
insn(DEC, 2,			OpCls( M08,	 NONE,	     NONE ), 0,	     0,	 0,	 0xFE,	   0x08,       P_86,	    AP_LOCK)
insn(DEC, 3,			OpCls( MGT8,	 NONE,	     NONE ), 0,	     0,	 0,	 0xFF,	   0x08,       P_86,	    AP_LOCK)

; PUSH/POP (16- and 32-bit only)

insa(PUSH, push,		OpCls( R16_R32,	 NONE,	     NONE ), 0,	    0,	R_in_OP,0x50,	  0,	      P_86,	   0)
insn(PUSH, 1,			OpCls( I8,	 NONE,	     NONE ), 0,	    0,	no_RM,	0x6A,	  0,	      P_186,	   0)
insn(PUSH, 2,			OpCls( I,	 NONE,	     NONE ), 0,	    0,	no_RM,	0x68,	  0,	      P_186,	   0)
insn(PUSH, 3,			OpCls( SR86,	 NONE,	     NONE ), 0,	    1,	R_in_OP,0x06,	  0,	      P_86,	   0)
insn(PUSH, 4,			OpCls( SR,	 NONE,	     NONE ), F_0F,  1,	R_in_OP,0x80,	  0,	      P_386,	   0)
insn(PUSH, 5,			OpCls( M16_M32,	 NONE,	     NONE ), 0,	    0,	0,	0xFF,	  0x30,	      P_86,	   0)
insa(POP, pop,			OpCls( R16_R32,	 NONE,	     NONE ), 0,	    0,	R_in_OP,0x58,	  0,	      P_86,	   0)
insn(POP, 1,			OpCls( SR86,	 NONE,	     NONE ), 0,	    1,	R_in_OP,0x07,	  0,	      P_86,	   0)
insn(POP, 2,			OpCls( SR,	 NONE,	     NONE ), F_0F,  1,	R_in_OP,0x81,	  0,	      P_386,	   0)
insn(POP, 3,			OpCls( M16_M32,	 NONE,	     NONE ), 0,	    0,	0,	0x8F,	  0,	      P_86,	   0)
insa(PUSHW,	 pushw,		OpCls( I8,	 NONE,	     NONE ), F_16,  0,	no_RM,	0x6A,	  0,	      P_186,	   0)
insn(PUSHW,  1,			OpCls( I16,	 NONE,	     NONE ), F_16,  0,	no_RM,	0x68,	  0,	      P_186,	   0)
insa(PUSHF,	 pushf,		OpCls( NONE,	 NONE,	     NONE ), F_16,  0,	no_RM,	0x9C,	  0,	      P_86,	   0)
insa(POPF, popf,		OpCls( NONE,	 NONE,	     NONE ), F_16,  0,	no_RM,	0x9D,	  0,	      P_86,	   0)

; MOV

insa(MOV, mov,			OpCls( A,	 MS,	     NONE ), 0,	     1,	 no_RM,	 0xA0,	   0,	   P_86,	    0)
insn(MOV, 1,			OpCls( R,	 R_MS,	     NONE ), 0,	     1,	 0,	 0x8A,	   0,	   P_86,	    0)
insn(MOV, 2,			OpCls( R8,	 I,	     NONE ), 0,	     0,	 R_in_OP,0xB0,	   0,	   P_86,	    0)
insn(MOV, 3,			OpCls( R16_R32,	 I,	     NONE ), 0,	     0,	 R_in_OP,0xB8,	   0,	   P_86,	    0)

insn(MOV, 4,			OpCls( R64,	 I,	     NONE ), 0,	     0,	 0,	 0xC6,	   0,	   P_64,	    0)
insn(MOV, 5,			OpCls( R64,	 I64,	     NONE ), 0,	     0,	 R_in_OP,0xB8,	   0,	   P_64,	    0)

insn(MOV, 6,			OpCls( RGT8,	 SR,	     NONE ), 0,	     0,	 no_WDS, 0x8C,	   0xC0,       P_86,	    0)
insn(MOV, 7,			OpCls( SR,	 RGT8,	     NONE ), 0,	     1,	 no_WDS, 0x8E,	   0xC0,       P_86,	    0)
insn(MOV, 8,			OpCls( SR,	 MS,	     NONE ), 0,	     1,	 no_WDS, 0x8E,	   0,	   P_86,	    0)
insn(MOV, 9,			OpCls( MS,	 A,	     NONE ), 0,	     0,	 no_RM,	 0xA2,	   0,	   P_86,	    0)
insn(MOV, 10,			OpCls( MS,	 R,	     NONE ), 0,	     0,	 0,	 0x88,	   0,	   P_86,	    0)
insn(MOV, 11,			OpCls( MS,	 I,	     NONE ), 0,	     0,	 0,	 0xC6,	   0,	   P_86,	    0)
insn(MOV, 12,			OpCls( MS,	 SR,	     NONE ), 0,	     0,	 no_WDS, 0x8C,	   0,	   P_86,	    0)
insn(MOV, 13,			OpCls( RGT16,	 RSPEC,	     NONE ), F_0FNO66,0, no_WDS, 0x20,	   0xC0,       P_386,	    0)
insn(MOV, 14,			OpCls( RSPEC,	 RGT16,	     NONE ), F_0FNO66,1, no_WDS, 0x22,	   0xC0,       P_386,	    0)

; rest

insa(BOUND_, bound,		OpCls( RGT8,	 MS,	     NONE ), 0,	     1,	 no_WDS, 0x62,	   0,	   P_186,	    0)
insa(BSF, bsf,			OpCls( RGT8,	 RGT8_MS,    NONE ), F_0F,   1,	 no_WDS, 0xBC,	   0,	   P_386,	    0)
insa(BSR, bsr,			OpCls( RGT8,	 RGT8_MS,    NONE ), F_0F,   1,	 no_WDS, 0xBD,	   0,	   P_386,	    0)
insa(BSWAP, bswap,		OpCls( RGT16,	 NONE,	     NONE ), F_0F,   0,	 R_in_OP,0xC8,	   0,	   P_486,	    0)
insa(CBW, cbw,			OpCls( NONE,	 NONE,	     NONE ), F_16,   0,	 no_RM,	 0x98,	   0,	   P_86,	    0)
insa(CDQ, cdq,			OpCls( NONE,	 NONE,	     NONE ), F_32,   0,	 no_RM,	 0x99,	   0,	   P_386,	    0)
insa(CWD, cwd,			OpCls( NONE,	 NONE,	     NONE ), F_16,   0,	 no_RM,	 0x99,	   0,	   P_86,	    0)
insa(CWDE, cwde,		OpCls( NONE,	 NONE,	     NONE ), F_32,   0,	 no_RM,	 0x98,	   0,	   P_386,	    0)
insa(CLTS, clts,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0x0F,	   0x06,       P_286p,	    0)
insa(CMPXCHG, cmpxchg,		OpCls( R,	 R,	     NONE ), F_0F,   0,	 0,	 0xB0,	   0,	   P_486,	    0)
insn(CMPXCHG, 1,		OpCls( MS,	 R,	     NONE ), F_0F,   0,	 0,	 0xB0,	   0,	   P_486,	    AP_LOCK)
insa(CMPXCHG8B, cmpxchg8b, OpCls( M64,	 NONE,	     NONE ), F_0F,   0,	 0,	 0xC7,	   0x08,       P_586,	    AP_LOCK)
insa(CPUID, cpuid,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0x0F,	   0xA2,       P_586,	    0)
insa(ENTER, enter,		OpCls( I16,	 I8_U,	     NONE ), 0,	     0,	 no_RM,	 0xC8,	   0,	   P_186,	    0)
insa(HLT, hlt,			OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xF4,	   0,	   P_86,	    0)
insa(IMUL, imul,		OpCls( R,	 NONE,	     NONE ), 0,	     0,	 0,	 0xF6,	   0x28,       P_86,	    0)
insn(IMUL, 2,			OpCls( M08,	 NONE,	     NONE ), 0,	     0,	 0,	 0xF6,	   0x28,       P_86,	    0)
insn(IMUL, 3,			OpCls( MGT8,	 NONE,	     NONE ), 0,	     0,	 0,	 0xF7,	   0x28,       P_86,	    0)
insn(IMUL, 4,			OpCls( RGT8,	 R_MS,	     NONE ), F_0F,   1,	 no_WDS, 0xAF,	   0,	   P_386,	    0)
insn(IMUL, 6,			OpCls( RGT8,	 I8,	     NONE ), 0,	     1,	 no_WDS, 0x6B,	   0,	   P_186,	    0)
insn(IMUL, 7,			OpCls( RGT8,	 I,	     NONE ), 0,	     1,	 no_WDS, 0x69,	   0,	   P_186,	    0)
insn(IMUL, 8,			OpCls( RGT8,	 R_MS,	     I8_U ), 0,	     1,	 no_WDS, 0x6B,	   0,	   P_186,	    0)
insn(IMUL, 9,			OpCls( RGT8,	 R_MS,	     I	  ), 0,	     1,	 no_WDS, 0x69,	   0,	   P_186,	    0)
insa(IN, in,			OpCls( A,	 DX_ONLY,    NONE ), 0,	     0,	 no_RM,	 0xEC,	   0,	   P_86,	    0)
insn(IN, 1,			OpCls( A,	 I8_U,	     NONE ), 0,	     0,	 no_RM,	 0xE4,	   0,	   P_86,	    0)
insa(INT, int,			OpCls( I_3,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xCC,	   0,	   P_86,	    0)
insn(INT, 1,			OpCls( I8_U,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xCD,	   0,	   P_86,	    0)
insa(INTO, into,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xCE,	   0,	   P_86,	    0)
insa(INVD, invd,		OpCls( NONE,	 NONE,	     NONE ), F_0F,   0,	 no_RM,	 0x08,	   0,	   P_486,	    0)
insa(INVLPG, invlpg,		OpCls( M_ANY,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x01,	   0x38,       P_486,	    0)
insa(IRET, iret,		OpCls( NONE,	 NONE,	     NONE ), F_16,   0,	 no_RM,	 0xCF,	   0,	   P_86,	    0)
insa(IRETD, iretd,		OpCls( NONE,	 NONE,	     NONE ), F_32,   0,	 no_RM,	 0xCF,	   0,	   P_386,	    0)
; the F-suffix variants of IRET/IRETD are just aliases and pretty useless.
; In Masm v8+, IRETF has disappeared, but IRETDF is still there.
;
insa(IRETF, iretf,		OpCls( NONE,	 NONE,	     NONE ), F_16,   0,	 no_RM,	 0xCF,	   0,	   P_86,	    0)
insa(IRETDF, iretdf,		OpCls( NONE,	 NONE,	     NONE ), F_32,   0,	 no_RM,	 0xCF,	   0,	   P_386,	    0)
insa(LAHF, lahf,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0x9F,	   0,	   P_86,	    0)
insa(LAR, lar,			OpCls( RGT8,	 RGT8_MS,    NONE ), F_0F,   1,	 no_WDS, 0x02,	   0,	   P_286,	    0)
insa(LSL, lsl,			OpCls( RGT8,	 RGT8_MS,    NONE ), F_0F,   1,	 no_WDS, 0x03,	   0,	   P_286,	    0)
insa(LEA, lea,			OpCls( RGT8,	 MS,	     NONE ), 0,	     1,	 no_WDS, 0x8D,	   0,	   P_86,	    0)
insa(LEAVE, leave,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xC9,	   0,	   P_186,	    0)
insa(LFS, lfs,			OpCls( RGT8,	 MFPTR,	     NONE ), F_0F,   1,	 no_WDS, 0xB4,	   0,	   P_386,	    0)
insa(LGS, lgs,			OpCls( RGT8,	 MFPTR,	     NONE ), F_0F,   1,	 no_WDS, 0xB5,	   0,	   P_386,	    0)
insa(LSS, lss,			OpCls( RGT8,	 MFPTR,	     NONE ), F_0F,   1,	 no_WDS, 0xB2,	   0,	   P_386,	    0)
insa(LGDT, lgdt,		OpCls( M48,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x01,	   0x10,       P_286p,	    0)
insa(LIDT, lidt,		OpCls( M48,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x01,	   0x18,       P_286p,	    0)
insa(MOVSX, movsx,		OpCls( RGT8,	 R_MS,	     NONE ), F_0F,   1,	 0,	 0xBE,	   0,	   P_386,	    0)
insa(MOVZX, movzx,		OpCls( RGT8,	 R_MS,	     NONE ), F_0F,   1,	 0,	 0xB6,	   0,	   P_386,	    0)
insa(NOP, nop,			OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0x90,	   0,	   P_86,	    0)
insa(OUT, out,			OpCls( DX_ONLY,	 A,	     NONE ), 0,	     0,	 no_RM,	 0xEE,	   0,	   P_86,	    0)
insn(OUT, 1,			OpCls( I8_U,	 A,	     NONE ), 0,	     0,	 no_RM,	 0xE6,	   0,	   P_86,	    0)

insa(RDMSR, rdmsr,		OpCls( NONE,	 NONE,	     NONE ), F_0F,   0,	 no_RM,	 0x32,	   0,	   P_586,	    0)
; v2.11: RDPMC is accepted with .586 ( was: .686 )
insa(RDPMC, rdpmc,		OpCls( NONE,	 NONE,	     NONE ), F_0F,   0,	 no_RM,	 0x33,	   0,	   P_586,	    0)
insa(RDTSC, rdtsc,		OpCls( NONE,	 NONE,	     NONE ), F_0F,   0,	 no_RM,	 0x31,	   0,	   P_586,	    0)
insa(RDTSCP, rdtscp,		OpCls( NONE,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x01,	   0xF9,       P_686,	    0)
insa(RET, ret,			OpCls( I16,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xC2,	   0,	   P_86,	    0)
insn(RET,  1,			OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xC3,	   0,	   P_86,	    0)
insa(RETN, retn,		OpCls( I16,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xC2,	   0,	   P_86,	    0)
insn(RETN, 1,			OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xC3,	   0,	   P_86,	    0)
insa(RETF, retf,		OpCls( I16,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xCA,	   0,	   P_86,	    0)
insn(RETF, 1,			OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xCB,	   0,	   P_86,	    0)
insa(RSM, rsm,			OpCls( NONE,	 NONE,	     NONE ), F_0F,   0,	 no_RM,	 0xAA,	   0,	   P_586,	    0)
insa(SAHF, sahf,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0x9E,	   0,	   P_86,	    0)
insa(SGDT, sgdt,		OpCls( M_ANY,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x01,	   0,	   P_286,	    0)
insa(SIDT, sidt,		OpCls( M_ANY,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x01,	   0x08,       P_286,	    0)
insa(SHLD, shld,		OpCls( RGT8_MGT8,RGT8,	     CL	  ), F_0F,   0,	 no_WDS, 0xA5,	   0,	   P_386,	    0)
insn(SHLD, 1,			OpCls( RGT8_MGT8,RGT8,	     I8_U ), F_0F,   0,	 no_WDS, 0xA4,	   0,	   P_386,	    0)
insa(SHRD, shrd,		OpCls( RGT8_MGT8,RGT8,	     CL	  ), F_0F,   0,	 no_WDS, 0xAD,	   0,	   P_386,	    0)
insn(SHRD, 1,			OpCls( RGT8_MGT8,RGT8,	     I8_U ), F_0F,   0,	 no_WDS, 0xAC,	   0,	   P_386,	    0)
insa(SYSENTER, sysenter, OpCls( NONE,	 NONE,	     NONE ), F_0F,   0,	 no_RM,	 0x34,	   0,	   P_686,	    0)
insa(SYSEXIT, sysexit,		OpCls( NONE,	 NONE,	     NONE ), F_0F,   0,	 no_RM,	 0x35,	   0,	   P_686p,	    0)
insa(TEST, test,		OpCls( A,	 I,	     NONE ), 0,	     0,	 no_RM,	 0xA8,	   0,	   P_86,	    0)
insn(TEST, 1,			OpCls( R,	 R_MS,	     NONE ), 0,	     1,	 0,	 0x84,	   0,	   P_86,	    0)
insn(TEST, 3,			OpCls( R_MS,	 I,	     NONE ), 0,	     0,	 0,	 0xF6,	   0,	   P_86,	    0)
insn(TEST, 4,			OpCls( MS,	 R,	     NONE ), 0,	     0,	 0,	 0x84,	   0,	   P_86,	    0)
insa(UD2, ud2,			OpCls( NONE,	 NONE,	     NONE ), F_0F,   0,	 no_RM,	 0x0B,	   0,	   P_686,	    0)
insa(WAIT, wait,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0x9B,	   0,	   P_86,	    0)
insa(WBINVD, wbinvd,		OpCls( NONE,	 NONE,	     NONE ), F_0F,   0,	 no_RM,	 0x09,	   0,	   P_486,	    0)
insa(WRMSR, wrmsr,		OpCls( NONE,	 NONE,	     NONE ), F_0F,   0,	 no_RM,	 0x30,	   0,	   P_586,	    0)
insa(XADD, xadd,		OpCls( R,	 R,	     NONE ), F_0F,   0,	 0,	 0xC0,	   0,	   P_486,	    0)
insn(XADD, 1,			OpCls( MS,	 R,	     NONE ), F_0F,   0,	 0,	 0xC0,	   0,	   P_486,	    AP_LOCK)
insa(XCHG, xchg,		OpCls( A,	 RGT8,	     NONE ), 0,	     0,	 R_in_OP,0x90,	   0,	   P_86,	    0)
insn(XCHG, 1,			OpCls( RGT8,	 A,	     NONE ), 0,	     0,	 R_in_OP,0x90,	   0,	   P_86,	    0)
insn(XCHG, 2,			OpCls( R,	 R,	     NONE ), 0,	     1,	 0,	 0x86,	   0,	   P_86,	    0)
insn(XCHG, 3,			OpCls( R,	 MS,	     NONE ), 0,	     1,	 0,	 0x86,	   0,	   P_86,	    AP_LOCK)
insn(XCHG, 4,			OpCls( MS,	 R,	     NONE ), 0,	     0,	 0,	 0x86,	   0,	   P_86,	    AP_LOCK)
insa(XLAT, xlat,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xD7,	   0,	   P_86,	    0)
insn(XLAT, 1,			OpCls( M08,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xD7,	   0,	   P_86,	    0)
insa(XLATB, xlatb,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xD7,	   0,	   P_86,	    0)
insn(XLATB, 1,			OpCls( M08,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0xD7,	   0,	   P_86,	    0)

insa(SETA, seta,		OpCls( R8_M08,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x97,	   0,	   P_386,	    0)
insa(SETAE, setae,		OpCls( R8_M08,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x93,	   0,	   P_386,	    0)
insa(SETB, setb,		OpCls( R8_M08,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x92,	   0,	   P_386,	    0)
insa(SETBE, setbe,		OpCls( R8_M08,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x96,	   0,	   P_386,	    0)
insa(SETC, setc,		OpCls( R8_M08,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x92,	   0,	   P_386,	    0)
insa(SETE, sete,		OpCls( R8_M08,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x94,	   0,	   P_386,	    0)
insa(SETG, setg,		OpCls( R8_M08,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x9F,	   0,	   P_386,	    0)
insa(SETGE, setge,		OpCls( R8_M08,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x9D,	   0,	   P_386,	    0)
insa(SETL, setl,		OpCls( R8_M08,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x9C,	   0,	   P_386,	    0)
insa(SETLE, setle,		OpCls( R8_M08,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x9E,	   0,	   P_386,	    0)
insa(SETNA, setna,		OpCls( R8_M08,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x96,	   0,	   P_386,	    0)
insa(SETNAE,setnae,		OpCls( R8_M08,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x92,	   0,	   P_386,	    0)
insa(SETNB, setnb,		OpCls( R8_M08,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x93,	   0,	   P_386,	    0)
insa(SETNBE,setnbe,		OpCls( R8_M08,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x97,	   0,	   P_386,	    0)
insa(SETNC, setnc,		OpCls( R8_M08,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x93,	   0,	   P_386,	    0)
insa(SETNE, setne,		OpCls( R8_M08,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x95,	   0,	   P_386,	    0)
insa(SETNG, setng,		OpCls( R8_M08,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x9E,	   0,	   P_386,	    0)
insa(SETNGE,setnge,		OpCls( R8_M08,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x9C,	   0,	   P_386,	    0)
insa(SETNL, setnl,		OpCls( R8_M08,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x9D,	   0,	   P_386,	    0)
insa(SETNLE,setnle,		OpCls( R8_M08,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x9F,	   0,	   P_386,	    0)
insa(SETNO, setno,		OpCls( R8_M08,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x91,	   0,	   P_386,	    0)
insa(SETNP, setnp,		OpCls( R8_M08,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x9B,	   0,	   P_386,	    0)
insa(SETNS, setns,		OpCls( R8_M08,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x99,	   0,	   P_386,	    0)
insa(SETNZ, setnz,		OpCls( R8_M08,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x95,	   0,	   P_386,	    0)
insa(SETO, seto,		OpCls( R8_M08,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x90,	   0,	   P_386,	    0)
insa(SETP, setp,		OpCls( R8_M08,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x9A,	   0,	   P_386,	    0)
insa(SETPE, setpe,		OpCls( R8_M08,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x9A,	   0,	   P_386,	    0)
insa(SETPO, setpo,		OpCls( R8_M08,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x9B,	   0,	   P_386,	    0)
insa(SETS, sets,		OpCls( R8_M08,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x98,	   0,	   P_386,	    0)
insa(SETZ, setz,		OpCls( R8_M08,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x94,	   0,	   P_386,	    0)

cmov	macro cond, c_id, condlc
	insa(CMOV&cond&, cmov&condlc&,OpCls( RGT8, R_MS, NONE ), F_0F, 1, no_WDS, 0x40+c_id,0, P_686, 0)
	endm

cmov A,	  0x7,	  a
cmov AE,  0x3,	 ae
cmov B,	  0x2,	  b
cmov BE,  0x6,	 be
cmov C,	  0x2,	  c
cmov E,	  0x4,	  e
cmov G,	  0xf,	  g
cmov GE,  0xd,	 ge
cmov L,	  0xc,	  l
cmov LE,  0xe,	 le
cmov NA,  0x6,	 na
cmov NAE, 0x2, nae
cmov NB,  0x3,	 nb
cmov NBE, 0x7, nbe
cmov NC,  0x3,	 nc
cmov NE,  0x5,	 ne
cmov NG,  0xe,	 ng
cmov NGE, 0xc, nge
cmov NL,  0xd,	 nl
cmov NLE, 0xf, nle
cmov NO,  0x1,	 no
cmov NP,  0xb,	 np
cmov NS,  0x9,	 ns
cmov NZ,  0x5,	 nz
cmov O,	  0x0,	  o
cmov P,	  0xa,	  p
cmov PE,  0xa,	 pe
cmov PO,  0xb,	 po
cmov S,	  0x8,	  s
cmov Z,	  0x4,	  z

; FPU opcodes

insa(FCMOVB, fcmovb,		OpCls( ST,	 STI,	     NONE ), 0,	     0,	 0,	 0xDA,	   0xC0,       P_686,	    0)
insa(FCMOVBE, fcmovbe,		OpCls( ST,	 STI,	     NONE ), 0,	     0,	 0,	 0xDA,	   0xD0,       P_686,	    0)
insa(FCMOVE, fcmove,		OpCls( ST,	 STI,	     NONE ), 0,	     0,	 0,	 0xDA,	   0xC8,       P_686,	    0)
insa(FCMOVNB, fcmovnb,		OpCls( ST,	 STI,	     NONE ), 0,	     0,	 0,	 0xDB,	   0xC0,       P_686,	    0)
insa(FCMOVNBE, fcmovnbe, OpCls( ST,	 STI,	     NONE ), 0,	     0,	 0,	 0xDB,	   0xD0,       P_686,	    0)
insa(FCMOVNE, fcmovne,		OpCls( ST,	 STI,	     NONE ), 0,	     0,	 0,	 0xDB,	   0xC8,       P_686,	    0)
insa(FCMOVNU, fcmovnu,		OpCls( ST,	 STI,	     NONE ), 0,	     0,	 0,	 0xDB,	   0xD8,       P_686,	    0)
insa(FCMOVU, fcmovu,		OpCls( ST,	 STI,	     NONE ), 0,	     0,	 0,	 0xDA,	   0xD8,       P_686,	    0)

insa(FCOM, fcom,		OpCls( STI,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD8,	   0xD0,       P_87,	    0)
insn(FCOM, 1,			OpCls( M32,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD8,	   0x10,       P_87,	    0)
insn(FCOM, 2,			OpCls( M64,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDC,	   0x10,       P_87,	    0)
insn(FCOM, 3,			OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD8,	   0xD1,       P_87,	    0)
insa(FCOMP, fcomp,		OpCls( STI,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD8,	   0xD8,       P_87,	    0)
insn(FCOMP, 1,			OpCls( M32,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD8,	   0x18,       P_87,	    0)
insn(FCOMP, 2,			OpCls( M64,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDC,	   0x18,       P_87,	    0)
insn(FCOMP, 3,			OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD8,	   0xD9,       P_87,	    0)
insa(FCOMPP, fcompp,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDE,	   0xD9,       P_87,	    0)

insa(FUCOM, fucom,		OpCls( STI,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDD,	   0xE0,       P_387,	    0)
insn(FUCOM, 1,			OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDD,	   0xE1,       P_387,	    0)
insa(FUCOMP, fucomp,		OpCls( STI,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDD,	   0xE8,       P_387,	    0)
insn(FUCOMP, 1,			OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDD,	   0xE9,       P_387,	    0)
insa(FUCOMPP, fucompp,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDA,	   0xE9,       P_387,	    0)
insa(FCOMI, fcomi,		OpCls( ST,	 STI,	     NONE ), 0,	     0,	 0,	 0xDB,	   0xF0,       P_686,	    0)
insa(FCOMIP, fcomip,		OpCls( ST,	 STI,	     NONE ), 0,	     0,	 0,	 0xDF,	   0xF0,       P_686,	    0)
insa(FUCOMI, fucomi,		OpCls( ST,	 STI,	     NONE ), 0,	     0,	 0,	 0xDB,	   0xE8,       P_686,	    0)
insa(FUCOMIP, fucomip,		OpCls( ST,	 STI,	     NONE ), 0,	     0,	 0,	 0xDF,	   0xE8,       P_686,	    0)

; v2.11: first 2 variants of FADD, FMUL, FDIV, FDIVP, FSUP and FSUBR exchanged
insa(FADD, fadd,		OpCls( ST,	 STI,	     NONE ), 0,	     0,	 0,	 0xD8,	   0xC0,       P_87,	    0)
insn(FADD, 1,			OpCls( STI,	 ST,	     NONE ), 0,	     0,	 0,	 0xDC,	   0xC0,       P_87,	    0)
insn(FADD, 2,			OpCls( M32,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD8,	   0,	   P_87,	    0)
insn(FADD, 3,			OpCls( M64,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDC,	   0,	   P_87,	    0)
insn(FADD, 4,			OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDE,	   0xC1,       P_87,	    0)
insa(FADDP, faddp,		OpCls( STI,	 ST,	     NONE ), 0,	     0,	 0,	 0xDE,	   0xC0,       P_87,	    0)
insn(FADDP, 1,			OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDE,	   0xC1,       P_87,	    0)
insa(FMUL, fmul,		OpCls( ST,	 STI,	     NONE ), 0,	     0,	 0,	 0xD8,	   0xC8,       P_87,	    0)
insn(FMUL, 1,			OpCls( STI,	 ST,	     NONE ), 0,	     0,	 0,	 0xDC,	   0xC8,       P_87,	    0)
insn(FMUL, 2,			OpCls( M32,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD8,	   0x08,       P_87,	    0)
insn(FMUL, 3,			OpCls( M64,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDC,	   0x08,       P_87,	    0)
insn(FMUL, 4,			OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDE,	   0xC9,       P_87,	    0)
insa(FMULP, fmulp,		OpCls( STI,	 ST,	     NONE ), 0,	     0,	 0,	 0xDE,	   0xC8,       P_87,	    0)
insn(FMULP, 1,			OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDE,	   0xC9,       P_87,	    0)

insa(FDIV, fdiv,		OpCls( ST,	 STI,	     NONE ), 0,	     0,	 0,	 0xD8,	   0xF0,       P_87,	    0)
insn(FDIV, 1,			OpCls( STI,	 ST,	     NONE ), 0,	     0,	 0,	 0xDC,	   0xF8,       P_87,	    0)
insn(FDIV, 2,			OpCls( M32,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD8,	   0x30,       P_87,	    0)
insn(FDIV, 3,			OpCls( M64,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDC,	   0x30,       P_87,	    0)
insn(FDIV, 4,			OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDE,	   0xF9,       P_87,	    0)
insa(FDIVP, fdivp,		OpCls( STI,	 ST,	     NONE ), 0,	     0,	 0,	 0xDE,	   0xF8,       P_87,	    0)
insn(FDIVP, 1,			OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDE,	   0xF9,       P_87,	    0)
insa(FDIVR, fdivr,		OpCls( ST,	 STI,	     NONE ), 0,	     0,	 0,	 0xD8,	   0xF8,       P_87,	    0)
insn(FDIVR, 1,			OpCls( STI,	 ST,	     NONE ), 0,	     0,	 0,	 0xDC,	   0xF0,       P_87,	    0)
insn(FDIVR, 2,			OpCls( M32,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD8,	   0x38,       P_87,	    0)
insn(FDIVR, 3,			OpCls( M64,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDC,	   0x38,       P_87,	    0)
insn(FDIVR, 4,			OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDE,	   0xF1,       P_87,	    0)
insa(FDIVRP, fdivrp,		OpCls( STI,	 ST,	     NONE ), 0,	     0,	 0,	 0xDE,	   0xF0,       P_87,	    0)
insn(FDIVRP, 1,			OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDE,	   0xF1,       P_87,	    0)
insa(FSUB, fsub,		OpCls( ST,	 STI,	     NONE ), 0,	     0,	 0,	 0xD8,	   0xE0,       P_87,	    0)
insn(FSUB, 1,			OpCls( STI,	 ST,	     NONE ), 0,	     0,	 0,	 0xDC,	   0xE8,       P_87,	    0)
insn(FSUB, 2,			OpCls( M32,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD8,	   0x20,       P_87,	    0)
insn(FSUB, 3,			OpCls( M64,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDC,	   0x20,       P_87,	    0)
insn(FSUB, 4,			OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDE,	   0xE9,       P_87,	    0)
insa(FSUBP, fsubp,		OpCls( STI,	 ST,	     NONE ), 0,	     0,	 0,	 0xDE,	   0xE8,       P_87,	    0)
insn(FSUBP, 1,			OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDE,	   0xE9,       P_87,	    0)
insa(FSUBR, fsubr,		OpCls( ST,	 STI,	     NONE ), 0,	     0,	 0,	 0xD8,	   0xE8,       P_87,	    0)
insn(FSUBR, 1,			OpCls( STI,	 ST,	     NONE ), 0,	     0,	 0,	 0xDC,	   0xE0,       P_87,	    0)
insn(FSUBR, 2,			OpCls( M32,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD8,	   0x28,       P_87,	    0)
insn(FSUBR, 3,			OpCls( M64,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDC,	   0x28,       P_87,	    0)
insn(FSUBR, 4,			OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDE,	   0xE1,       P_87,	    0)
insa(FSUBRP, fsubrp,		OpCls( STI,	 ST,	     NONE ), 0,	     0,	 0,	 0xDE,	   0xE0,       P_87,	    0)
insn(FSUBRP, 1,			OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDE,	   0xE1,       P_87,	    0)

insa(FIADD, fiadd,		OpCls( M32,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDA,	   0,	   P_87,	    0)
insn(FIADD, 1,			OpCls( M16,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDE,	   0,	   P_87,	    0)
insa(FICOM, ficom,		OpCls( M32,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDA,	   0x10,       P_87,	    0)
insn(FICOM, 1,			OpCls( M16,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDE,	   0x10,       P_87,	    0)
insa(FICOMP, ficomp,		OpCls( M32,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDA,	   0x18,       P_87,	    0)
insn(FICOMP, 1,			OpCls( M16,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDE,	   0x18,       P_87,	    0)
insa(FIDIV, fidiv,		OpCls( M32,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDA,	   0x30,       P_87,	    0)
insn(FIDIV, 1,			OpCls( M16,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDE,	   0x30,       P_87,	    0)
insa(FIDIVR, fidivr,		OpCls( M32,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDA,	   0x38,       P_87,	    0)
insn(FIDIVR, 1,			OpCls( M16,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDE,	   0x38,       P_87,	    0)
insa(FIMUL, fimul,		OpCls( M32,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDA,	   0x08,       P_87,	    0)
insn(FIMUL, 1,			OpCls( M16,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDE,	   0x08,       P_87,	    0)
insa(FISUB, fisub,		OpCls( M32,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDA,	   0x20,       P_87,	    0)
insn(FISUB, 1,			OpCls( M16,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDE,	   0x20,       P_87,	    0)
insa(FISUBR, fisubr,		OpCls( M32,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDA,	   0x28,       P_87,	    0)
insn(FISUBR, 1,			OpCls( M16,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDE,	   0x28,       P_87,	    0)

insa(FILD, fild,		OpCls( M32,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDB,	   0,	   P_87,	    0)
insn(FILD, 1,			OpCls( M64,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDF,	   0x28,       P_87,	    0)
insn(FILD, 2,			OpCls( M16,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDF,	   0,	   P_87,	    0)
insa(FISTP, fistp,		OpCls( M32,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDB,	   0x18,       P_87,	    0)
insn(FISTP, 1,			OpCls( M64,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDF,	   0x38,       P_87,	    0)
insn(FISTP, 2,			OpCls( M16,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDF,	   0x18,       P_87,	    0)
insa(FIST, fist,		OpCls( M32,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDB,	   0x10,       P_87,	    0)
insn(FIST, 1,			OpCls( M16,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDF,	   0x10,       P_87,	    0)

insa(FLD, fld,			OpCls( STI,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0xC0,       P_87,	    0)
insn(FLD, 1,			OpCls( M32,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0,	   P_87,	    0)
insn(FLD, 2,			OpCls( M64,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDD,	   0,	   P_87,	    0)
insn(FLD, 3,			OpCls( M80,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDB,	   0x28,       P_87,	    0)
insa(FSTP, fstp,		OpCls( STI,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDD,	   0xD8,       P_87,	    0)
insn(FSTP, 1,			OpCls( M32,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0x18,       P_87,	    0)
insn(FSTP, 2,			OpCls( M64,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDD,	   0x18,       P_87,	    0)
insn(FSTP, 3,			OpCls( M80,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDB,	   0x38,       P_87,	    0)
insa(FST, fst,			OpCls( STI,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDD,	   0xD0,       P_87,	    0)
insn(FST, 1,			OpCls( M32,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0x10,       P_87,	    0)
insn(FST, 2,			OpCls( M64,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDD,	   0x10,       P_87,	    0)

insa(FLDENV, fldenv,		OpCls( M_ANY,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0x20,       P_87,	    0)
insa(FLDENVD, fldenvd,		OpCls( M_ANY,	 NONE,	     NONE ), F_32,   0,	 0,	 0xD9,	   0x20,       P_387,	    0)
insa(FLDENVW, fldenvw,		OpCls( M_ANY,	 NONE,	     NONE ), F_16,   0,	 0,	 0xD9,	   0x20,       P_87,	    0)
insa(FNSAVE, fnsave,		OpCls( M_ANY,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDD,	   0x30,       P_87,	    AP_NO_FWAIT)
insa(FNSAVED, fnsaved,		OpCls( M_ANY,	 NONE,	     NONE ), F_32,   0,	 0,	 0xDD,	   0x30,       P_387,	    AP_NO_FWAIT)
insa(FNSAVEW, fnsavew,		OpCls( M_ANY,	 NONE,	     NONE ), F_16,   0,	 0,	 0xDD,	   0x30,       P_87,	    AP_NO_FWAIT)
insa(FNSTENV, fnstenv,		OpCls( M_ANY,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0x30,       P_87,	    AP_NO_FWAIT)
insa(FNSTENVD, fnstenvd, OpCls( M_ANY,	 NONE,	     NONE ), F_32,   0,	 0,	 0xD9,	   0x30,       P_387,	    AP_NO_FWAIT)
insa(FNSTENVW, fnstenvw, OpCls( M_ANY,	 NONE,	     NONE ), F_16,   0,	 0,	 0xD9,	   0x30,       P_87,	    AP_NO_FWAIT)
insa(FRSTOR, frstor,		OpCls( M_ANY,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDD,	   0x20,       P_87,	    0)
insa(FRSTORD, frstord,		OpCls( M_ANY,	 NONE,	     NONE ), F_32,   0,	 0,	 0xDD,	   0x20,       P_387,	    0)
insa(FRSTORW, frstorw,		OpCls( M_ANY,	 NONE,	     NONE ), F_16,   0,	 0,	 0xDD,	   0x20,       P_87,	    0)
insa(FSAVE, fsave,		OpCls( M_ANY,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDD,	   0x30,       P_87,	    AP_FWAIT)
insa(FSAVED, fsaved,		OpCls( M_ANY,	 NONE,	     NONE ), F_32,   0,	 0,	 0xDD,	   0x30,       P_387,	    AP_FWAIT)
insa(FSAVEW, fsavew,		OpCls( M_ANY,	 NONE,	     NONE ), F_16,   0,	 0,	 0xDD,	   0x30,       P_87,	    AP_FWAIT)
insa(FSTENV, fstenv,		OpCls( M_ANY,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0x30,       P_87,	    AP_FWAIT)
insa(FSTENVD, fstenvd,		OpCls( M_ANY,	 NONE,	     NONE ), F_32,   0,	 0,	 0xD9,	   0x30,       P_387,	    AP_FWAIT)
insa(FSTENVW, fstenvw,		OpCls( M_ANY,	 NONE,	     NONE ), F_16,   0,	 0,	 0xD9,	   0x30,       P_87,	    AP_FWAIT)

insa(FLDCW, fldcw,		OpCls( M16,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0x28,       P_87,	    0)
insa(FNSTCW, fnstcw,		OpCls( M16,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0x38,       P_87,	    AP_NO_FWAIT)
insa(FNSTSW, fnstsw,		OpCls( AX,	 NONE,	     NONE ), 0,	     0,	 no_WDS, 0xDF,	   0xE0,       P_287,	    AP_NO_FWAIT)
insn(FNSTSW, 1,			OpCls( M16,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDD,	   0x38,       P_87,	    AP_NO_FWAIT)
insa(FSTCW, fstcw,		OpCls( M16,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0x38,       P_87,	    AP_FWAIT)
insa(FSTSW, fstsw,		OpCls( AX,	 NONE,	     NONE ), 0,	     0,	 no_WDS, 0xDF,	   0xE0,       P_287,	    AP_FWAIT)
insn(FSTSW, 1,			OpCls( M16,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDD,	   0x38,       P_87,	    AP_FWAIT)

insa(FCOS, fcos,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0xFF,       P_387,	    0)
insa(FPATAN, fpatan,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0xF3,       P_87,	    0)
insa(FPTAN, fptan,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0xF2,       P_87,	    0)
insa(FSIN, fsin,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0xFE,       P_387,	    0)
insa(FSINCOS, fsincos,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0xFB,       P_387,	    0)

insa(FINIT, finit,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDB,	   0xE3,       P_87,	    AP_FWAIT)
insa(FNINIT, fninit,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDB,	   0xE3,       P_87,	    AP_NO_FWAIT)
insa(FDISI, fdisi,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDB,	   0xE1,       P_87,	    AP_FWAIT)
insa(FNDISI, fndisi,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDB,	   0xE1,       P_87,	    AP_NO_FWAIT)
insa(FENI, feni,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDB,	   0xE0,       P_87,	    AP_FWAIT)
insa(FNENI, fneni,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDB,	   0xE0,       P_87,	    AP_NO_FWAIT)
insa(FCLEX, fclex,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDB,	   0xE2,       P_87,	    AP_FWAIT)
insa(FNCLEX, fnclex,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDB,	   0xE2,       P_87,	    AP_NO_FWAIT)

insa(F2XM1, f2xm1,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0xF0,       P_87,	    0)
insa(FABS, fabs,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0xE1,       P_87,	    0)
insa(FBLD, fbld,		OpCls( M80,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDF,	   0x20,       P_87,	    0)
insa(FBSTP, fbstp,		OpCls( M80,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDF,	   0x30,       P_87,	    0)
insa(FCHS, fchs,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0xE0,       P_87,	    0)
insa(FLD1, fld1,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0xE8,       P_87,	    0)
insa(FLDL2E, fldl2e,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0xEA,       P_87,	    0)
insa(FLDL2T, fldl2t,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0xE9,       P_87,	    0)
insa(FLDLG2, fldlg2,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0xEC,       P_87,	    0)
insa(FLDLN2, fldln2,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0xED,       P_87,	    0)
insa(FLDPI, fldpi,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0xEB,       P_87,	    0)
insa(FLDZ, fldz,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0xEE,       P_87,	    0)
insa(FDECSTP, fdecstp,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0xF6,       P_87,	    0)
insa(FINCSTP, fincstp,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0xF7,       P_87,	    0)
insa(FFREE, ffree,		OpCls( STI,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDD,	   0xC0,       P_87,	    0)
; FFREEP is undocumented (same as FFREE + POP)
insa(FFREEP, ffreep,		OpCls( STI,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDF,	   0xC0,       P_87,	    0)
insa(FNOP, fnop,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0xD0,       P_87,	    0)
insa(FPREM, fprem,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0xF8,       P_87,	    0)
insa(FPREM1, fprem1,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0xF5,       P_387,	    0)
insa(FRNDINT, frndint,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0xFC,       P_87,	    0)
insa(FSCALE, fscale,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0xFD,       P_87,	    0)
insa(FSETPM, fsetpm,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xDB,	   0xE4,       P_287,	    0)
insa(FSQRT, fsqrt,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0xFA,       P_87,	    0)
insa(FTST, ftst,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0xE4,       P_87,	    0)
insa(FWAIT, fwait,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0x9B,	   0,	   P_87,	    0)
insa(FXAM, fxam,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0xE5,       P_87,	    0)
insa(FXCH, fxch,		OpCls( STI,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0xC8,       P_87,	    0)
insn(FXCH, 1,			OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0xC9,       P_87,	    0)
insa(FXRSTOR, fxrstor,		OpCls( M_ANY,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0xAE,	   0x08,       P_686|P_SSE1,0)
insa(FXSAVE, fxsave,		OpCls( M_ANY,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0xAE,	   0,	   P_686|P_SSE1,0)
insa(FXTRACT, fxtract,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0xF4,       P_87,	    0)
insa(FYL2X, fyl2x,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0xF1,       P_87,	    0)
insa(FYL2XP1, fyl2xp1,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 0,	 0xD9,	   0xF9,       P_87,	    0)

; MMX/SSE related opcodes (except SSE instructions CMPSD and MOVSD)

insa(EMMS, emms,		OpCls( NONE,	 NONE,	     NONE ), F_0F,   0,	 no_RM,	 0x77,	   0,	   P_586|P_MMX, 0)
insa(CLFLUSH, clflush,		OpCls( M_ANY,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0xAE,	   0x38,       P_686|P_SSE2,0)
insa(LDMXCSR, ldmxcsr,		OpCls( M32,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0xAE,	   0x10,       P_686|P_SSE1,0)
insa(STMXCSR, stmxcsr,		OpCls( M32,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0xAE,	   0x18,       P_686|P_SSE1,0)
insa(LFENCE, lfence,		OpCls( NONE,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0xAE,	   0xE8,       P_686|P_SSE2,0)
insa(MFENCE, mfence,		OpCls( NONE,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0xAE,	   0xF0,       P_686|P_SSE2,0)
insa(SFENCE, sfence,		OpCls( NONE,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0xAE,	   0xF8,       P_686|P_SSE1,0)
insa(PREFETCHNTA,prefetchnta,	OpCls( M_ANY,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x18,	   0,	   P_686|P_SSE1,0)
insa(PREFETCHT0, prefetcht0,	OpCls( M_ANY,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x18,	   0x08,       P_686|P_SSE1,0)
insa(PREFETCHT1, prefetcht1,	OpCls( M_ANY,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x18,	   0x10,       P_686|P_SSE1,0)
insa(PREFETCHT2, prefetcht2,	OpCls( M_ANY,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x18,	   0x18,       P_686|P_SSE1,0)
insa(PAUSE, pause,		OpCls( NONE,	 NONE,	     NONE ), F_F3,   0,	 no_RM,	 0x90,	   0,	   P_686|P_SSE2,0)

; define ADDPD, ADDPS, ADDSD, ADDSS, DIVPD, DIVPS, DIVSD, DIVSS, ...

arfl	macro prefix, prefixlc, opc
	insa(&prefix&PD, &prefixlc&pd, OpCls( XMM, XMM_M128,NONE ), F_660F, 1,	no_WDS, opc, 0, P_686+P_SSE2,0)
	insa(&prefix&PS, &prefixlc&ps, OpCls( XMM, XMM_M128,NONE ), F_0F,   1,	no_WDS, opc, 0, P_686+P_SSE1,0)
	insa(&prefix&SD, &prefixlc&sd, OpCls( XMM, XMM_M64, NONE ), F_F20F, 1,	no_WDS, opc, 0, P_686+P_SSE2,0)
	insa(&prefix&SS, &prefixlc&ss, OpCls( XMM, XMM_M32, NONE ), F_F30F, 1,	no_WDS, opc, 0, P_686+P_SSE1,0)
	endm

arfl ADD,  add,	 0x58
arfl DIV,  div,	 0x5E
arfl MAX,  max,	 0x5F
arfl MIN,  min,	 0x5D
arfl MUL,  mul,	 0x59
arfl SQRT, sqrt, 0x51
arfl SUB,  sub,	 0x5C

; CMP can't be added because CMPSD is special
insa(CMPPD, cmppd,		OpCls( XMM,	 XMM_M128, I8_U ), F_660F, 1,  no_WDS, 0xC2,	 0,	     P_686+|P_SSE2,0)
insa(CMPPS, cmpps,		OpCls( XMM,	 XMM_M128, I8_U ), F_0F,   1,  no_WDS, 0xC2,	 0,	     P_686+P_SSE1,0)
insa(CMPSS, cmpss,		OpCls( XMM,	 XMM_M32,  I8_U ), F_F30F, 1,  no_WDS, 0xC2,	 0,	     P_686+P_SSE1,0)

cmpxx	macro suffix, suffixlc, byte1, memop, ssever
	insa(CMPEQ&suffix&, cmpeq&suffixlc&,	  OpCls( XMM, XMM_&memop&, HID ),byte1, 1, no_WDS, 0C2h, 0, P_686+ssever, 0 )
	insa(CMPLT&suffix&, cmplt&suffixlc&,	  OpCls( XMM, XMM_&memop&, HID ),byte1, 1, no_WDS, 0C2h, 0, P_686+ssever, 0 )
	insa(CMPLE&suffix&, cmple&suffixlc&,	  OpCls( XMM, XMM_&memop&, HID ),byte1, 1, no_WDS, 0C2h, 0, P_686+ssever, 0 )
	insa(CMPUNORD&suffix&, cmpunord&suffixlc&,OpCls( XMM, XMM_&memop&, HID ),byte1, 1, no_WDS, 0C2h, 0, P_686+ssever, 0 )
	insa(CMPNEQ&suffix&, cmpneq&suffixlc&,	  OpCls( XMM, XMM_&memop&, HID ),byte1, 1, no_WDS, 0C2h, 0, P_686+ssever, 0 )
	insa(CMPNLT&suffix&, cmpnlt&suffixlc&,	  OpCls( XMM, XMM_&memop&, HID ),byte1, 1, no_WDS, 0C2h, 0, P_686+ssever, 0 )
	insa(CMPNLE&suffix&, cmpnle&suffixlc&,	  OpCls( XMM, XMM_&memop&, HID ),byte1, 1, no_WDS, 0C2h, 0, P_686+ssever, 0 )
	insa(CMPORD&suffix&, cmpord&suffixlc&,	  OpCls( XMM, XMM_&memop&, HID ),byte1, 1, no_WDS, 0C2h, 0, P_686+ssever, 0 )
	endm

cmpxx PD, pd, F_660F, M128, P_SSE2
cmpxx PS, ps, F_0F,   M128, P_SSE1
cmpxx SD, sd, F_F20F, M64,  P_SSE2
cmpxx SS, ss, F_F30F, M32,  P_SSE1

insa(ANDNPD, andnpd,		OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0x55,	 0,	     P_686|P_SSE2,0)
insa(ANDNPS, andnps,		OpCls( XMM,	 XMM_M128, NONE ), F_0F,   1,  no_WDS, 0x55,	 0,	     P_686|P_SSE1,0)
insa(ANDPD, andpd,		OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0x54,	 0,	     P_686|P_SSE2,0)
insa(ANDPS, andps,		OpCls( XMM,	 XMM_M128, NONE ), F_0F,   1,  no_WDS, 0x54,	 0,	     P_686|P_SSE1,0)
insa(ORPD, orpd,		OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0x56,	 0,	     P_686|P_SSE2,0)
insa(ORPS, orps,		OpCls( XMM,	 XMM_M128, NONE ), F_0F,   1,  no_WDS, 0x56,	 0,	     P_686|P_SSE1,0)
insa(COMISD, comisd,		OpCls( XMM,	 XMM_M64,  NONE ), F_660F, 1,  no_WDS, 0x2F,	 0,	     P_686|P_SSE2,0)
insa(COMISS, comiss,		OpCls( XMM,	 XMM_M32,  NONE ), F_0F,   1,  no_WDS, 0x2F,	 0,	     P_686|P_SSE1,0)
insa(XORPD, xorpd,		OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0x57,	 0,	     P_686|P_SSE2,0)
insa(XORPS, xorps,		OpCls( XMM,	 XMM_M128, NONE ), F_0F,   1,  no_WDS, 0x57,	 0,	     P_686|P_SSE1,0)

insa(CVTPD2PI, cvtpd2pi, OpCls( MMX,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0x2D,	 0,	     P_686|P_SSE2,0)
insa(CVTPS2PI, cvtps2pi, OpCls( MMX,	 XMM_M64,  NONE ), F_0F,   1,  no_WDS, 0x2D,	 0,	     P_686|P_SSE1,0)
insa(CVTSD2SI, cvtsd2si, OpCls( RGT16,	 XMM_M64,  NONE ), F_F20F, 1,  no_WDS, 0x2D,	 0,	     P_686|P_SSE2,0)
insa(CVTSS2SI, cvtss2si, OpCls( RGT16,	 XMM_M32,  NONE ), F_F30F, 1,  no_WDS, 0x2D,	 0,	     P_686|P_SSE1,0)
insa(CVTPI2PD, cvtpi2pd, OpCls( XMM,	 MMX_M64,  NONE ), F_660F, 1,  no_WDS, 0x2A,	 0,	     P_686|P_SSE2,0)
insa(CVTPI2PS, cvtpi2ps, OpCls( XMM,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0x2A,	 0,	     P_686|P_SSE1,0)
insa(CVTSI2SD, cvtsi2sd, OpCls( XMM,	 RMGT16,   NONE ), F_F20F, 1,  no_WDS, 0x2A,	 0,	     P_686|P_SSE2,0)
insa(CVTSI2SS, cvtsi2ss, OpCls( XMM,	 RMGT16,   NONE ), F_F30F, 1,  no_WDS, 0x2A,	 0,	     P_686|P_SSE1,0)
insa(CVTTPD2PI, cvttpd2pi, OpCls( MMX,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0x2C,	 0,	     P_686|P_SSE2,0)
insa(CVTTPS2PI, cvttps2pi, OpCls( MMX,	 XMM_M64,  NONE ), F_0F,   1,  no_WDS, 0x2C,	 0,	     P_686|P_SSE1,0)
insa(CVTTSD2SI, cvttsd2si, OpCls( RGT16,	 XMM_M64,  NONE ), F_F20F, 1,  no_WDS, 0x2C,	 0,	     P_686|P_SSE2,0)
insa(CVTTSS2SI, cvttss2si, OpCls( RGT16,	 XMM_M32,  NONE ), F_F30F, 1,  no_WDS, 0x2C,	 0,	     P_686|P_SSE1,0)

insa(CVTDQ2PS, cvtdq2ps, OpCls( XMM,	 XMM_M128, NONE ), F_0F,   1,  no_WDS, 0x5B,	 0,	     P_686|P_SSE2,0)
insa(CVTPS2DQ, cvtps2dq, OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0x5B,	 0,	     P_686|P_SSE2,0)
insa(CVTTPS2DQ, cvttps2dq, OpCls( XMM,	 XMM_M128, NONE ), F_F30F, 1,  no_WDS, 0x5B,	 0,	     P_686|P_SSE2,0)

insa(CVTPD2DQ, cvtpd2dq, OpCls( XMM,	 XMM_M128, NONE ), F_F20F, 1,  no_WDS, 0xE6,	 0,	     P_686|P_SSE2,0)
insa(CVTDQ2PD, cvtdq2pd, OpCls( XMM,	 XMM_M64,  NONE ), F_F30F, 1,  no_WDS, 0xE6,	 0,	     P_686|P_SSE2,0)
insa(CVTTPD2DQ, cvttpd2dq, OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0xE6,	 0,	     P_686|P_SSE2,0)

insa(CVTPD2PS, cvtpd2ps, OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0x5A,	 0,	     P_686|P_SSE2,0)
insa(CVTPS2PD, cvtps2pd, OpCls( XMM,	 XMM_M64,  NONE ), F_0F,   1,  no_WDS, 0x5A,	 0,	     P_686|P_SSE2,0)
insa(CVTSD2SS, cvtsd2ss, OpCls( XMM,	 XMM_M64,  NONE ), F_F20F, 1,  no_WDS, 0x5A,	 0,	     P_686|P_SSE2,0)
insa(CVTSS2SD, cvtss2sd, OpCls( XMM,	 XMM_M32,  NONE ), F_F30F, 1,  no_WDS, 0x5A,	 0,	     P_686|P_SSE2,0)

insa(MASKMOVDQU, maskmovdqu,	OpCls( XMM,	 XMM,	   NONE ), F_660F, 1,  no_WDS, 0xF7,	 0,	     P_686|P_SSE2,0)
insa(MASKMOVQ, maskmovq, OpCls( MMX,	 MMX,	   NONE ), F_0F,   1,  no_WDS, 0xF7,	 0,	     P_686|P_SSE1,0)

; Masm (ML64) uses MOVD if a 64-bit register is src/dst. Intel docs prefer MOVQ
insa(MOVD, movd,		OpCls( MMX,	 RMGT16,   NONE ), F_0F,   1,  no_WDS, 0x6E,	 0,	     P_586|P_MMX, 0)
insn(MOVD, 1,			OpCls( XMM,	 RMGT16,   NONE ), F_660F, 1,  no_WDS, 0x6E,	 0,	     P_686|P_SSE2,0)
insn(MOVD, 2,			OpCls( RMGT16,	 MMX,	   NONE ), F_0F,   0,  no_WDS, 0x7E,	 0,	     P_586|P_MMX, 0)
insn(MOVD, 3,			OpCls( RMGT16,	 XMM,	   NONE ), F_660F, 0,  no_WDS, 0x7E,	 0,	     P_686|P_SSE2,0)
insa(MOVQ, movq,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0x6F,	 0,	     P_586|P_MMX, 0)
insn(MOVQ, 1,			OpCls( XMM,	 XMM_M64,  NONE ), F_F30F, 1,  no_WDS, 0x7E,	 0,	     P_686|P_SSE2,0)
insn(MOVQ, 2,			OpCls( M64,	 MMX,	   NONE ), F_0F,   0,  no_WDS, 0x7F,	 0,	     P_586|P_MMX, 0)
insn(MOVQ, 3,			OpCls( M64,	 XMM,	   NONE ), F_660F, 0,  no_WDS, 0xD6,	 0,	     P_686|P_SSE2,0)

insa(MOVAPD, movapd,		OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0x28,	 0,	     P_686|P_SSE2,0)
insn(MOVAPD, 1,			OpCls( M128,	 XMM,	   NONE ), F_660F, 0,  no_WDS, 0x29,	 0,	     P_686|P_SSE2,0)
insa(MOVAPS, movaps,		OpCls( XMM,	 XMM_M128, NONE ), F_0F,   1,  no_WDS, 0x28,	 0,	     P_686|P_SSE1,0)
insn(MOVAPS, 1,			OpCls( M128,	 XMM,	   NONE ), F_0F,   0,  no_WDS, 0x29,	 0,	     P_686|P_SSE1,0)
insa(MOVDQA, movdqa,		OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0x6F,	 0,	     P_686|P_SSE2,0)
insn(MOVDQA, 1,			OpCls( M128,	 XMM,	   NONE ), F_660F, 0,  no_WDS, 0x7F,	 0,	     P_686|P_SSE2,0)
insa(MOVDQU, movdqu,		OpCls( XMM,	 XMM_M128, NONE ), F_F30F, 1,  no_WDS, 0x6F,	 0,	     P_686|P_SSE2,0)
insn(MOVDQU, 1,			OpCls( M128,	 XMM,	   NONE ), F_F30F, 0,  no_WDS, 0x7F,	 0,	     P_686|P_SSE2,0)
insa(MOVUPD, movupd,		OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0x10,	 0,	     P_686|P_SSE2,0)
insn(MOVUPD, 1,			OpCls( M128,	 XMM,	   NONE ), F_660F, 0,  no_WDS, 0x11,	 0,	     P_686|P_SSE2,0)
insa(MOVUPS, movups,		OpCls( XMM,	 XMM_M128, NONE ), F_0F,   1,  no_WDS, 0x10,	 0,	     P_686|P_SSE1,0)
insn(MOVUPS, 1,			OpCls( M128,	 XMM,	   NONE ), F_0F,   0,  no_WDS, 0x11,	 0,	     P_686|P_SSE1,0)

insa(MOVHPD, movhpd,		OpCls( XMM,	 M64,	   NONE ), F_660F, 1,  no_WDS, 0x16,	 0,	     P_686|P_SSE2,0)
insn(MOVHPD, 1,			OpCls( M64,	 XMM,	   NONE ), F_660F, 0,  no_WDS, 0x17,	 0,	     P_686|P_SSE2,0)
insa(MOVHPS, movhps,		OpCls( XMM,	 M64,	   NONE ), F_0F,   1,  no_WDS, 0x16,	 0,	     P_686|P_SSE1,0)
insn(MOVHPS, 1,			OpCls( M64,	 XMM,	   NONE ), F_0F,   0,  no_WDS, 0x17,	 0,	     P_686|P_SSE1,0)
insa(MOVLPD, movlpd,		OpCls( XMM,	 M64,	   NONE ), F_660F, 1,  no_WDS, 0x12,	 0,	     P_686|P_SSE2,0)
insn(MOVLPD, 1,			OpCls( M64,	 XMM,	   NONE ), F_660F, 0,  no_WDS, 0x13,	 0,	     P_686|P_SSE2,0)
insa(MOVLPS, movlps,		OpCls( XMM,	 M64,	   NONE ), F_0F,   1,  no_WDS, 0x12,	 0,	     P_686|P_SSE1,0)
insn(MOVLPS, 1,			OpCls( M64,	 XMM,	   NONE ), F_0F,   0,  no_WDS, 0x13,	 0,	     P_686|P_SSE1,0)

insa(MOVHLPS, movhlps,		OpCls( XMM,	 XMM,	   NONE ), F_0F,   1,  no_WDS, 0x12,	 0,	     P_686|P_SSE1,0)
insa(MOVLHPS, movlhps,		OpCls( XMM,	 XMM,	   NONE ), F_0F,   1,  no_WDS, 0x16,	 0,	     P_686|P_SSE1,0)
insa(MOVDQ2Q, movdq2q,		OpCls( MMX,	 XMM,	   NONE ), F_F20F, 1,  no_WDS, 0xD6,	 0,	     P_686|P_SSE2,0)
insa(MOVQ2DQ, movq2dq,		OpCls( XMM,	 MMX,	   NONE ), F_F30F, 1,  no_WDS, 0xD6,	 0,	     P_686|P_SSE2,0)

insa(MOVMSKPD, movmskpd, OpCls( RGT16,	 XMM,	   NONE ), F_660F, 1,  no_WDS, 0x50,	 0,	     P_686|P_SSE2,0)
insa(MOVMSKPS, movmskps, OpCls( RGT16,	 XMM,	   NONE ), F_0F,   1,  no_WDS, 0x50,	 0,	     P_686|P_SSE1,0)
insa(MOVNTDQ, movntdq,		OpCls( M128,	 XMM,	   NONE ), F_660F, 0,  no_WDS, 0xE7,	 0,	     P_686|P_SSE2,0)
insa(MOVNTI, movnti,		OpCls( MGT16,	 RGT16,	   NONE ), F_0F,   0,  no_WDS, 0xC3,	 0,	     P_686|P_SSE2,0)
insa(MOVNTPD, movntpd,		OpCls( M128,	 XMM,	   NONE ), F_660F, 0,  no_WDS, 0x2B,	 0,	     P_686|P_SSE2,0)
insa(MOVNTPS, movntps,		OpCls( M128,	 XMM,	   NONE ), F_0F,   0,  no_WDS, 0x2B,	 0,	     P_686|P_SSE1,0)
insa(MOVNTQ, movntq,		OpCls( M64,	 MMX,	   NONE ), F_0F,   0,  no_WDS, 0xE7,	 0,	     P_686|P_SSE1,0)
insa(MOVSS, movss,		OpCls( XMM,	 XMM_M32,  NONE ), F_F30F, 1,  no_WDS, 0x10,	 0,	     P_686|P_SSE1,0)
insn(MOVSS, 1,			OpCls( M32,	 XMM,	   NONE ), F_F30F, 0,  no_WDS, 0x11,	 0,	     P_686|P_SSE1,0)

insa(PACKSSDW, packssdw, OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0x6B,	 0,	     P_586|P_MMX, 0)
insn(PACKSSDW, 1,		OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0x6B,	 0,	     P_686|P_SSE2,0)
insa(PACKSSWB, packsswb, OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0x63,	 0,	     P_586|P_MMX, 0)
insn(PACKSSWB, 1,		OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0x63,	 0,	     P_686|P_SSE2,0)
insa(PACKUSWB, packuswb, OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0x67,	 0,	     P_586|P_MMX, 0)
insn(PACKUSWB, 1,		OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0x67,	 0,	     P_686|P_SSE2,0)
insa(PADDB, paddb,		OpCls( MMX,    MMX_M64_08, NONE ), F_0F,   1,  no_WDS, 0xFC,	 0,	     P_586|P_MMX, 0)
insn(PADDB, 1,			OpCls( XMM,    XMM_M128_08,NONE ), F_660F, 1,  no_WDS, 0xFC,	 0,	     P_686|P_SSE2,0)
insa(PADDW, paddw,		OpCls( MMX,    MMX_M64_16, NONE ), F_0F,   1,  no_WDS, 0xFD,	 0,	     P_586|P_MMX, 0)
insn(PADDW, 1,			OpCls( XMM,    XMM_M128_16,NONE ), F_660F, 1,  no_WDS, 0xFD,	 0,	     P_686|P_SSE2,0)
insa(PADDD, paddd,		OpCls( MMX,    MMX_M64_32, NONE ), F_0F,   1,  no_WDS, 0xFE,	 0,	     P_586|P_MMX, 0)
insn(PADDD, 1,			OpCls( XMM,    XMM_M128_32,NONE ), F_660F, 1,  no_WDS, 0xFE,	 0,	     P_686|P_SSE2,0)
insa(PADDQ, paddq,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0xD4,	 0,	     P_686|P_SSE2,0)
insn(PADDQ, 1,			OpCls( XMM,    XMM_M128_64,NONE ), F_660F, 1,  no_WDS, 0xD4,	 0,	     P_686|P_SSE2,0)
insa(PADDSB, paddsb,		OpCls( MMX,    MMX_M64_08, NONE ), F_0F,   1,  no_WDS, 0xEC,	 0,	     P_586|P_MMX, 0)
insn(PADDSB, 1,			OpCls( XMM,    XMM_M128_08,NONE ), F_660F, 1,  no_WDS, 0xEC,	 0,	     P_686|P_SSE2,0)
insa(PADDSW, paddsw,		OpCls( MMX,    MMX_M64_16, NONE ), F_0F,   1,  no_WDS, 0xED,	 0,	     P_586|P_MMX, 0)
insn(PADDSW, 1,			OpCls( XMM,    XMM_M128_16,NONE ), F_660F, 1,  no_WDS, 0xED,	 0,	     P_686|P_SSE2,0)
insa(PADDUSB, paddusb,		OpCls( MMX,    MMX_M64_08, NONE ), F_0F,   1,  no_WDS, 0xDC,	 0,	     P_586|P_MMX, 0)
insn(PADDUSB, 1,		OpCls( XMM,    XMM_M128_08,NONE ), F_660F, 1,  no_WDS, 0xDC,	 0,	     P_686|P_SSE2,0)
insa(PADDUSW, paddusw,		OpCls( MMX,    MMX_M64_16, NONE ), F_0F,   1,  no_WDS, 0xDD,	 0,	     P_586|P_MMX, 0)
insn(PADDUSW, 1,		OpCls( XMM,    XMM_M128_16,NONE ), F_660F, 1,  no_WDS, 0xDD,	 0,	     P_686|P_SSE2,0)
insa(PAND, pand,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0xDB,	 0,	     P_586|P_MMX, 0)
insn(PAND, 1,			OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0xDB,	 0,	     P_686|P_SSE2,0)
insa(PANDN, pandn,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0xDF,	 0,	     P_586|P_MMX, 0)
insn(PANDN, 1,			OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0xDF,	 0,	     P_686|P_SSE2,0)
insa(PAVGB, pavgb,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0xE0,	 0,	     P_686|P_SSE1,0)
insn(PAVGB, 1,			OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0xE0,	 0,	     P_686|P_SSE2,0)
insa(PAVGW, pavgw,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0xE3,	 0,	     P_686|P_SSE1,0)
insn(PAVGW, 1,			OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0xE3,	 0,	     P_686|P_SSE2,0)
insa(PCMPEQB, pcmpeqb,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0x74,	 0,	     P_586|P_MMX, 0)
insn(PCMPEQB, 1,		OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0x74,	 0,	     P_686|P_SSE2,0)
insa(PCMPEQW, pcmpeqw,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0x75,	 0,	     P_586|P_MMX, 0)
insn(PCMPEQW, 1,		OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0x75,	 0,	     P_686|P_SSE2,0)
insa(PCMPEQD, pcmpeqd,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0x76,	 0,	     P_586|P_MMX, 0)
insn(PCMPEQD, 1,		OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0x76,	 0,	     P_686|P_SSE2,0)
insa(PCMPGTB, pcmpgtb,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0x64,	 0,	     P_586|P_MMX, 0)
insn(PCMPGTB, 1,		OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0x64,	 0,	     P_686|P_SSE2,0)
insa(PCMPGTW, pcmpgtw,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0x65,	 0,	     P_586|P_MMX, 0)
insn(PCMPGTW, 1,		OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0x65,	 0,	     P_686|P_SSE2,0)
insa(PCMPGTD, pcmpgtd,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0x66,	 0,	     P_586|P_MMX, 0)
insn(PCMPGTD, 1,		OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0x66,	 0,	     P_686|P_SSE2,0)
insa(PEXTRW, pextrw,		OpCls( RGT16,	 MMX,	   I8_U ), F_0F,   1,  no_WDS, 0xC5,	 0,	     P_686|P_SSE1,0)
insn(PEXTRW, 1,			OpCls( RGT16,	 XMM,	   I8_U ), F_660F, 1,  no_WDS, 0xC5,	 0,	     P_686|P_SSE1,0)

insn(PEXTRW, 2,			OpCls( M16,	 XMM,	   I8_U ), F_660F3A, 0,no_WDS, 0x15,	 0,	     P_686|P_SSE4,0)
insa(PINSRW, pinsrw,		OpCls( MMX,	 R32_M16,  I8_U ), F_0F,   1,  no_WDS, 0xC4,	 0,	     P_686|P_SSE1,0)
insn(PINSRW, 1,			OpCls( XMM,	 R32_M16,  I8_U ), F_660F, 1,  no_WDS, 0xC4,	 0,	     P_686|P_SSE1,0)
insa(PMADDWD, pmaddwd,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0xF5,	 0,	     P_586|P_MMX, 0)
insn(PMADDWD, 1,		OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0xF5,	 0,	     P_686|P_SSE2,0)
insa(PMAXSW, pmaxsw,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0xEE,	 0,	     P_686|P_SSE1,0)
insn(PMAXSW, 1,			OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0xEE,	 0,	     P_686|P_SSE2,0)
insa(PMAXUB, pmaxub,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0xDE,	 0,	     P_686|P_SSE1,0)
insn(PMAXUB, 1,			OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0xDE,	 0,	     P_686|P_SSE2,0)
insa(PMINSW, pminsw,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0xEA,	 0,	     P_686|P_SSE1,0)
insn(PMINSW, 1,			OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0xEA,	 0,	     P_686|P_SSE2,0)
insa(PMINUB, pminub,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0xDA,	 0,	     P_686|P_SSE1,0)
insn(PMINUB, 1,			OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0xDA,	 0,	     P_686|P_SSE2,0)
insa(PMOVMSKB, pmovmskb, OpCls( RGT16,	 MMX,	   NONE ), F_0F,   1,  no_WDS, 0xD7,	 0,	     P_686|P_SSE1,0)
insn(PMOVMSKB, 1,		OpCls( RGT16,	 XMM,	   NONE ), F_660F, 1,  no_WDS, 0xD7,	 0,	     P_686|P_SSE2,0)
insa(PMULHUW, pmulhuw,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0xE4,	 0,	     P_586|P_SSE1,0)
insn(PMULHUW, 1,		OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0xE4,	 0,	     P_686|P_SSE2,0)
insa(PMULHW, pmulhw,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0xE5,	 0,	     P_586|P_MMX, 0)
insn(PMULHW, 1,			OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0xE5,	 0,	     P_686|P_SSE2,0)
insa(PMULLW, pmullw,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0xD5,	 0,	     P_586|P_MMX, 0)
insn(PMULLW, 1,			OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0xD5,	 0,	     P_686|P_SSE2,0)
insa(PMULUDQ, pmuludq,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0xF4,	 0,	     P_686|P_SSE2,0)
insn(PMULUDQ, 1,		OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0xF4,	 0,	     P_686|P_SSE2,0)
insa(POR, por,			OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0xEB,	 0,	     P_586|P_MMX, 0)
insn(POR,  1,			OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0xEB,	 0,	     P_686|P_SSE2,0)
insa(PSADBW, psadbw,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0xF6,	 0,	     P_686|P_SSE1,0)
insn(PSADBW, 1,			OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0xF6,	 0,	     P_686|P_SSE2,0)
insa(PSHUFD, pshufd,		OpCls( XMM,	 XMM_M128, I8_U ), F_660F, 1,  no_WDS, 0x70,	 0,	     P_686|P_SSE2,0)
insa(PSHUFW, pshufw,		OpCls( MMX,	 MMX_M64,  I8_U ), F_0F,   1,  no_WDS, 0x70,	 0,	     P_686|P_SSE1,0)
insa(PSHUFHW, pshufhw,		OpCls( XMM,	 XMM_M128, I8_U ), F_F30F, 1,  no_WDS, 0x70,	 0,	     P_686|P_SSE2,0)
insa(PSHUFLW, pshuflw,		OpCls( XMM,	 XMM_M128, I8_U ), F_F20F, 1,  no_WDS, 0x70,	 0,	     P_686|P_SSE2,0)

insa(PSLLW, psllw,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0xF1,	 0,	     P_586|P_MMX, 0)
insn(PSLLW, 1,			OpCls( MMX,	 I8_U,	   NONE ), F_0F,   0,  no_WDS, 0x71,	 0x30,	     P_586|P_MMX, 0)
insn(PSLLW, 2,			OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0xF1,	 0,	     P_686|P_SSE2,0)
insn(PSLLW, 3,			OpCls( XMM,	 I8_U,	   NONE ), F_660F, 0,  no_WDS, 0x71,	 0x30,	     P_686|P_SSE2,0)
insa(PSLLD, pslld,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0xF2,	 0,	     P_586|P_MMX, 0)
insn(PSLLD, 1,			OpCls( MMX,	 I8_U,	   NONE ), F_0F,   0,  no_WDS, 0x72,	 0x30,	     P_586|P_MMX, 0)
insn(PSLLD, 2,			OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0xF2,	 0,	     P_686|P_SSE2,0)
insn(PSLLD, 3,			OpCls( XMM,	 I8_U,	   NONE ), F_660F, 0,  no_WDS, 0x72,	 0x30,	     P_686|P_SSE2,0)
insa(PSLLQ, psllq,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0xF3,	 0,	     P_586|P_MMX, 0)
insn(PSLLQ, 1,			OpCls( MMX,	 I8_U,	   NONE ), F_0F,   0,  no_WDS, 0x73,	 0x30,	     P_586|P_MMX, 0)
insn(PSLLQ, 2,			OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0xF3,	 0,	     P_686|P_SSE2,0)
insn(PSLLQ, 3,			OpCls( XMM,	 I8_U,	   NONE ), F_660F, 0,  no_WDS, 0x73,	 0x30,	     P_686|P_SSE2,0)
insa(PSRAW, psraw,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0xE1,	 0,	     P_586|P_MMX, 0)
insn(PSRAW, 1,			OpCls( MMX,	 I8_U,	   NONE ), F_0F,   0,  no_WDS, 0x71,	 0x20,	     P_586|P_MMX, 0)
insn(PSRAW, 2,			OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0xE1,	 0,	     P_586|P_SSE2,0)
insn(PSRAW, 3,			OpCls( XMM,	 I8_U,	   NONE ), F_660F, 0,  no_WDS, 0x71,	 0x20,	     P_686|P_SSE2,0)
insa(PSRAD, psrad,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0xE2,	 0,	     P_586|P_MMX, 0)
insn(PSRAD, 1,			OpCls( MMX,	 I8_U,	   NONE ), F_0F,   0,  no_WDS, 0x72,	 0x20,	     P_586|P_MMX, 0)
insn(PSRAD, 2,			OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0xE2,	 0,	     P_686|P_SSE2,0)
insn(PSRAD, 3,			OpCls( XMM,	 I8_U,	   NONE ), F_660F, 0,  no_WDS, 0x72,	 0x20,	     P_686|P_SSE2,0)
insa(PSRLW, psrlw,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0xD1,	 0,	     P_586|P_MMX, 0)
insn(PSRLW, 1,			OpCls( MMX,	 I8_U,	   NONE ), F_0F,   0,  no_WDS, 0x71,	 0x10,	     P_586|P_MMX, 0)
insn(PSRLW, 2,			OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0xD1,	 0,	     P_686|P_SSE2,0)
insn(PSRLW, 3,			OpCls( XMM,	 I8_U,	   NONE ), F_660F, 0,  no_WDS, 0x71,	 0x10,	     P_686|P_SSE2,0)
insa(PSRLD, psrld,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0xD2,	 0,	     P_586|P_MMX, 0)
insn(PSRLD, 1,			OpCls( MMX,	 I8_U,	   NONE ), F_0F,   0,  no_WDS, 0x72,	 0x10,	     P_586|P_MMX, 0)
insn(PSRLD, 2,			OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0xD2,	 0,	     P_686|P_SSE2,0)
insn(PSRLD, 3,			OpCls( XMM,	 I8_U,	   NONE ), F_660F, 0,  no_WDS, 0x72,	 0x10,	     P_686|P_SSE2,0)
insa(PSRLQ, psrlq,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0xD3,	 0,	     P_586|P_MMX, 0)
insn(PSRLQ, 1,			OpCls( MMX,	 I8_U,	   NONE ), F_0F,   0,  no_WDS, 0x73,	 0x10,	     P_586|P_MMX, 0)
insn(PSRLQ, 2,			OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0xD3,	 0,	     P_686|P_SSE2,0)
insn(PSRLQ, 3,			OpCls( XMM,	 I8_U,	   NONE ), F_660F, 0,  no_WDS, 0x73,	 0x10,	     P_686|P_SSE2,0)

insa(PSLLDQ, pslldq,		OpCls( XMM,	 I8_U,	   NONE ), F_660F, 0,  no_WDS, 0x73,	 0x38,	     P_686|P_SSE2,0)
insa(PSRLDQ, psrldq,		OpCls( XMM,	 I8_U,	   NONE ), F_660F, 0,  no_WDS, 0x73,	 0x18,	     P_686|P_SSE2,0)

insa(PSUBB, psubb,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0xF8,	 0,	     P_586|P_MMX, 0)
insn(PSUBB, 1,			OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0xF8,	 0,	     P_686|P_SSE2,0)
insa(PSUBW, psubw,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0xF9,	 0,	     P_586|P_MMX, 0)
insn(PSUBW, 1,			OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0xF9,	 0,	     P_686|P_SSE2,0)
insa(PSUBD, psubd,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0xFA,	 0,	     P_586|P_MMX, 0)
insn(PSUBD, 1,			OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0xFA,	 0,	     P_686|P_SSE2,0)
insa(PSUBQ, psubq,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0xFB,	 0,	     P_686|P_SSE2,0)
insn(PSUBQ, 1,			OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0xFB,	 0,	     P_686|P_SSE2,0)
insa(PSUBSB, psubsb,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0xE8,	 0,	     P_586|P_MMX, 0)
insn(PSUBSB, 1,			OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0xE8,	 0,	     P_686|P_SSE2,0)
insa(PSUBSW, psubsw,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0xE9,	 0,	     P_586|P_MMX, 0)
insn(PSUBSW, 1,			OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0xE9,	 0,	     P_686|P_SSE2,0)
insa(PSUBUSB, psubusb,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0xD8,	 0,	     P_586|P_MMX, 0)
insn(PSUBUSB, 1,		OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0xD8,	 0,	     P_686|P_SSE2,0)
insa(PSUBUSW, psubusw,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0xD9,	 0,	     P_586|P_MMX, 0)
insn(PSUBUSW, 1,		OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0xD9,	 0,	     P_686|P_SSE2,0)
insa(PXOR, pxor,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0xEF,	 0,	     P_586|P_MMX, 0)
insn(PXOR, 1,			OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0xEF,	 0,	     P_686|P_SSE2,0)
insa(PUNPCKHBW, punpckhbw, OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0x68,	 0,	     P_586|P_MMX, 0)
insn(PUNPCKHBW, 1,		OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0x68,	 0,	     P_686|P_SSE2,0)
insa(PUNPCKHWD, punpckhwd, OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0x69,	 0,	     P_586|P_MMX, 0)
insn(PUNPCKHWD, 1,		OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0x69,	 0,	     P_686|P_SSE2,0)
insa(PUNPCKHDQ, punpckhdq, OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0x6A,	 0,	     P_586|P_MMX, 0)
insn(PUNPCKHDQ, 1,		OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0x6A,	 0,	     P_686|P_SSE2,0)
insa(PUNPCKLBW, punpcklbw, OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0x60,	 0,	     P_586|P_MMX, 0)
insn(PUNPCKLBW, 1,		OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0x60,	 0,	     P_686|P_SSE2,0)
insa(PUNPCKLWD, punpcklwd, OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0x61,	 0,	     P_586|P_MMX, 0)
insn(PUNPCKLWD, 1,		OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0x61,	 0,	     P_686|P_SSE2,0)
insa(PUNPCKLDQ, punpckldq, OpCls( MMX,	 MMX_M64,  NONE ), F_0F,   1,  no_WDS, 0x62,	 0,	     P_586|P_MMX, 0)
insn(PUNPCKLDQ, 1,		OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0x62,	 0,	     P_686|P_SSE2,0)
insa(PUNPCKHQDQ, punpckhqdq,	OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0x6D,	 0,	     P_686|P_SSE2,0)
insa(PUNPCKLQDQ, punpcklqdq,	OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0x6C,	 0,	     P_686|P_SSE2,0)

insa(RCPPS, rcpps,		OpCls( XMM,	 XMM_M128, NONE ), F_0F,   1,  no_WDS, 0x53,	 0,	     P_686|P_SSE1,0)
insa(RCPSS, rcpss,		OpCls( XMM,	 XMM_M32,  NONE ), F_F30F, 1,  no_WDS, 0x53,	 0,	     P_686|P_SSE1,0)
insa(RSQRTPS, rsqrtps,		OpCls( XMM,	 XMM_M128, NONE ), F_0F,   1,  no_WDS, 0x52,	 0,	     P_686|P_SSE1,0)
insa(RSQRTSS, rsqrtss,		OpCls( XMM,	 XMM_M32,  NONE ), F_F30F, 1,  no_WDS, 0x52,	 0,	     P_686|P_SSE1,0)
insa(SHUFPD, shufpd,		OpCls( XMM,	 XMM_M128, I8_U ), F_660F, 1,  no_WDS, 0xC6,	 0,	     P_686|P_SSE2,0)
insa(SHUFPS, shufps,		OpCls( XMM,	 XMM_M128, I8_U ), F_0F,   1,  no_WDS, 0xC6,	 0,	     P_686|P_SSE1,0)
insa(UCOMISD, ucomisd,		OpCls( XMM,	 XMM_M64,  NONE ), F_660F, 1,  no_WDS, 0x2E,	 0,	     P_686|P_SSE2,0)
insa(UCOMISS, ucomiss,		OpCls( XMM,	 XMM_M32,  NONE ), F_0F,   1,  no_WDS, 0x2E,	 0,	     P_686|P_SSE1,0)
insa(UNPCKHPD, unpckhpd, OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0x15,	 0,	     P_686|P_SSE2,0)
insa(UNPCKHPS, unpckhps, OpCls( XMM,	 XMM_M128, NONE ), F_0F,   1,  no_WDS, 0x15,	 0,	     P_686|P_SSE1,0)
insa(UNPCKLPD, unpcklpd, OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0x14,	 0,	     P_686|P_SSE2,0)
insa(UNPCKLPS, unpcklps, OpCls( XMM,	 XMM_M128, NONE ), F_0F,   1,  no_WDS, 0x14,	 0,	     P_686|P_SSE1,0)

; K3D instructions
insa(FEMMS, femms,		OpCls( NONE,	 NONE,	   NONE ), F_0F,   0,  no_RM,  0x0E,	 0,	     P_586|P_K3D, 0)
insa(PREFETCH, prefetch, OpCls( M_ANY,	 NONE,	   NONE ), F_0F,   0,  no_WDS, 0x0D,	 0,	     P_586|P_K3D, 0)
insa(PREFETCHW, prefetchw, OpCls( M_ANY,	 NONE,	   NONE ), F_0F,   0,  no_WDS, 0x0D,	 0x08,	     P_586|P_K3D, 0)
insa(PAVGUSB, pavgusb,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F0F, 1,  no_WDS, 0xBF,	 0,	     P_586|P_K3D, 0)
insa(PF2ID, pf2id,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F0F, 1,  no_WDS, 0x1D,	 0,	     P_586|P_K3D, 0)
insa(PF2IW, pf2iw,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F0F, 1,  no_WDS, 0x1C,	 0,	     P_586|P_K3D, 0)
insa(PFACC, pfacc,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F0F, 1,  no_WDS, 0xAE,	 0,	     P_586|P_K3D, 0)
insa(PFADD, pfadd,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F0F, 1,  no_WDS, 0x9E,	 0,	     P_586|P_K3D, 0)
insa(PFCMPEQ, pfcmpeq,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F0F, 1,  no_WDS, 0xB0,	 0,	     P_586|P_K3D, 0)
insa(PFCMPGE, pfcmpge,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F0F, 1,  no_WDS, 0x90,	 0,	     P_586|P_K3D, 0)
insa(PFCMPGT, pfcmpgt,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F0F, 1,  no_WDS, 0xA0,	 0,	     P_586|P_K3D, 0)
insa(PFMAX, pfmax,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F0F, 1,  no_WDS, 0xA4,	 0,	     P_586|P_K3D, 0)
insa(PFMIN, pfmin,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F0F, 1,  no_WDS, 0x94,	 0,	     P_586|P_K3D, 0)
insa(PFMUL, pfmul,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F0F, 1,  no_WDS, 0xB4,	 0,	     P_586|P_K3D, 0)
insa(PFNACC, pfnacc,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F0F, 1,  no_WDS, 0x8A,	 0,	     P_586|P_K3D, 0)
insa(PFPNACC, pfpnacc,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F0F, 1,  no_WDS, 0x8E,	 0,	     P_586|P_K3D, 0)
insa(PFRCP, pfrcp,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F0F, 1,  no_WDS, 0x96,	 0,	     P_586|P_K3D, 0)
insa(PFRCPIT1, pfrcpit1, OpCls( MMX,	 MMX_M64,  NONE ), F_0F0F, 1,  no_WDS, 0xA6,	 0,	     P_586|P_K3D, 0)
insa(PFRCPIT2, pfrcpit2, OpCls( MMX,	 MMX_M64,  NONE ), F_0F0F, 1,  no_WDS, 0xB6,	 0,	     P_586|P_K3D, 0)
insa(PFRSQIT1, pfrsqit1, OpCls( MMX,	 MMX_M64,  NONE ), F_0F0F, 1,  no_WDS, 0xA7,	 0,	     P_586|P_K3D, 0)
insa(PFRSQRT, pfrsqrt,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F0F, 1,  no_WDS, 0x97,	 0,	     P_586|P_K3D, 0)
insa(PFSUB, pfsub,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F0F, 1,  no_WDS, 0x9A,	 0,	     P_586|P_K3D, 0)
insa(PFSUBR, pfsubr,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F0F, 1,  no_WDS, 0xAA,	 0,	     P_586|P_K3D, 0)
insa(PI2FD, pi2fd,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F0F, 1,  no_WDS, 0x0D,	 0,	     P_586|P_K3D, 0)
insa(PI2FW, pi2fw,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F0F, 1,  no_WDS, 0x0C,	 0,	     P_586|P_K3D, 0)
insa(PMULHRW, pmulhrw,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F0F, 1,  no_WDS, 0xB7,	 0,	     P_586|P_K3D, 0)
insa(PSWAPD, pswapd,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F0F, 1,  no_WDS, 0xBB,	 0,	     P_586|P_K3D, 0)

insa(ADDSUBPD, addsubpd, OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0xD0,	 0,	     P_686|P_SSE3,0)
insa(ADDSUBPS, addsubps, OpCls( XMM,	 XMM_M128, NONE ), F_F20F, 1,  no_WDS, 0xD0,	 0,	     P_686|P_SSE3,0)
insa(FISTTP, fisttp,		OpCls( M32,	 NONE,	   NONE ), 0,	   0,  no_WDS, 0xDB,	 0x08,	     P_686|P_SSE3,0)
insn(FISTTP, 1,			OpCls( M64,	 NONE,	   NONE ), 0,	   0,  no_WDS, 0xDD,	 0x08,	     P_686|P_SSE3,0)
insn(FISTTP, 2,			OpCls( M16,	 NONE,	   NONE ), 0,	   0,  no_WDS, 0xDF,	 0x08,	     P_686|P_SSE3,0)
insa(HADDPD, haddpd,		OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0x7C,	 0,	     P_686|P_SSE3,0)
insa(HADDPS, haddps,		OpCls( XMM,	 XMM_M128, NONE ), F_F20F, 1,  no_WDS, 0x7C,	 0,	     P_686|P_SSE3,0)
insa(HSUBPD, hsubpd,		OpCls( XMM,	 XMM_M128, NONE ), F_660F, 1,  no_WDS, 0x7D,	 0,	     P_686|P_SSE3,0)
insa(HSUBPS, hsubps,		OpCls( XMM,	 XMM_M128, NONE ), F_F20F, 1,  no_WDS, 0x7D,	 0,	     P_686|P_SSE3,0)
insa(LDDQU, lddqu,		OpCls( XMM,	 M128,	   NONE ), F_F20F, 1,  no_WDS, 0xF0,	 0,	     P_686|P_SSE3,0)
insa(MONITOR, monitor,		OpCls( NONE,	 NONE,	   NONE ), F_0F,   0,  0,      0x01,	 0xC8,	     P_686|P_SSE3,0)
insa(MOVDDUP, movddup,		OpCls( XMM,	 XMM_M64,  NONE ), F_F20F, 1,  no_WDS, 0x12,	 0,	     P_686|P_SSE3,0)
insa(MOVSHDUP, movshdup, OpCls( XMM,	 XMM_M128, NONE ), F_F30F, 1,  no_WDS, 0x16,	 0,	     P_686|P_SSE3,0)
insa(MOVSLDUP, movsldup, OpCls( XMM,	 XMM_M128, NONE ), F_F30F, 1,  no_WDS, 0x12,	 0,	     P_686|P_SSE3,0)
insa(MWAIT, mwait,		OpCls( NONE,	 NONE,	   NONE ), F_0F,   0,  0,      0x01,	 0xC9,	     P_686|P_SSE3,0)

insa(PABSB, pabsb,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F38,  1,	no_WDS, 0x1C,	  0,	      P_686|P_SSSE3, 0)
insn(PABSB, 1,			OpCls( XMM,	 XMM_M128, NONE ), F_660F38,1,	no_WDS, 0x1C,	  0,	      P_686|P_SSSE3, 0)
insa(PABSD, pabsd,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F38,  1,	no_WDS, 0x1E,	  0,	      P_686|P_SSSE3, 0)
insn(PABSD, 1,			OpCls( XMM,	 XMM_M128, NONE ), F_660F38,1,	no_WDS, 0x1E,	  0,	      P_686|P_SSSE3, 0)
insa(PABSW, pabsw,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F38,  1,	no_WDS, 0x1D,	  0,	      P_686|P_SSSE3, 0)
insn(PABSW, 1,			OpCls( XMM,	 XMM_M128, NONE ), F_660F38,1,	no_WDS, 0x1D,	  0,	      P_686|P_SSSE3, 0)
insa(PALIGNR, palignr,		OpCls( MMX,	 MMX_M64,  I8_U ), F_0F3A,  1,	no_WDS, 0x0F,	  0,	      P_686|P_SSSE3, 0)
insn(PALIGNR, 1,		OpCls( XMM,	 XMM_M128, I8_U ), F_660F3A,1,	no_WDS, 0x0F,	  0,	      P_686|P_SSSE3, 0)
insa(PHADDD, phaddd,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F38,  1,	no_WDS, 0x02,	  0,	      P_686|P_SSSE3, 0)
insn(PHADDD, 1,			OpCls( XMM,	 XMM_M128, NONE ), F_660F38,1,	no_WDS, 0x02,	  0,	      P_686|P_SSSE3, 0)
insa(PHADDSW, phaddsw,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F38,  1,	no_WDS, 0x03,	  0,	      P_686|P_SSSE3, 0)
insn(PHADDSW, 1,		OpCls( XMM,	 XMM_M128, NONE ), F_660F38,1,	no_WDS, 0x03,	  0,	      P_686|P_SSSE3, 0)
insa(PHADDW, phaddw,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F38,  1,	no_WDS, 0x01,	  0,	      P_686|P_SSSE3, 0)
insn(PHADDW, 1,			OpCls( XMM,	 XMM_M128, NONE ), F_660F38,1,	no_WDS, 0x01,	  0,	      P_686|P_SSSE3, 0)
insa(PHSUBD, phsubd,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F38,  1,	no_WDS, 0x06,	  0,	      P_686|P_SSSE3, 0)
insn(PHSUBD, 1,			OpCls( XMM,	 XMM_M128, NONE ), F_660F38,1,	no_WDS, 0x06,	  0,	      P_686|P_SSSE3, 0)
insa(PHSUBSW, phsubsw,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F38,  1,	no_WDS, 0x07,	  0,	      P_686|P_SSSE3, 0)
insn(PHSUBSW, 1,		OpCls( XMM,	 XMM_M128, NONE ), F_660F38,1,	no_WDS, 0x07,	  0,	      P_686|P_SSSE3, 0)
insa(PHSUBW, phsubw,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F38,  1,	no_WDS, 0x05,	  0,	      P_686|P_SSSE3, 0)
insn(PHSUBW, 1,			OpCls( XMM,	 XMM_M128, NONE ), F_660F38,1,	no_WDS, 0x05,	  0,	      P_686|P_SSSE3, 0)
insa(PMADDUBSW, pmaddubsw,	OpCls( MMX,	 MMX_M64,  NONE ), F_0F38,  1,	no_WDS, 0x04,	  0,	      P_686|P_SSSE3, 0)
insn(PMADDUBSW, 1,		OpCls( XMM,	 XMM_M128, NONE ), F_660F38,1,	no_WDS, 0x04,	  0,	      P_686|P_SSSE3, 0)
insa(PMULHRSW, pmulhrsw,	OpCls( MMX,	 MMX_M64,  NONE ), F_0F38,  1,	no_WDS, 0x0B,	  0,	      P_686|P_SSSE3, 0)
insn(PMULHRSW, 1,		OpCls( XMM,	 XMM_M128, NONE ), F_660F38,1,	no_WDS, 0x0B,	  0,	      P_686|P_SSSE3, 0)
insa(PSHUFB, pshufb,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F38,  1,	no_WDS, 0,	  0,	      P_686|P_SSSE3, 0)
insn(PSHUFB, 1,			OpCls( XMM,	 XMM_M128, NONE ), F_660F38,1,	no_WDS, 0,	  0,	      P_686|P_SSSE3, 0)
insa(PSIGNB, psignb,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F38,  1,	no_WDS, 0x08,	  0,	      P_686|P_SSSE3, 0)
insn(PSIGNB, 1,			OpCls( XMM,	 XMM_M128, NONE ), F_660F38,1,	no_WDS, 0x08,	  0,	      P_686|P_SSSE3, 0)
insa(PSIGND, psignd,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F38,  1,	no_WDS, 0x0A,	  0,	      P_686|P_SSSE3, 0)
insn(PSIGND, 1,			OpCls( XMM,	 XMM_M128, NONE ), F_660F38,1,	no_WDS, 0x0A,	  0,	      P_686|P_SSSE3, 0)
insa(PSIGNW, psignw,		OpCls( MMX,	 MMX_M64,  NONE ), F_0F38,  1,	no_WDS, 0x09,	  0,	      P_686|P_SSSE3, 0)
insn(PSIGNW, 1,			OpCls( XMM,	 XMM_M128, NONE ), F_660F38,1,	no_WDS, 0x09,	  0,	      P_686|P_SSSE3, 0)
insa(PCLMULQDQ, pclmulqdq,	OpCls( XMM,	 XMM_M128, I8_U ), F_660F3A,1,	no_WDS, 0x44,	  0x00,	      P_686|P_SSSE3, 0)
insa(AESDECLAST, aesdeclast,	OpCls( XMM,	 XMM_M128, NONE ), F_660F38,1,	no_WDS, 0xDF,	  0x00,	      P_686|P_SSSE3, 0)
insa(AESDEC, aesdec,		OpCls( XMM,	 XMM_M128, NONE ), F_660F38,1,	no_WDS, 0xDE,	  0x00,	      P_686|P_SSSE3, 0)
insa(AESENC, aesenc,		OpCls( XMM,	 XMM_M128, NONE ), F_660F38,1,	no_WDS, 0xDC,	  0x00,	      P_686|P_SSSE3, 0)
insa(AESENCLAST, aesenclast,	OpCls( XMM,	 XMM_M128, NONE ), F_660F38,1,	no_WDS, 0xDD,	  0x00,	      P_686|P_SSSE3, 0)
insa(AESIMC, aesimc,		OpCls( XMM,	 XMM_M128, NONE ), F_660F38,1,	no_WDS, 0xDB,	  0x00,	      P_686|P_SSSE3, 0)
insa(AESKEYGENASSIST,aeskeygenassist,OpCls(XMM,	 XMM_M128, I8_U ), F_660F3A,1,	no_WDS, 0xDF,	  0x00,	      P_686|P_SSSE3, 0)
insa(ADCX, adcx,		OpCls( R32,	 R32_M32,  NONE ), F_660F38,1,	no_WDS, 0xF6,	  0x00,	      P_686|P_SSSE3, 0)
insn(ADCX, 1,			OpCls( R64,	 R64_M64,  NONE ), F_660F38,1,	no_WDS, 0xF6,	  0x00,	      P_686|P_SSSE3, 0)

; CDQE must be first in this group, see reswords.c
insx(CDQE, cdqe,		OpCls( NONE,	 NONE,	     NONE ), F_48,   0,	 no_RM,	 0x98,	   0,	   P_64,	   0,	     RWF_X64)
insx(CQO, cqo,			OpCls( NONE,	 NONE,	     NONE ), F_48,   0,	 no_RM,	 0x99,	   0,	   P_64,	   0,	     RWF_X64)
insx(PUSHFQ,pushfq,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0x9C,	   0,	   P_64,	   0,	     RWF_X64)
insx(POPFQ, popfq,		OpCls( NONE,	 NONE,	     NONE ), 0,	     0,	 no_RM,	 0x9D,	   0,	   P_64,	   0,	     RWF_X64)
insx(IRETQ, iretq,		OpCls( NONE,	 NONE,	     NONE ), F_48,   0,	 no_RM,	 0xCF,	   0,	   P_64,	   0,	     RWF_X64)
insx(CMPXCHG16B, cmpxchg16b,	OpCls( M128,	 NONE,	     NONE ), F_480F, 0,	 0,	 0xC7,	   0x08,       P_64,	   AP_LOCK,  RWF_X64)
insx(MOVSXD,movsxd,		OpCls( R64,	 R32_M32,    NONE ), 0,	     1,	 0,	 0x63,	   0,	   P_64,	   0,	     RWF_X64)

insx(CMPSQ, cmpsq,		OpCls( NONE,	 NONE,	     NONE ), F_48,   0,	 no_RM,	 0xA7,	   0,	   P_64,	   AP_REPxx, RWF_X64)
insn(CMPSQ, 1,			OpCls( M64,	 M64,	     NONE ), F_48,   0,	 no_RM,	 0xA7,	   0,	   P_64,	   AP_REPxx)
insx(LODSQ, lodsq,		OpCls( NONE,	 NONE,	     NONE ), F_48,   0,	 no_RM,	 0xAD,	   0,	   P_64,	   AP_REP,   RWF_X64)
insn(LODSQ, 1,			OpCls( M64,	 NONE,	     NONE ), F_48,   0,	 no_RM,	 0xAD,	   0,	   P_64,	   AP_REP  )
insx(MOVSQ, movsq,		OpCls( NONE,	 NONE,	     NONE ), F_48,   0,	 no_RM,	 0xA5,	   0,	   P_64,	   AP_REP,   RWF_X64)
insn(MOVSQ, 1,			OpCls( M64,	 M64,	     NONE ), F_48,   0,	 no_RM,	 0xA5,	   0,	   P_64,	   AP_REP  )
insx(SCASQ, scasq,		OpCls( NONE,	 NONE,	     NONE ), F_48,   0,	 no_RM,	 0xAF,	   0,	   P_64,	   AP_REPxx, RWF_X64)
insn(SCASQ, 1,			OpCls( M64,	 NONE,	     NONE ), F_48,   0,	 no_RM,	 0xAF,	   0,	   P_64,	   AP_REPxx)
insx(STOSQ, stosq,		OpCls( NONE,	 NONE,	     NONE ), F_48,   0,	 no_RM,	 0xAB,	   0,	   P_64,	   AP_REP,   RWF_X64)
insn(STOSQ, 1,			OpCls( M64,	 NONE,	     NONE ), F_48,   0,	 no_RM,	 0xAB,	   0,	   P_64,	   AP_REP  )

; PEXTRQ/PINSRQ need a REX.W prefix if M64 is dst/src!
insx(PEXTRQ, pextrq,		OpCls( R64_M64,	 XMM,	     I8_U ), F_660F3A,0, no_WDS, 0x16,	   0,	   P_64|P_SSE4,0,	     RWF_X64)
insx(PINSRQ, pinsrq,		OpCls( XMM,	 R64_M64,    I8_U ), F_660F3A,1, no_WDS, 0x22,	   0,	   P_64|P_SSE4,0,	     RWF_X64)

insx(SWAPGS, swapgs,		OpCls( NONE,	 NONE,	     NONE ), F_0F,   0,	 0,	 0x01,	   0xF8,       P_64,	   0,	     RWF_X64)
insx(SYSCALL_, syscall,		OpCls( NONE,	 NONE,	     NONE ), F_0F,   0,	 no_RM,	 0x05,	   0,	   P_64,	   0,	     RWF_X64)
insx(SYSRET, sysret,		OpCls( NONE,	 NONE,	     NONE ), F_0F,   0,	 no_RM,	 0x07,	   0,	   P_64,	   0,	     RWF_X64)

; SSE4.1
insa(BLENDPD, blendpd,		OpCls( XMM,	 XMM_M128, I8_U ), F_660F3A, 1,	 no_WDS, 0x0D,	   0,	   P_686|P_SSE4, 0)
insa(BLENDPS, blendps,		OpCls( XMM,	 XMM_M128, I8_U ), F_660F3A, 1,	 no_WDS, 0x0C,	   0,	   P_686|P_SSE4, 0)
insa(BLENDVPD, blendvpd, OpCls( XMM,	 XMM_M128, XMM0 ), F_660F38, 1,	 no_WDS, 0x15,	   0,	   P_686|P_SSE4, 0)
insa(BLENDVPS, blendvps, OpCls( XMM,	 XMM_M128, XMM0 ), F_660F38, 1,	 no_WDS, 0x14,	   0,	   P_686|P_SSE4, 0)
insa(DPPD, dppd,		OpCls( XMM,	 XMM_M128, I8_U ), F_660F3A, 1,	 no_WDS, 0x41,	   0,	   P_686|P_SSE4, 0)
insa(DPPS, dpps,		OpCls( XMM,	 XMM_M128, I8_U ), F_660F3A, 1,	 no_WDS, 0x40,	   0,	   P_686|P_SSE4, 0)
insa(EXTRACTPS, extractps, OpCls( RGT16,	 XMM,	   I8_U ), F_660F3A, 0,	 no_WDS, 0x17,	   0,	   P_686|P_SSE4, 0)
insn(EXTRACTPS, 1,		OpCls( M32,	 XMM,	   I8_U ), F_660F3A, 0,	 no_WDS, 0x17,	   0,	   P_686|P_SSE4, 0)
insa(INSERTPS, insertps, OpCls( XMM,	 XMM_M32,  I8_U ), F_660F3A, 1,	 no_WDS, 0x21,	   0,	   P_686|P_SSE4, 0)
insa(MOVNTDQA, movntdqa, OpCls( XMM,	 M128,	   NONE ), F_660F38, 1,	 no_WDS, 0x2A,	   0,	   P_686|P_SSE4, 0)
insa(MPSADBW, mpsadbw,		OpCls( XMM,	 XMM_M128, I8_U ), F_660F3A, 1,	 no_WDS, 0x42,	   0,	   P_686|P_SSE4, 0)
insa(PACKUSDW, packusdw, OpCls( XMM,	 XMM_M128, NONE ), F_660F38, 1,	 no_WDS, 0x2B,	   0,	   P_686|P_SSE4, 0)
insa(PBLENDVB, pblendvb, OpCls( XMM,	 XMM_M128, XMM0 ), F_660F38, 1,	 no_WDS, 0x10,	   0,	   P_686|P_SSE4, 0)
insa(PBLENDW, pblendw,		OpCls( XMM,	 XMM_M128, I8_U ), F_660F3A, 1,	 no_WDS, 0x0E,	   0,	   P_686|P_SSE4, 0)
insa(PCMPEQQ, pcmpeqq,		OpCls( XMM,	 XMM_M128, NONE ), F_660F38, 1,	 no_WDS, 0x29,	   0,	   P_686|P_SSE4, 0)
insa(PEXTRB, pextrb,		OpCls( RGT16_M08,XMM,	   I8_U ), F_660F3A, 0,	 no_WDS, 0x14,	   0,	   P_686|P_SSE4, 0)
insa(PEXTRD, pextrd,		OpCls( R32_M32,	 XMM,	   I8_U ), F_660F3A, 0,	 no_WDS, 0x16,	   0,	   P_686|P_SSE4, 0)
insa(PHMINPOSUW, phminposuw,	OpCls( XMM,	 XMM_M128, NONE ), F_660F38, 1,	 no_WDS, 0x41,	   0,	   P_686|P_SSE4, 0)
insa(PINSRB, pinsrb,		OpCls( XMM,	 R32_M08,  I8_U ), F_660F3A, 1,	 no_WDS, 0x20,	   0,	   P_686|P_SSE4, 0)
insa(PINSRD, pinsrd,		OpCls( XMM,	 R32_M32,  I8_U ), F_660F3A, 1,	 no_WDS, 0x22,	   0,	   P_686|P_SSE4, 0)
insa(PMAXSB, pmaxsb,		OpCls( XMM,	 XMM_M128, NONE ), F_660F38, 1,	 no_WDS, 0x3C,	   0,	   P_686|P_SSE4, 0)
insa(PMAXSD, pmaxsd,		OpCls( XMM,	 XMM_M128, NONE ), F_660F38, 1,	 no_WDS, 0x3D,	   0,	   P_686|P_SSE4, 0)
insa(PMAXUW, pmaxuw,		OpCls( XMM,	 XMM_M128, NONE ), F_660F38, 1,	 no_WDS, 0x3E,	   0,	   P_686|P_SSE4, 0)
insa(PMAXUD, pmaxud,		OpCls( XMM,	 XMM_M128, NONE ), F_660F38, 1,	 no_WDS, 0x3F,	   0,	   P_686|P_SSE4, 0)
insa(PMINSB, pminsb,		OpCls( XMM,	 XMM_M128, NONE ), F_660F38, 1,	 no_WDS, 0x38,	   0,	   P_686|P_SSE4, 0)
insa(PMINSD, pminsd,		OpCls( XMM,	 XMM_M128, NONE ), F_660F38, 1,	 no_WDS, 0x39,	   0,	   P_686|P_SSE4, 0)
insa(PMINUW, pminuw,		OpCls( XMM,	 XMM_M128, NONE ), F_660F38, 1,	 no_WDS, 0x3A,	   0,	   P_686|P_SSE4, 0)
insa(PMINUD, pminud,		OpCls( XMM,	 XMM_M128, NONE ), F_660F38, 1,	 no_WDS, 0x3B,	   0,	   P_686|P_SSE4, 0)
insa(PMOVSXBW, pmovsxbw, OpCls( XMM,	 XMM_M64,  NONE ), F_660F38, 1,	 no_WDS, 0x20,	   0,	   P_686|P_SSE4, 0)
insa(PMOVSXBD, pmovsxbd, OpCls( XMM,	 XMM_M32,  NONE ), F_660F38, 1,	 no_WDS, 0x21,	   0,	   P_686|P_SSE4, 0)
insa(PMOVSXBQ, pmovsxbq, OpCls( XMM,	 XMM_M16,  NONE ), F_660F38, 1,	 no_WDS, 0x22,	   0,	   P_686|P_SSE4, 0)
insa(PMOVSXWD, pmovsxwd, OpCls( XMM,	 XMM_M64,  NONE ), F_660F38, 1,	 no_WDS, 0x23,	   0,	   P_686|P_SSE4, 0)
insa(PMOVSXWQ, pmovsxwq, OpCls( XMM,	 XMM_M32,  NONE ), F_660F38, 1,	 no_WDS, 0x24,	   0,	   P_686|P_SSE4, 0)
insa(PMOVSXDQ, pmovsxdq, OpCls( XMM,	 XMM_M64,  NONE ), F_660F38, 1,	 no_WDS, 0x25,	   0,	   P_686|P_SSE4, 0)
insa(PMOVZXBW, pmovzxbw, OpCls( XMM,	 XMM_M64,  NONE ), F_660F38, 1,	 no_WDS, 0x30,	   0,	   P_686|P_SSE4, 0)
insa(PMOVZXBD, pmovzxbd, OpCls( XMM,	 XMM_M32,  NONE ), F_660F38, 1,	 no_WDS, 0x31,	   0,	   P_686|P_SSE4, 0)
insa(PMOVZXBQ, pmovzxbq, OpCls( XMM,	 XMM_M16,  NONE ), F_660F38, 1,	 no_WDS, 0x32,	   0,	   P_686|P_SSE4, 0)
insa(PMOVZXWD, pmovzxwd, OpCls( XMM,	 XMM_M64,  NONE ), F_660F38, 1,	 no_WDS, 0x33,	   0,	   P_686|P_SSE4, 0)
insa(PMOVZXWQ, pmovzxwq, OpCls( XMM,	 XMM_M32,  NONE ), F_660F38, 1,	 no_WDS, 0x34,	   0,	   P_686|P_SSE4, 0)
insa(PMOVZXDQ, pmovzxdq, OpCls( XMM,	 XMM_M64,  NONE ), F_660F38, 1,	 no_WDS, 0x35,	   0,	   P_686|P_SSE4, 0)
insa(PMULDQ,   pmuldq,		OpCls( XMM,	 XMM_M128, NONE ), F_660F38, 1,	 no_WDS, 0x28,	   0,	   P_686|P_SSE4, 0)
insa(PMULLD,   pmulld,		OpCls( XMM,	 XMM_M128, NONE ), F_660F38, 1,	 no_WDS, 0x40,	   0,	   P_686|P_SSE4, 0)
insa(PTEST,    ptest,		OpCls( XMM,	 XMM_M128, NONE ), F_660F38, 1,	 no_WDS, 0x17,	   0,	   P_686|P_SSE4, 0)
insa(ROUNDPS, roundps,		OpCls( XMM,	 XMM_M128, I8_U ), F_660F3A, 1,	 no_WDS, 0x08,	   0,	   P_686|P_SSE4, 0)
insa(ROUNDPD, roundpd,		OpCls( XMM,	 XMM_M128, I8_U ), F_660F3A, 1,	 no_WDS, 0x09,	   0,	   P_686|P_SSE4, 0)
insa(ROUNDSS, roundss,		OpCls( XMM,	 XMM_M32 , I8_U ), F_660F3A, 1,	 no_WDS, 0x0A,	   0,	   P_686|P_SSE4, 0)
insa(ROUNDSD, roundsd,		OpCls( XMM,	 XMM_M64 , I8_U ), F_660F3A, 1,	 no_WDS, 0x0B,	   0,	   P_686|P_SSE4, 0)
; SSE4.2
insa(CRC32, crc32,		OpCls( RGT16,	 R8_M08,   NONE ), F_F20F38, 1,	 no_WDS, 0xF0,	   0,	   P_686|P_SSE4, 0)
insn(CRC32, 1,			OpCls( RGT16,	 RGT8_MS,  NONE ), F_F20F38, 1,	 no_WDS, 0xF1,	   0,	   P_686|P_SSE4, 0)
insa(PCMPESTRM, pcmpestrm, OpCls( XMM,	 XMM_M128, I8_U ), F_660F3A, 1,	 no_WDS, 0x60,	   0,	   P_686|P_SSE4, 0)
insa(PCMPESTRI, pcmpestri, OpCls( XMM,	 XMM_M128, I8_U ), F_660F3A, 1,	 no_WDS, 0x61,	   0,	   P_686|P_SSE4, 0)
insa(PCMPISTRM, pcmpistrm, OpCls( XMM,	 XMM_M128, I8_U ), F_660F3A, 1,	 no_WDS, 0x62,	   0,	   P_686|P_SSE4, 0)
insa(PCMPISTRI, pcmpistri, OpCls( XMM,	 XMM_M128, I8_U ), F_660F3A, 1,	 no_WDS, 0x63,	   0,	   P_686|P_SSE4, 0)
insa(PCMPGTQ, pcmpgtq,		OpCls( XMM,	 XMM_M128, NONE ), F_660F38, 1,	 no_WDS, 0x37,	   0,	   P_686|P_SSE4, 0)
insa(POPCNT, popcnt,		OpCls( RGT8,	 RGT8_MS,  NONE ), F_F30F,   1,	 no_WDS ,0xB8,	   0,	   P_686|P_SSE4, 0)
; v2.06: added xrstor, xsave, xgetbv, xsetbv
insa(XRSTOR, xrstor,		OpCls( M_ANY,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0xAE,	   0x28,     P_686|P_SSE4,0)
insa(XSAVE, xsave,		OpCls( M_ANY,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0xAE,	   0x20,     P_686|P_SSE4,0)
insa(XSAVEOPT, xsaveopt, OpCls( M_ANY,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0xAE,	   0x30,     P_686|P_SSE4,0)
insa(XGETBV, xgetbv,		OpCls( NONE,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x01,	   0xD0,     P_686|P_SSE4,0)
insa(XSETBV, xsetbv,		OpCls( NONE,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0x01,	   0xD1,     P_686p|P_SSE4,0)

; v2.09: added
insa(VMCALL,  vmcall,		OpCls( NONE,	 NONE,	     NONE ), F_0F,   0,	 0,	 0x01,	   0xC1,     P_686, 0)
insa(VMLAUNCH,vmlaunch,		OpCls( NONE,	 NONE,	     NONE ), F_0F,   0,	 0,	 0x01,	   0xC2,     P_686p,0)
insa(VMRESUME,vmresume,		OpCls( NONE,	 NONE,	     NONE ), F_0F,   0,	 0,	 0x01,	   0xC3,     P_686p,0)
insa(VMXOFF,  vmxoff,		OpCls( NONE,	 NONE,	     NONE ), F_0F,   0,	 0,	 0x01,	   0xC4,     P_686p,0)
insa(VMPTRLD, vmptrld,		OpCls( M64,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0xC7,	   0x30,     P_686p,0)
insa(VMPTRST, vmptrst,		OpCls( M64,	 NONE,	     NONE ), F_0F,   0,	 no_WDS, 0xC7,	   0x38,     P_686p,0)
insa(VMCLEAR, vmclear,		OpCls( M64,	 NONE,	     NONE ), F_660F, 0,	 no_WDS, 0xC7,	   0x30,     P_686p,0)
insa(VMXON,   vmxon,		OpCls( M64,	 NONE,	     NONE ), F_F30F, 0,	 no_WDS, 0xC7,	   0x30,     P_686p,0)
insa(VMREAD,  vmread,		OpCls( R32_M32,	 R32,	     NONE ), F_0F,   0,	 no_WDS, 0x78,	   0,	 P_686p,0)
insa(VMWRITE, vmwrite,		OpCls( R32,	 R32_M32,    NONE ), F_0F,   1,	 no_WDS, 0x79,	   0,	 P_686p,0)
insa(INVEPT,  invept,		OpCls( RGT16,	 M128,	     NONE ), F_660F38,1, no_WDS, 0x80,	   0,	 P_686p,0)
insa(INVVPID, invvpid,		OpCls( RGT16,	 M128,	     NONE ), F_660F38,1, no_WDS, 0x81,	   0,	 P_686p,0)

; VBROADCASTSS is first VEX encoded instruction (VEX_START in parser.h).
; Important: currently vex_flags[] in reswords.c must match the order here!
; (this is to be improved).
; Most AVX instructions that also have a "legacy" encoding are not listed
; here but are contained in instravx.h!. Exceptions:
; - VBLENDVPD, VBLENDVPS, VPBLENDVB ( they use a different opcode in VEX )
; - VCVT[T]PD* ( they expect a mix of xmm and ymm/m256 arguments )

insx(VBROADCASTSS, vbroadcastss,       OpCls( XMM,	M32,	    NONE ), F_660F38,1,	 no_WDS, 0x18,	   0,	 P_686|P_AVX, 0, RWF_VEX )
insn(VBROADCASTSS, 1,		       OpCls( YMM,	M32,	    NONE ), F_660F38,1,	 no_WDS, 0x18,	   0,	 P_686|P_AVX, 0)
insx(VBROADCASTSD, vbroadcastsd,       OpCls( YMM,	M64,	    NONE ), F_660F38,1,	 no_WDS, 0x19,	   0,	 P_686|P_AVX, 0, RWF_VEX )
insx(VBROADCASTF128, vbroadcastf128,   OpCls( YMM,	M128,	    NONE ), F_660F38,1,	 no_WDS, 0x1A,	   0,	 P_686|P_AVX, 0, RWF_VEX )
insx(VBLENDVPD, vblendvpd,	       OpCls( XMM,	XMM_M128,   XMM	 ), F_660F3A,1,	 no_WDS, 0x4B,	   0,	 P_686|P_AVX, 0, RWF_VEX )
insx(VBLENDVPS, vblendvps,	       OpCls( XMM,	XMM_M128,   XMM	 ), F_660F3A,1,	 no_WDS, 0x4A,	   0,	 P_686|P_AVX, 0, RWF_VEX )
insx(VINSERTF128, vinsertf128,	       OpCls( YMM,	XMM_M128,   I8_U ), F_660F3A,1,	 no_WDS, 0x18,	   0,	 P_686|P_AVX, 0, RWF_VEX )
insx(VEXTRACTF128, vextractf128,       OpCls( XMM,	YMM,	    I8_U ), F_660F3A,0,	 no_WDS, 0x19,	   0,	 P_686|P_AVX, 0, RWF_VEX )
insn(VEXTRACTF128, 1,		       OpCls( M128,	YMM,	    I8_U ), F_660F3A,0,	 no_WDS, 0x19,	   0,	 P_686|P_AVX, 0)
insx(VMASKMOVPS, vmaskmovps,	       OpCls( XMM,	XMM_M128,   NONE ), F_660F38,1,	 no_WDS, 0x2C,	   0,	 P_686|P_AVX, 0, RWF_VEX )
insn(VMASKMOVPS, 1,		       OpCls( M128,	XMM,	    NONE ), F_660F38,0,	 no_WDS, 0x2E,	   0,	 P_686|P_AVX, 0)
insx(VMASKMOVPD, vmaskmovpd,	       OpCls( XMM,	XMM_M128,   NONE ), F_660F38,1,	 no_WDS, 0x2D,	   0,	 P_686|P_AVX, 0, RWF_VEX )
insn(VMASKMOVPD, 1,		       OpCls( M128,	XMM,	    NONE ), F_660F38,0,	 no_WDS, 0x2F,	   0,	 P_686|P_AVX, 0)
insx(VPBLENDVB, vpblendvb,	       OpCls( XMM,	XMM_M128,   XMM	 ), F_660F3A,1,	 no_WDS, 0x4C,	   0,	 P_686|P_AVX, 0, RWF_VEX )
insx(VPERMILPD, vpermilpd,	       OpCls( XMM,	XMM_M128,   NONE ), F_660F38,1,	 no_WDS, 0x0D,	   0,	 P_686|P_AVX, 0, RWF_VEX )
; bug v2.17 vpermilpd: Selection by immediate byte operand: C4 RXB.00011 0.1111.1.01 05 /r ib
insn(VPERMILPD, 1,		       OpCls( XMM,	XMM_M128,   I8_U ), F_660F3A,1,	 no_WDS, 0x05,	   0x00,     P_686|P_AVX, 0)
insx(VPERMILPS, vpermilps,	       OpCls( XMM,	XMM_M128,   NONE ), F_660F38,1,	 no_WDS, 0x0C,	   0x00,     P_686|P_AVX, 0, RWF_VEX )
; bug v2.17 vpermilps: Selection by immediate byte operand: C4 RXB.00011 0.1111.1.01 04 /r ib */
insn(VPERMILPS, 1,		       OpCls( XMM,	XMM_M128,   I8_U ), F_660F3A,1,	 no_WDS, 0x04,	   0x00,     P_686|P_AVX, 0)
; the VPERMIL2xx instructions were dropped
insx(VPERM2F128, vperm2f128,	       OpCls( YMM,	YMM_M256,   I8_U ), F_660F3A,1,	 no_WDS, 0x06,	   0,	 P_686|P_AVX, 0, RWF_VEX )
insx(VTESTPS, vtestps,		       OpCls( XMM,	XMM_M128,   NONE ), F_660F38,1,	 no_WDS, 0x0E,	   0,	 P_686|P_AVX, 0, RWF_VEX )
insx(VTESTPD, vtestpd,		       OpCls( XMM,	XMM_M128,   NONE ), F_660F38,1,	 no_WDS, 0x0F,	   0,	 P_686|P_AVX, 0, RWF_VEX )
insx(VZEROALL, vzeroall,	       OpCls( NONE,	NONE,	    NONE ), F_0F,    0,	 no_RM,	 0x77,	   0,	 P_686|P_AVX, 0, RWF_VEX )
insx(VZEROUPPER, vzeroupper,	       OpCls( NONE,	NONE,	    NONE ), F_0F,    0,	 no_RM,	 0x77,	   0,	 P_686|P_AVX, 0, RWF_VEX )
insx(VCVTPD2DQ, vcvtpd2dq,	       OpCls( XMM,	XMM_M128,   NONE ), F_F20F,  1,	 no_WDS, 0xE6,	   0,	 P_686|P_AVX, 0, RWF_VEX )
insn(VCVTPD2DQ, 1,		       OpCls( XMM,	YMM_M256,   NONE ), F_F20F,  1,	 no_WDS, 0xE6,	   0,	 P_686|P_AVX, 0)
insx(VCVTTPD2DQ, vcvttpd2dq,	       OpCls( XMM,	XMM_M128,   NONE ), F_660F,  1,	 no_WDS, 0xE6,	   0,	 P_686|P_AVX, 0, RWF_VEX )
insn(VCVTTPD2DQ, 1,		       OpCls( XMM,	YMM_M256,   NONE ), F_660F,  1,	 no_WDS, 0xE6,	   0,	 P_686|P_AVX, 0)
insx(VCVTPD2PS, vcvtpd2ps,	       OpCls( XMM,	XMM_M128,   NONE ), F_660F,  1,	 no_WDS, 0x5A,	   0,	 P_686|P_AVX, 0, RWF_VEX )
insn(VCVTPD2PS, 1,		       OpCls( XMM,	YMM_M256,   NONE ), F_660F,  1,	 no_WDS, 0x5A,	   0,	 P_686|P_AVX, 0)
insx(VMOVDDUP, vmovddup,	       OpCls( XMM,	XMM_M64,    NONE ), F_F20F,  1,	 no_WDS, 0x12,	   0,	 P_686|P_AVX, 0, RWF_VEX )
insn(VMOVDDUP, 1,		       OpCls( YMM,	YMM_M256,   NONE ), F_F20F,  1,	 no_WDS, 0x12,	   0,	 P_686|P_AVX, 0)
; v2.11: added here, removed in instravx.h
insx(VMOVMSKPD, vmovmskpd,	       OpCls( RGT16,	XMM,	    NONE ), F_660F,  1,	 no_WDS, 0x50,	   0,	 P_686|P_AVX, 0, RWF_VEX )
insn(VMOVMSKPD, 1,		       OpCls( RGT16,	YMM,	    NONE ), F_660F,  1,	 no_WDS, 0x50,	   0,	 P_686|P_AVX, 0)
insx(VMOVMSKPS, vmovmskps,	       OpCls( RGT16,	XMM,	    NONE ), F_0F,    1,	 no_WDS, 0x50,	   0,	 P_686|P_AVX, 0, RWF_VEX )
insn(VMOVMSKPS, 1,		       OpCls( RGT16,	YMM,	    NONE ), F_0F,    1,	 no_WDS, 0x50,	   0,	 P_686|P_AVX, 0)
; AVX2 - v2.26
insx(VPMASKMOVD, vpmaskmovd, OpCls( XMM, XMM,	 XMM_M128 ), F_660F38,1, no_WDS, 0x8C, 0x00, P_686|P_AVX, 0, RWF_VEX )
insn(VPMASKMOVD, 1,	     OpCls( XMM_M128, XMM,   NONE ), F_660F38,0, no_WDS, 0x8E, 0x00, P_686|P_AVX, 0)
insx(VPMASKMOVQ, vpmaskmovq, OpCls( XMM, XMM,	 XMM_M128 ), F_660F38,1, no_WDS, 0x8E, 0x00, P_686|P_AVX, 0, RWF_VEX )
insn(VPMASKMOVQ, 1,	     OpCls( XMM_M128, XMM,   NONE ), F_660F38,0, no_WDS, 0x8E, 0x00, P_686|P_AVX, 0)
insx(VPERMPD, vpermpd,	     OpCls( XMM, XMM_M128,   NONE ), F_660F38,1, no_WDS, 0x16, 0x00, P_686|P_AVX, 0, RWF_VEX )
insn(VPERMPD, 1,	     OpCls( YMM, YMM_M256,   I8_U ), F_660F3A,1, no_WDS, 0x01, 0x00, P_686|P_AVX, 0)
insx(VPERMB,  vpermb,	     OpCls( XMM, XMM_M128,   NONE ), F_660F38,1, no_WDS, 0x8D, 0x00, P_686|P_AVX, 0, RWF_VEX )
insx(VPERMD,  vpermd,	     OpCls( XMM, XMM_M128,   NONE ), F_660F38,1, no_WDS, 0x36, 0x00, P_686|P_AVX, 0, RWF_VEX )
insx(VPERMQ,  vpermq,	     OpCls( XMM, XMM_M128,   NONE ), F_660F38,1, no_WDS, 0x36, 0x00, P_686|P_AVX, 0, RWF_VEX )
insn(VPERMQ,  1,	     OpCls( YMM, YMM_M256,   I8_U ), F_660F3A,1, no_WDS, 0x00, 0x00, P_686|P_AVX, 0)
insx(VPERMPS, vpermps,	     OpCls( XMM, XMM_M128,   NONE ), F_660F38,1, no_WDS, 0x16, 0x00, P_686|P_AVX, 0, RWF_VEX )
insx(VPSLLVW, vpsllvw,	     OpCls( XMM, XMM_M128,   NONE ), F_660F38,1, no_WDS, 0x12, 0x00, P_686|P_AVX, 0, RWF_VEX )
insx(VPSLLVD, vpsllvd,	     OpCls( XMM, XMM_M128,   NONE ), F_660F38,1, no_WDS, 0x47, 0x00, P_686|P_AVX, 0, RWF_VEX )
insx(VPSLLVQ, vpsllvq,	     OpCls( XMM, XMM_M128,   NONE ), F_660F38,1, no_WDS, 0x47, 0x00, P_686|P_AVX, 0, RWF_VEX )
insx(VPSRAVD, vpsravd,	     OpCls( XMM, XMM_M128,   NONE ), F_660F38,1, no_WDS, 0x46, 0x00, P_686|P_AVX, 0, RWF_VEX )
insx(VPSRLVD, vpsrlvd,	     OpCls( XMM, XMM_M128,   NONE ), F_660F38,1, no_WDS, 0x45, 0x00, P_686|P_AVX, 0, RWF_VEX )
insx(VPSRLVQ, vpsrlvq,	     OpCls( XMM, XMM_M128,   NONE ), F_660F38,1, no_WDS, 0x45, 0x00, P_686|P_AVX, 0, RWF_VEX )
insx(VPBLENDD, vpblendd,     OpCls( XMM, XMM_M128,   I8_U ), F_660F3A,1, no_WDS, 0x02, 0x00, P_686|P_AVX, 0, RWF_VEX )
insx(VPERM2I128, vperm2i128, OpCls( YMM, YMM_M256,   I8_U ), F_660F3A,1, no_WDS, 0x46, 0x00, P_686|P_AVX, 0, RWF_VEX )
insx(VINSERTI128,vinserti128,OpCls( XMM, XMM_M128,   I8_U ), F_660F3A,1, no_WDS, 0x38, 0x00, P_686|P_AVX, 0, RWF_VEX )
insx(VBROADCASTI128,vbroadcasti128,OpCls( YMM, M128, NONE ), F_660F38,1, no_WDS, 0x5A, 0x00, P_686|P_AVX, 0, RWF_VEX )
insx(VEXTRACTI128, vextracti128,OpCls( XMM,  YMM,    I8_U ), F_660F3A,0, no_WDS, 0x39, 0x00, P_686|P_AVX, 0, RWF_VEX )
insn(VEXTRACTI128, 1,		OpCls( M128, YMM,    I8_U ), F_660F3A,0, no_WDS, 0x39, 0x00, P_686|P_AVX, 0)
insx(VPBROADCASTQ, vpbroadcastq,OpCls( XMM, R64,     NONE ), F_660F38,1, no_WDS, 0x7C, 0x00, P_686|P_AVX, 0, RWF_VEX )
insn(VPBROADCASTQ, 1,		OpCls( XMM, XMM_M64, NONE ), F_660F38,1, no_WDS, 0x59, 0x00, P_686|P_AVX, 0)
insx(VPBROADCASTD, vpbroadcastd,OpCls( XMM, R32,     NONE ), F_660F38,1, no_WDS, 0x7C, 0x00, P_686|P_AVX, 0, RWF_VEX )
insn(VPBROADCASTD, 1,		OpCls( XMM, XMM_M32, NONE ), F_660F38,1, no_WDS, 0x58, 0x00, P_686|P_AVX, 0)
insx(VPBROADCASTW, vpbroadcastw,OpCls( XMM, R16,     NONE ), F_660F38,1, no_WDS, 0x7B, 0x00, P_686|P_AVX, 0, RWF_VEX )
insn(VPBROADCASTW, 1,		OpCls( XMM, XMM_M16, NONE ), F_660F38,1, no_WDS, 0x79, 0x00, P_686|P_AVX, 0)
insx(VPBROADCASTB, vpbroadcastb,OpCls( XMM, R8,	     NONE ), F_660F38,1, no_WDS, 0x7A, 0x00, P_686|P_AVX, 0, RWF_VEX )
insn(VPBROADCASTB, 1,		OpCls( XMM, XMM_M08, NONE ), F_660F38,1, no_WDS, 0x78, 0x00, P_686|P_AVX, 0)

; AVX512
insx(VPERMW,  vpermw,	     OpCls( XMM, XMM_M128,   NONE ), F_660F38,1, no_WDS, 0x8D, 0x00, P_686|P_AVX, 0, RWF_VEX )
insx(VPSRAVW, vpsravw,	     OpCls( XMM, XMM_M128,   NONE ), F_660F38,1, no_WDS, 0x11, 0x00, P_686|P_AVX, 0, RWF_VEX )
insx(VPSRAVQ, vpsravq,	     OpCls( XMM, XMM_M128,   NONE ), F_660F38,1, no_WDS, 0x46, 0x00, P_686|P_AVX, 0, RWF_VEX )
insx(VPSRLVW, vpsrlvw,	     OpCls( XMM, XMM_M128,   NONE ), F_660F38,1, no_WDS, 0x10, 0x00, P_686|P_AVX, 0, RWF_VEX )
insx(VPANDD,  vpandd,	     OpCls( XMM, XMM_M128,   NONE ), F_660F,  1, no_WDS, 0xDB, 0x00, P_686|P_AVX, 0, RWF_VEX | RWF_EVEX )
insx(VPANDQ,  vpandq,	     OpCls( XMM, XMM_M128,   NONE ), F_660F,  1, no_WDS, 0xDB, 0x00, P_686|P_AVX, 0, RWF_VEX | RWF_EVEX )
insx(VPANDND, vpandnd,	     OpCls( XMM, XMM_M128,   NONE ), F_660F,  1, no_WDS, 0xDF, 0x00, P_686|P_SSE2,0, RWF_VEX | RWF_EVEX )
insx(VPANDNQ, vpandnq,	     OpCls( XMM, XMM_M128,   NONE ), F_660F,  1, no_WDS, 0xDF, 0x00, P_686|P_SSE2,0, RWF_VEX | RWF_EVEX )
insx(VPXORD,  vpxord,	     OpCls( XMM, XMM_M128,   NONE ), F_660F,  1, no_WDS, 0xEF, 0x00, P_686|P_AVX, 0, RWF_VEX | RWF_EVEX )
insx(VPXORQ,  vpxorq,	     OpCls( XMM, XMM_M128,   NONE ), F_660F,  1, no_WDS, 0xEF, 0x00, P_686|P_AVX, 0, RWF_VEX | RWF_EVEX )
insx(VPSRAQ,  vpsraq,	     OpCls( XMM, I8_U,	     NONE ), F_660F,  0, no_WDS, 0x72, 0x20, P_686|P_AVX, 0, RWF_VEX | RWF_EVEX )
insx(VPCONFLICTD, vpconflictd, OpCls( XMM, XMM_M32,  NONE ), F_660F38,1, no_WDS, 0xC4, 0x00, P_686|P_AVX, 0, RWF_VEX | RWF_EVEX )
insx(VPCONFLICTQ, vpconflictq, OpCls( XMM, XMM_M64,  NONE ), F_660F38,1, no_WDS, 0xC4, 0x00, P_686|P_AVX, 0, RWF_VEX | RWF_EVEX )
insx(VPLZCNTD, vplzcntd,     OpCls( XMM, XMM_M32,    NONE ), F_660F38,1, no_WDS, 0x44, 0x00, P_686|P_AVX, 0, RWF_VEX | RWF_EVEX )
insx(VPLZCNTQ, vplzcntq,     OpCls( XMM, XMM_M64,    NONE ), F_660F38,1, no_WDS, 0x44, 0x00, P_686|P_AVX, 0, RWF_VEX | RWF_EVEX )
insx(VPTESTNMB, vptestnmb,   OpCls( XMM, XMM_M128,   NONE ), F_F30F38,1, no_WDS, 0x26, 0x00, P_686|P_AVX, 0, RWF_VEX | RWF_EVEX )
insx(VPTESTNMW, vptestnmw,   OpCls( XMM, XMM_M128,   NONE ), F_F30F38,1, no_WDS, 0x26, 0x00, P_686|P_AVX, 0, RWF_VEX | RWF_EVEX )
insx(VPTESTNMD, vptestnmd,   OpCls( K,	 XMM_M128,   NONE ), F_F30F38,1, no_WDS, 0x27, 0x00, P_686|P_AVX, 0, RWF_VEX | RWF_EVEX )
insx(VPTESTNMQ, vptestnmq,   OpCls( XMM, XMM_M128,   NONE ), F_F30F38,1, no_WDS, 0x27, 0x00, P_686|P_AVX, 0, RWF_VEX | RWF_EVEX )
insx(VPBROADCASTMW2D, vpbroadcastmw2d, OpCls( XMM, K,NONE ), F_F30F38,1, no_WDS, 0x3A, 0x00, P_686|P_AVX, 0, RWF_VEX | RWF_EVEX )
insx(VPBROADCASTMB2Q, vpbroadcastmb2q, OpCls( XMM, K,NONE ), F_F30F38,1, no_WDS, 0x2A, 0x00, P_686|P_AVX, 0, RWF_VEX | RWF_EVEX )

insx(KADDB,	kaddb,	     OpCls( K,	      K,	  K    ), F_660F,   1, no_WDS, 0x4A, 0x00, P_686|P_AVX, 1, RWF_VEX)
insx(KADDW,	kaddw,	     OpCls( K,	      K,	  K    ), F_0F,	    1, no_WDS, 0x4A, 0x00, P_686|P_AVX, 0, RWF_VEX)
insx(KANDB,	kandb,	     OpCls( K,	      K,	  K    ), F_660F,   1, no_WDS, 0x41, 0x00, P_686|P_AVX, 1, RWF_VEX)
insx(KANDW,	kandw,	     OpCls( K,	      K,	  K    ), F_0F,	    1, no_WDS, 0x41, 0x00, P_686|P_AVX, 0, RWF_VEX)
insx(KANDNB,	kandnb,	     OpCls( K,	      K,	  K    ), F_660F,   1, no_WDS, 0x42, 0x00, P_686|P_AVX, 1, RWF_VEX)
insx(KANDNW,	kandnw,	     OpCls( K,	      K,	  K    ), F_0F,	    1, no_WDS, 0x42, 0x00, P_686|P_AVX, 0, RWF_VEX)
insx(KORB,	korb,	     OpCls( K,	      K,	  K    ), F_660F,   1, no_WDS, 0x45, 0x00, P_686|P_AVX, 1, RWF_VEX)
insx(KORW,	korw,	     OpCls( K,	      K,	  K    ), F_0F,	    1, no_WDS, 0x45, 0x00, P_686|P_AVX, 0, RWF_VEX)
insx(KXORB,	kxorb,	     OpCls( K,	      K,	  K    ), F_660F,   1, no_WDS, 0x47, 0x00, P_686|P_AVX, 1, RWF_VEX)
insx(KXORW,	kxorw,	     OpCls( K,	      K,	  K    ), F_0F,	    1, no_WDS, 0x47, 0x00, P_686|P_AVX, 0, RWF_VEX)
insx(KXNORB,	kxnorb,	     OpCls( K,	      K,	  K    ), F_660F,   1, no_WDS, 0x46, 0x00, P_686|P_AVX, 1, RWF_VEX)
insx(KXNORW,	kxnorw,	     OpCls( K,	      K,	  K    ), F_0F,	    1, no_WDS, 0x46, 0x00, P_686|P_AVX, 0, RWF_VEX)
insx(KUNPCKBW,	kunpckbw,    OpCls( K,	      K,	  K    ), F_660F,   1, no_WDS, 0x4B, 0x00, P_686|P_AVX, 0, RWF_VEX)
insx(KUNPCKWD,	kunpckwd,    OpCls( K,	      K,	  K    ), F_0F,	    1, no_WDS, 0x4B, 0x00, P_686|P_AVX, 1, RWF_VEX)
insx(KADDD,	kaddd,	     OpCls( K,	      K,	  K    ), F_660F,   1, 0,      0x4A, 0x00, P_686|P_AVX, 2, RWF_VEX)
insx(KADDQ,	kaddq,	     OpCls( K,	      K,	  K    ), F_0F,	    1, 0,      0x4A, 0x00, P_686|P_AVX, 2, RWF_VEX)
insx(KANDD,	kandd,	     OpCls( K,	      K,	  K    ), F_660F,   1, 0,      0x41, 0x00, P_686|P_AVX, 2, RWF_VEX)
insx(KANDQ,	kandq,	     OpCls( K,	      K,	  K    ), F_0F,	    1, 0,      0x41, 0x00, P_686|P_AVX, 2, RWF_VEX)
insx(KANDND,	kandnd,	     OpCls( K,	      K,	  K    ), F_660F,   1, 0,      0x42, 0x00, P_686|P_AVX, 2, RWF_VEX)
insx(KANDNQ,	kandnq,	     OpCls( K,	      K,	  K    ), F_0F,	    1, 0,      0x42, 0x00, P_686|P_AVX, 2, RWF_VEX)
insx(KORD,	kord,	     OpCls( K,	      K,	  K    ), F_660F,   1, 0,      0x45, 0x00, P_686|P_AVX, 2, RWF_VEX)
insx(KORQ,	korq,	     OpCls( K,	      K,	  K    ), F_0F,	    1, 0,      0x45, 0x00, P_686|P_AVX, 2, RWF_VEX)
insx(KXORD,	kxord,	     OpCls( K,	      K,	  K    ), F_660F,   1, 0,      0x47, 0x00, P_686|P_AVX, 2, RWF_VEX)
insx(KXORQ,	kxorq,	     OpCls( K,	      K,	  K    ), F_0F,	    1, 0,      0x47, 0x00, P_686|P_AVX, 2, RWF_VEX)
insx(KXNORD,	kxnord,	     OpCls( K,	      K,	  K    ), F_660F,   1, 0,      0x46, 0x00, P_686|P_AVX, 2, RWF_VEX)
insx(KXNORQ,	kxnorq,	     OpCls( K,	      K,	  K    ), F_0F,	    1, 0,      0x46, 0x00, P_686|P_AVX, 2, RWF_VEX)
insx(KUNPCKDQ,	kunpckdq,    OpCls( K,	      K,	  K    ), F_0F,	    1, 0,      0x4B, 0x00, P_686|P_AVX, 2, RWF_VEX)
insx(KNOTB,	knotb,	     OpCls( K,	      K,	  NONE ), F_660F,   1, no_WDS, 0x44, 0x00, P_686|P_AVX, 1, RWF_VEX)
insx(KNOTW,	knotw,	     OpCls( K,	      K,	  NONE ), F_0F,	    1, no_WDS, 0x44, 0x00, P_686|P_AVX, 0, RWF_VEX)
insx(KNOTD,	knotd,	     OpCls( K,	      K,	  NONE ), F_660F,   1, 0,      0x44, 0x00, P_686|P_AVX, 2, RWF_VEX)
insx(KNOTQ,	knotq,	     OpCls( K,	      K,	  NONE ), F_0F,	    1, 0,      0x44, 0x00, P_686|P_AVX, 2, RWF_VEX)
insx(KORTESTB,	kortestb,    OpCls( K,	      K,	  NONE ), F_660F,   1, no_WDS, 0x98, 0x00, P_686|P_AVX, 1, RWF_VEX)
insx(KORTESTW,	kortestw,    OpCls( K,	      K,	  NONE ), F_0F,	    1, no_WDS, 0x98, 0x00, P_686|P_AVX, 0, RWF_VEX)
insx(KORTESTD,	kortestd,    OpCls( K,	      K,	  NONE ), F_660F,   1, 0,      0x98, 0x00, P_686|P_AVX, 2, RWF_VEX)
insx(KORTESTQ,	kortestq,    OpCls( K,	      K,	  NONE ), F_0F,	    1, 0,      0x98, 0x00, P_686|P_AVX, 2, RWF_VEX)
insx(KSHIFTLB,	kshiftlb,    OpCls( K,	      K,	  I8_U ), F_660F3A, 1, 0,      0x32, 0x00, P_686|P_AVX, 1, RWF_VEX)
insx(KSHIFTLW,	kshiftlw,    OpCls( K,	      K,	  I8_U ), F_660F3A, 1, 0,      0x32, 0x00, P_686|P_AVX, 1, RWF_VEX)
insx(KSHIFTLD,	kshiftld,    OpCls( K,	      K,	  I8_U ), F_660F3A, 1, 0,      0x33, 0x00, P_686|P_AVX, 1, RWF_VEX)
insx(KSHIFTLQ,	kshiftlq,    OpCls( K,	      K,	  I8_U ), F_660F3A, 1, 0,      0x33, 0x00, P_686|P_AVX, 1, RWF_VEX)
insx(KSHIFTRB,	kshiftrb,    OpCls( K,	      K,	  I8_U ), F_660F3A, 1, 0,      0x30, 0x00, P_686|P_AVX, 1, RWF_VEX)
insx(KSHIFTRW,	kshiftrw,    OpCls( K,	      K,	  I8_U ), F_660F3A, 1, 0,      0x30, 0x00, P_686|P_AVX, 1, RWF_VEX)
insx(KSHIFTRD,	kshiftrd,    OpCls( K,	      K,	  I8_U ), F_660F3A, 1, 0,      0x31, 0x00, P_686|P_AVX, 1, RWF_VEX)
insx(KSHIFTRQ,	kshiftrq,    OpCls( K,	      K,	  I8_U ), F_660F3A, 1, 0,      0x31, 0x00, P_686|P_AVX, 1, RWF_VEX)

insx(KMOVB,  kmovb,	     OpCls( K,	      K,	  NONE ), F_660F,   1, no_WDS, 0x90, 0x00, P_686|P_AVX, 0, RWF_VEX)
insn(KMOVB,	 1,	     OpCls( K,	      M08,	  NONE ), F_660F,   1, no_WDS, 0x90, 0x00, P_686|P_AVX, 0)
insn(KMOVB,	 2,	     OpCls( M08,      K,	  NONE ), F_660F,   0, no_WDS, 0x91, 0x00, P_686|P_AVX, 0)
insn(KMOVB,	 3,	     OpCls( K,	      R32,	  NONE ), F_660F,   1, no_WDS, 0x92, 0x00, P_686|P_AVX, 0)
insn(KMOVB,	 4,	     OpCls( R32,      K,	  NONE ), F_660F,   1, no_WDS, 0x93, 0x00, P_686|P_AVX, 0)
insx(KMOVD,  kmovd,	     OpCls( K,	      K,	  NONE ), F_660F,   1, 0,      0x90, 0x00, P_686|P_AVX, 0, RWF_VEX)
insn(KMOVD,	 1,	     OpCls( K,	      M32,	  NONE ), F_660F,   1, 0,      0x90, 0x00, P_686|P_AVX, 0)
insn(KMOVD,	 2,	     OpCls( M32,      K,	  NONE ), F_660F,   0, 0,      0x91, 0x00, P_686|P_AVX, 0)
insn(KMOVD,	 3,	     OpCls( K,	      R32,	  NONE ), F_F20F,   1, no_WDS, 0x92, 0x00, P_686|P_AVX, 0)
insn(KMOVD,	 4,	     OpCls( R32,      K,	  NONE ), F_F20F,   1, no_WDS, 0x93, 0x00, P_686|P_AVX, 0)
insx(KMOVQ,  kmovq,	     OpCls( K,	      K,	  NONE ), F_0F,	    1, 0,      0x90, 0x00, P_686|P_AVX, 0, RWF_VEX)
insn(KMOVQ,	 1,	     OpCls( K,	      M64,	  NONE ), F_0F,	    1, 0,      0x90, 0x00, P_686|P_AVX, 0)
insn(KMOVQ,	 2,	     OpCls( M64,      K,	  NONE ), F_0F,	    0, 0,      0x91, 0x00, P_686|P_AVX, 0)
insn(KMOVQ,	 3,	     OpCls( K,	      R64,	  NONE ), F_F20F,   1, no_WDS, 0x92, 0x00, P_686|P_AVX, 0)
insn(KMOVQ,	 4,	     OpCls( R64,      K,	  NONE ), F_F20F,   1, no_WDS, 0x93, 0x00, P_686|P_AVX, 0)
insx(KMOVW,  kmovw,	     OpCls( K,	      K,	  NONE ), F_0F,	    1, 0,      0x90, 0x00, P_686|P_AVX, 0, RWF_VEX)
insn(KMOVW,	 1,	     OpCls( K,	      M16,	  NONE ), F_0F,	    1, 0,      0x90, 0x00, P_686|P_AVX, 0)
insn(KMOVW,	 2,	     OpCls( M16,      K,	  NONE ), F_0F,	    0, 0,      0x91, 0x00, P_686|P_AVX, 0)
insn(KMOVW,	 3,	     OpCls( K,	      R32,	  NONE ), F_0F,	    1, 0,      0x92, 0x00, P_686|P_AVX, 0)
insn(KMOVW,	 4,	     OpCls( R32,      K,	  NONE ), F_0F,	    1, 0,      0x93, 0x00, P_686|P_AVX, 0)

