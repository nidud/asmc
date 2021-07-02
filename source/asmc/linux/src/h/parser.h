/****************************************************************************
*
*			     Open Watcom Project
*
*    Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
*
*  ========================================================================
*
*    This file contains Original Code and/or Modifications of Original
*    Code as defined in and that are subject to the Sybase Open Watcom
*    Public License version 1.0 (the 'License'). You may not use this file
*    except in compliance with the License. BY USING THIS FILE YOU AGREE TO
*    ALL TERMS AND CONDITIONS OF THE LICENSE. A copy of the License is
*    provided with the Original Code and Modifications, and is also
*    available at www.sybase.com/developer/opensource.
*
*    The Original Code and all software distributed under the License are
*    distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
*    EXPRESS OR IMPLIED, AND SYBASE AND ALL CONTRIBUTORS HEREBY DISCLAIM
*    ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR
*    NON-INFRINGEMENT. Please see the License for the specific language
*    governing rights and limitations under the License.
*
*  ========================================================================
*
* Description:	Parser items
*
****************************************************************************/

#ifndef PARSER_H
#define PARSER_H

#include <operands.h>
#include <symbols.h>
#include <token.h>

#define COMMENT /* .asm comment.. */

/* define tokens for SpecialTable (registers, operators, ... ) */
enum special_token {
    T_NULL,
#define	 res(token, string, type, value, bytval, flags, cpu, sflags) T_ ## token ,
#include <special.h>
#undef res
/* define tokens for SpecialTable (directives) */
#define	 res(token, string, value, bytval, flags, cpu, sflags) T_ ## token ,
#include <directve.h>
#undef res
SPECIAL_LAST
};

/* define tokens for instruction table (InstrTable[] in reswords.c) */

enum instr_token {
    INS_FIRST_1 = SPECIAL_LAST - 1, /* to ensure tokens are unique */
#define insa(token, string, opcls, byte1_info,op_dir,rm_info,opcode,rm_byte,cpu,prefix,evex ) T_ ## token ,
#define insx(token, string, opcls, byte1_info,op_dir,rm_info,opcode,rm_byte,cpu,prefix,evex,flgs ) T_ ## token ,
#define insv(token, string, opcls, byte1_info,op_dir,rm_info,opcode,rm_byte,cpu,prefix,evex,flgs,vex ) T_ ## token ,
#define insn(tok, suffix,   opcls, byte1_info,op_dir,rm_info,opcode,rm_byte,cpu,prefix,evex)
#define insm(tok, suffix,   opcls, byte1_info,op_dir,rm_info,opcode,rm_byte,cpu,prefix,evex)
#define avxins(alias, token, string, cpu, flgs ) T_ ## token ,
#include <instruct.h>
#undef insm
#undef insn
#undef insx
#undef insv
#undef insa
#undef avxins
#define VEX_START T_VBROADCASTSS  /* first VEX encoded item */
};

/*---------------------------------------------------------------------------*/

/* queue of symbols */
struct symbol_queue {
    struct dsym *head;
    struct dsym *tail;
};

enum queue_type {
    TAB_UNDEF = 0,
    TAB_EXT,	  /* externals (EXTERNDEF, EXTERN, COMM, PROTO ) */
    TAB_SEG,	  /* SEGMENT items */
    TAB_GRP,	  /* GROUP items */
    TAB_PROC,	  /* PROC items */
    TAB_ALIAS,	  /* ALIAS items */
    TAB_LAST,
};

/* several lists, see enum queue_type above */
extern struct symbol_queue SymTables[];

/*
 values for <rm_info> (3 bits)
 000		-> has rm_byte with w-, d- and/or s-bit in opcode
 001( no_RM   ) -> no rm_byte - may have w-bit
 010( no_WDS  ) -> has rm_byte, but w-bit, d-bit, s-bit of opcode are absent
 011( R_in_OP ) -> no rm_byte, reg field (if any) is included in opcode
 */
enum rm_info {
    no_RM   = 0x1,
    no_WDS  = 0x2,
    R_in_OP = 0x3,
};

/* values for <allowed_prefix> (3 bits) */
enum allowed_prefix {
    // AP_NO_PREFIX= 0x00, /* value 0 means "normal" */
    AP_LOCK	= 0x01,
    AP_REP	= 0x02,
    AP_REPxx	= 0x03,
    AP_FWAIT	= 0x04,
    AP_NO_FWAIT = 0x05
};

/* values for field type in special_item.
 * it should match order of T_REGISTER - T_RES_ID in token.h
 */

enum special_type {
    RWT_REG = 2,  /* same value as for T_REG */
    RWT_DIRECTIVE,
    RWT_UNARY_OP,
    RWT_BINARY_OP,
    RWT_STYPE,
    RWT_RES_ID
};

// values for sflags if register
enum op1_flags {
    SFR_SIZMSK	= 0x7F, /* size in bits 0-4 */
    SFR_IREG	= 0x80,
    SFR_SSBASED = 0x100, /* v2.11: added */
};

enum rex_bits {
    REX_B = 1,	/* regno 0-7 <-> 8-15 of ModR/M or SIB base */
    REX_X = 2,	/* regno 0-7 <-> 8-15 of SIB index */
    REX_R = 4,	/* regno 0-7 <-> 8-15 of ModR/M REG */
    REX_W = 8	/* wide 32 <-> 64 */
};

/* operand classes. this table is defined in reswords.c.
 * index into this array is member opclsidx in instr_item.
 * v2.06: data removed from struct instr_item.
 */
struct opnd_class {
    enum operand_type opnd_type[2];  /* operands 1 + 2 */
    unsigned char opnd_type_3rd;     /* operand 3 */
};

/* instr_item is the structure used to store instructions
 * in InstrTable (instruct.h).
 * Most compilers will use unsigned type for enums, just OW
 * allows to use the smallest size possible.
 */

struct instr_item {
    unsigned char opclsidx;	/* v2.06: index for opnd_clstab */
    unsigned char byte1_info;	/* flags for 1st byte */
    unsigned char
	allowed_prefix	: 3,	/* allowed prefix */
	first		: 1,	/* 1=opcode's first entry */
	rm_info		: 3,	/* info on r/m byte */
	opnd_dir	: 1;	/* operand direction */
    unsigned char   evex;	/* EVEX */
    unsigned short  cpu;
    unsigned char   opcode;	/* opcode byte */
    unsigned char   rm_byte;	/* mod_rm_byte */
};

/* special_item is the structure used to store directives and
 * other reserved words in SpecialTable (special.h).
 */
struct special_item {
    unsigned	 value;
    unsigned	 sflags;
    uint_16	 cpu;	  /* CPU type */
    uint_8	 bytval;
    uint_8	 type;
};

#define GetRegNo( x )	 SpecialTable[x].bytval
#define GetSflagsSp( x ) SpecialTable[x].sflags
#define GetValueSp( x )	 SpecialTable[x].value
#define GetMemtypeSp( x ) SpecialTable[x].bytval
#define GetCpuSp( x )	 SpecialTable[x].cpu

/* values for <value> if type == RWT_DIRECTIVE */
enum directive_flags {
    DF_CEXPR	= 0x01, /* avoid '<' being used as string delimiter (.IF, ...) */
    DF_STRPARM	= 0x02, /* directive expects string param(s) (IFB, IFDIF, ...) */
			/* enclose strings in <> in macro expansion step */
    DF_NOEXPAND = 0x04, /* don't expand params for directive (PURGE, FOR, IFDEF, ...) */
    DF_LABEL	= 0x08, /* directive requires a label */
    DF_NOSTRUC	= 0x10, /* directive not allowed inside structs/unions */
    DF_NOCONCAT = 0x20, /* don't concat line */
    DF_PROC	= 0x40, /* directive triggers prologue generation */
    DF_STORE	= 0x80, /* directive triggers line store */
    DF_CGEN	= 0x100 /* directive generates lines */
};

/* values for <bytval> if type == RWT_DIRECTIVE */
#define	 res(token, function) DRT_ ## token ,
enum directive_type {
#include <dirtype.h>
};
#undef	res

#define MAX_OPND 3

struct opnd_item {
    enum operand_type type;
    struct fixup      *InsFixup;
    union {
	struct {
	    int_32    data32l;
	    int_32    data32h; /* needed for OP_I48 and OP_I64 */
	};
	uint_64	      data64;
    };
};

/* code_info describes the current instruction. It's the communication
 * structure between parser and code generator.
 */

/* EVEX:
 * P1: R.X.B.R1.0.0.m1.m2
 * P2: W.v3.v2.v1.v0.1.p1.p0
 * P3: z.L1.L0.b.V1.a2.a1.a0
 */
#define VX1_R	0x80
#define VX1_X	0x40
#define VX1_B	0x20
#define VX1_R1	0x10
#define VX1_M1	0x02
#define VX1_M2	0x01

#define VX2_W	0x80
#define VX2_V3	0x40
#define VX2_V2	0x20
#define VX2_V1	0x10
#define VX2_V0	0x08
#define VX2_1	0x04
#define VX2_P1	0x02
#define VX2_P0	0x01

#define VX3_Z	0x80 /* {z} */
#define VX3_L1	0x40
#define VX3_L0	0x20
#define VX3_B	0x10 /* {1to4} {1to8} {1to16} */
#define VX3_V	0x08
#define VX3_A2	0x04 /* {k1..k7} */
#define VX3_A1	0x02
#define VX3_A0	0x01

#define VX_OP1V 0x01 /* set if op1..3 is [z|y|x]mm16..31 register */
#define VX_OP2V 0x02
#define VX_OP3V 0x04
#define VX_OP3	0x08 /* more than 2 instruction args used */
#define VX_ZMM	0x10 /* ZMM used */
#define VX_SAE	0x20 /* {sae} used */
#define VX_ZMM8 0x40 /* zmm8..15 used */
#define VX_ZMM24 0x80 /* zmm24..31 used */

/* pinstr->evex */
#define VX_RXB	0x0F /* P1: R.X.B.R1 */
#define VX_XMMI 0x08 /* XMM register used as index */
#define VX_NV0	0x04 /* P2: V0=0 */
#define VX_W1	0x02 /* P2: W=1 */

struct code_info {
    int ins;			/* prefix before instruction, e.g. lock, rep, repnz */
    int RegOverride;		/* segment override (0=ES,1=CS,2=SS,3=DS,...) */
    unsigned char rex;
    unsigned char adrsiz;	/* address size prefix 0x67 is to be emitted */
    unsigned char opsiz;	/* operand size prefix 0x66 is to be emitted */
    unsigned char evex;		/* EVEX prefix 0x62 is to be emitted */
    unsigned char evexP3;
    unsigned char vflags;
    unsigned short token;
    struct opnd_item opnd[MAX_OPND];
    const struct instr_item *pinstr;	/* current pointer into InstrTable */
    unsigned char mem_type;		/* byte / word / etc. NOT near/far */
    unsigned char rm_byte;
    unsigned char sib;
    unsigned char Ofssize;
    unsigned char opc_or;
    unsigned char vexregop;		/* in based-1 format (0=empty) */
    union {
	unsigned char flags;
	struct {
	    unsigned char   iswide:1;	    /* 0=byte, 1=word/dword/qword */
	    unsigned char   isdirect:1;	    /* 1=direct addressing mode */
	    unsigned char   isfar:1;	    /* CALL/JMP far */
	    unsigned char   const_size_fixed:1; /* v2.01 */
	    unsigned char   x86hi_used:1;   /* AH,BH,CH,DH used */
	    unsigned char   x64lo_used:1;   /* SPL,BPL,SIL,DIL used */
	    unsigned char   undef_sym:1;    /* v2.06b: struct member is forward ref */
	    unsigned char   base_rip:1;
	};
    };
};

#define OPND1 0
#define OPND2 1
#define OPND3 2

/* branch instructions are still sorted:
 * CALL, JMP, Jcc, J[e|r]CXZ, LOOP, LOOPcc
 */

#define IS_CALL( inst )	      ( inst == T_CALL )
#define IS_JMPCALL( inst )    ( inst == T_CALL || inst == T_JMP	   )
#define IS_JMP( inst )	      ( inst >= T_JMP  && inst < T_LOOP	 )
#define IS_JCC( inst )	      ( inst >	T_JMP  && inst < T_JCXZ	 )
#define IS_BRANCH( inst )     ( inst >= T_CALL && inst < T_LOOP	 )
#define IS_ANY_BRANCH( inst ) ( inst >= T_CALL && inst <= T_LOOPNZW )
#define IS_XCX_BRANCH( inst ) ( inst >= T_JCXZ && inst <= T_LOOPNZW )

#define IS_OPER_32( s )	  ( s->Ofssize ? ( s->opsiz == FALSE ) : ( s->opsiz == TRUE ))

/* globals */
extern const struct instr_item	 InstrTable[];	 /* instruction table */
extern const struct special_item SpecialTable[]; /* rest of res words */
extern uint_16			 optable_idx[];	 /* helper, access thru IndexFromToken() only */

#define IndexFromToken( tok )  optable_idx[ ( tok ) - SPECIAL_LAST ]

int  SizeFromMemtype( unsigned char, int, struct asym * );
int  MemtypeFromSize( int, unsigned char * );
int  SizeFromRegister( int );
int  GetLangType( int *, struct asm_tok[], unsigned char * );
void sym_add_table( struct symbol_queue *, struct dsym * );
void sym_remove_table( struct symbol_queue *, struct dsym * );
void sym_ext2int( struct asym * );
int  OperandSize( enum operand_type, const struct code_info * );
void set_frame( const struct asym *sym );
void set_frame2( const struct asym *sym );
int  ParseLine( struct asm_tok[] );
void ProcessFile( struct asm_tok[] );
void WritePreprocessedLine( const char * );
int  parsevex( char *, unsigned char * );

#endif
