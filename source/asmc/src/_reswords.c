/****************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
* Description:	reserved word handling, including hash table access
*
****************************************************************************/

#include <globals.h>
#include <memalloc.h>
#include <parser.h>
#include <reswords.h>
#include <expreval.h>
#include <condasm.h>
#include <codegen.h>

#define HASH_TABITEMS 811
#define GetPtr( x, y ) x->y

/* reserved words hash table */

extern uint_16 resw_table[ HASH_TABITEMS ];

/* define unary operand (LOW, HIGH, OFFSET, ...) type flags */
enum unary_operand_types {
#define res( value, func ) UOT_ ## value,
#include <unaryop.h>
#undef res
};

/* v2.06: the following operand combinations are used
 * inside InstrTable[] only, they don't need to be known
 * by the parser.
 */
enum operand_sets {
    OP_R_MS	 = ( OP_R | OP_MS ),
    OP_R8_M08	 = ( OP_R8 | OP_M08 ),
    OP_RGT8_MS	 = ( OP_RGT8 | OP_MS ),
    OP_RGT8_MGT8 = ( OP_RGT8 | OP_MGT8 ),
    OP_RMGT16	 = ( OP_RGT16 | OP_MGT16 ),
    OP_RGT16_M08 = ( OP_RGT16 | OP_M08 ),
    OP_R16_R32	 = ( OP_R16 | OP_R32 ),
    OP_R16_M16	 = ( OP_R16 | OP_M16 ),
    OP_R32_M08	 = ( OP_R32 | OP_M08 ),
    OP_R32_M16	 = ( OP_R32 | OP_M16 ),
    OP_R32_M32	 = ( OP_R32 | OP_M32 ),
    OP_R16_R64	 = ( OP_R16 | OP_R64 ),
    OP_R64_M64	 = ( OP_R64 | OP_M64 ),
    OP_M16_M64	 = ( OP_M16 | OP_M64 ),
    OP_M16_M32	 = ( OP_M16 | OP_M32 ),
    OP_MMX_M64	 = ( OP_MMX | OP_M64 ),
    OP_XMM_M16	 = ( OP_XMM | OP_M16 ),
    OP_XMM_M32	 = ( OP_XMM | OP_M32 ),
    OP_XMM_M64	 = ( OP_XMM | OP_M64 ),
    OP_XMM_M128	 = ( OP_XMM | OP_M128 ),
/* extended Masm syntax: sometimes Masm accepts 2 mem types
 * for the memory operand, although the mem access will always
 * be QWORD/OWORD.
 */
    OP_MMX_M64_08  = ( OP_MMX | OP_M64	| OP_M08 ),
    OP_MMX_M64_16  = ( OP_MMX | OP_M64	| OP_M16 ),
    OP_MMX_M64_32  = ( OP_MMX | OP_M64	| OP_M32 ),

    OP_XMM_M128_08 = ( OP_XMM | OP_M128 | OP_M08 ),
    OP_XMM_M128_16 = ( OP_XMM | OP_M128 | OP_M16 ),
    OP_XMM_M128_32 = ( OP_XMM | OP_M128 | OP_M32 ),
    OP_XMM_M128_64 = ( OP_XMM | OP_M128 | OP_M64 ),
    OP_YMM_M256	 = ( OP_YMM | OP_M256 ),
};

/* v2.06: operand types have been removed from InstrTable[], they
 * are stored now in their own table, opnd_clstab[], below.
 * This will allow to add a 4th operand ( AVX ) more effectively.
 */
enum opnd_variants {
#define OpCls( op1, op2, op3 ) OPC_ ## op1 ## op2 ## op3,
#include <opndcls.h>
#undef OpCls
};

/* the tables to handle "reserved words" are now generated:
 * 1. InstrTable: contains info for instructions.
 *    instructions may need multiple rows!
 * 2. SpecialTable: contains info for reserved words which are
 *    NOT instructions. One row each.
 * 3. optable_idx: array of indices for InstrTable.
 * 4. resw_strings: strings of reserved words. No terminating x'00'!
 * 5. ResWordTable: array of reserved words (name, name length, flags).
 *
 * Each reserved word has a "token" value assigned, which is a short integer.
 * This integer can be used as index for:
 * - SpecialTable
 * - optable_idx ( needs adjustment, better use macro IndexFromToken() )
 * - ResWordTable
 */

/* create InstrTable. */

#define OpCls( op1, op2, op3 ) OPC_ ## op1 ## op2 ## op3

const struct instr_item InstrTable[] = {
#define ins(tok, string, opcls, byte1_info,op_dir,rm_info,opcode,rm_byte,cpu,prefix) \
    { opcls, byte1_info, prefix, 1, rm_info, op_dir, 0, cpu, opcode, rm_byte },
#define insx(tok,string, opcls, byte1_info,op_dir,rm_info,opcode,rm_byte,cpu,prefix,flgs) \
    { opcls, byte1_info, prefix, 1, rm_info, op_dir, 0, cpu, opcode, rm_byte },
#define insn(tok,suffix,     opcls, byte1_info,op_dir,rm_info,opcode,rm_byte,cpu,prefix) \
    { opcls, byte1_info, prefix, 0, rm_info, op_dir, 0, cpu, opcode, rm_byte },
#define insm(tok,suffix,     opcls, byte1_info,op_dir,rm_info,opcode,rm_byte,cpu,prefix) \
    { opcls, byte1_info, prefix, 1, rm_info, op_dir, 0, cpu, opcode, rm_byte },
#include <instruct.h>
#include <instr64.h>
ins (NULL,0,OpCls(NONE,NONE,NONE),0,0,0,0,0,0,0) /* last entry - needed for its ".first" (=1) field */
#undef insm
#undef insn
#undef insx
#undef ins
};
#undef OpCls

/* create SpecialTable. */

const struct special_item SpecialTable[] = {
    { 0, 0, 0, 0, 0 }, /* dummy entry for T_NULL */
#define res(tok, string, type, value, bytval, flags, cpu, sflags ) \
    { value, sflags, cpu, bytval, type },
#include <special.h>
#undef res
#define res(tok, string, value, bytval, flags, cpu, sflags ) \
    { value, sflags, cpu, bytval, RWT_DIRECTIVE },
#include <directve.h>
#undef res
};

/* define symbolic indices for InstrTable[] */

enum res_idx {
#define	 ins(tok, string, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix) T_ ## tok ## _I,
#define insx(tok, string, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix,flgs) T_ ## tok ## _I,
#define insn(tok, suffix, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix) T_ ## tok ## _ ## suffix,
#define insm(tok, suffix, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix) T_ ## tok ## _ ## suffix,
#include <instruct.h>
#undef insm
#undef insn
#undef ins

#define	 ins(tok, string, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix) T_ ## tok ## _I64,
#define insn(tok, suffix, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix) T_ ## tok ## _ ## suffix ## _I64,
#define insm(tok, suffix, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix) T_ ## tok ## _ ## suffix ## _I64,
#include <instr64.h>
#undef insm
#undef insn
#undef insx
#undef ins
//T_NULL_I /* v2.06: removed */
};

/* create optable_idx, the index array for InstrTable.
 * This is needed because instructions often need more than
 * one entry in InstrTable.
 */

uint_16 optable_idx[] = {

#define	 ins( tok, string, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix) T_ ## tok ## _I,
#define insx( tok, string, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix,flgs) T_ ## tok ## _I,
#define insn( tok, suffix, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix)
#define insm( tok, suffix, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix)
#include <instruct.h>
#undef insm
#undef insn
#undef insx
#undef ins
#define avxins( tok, string, cpu, flgs ) T_ ## tok ## _I,
#include <instravx.h>
#undef avxins
};

/* table of instruction operand classes
 */
const struct opnd_class opnd_clstab[] = {
#define OpCls( op1, op2, op3 ) { { OP_ ## op1, OP_ ## op2 }, OP3_ ## op3 },
#include <opndcls.h>
#undef OpCls
};

/* create the strings for all reserved words */

static const char resw_strings[] = {
#define res(tok, string, type, value, bytval, flags, cpu, sflags) \
 # string
#include <special.h>
#undef res
#define res(tok, string, value, bytval, flags, cpu, sflags) \
 # string
#include <directve.h>
#undef res

#define ins(tok,string, opcls, byte1_info,op_dir,rm_info,opcode,rm_byte,cpu,prefix) \
 # string
#define insn(tok,suffix, opcls, byte1_info,op_dir,rm_info,opcode,rm_byte,cpu,prefix)
#define insm(tok,suffix, opcls, byte1_info,op_dir,rm_info,opcode,rm_byte,cpu,prefix)
#define insx(tok,string, opcls, byte1_info,op_dir,rm_info,opcode,rm_byte,cpu,prefix,flgs) \
 # string
#include <instruct.h>
#define avxins( tok, string, cpu, flgs ) # string
#include <instravx.h>
#undef avxins
    "syscall_" /* replacement for "syscall" language type in 64-bit */
};
#define strSyscall_ &resw_strings[sizeof(resw_strings)-9]
#undef insx
#undef insm
#undef insn
#undef ins

/* create the 'reserved words' table (ResWordTable).
 * this table's entries will be used to create the instruction hash table.
 * v2.11: RWF_SPECIAL flag removed:
 * { 0, sizeof(#string)-1, RWF_SPECIAL | flags, NULL },
 */
struct ReservedWord ResWordTable[] = {
    { 0, 0, 0, NULL }, /* dummy entry for T_NULL */
#define res(tok, string, type, value, bytval, flags, cpu, sflags) \
    { 0, sizeof(#string)-1, flags, NULL },
#include <special.h>
#undef res
#define res(tok, string, value, bytval, flags, cpu, sflags) \
    { 0, sizeof(#string)-1, flags, NULL },
#include <directve.h>
#undef res

#define ins(tok,string,	 opcls, byte1_info,op_dir,rm_info,opcode,rm_byte,cpu,prefix) \
    { 0, sizeof(#string)-1, 0, NULL },
#define insn(tok,suffix, opcls, byte1_info,op_dir,rm_info,opcode,rm_byte,cpu,prefix)
#define insm(tok,suffix, opcls, byte1_info,op_dir,rm_info,opcode,rm_byte,cpu,prefix)
#define insx(tok,string, opcls, byte1_info,op_dir,rm_info,opcode,rm_byte,cpu,prefix,flags) \
    { 0, sizeof(#string)-1, flags, NULL },
#include <instruct.h>
#undef insx
#undef insm
#undef insn
#undef ins
#define avxins( tok, string, cpu, flgs ) \
    { 0, sizeof(#string)-1, RWF_VEX, NULL },
#include <instravx.h>
#undef avxins
};

/* these is a special 1-byte array for vex-encoded instructions.
 * it could probably be moved to InstrTable[] (there is an unused byte),
 * but in fact it's the wrong place, since the content of vex_flags[]
 * are associated with opcodes, not with instruction variants.
 */
const uint_8 vex_flags[] = {
    /* flags for the AVX instructions in instruct.h. The order must
     * be equal to the one in instruct.h! ( this is to be improved.)
     * For a description of the VX_ flags see codegen.h
     */
    VX_NND,	 /* VBROADCASTSS   */
    VX_NND,	 /* VBROADCASTSD   */
    VX_NND,	 /* VBROADCASTF128 */
    VX_L,	 /* VBLENDVPD	   */
    VX_L,	 /* VBLENDVPS	   */
    0,		 /* VINSERTF128	   */
    VX_NND,	 /* VEXTRACTF128   */
    VX_L,	 /* VMASKMOVPS	   */
    VX_L,	 /* VMASKMOVPD	   */
    0,		 /* VPBLENDVB	   */
    VX_L|VX_IMM, /* VPERMILPD	   */
    VX_L|VX_IMM, /* VPERMILPS	   */
    /* VPERMIL2xx has been dropped */
    //VX_L,	 /* VPERMIL2PD	   */
    //VX_L,	 /* VPERMIL2PS	   */
    0,		 /* VPERM2F128	   */
    VX_L|VX_NND, /* VTESTPS	   */
    VX_L|VX_NND, /* VTESTPD	   */
    VX_L,	 /* VZEROALL	   */
    0,		 /* VZEROUPPER	   */
    VX_NND,	 /* VCVTPD2DQ	   */
    VX_NND,	 /* VCVTTPD2DQ	   */
    VX_NND,	 /* VCVTPD2PS	   */
    VX_NND,	 /* VMOVDDUP	   */
    VX_L|VX_NND, /* VMOVMSKPD	   */ /* v2.11 */
    VX_L|VX_NND, /* VMOVMSKPS	   */ /* v2.11 */
#define avxins( tok, string, cpu, flgs ) flgs,
#include <instravx.h>
#undef avxins
};

/* keywords to be added for 64-bit */
static const enum instr_token patchtab64[] = {
    T_SPL,	       /* add x64 register part of special.h */
    T_FRAME,	       /* add x64 reserved word part of special.h */
    T_DOT_ALLOCSTACK,  /* add x64 directive part of directve.h (win64) */
    T_JRCXZ,	       /* branch instructions must be grouped together */
    T_CDQE,	       /* add x64 part of instruct.h */
    T_VPEXTRQ,	       /* add x64 part of instravx.h */
};

/* keywords to be removed for 64-bit */
static const enum instr_token patchtab32[] = {
    T_TR3,	    /* registers invalid for IA32+		*/
    T_DOT_SAFESEH,  /* directives invalid for IA32+		*/
    T_AAA,	    /* instructions invalid for IA32+		*/
    T_JCXZ,	    /* 1. branch instructions invalid for IA32+ */
    T_LOOPW	    /* 2. branch instructions invalid for IA32+ */
};

struct replace_ins {
    uint_16	  tok; /* is an optable_idx[] index */
    enum res_idx  idx32;
    enum res_idx  idx64;
};

/* keyword entries to be changed for 64-bit (see instr64.h) */
static const struct replace_ins patchtabr[] = {
    { T_LGDT - SPECIAL_LAST, T_LGDT_I, T_LGDT_I64 },
    { T_LIDT - SPECIAL_LAST, T_LIDT_I, T_LIDT_I64 },
    { T_CALL - SPECIAL_LAST, T_CALL_I, T_CALL_I64 },
    { T_JMP  - SPECIAL_LAST, T_JMP_I,  T_JMP_I64  },
    { T_POP  - SPECIAL_LAST, T_POP_I,  T_POP_I64  }, /* v2.06: added */
    { T_PUSH - SPECIAL_LAST, T_PUSH_I, T_PUSH_I64 }, /* v2.06: added */
    /* with Masm, in 16/32-bit SLDT|SMSW|STR accept a WORD argument only -
     * in 64-bit (ML64), 32- and 64-bit registers are also accepted!
     */
    { T_SLDT - SPECIAL_LAST, T_SLDT_I, T_SLDT_I64 },
    { T_SMSW - SPECIAL_LAST, T_SMSW_I, T_SMSW_I64 },
    { T_STR  - SPECIAL_LAST, T_STR_I,  T_STR_I64  },
    { T_VMREAD	- SPECIAL_LAST, T_VMREAD_I,   T_VMREAD_I64  },
    { T_VMWRITE - SPECIAL_LAST, T_VMWRITE_I,  T_VMWRITE_I64 },
};


static struct qdesc renamed_keys = { NULL, NULL };

/* global queue of "disabled" reserved words.
 * just indices of ResWordTable[] are used.
 */
static struct {
    uint_16 Head;
    uint_16 Tail;
} Removed = { 0, 0 };

static bool  b64bit = FALSE; /* resw tables in 64bit mode? */

unsigned __fastcall get_hash( const char *s, unsigned char size );

/* add reserved word to hash table */

static void AddResWord( int token )
/*********************************/
{
    int i;
    int old;
    int curr;
#ifdef BASEPTR
    __segment seg = FP_SEG( resw_strings );
#endif

    i = get_hash( ResWordTable[token].name, ResWordTable[token].len );

    /* sort the items of a line by length! */

    for( curr = resw_table[i], old = 0; curr != 0 && ResWordTable[curr].len <= ResWordTable[token].len; old = curr, curr = ResWordTable[curr].next );

    if ( old == 0 ) {
	ResWordTable[token].next = resw_table[i];
	resw_table[i] = token;
    } else {
	ResWordTable[token].next = ResWordTable[old].next;
	ResWordTable[old].next = token;
    }

    return;
}

/* remove a reserved word from the hash table. */

static int RemoveResWord( int token )
/***********************************/
{
    int i;
    int old;
    int curr;
#ifdef BASEPTR
    __segment seg = FP_SEG( resw_strings );
#endif

    i = get_hash( ResWordTable[token].name, ResWordTable[token].len );

    for( curr = resw_table[i], old = 0 ; curr != 0 ; old = curr, curr = ResWordTable[curr].next )  {
	if( curr == token ) {
	    if ( old != 0 )
		ResWordTable[old].next = ResWordTable[curr].next;
	    else
		resw_table[i] = ResWordTable[curr].next;
	    return( TRUE );
	}
    }
    return( FALSE );
}

struct rename_node {
    struct rename_node *next;
    const char *name; /* the original name in resw_strings[] */
    uint_16 token; /* is either enum instr_token or enum special_token */
    uint_8 length;
};

/* Rename a keyword - used by OPTION RENAMEKEYWORD.
 * - token: keyword to rename
 * - newname: new name of keyword
 * - length: length of new name
 */

void RenameKeyword( unsigned token, const char *newname, uint_8 length )
/**********************************************************************/
{
    struct rename_node *curr;
    struct rename_node *prev;

    /* v2.11: do nothing if new name matches current name */
    if ( ResWordTable[token].len == length && !_memicmp( newname, ResWordTable[token].name, length ) )
	return;

    RemoveResWord( token );
    /* if it is the first rename action for this keyword,
     * the original name must be saved.
     */
    if ( ResWordTable[token].name >= resw_strings &&
	ResWordTable[token].name < ( resw_strings + sizeof( resw_strings ) ) ) {
	curr = (struct rename_node *)LclAlloc( sizeof( struct rename_node ) );
	curr->next = NULL;
	curr->name = ResWordTable[token].name;
	curr->token = token;
	curr->length = ResWordTable[token].len;
	if ( renamed_keys.head == NULL ) {
	    renamed_keys.head = renamed_keys.tail = curr;
	} else {
	    ((struct rename_node *)renamed_keys.tail)->next = curr;
	    renamed_keys.tail = curr;
	}
    } else {
	/* v2.11: search the original name. if the "new" names matches
	 * the original name, restore the name pointer */
	for ( curr = renamed_keys.head, prev = NULL; curr; prev = curr ) {
	    if ( curr->token == token ) {
		if ( curr->length == length && !memcmp( newname, curr->name, length ) ) {
		    if ( prev )
			prev->next = curr->next;
		    else
			renamed_keys.head = curr->next;
		    if ( renamed_keys.tail == curr )
			renamed_keys.tail = prev;
		    ResWordTable[token].name = curr->name;
		    ResWordTable[token].len = curr->length;
		    AddResWord( token );
		    return;
		}
		break;
	    }
	}
    }
    ResWordTable[token].name = (const char *)LclAlloc( length );
    /* convert to lowercase? */
    memcpy( (void *)ResWordTable[token].name, newname, length );
    ResWordTable[token].len = length;
    AddResWord( token );
}

/* depending on 64bit on or off, some instructions must be added,
 * some removed. Currently this is a bit hackish.
 */
void Set64Bit( bool newmode )
/***************************/
{
    static const char *syscallname;   /* "true" syscall name stored here */
    int token;
    int i;

    if ( newmode != b64bit ) {
	if ( newmode != FALSE ) {
	    optable_idx[ T_INC - SPECIAL_LAST ]++;   /* skip the one-byte register INC */
	    optable_idx[ T_DEC - SPECIAL_LAST ]++;   /* skip the one-byte register DEC */
	    /*
	     * change SYSCALL to SYSCALL_ language in long mode.
	     * one cannot just change the name, since the hash value
	     * will differ!
	     */
	    RemoveResWord( T_SYSCALL );
	    syscallname = ResWordTable[T_SYSCALL].name; /* save the "true" name */
	    ResWordTable[T_SYSCALL].name = strSyscall_;
	    ResWordTable[T_SYSCALL].len++;
	    AddResWord( T_SYSCALL );

	    for ( i = 0; i < sizeof( patchtab64 ) / sizeof( patchtab64[0] ); i++ )
		for( token = patchtab64[i]; ResWordTable[token].flags & RWF_X64; token++ )
		    if ( !( ResWordTable[token].flags & RWF_DISABLED ) )
			AddResWord( token );
	    for ( i = 0; i < sizeof( patchtab32 ) / sizeof( patchtab32[0] ); i++ )
		for( token = patchtab32[i]; ResWordTable[token].flags & RWF_IA32; token++ )
		    if ( !( ResWordTable[token].flags & RWF_DISABLED ) )
			RemoveResWord( token );
	    for ( i = 0; i < sizeof( patchtabr) / sizeof( patchtabr[0] ); i++ ) {
		optable_idx[ patchtabr[i].tok] = patchtabr[i].idx64;
	    }
	} else	{
	    optable_idx[T_INC - SPECIAL_LAST]--;   /* restore the one-byte register INC */
	    optable_idx[T_DEC - SPECIAL_LAST]--;   /* restore the one-byte register DEC */

	    for ( i = 0; i < sizeof( patchtab64 ) / sizeof( patchtab64[0] ); i++ )
		for( token = patchtab64[i]; ResWordTable[token].flags & RWF_X64; token++ )
		    if ( !( ResWordTable[token].flags & RWF_DISABLED ) )
			RemoveResWord( token );
	    for ( i = 0; i < sizeof( patchtab32 ) / sizeof( patchtab32[0] ); i++ )
		for( token = patchtab32[i]; ResWordTable[token].flags & RWF_IA32; token++ )
		    if ( !( ResWordTable[token].flags & RWF_DISABLED ) )
			AddResWord( token );
	    for ( i = 0; i < sizeof( patchtabr) / sizeof( patchtabr[0] ); i++ ) {
		optable_idx[patchtabr[i].tok] = patchtabr[i].idx32;
	    }

	    /* change calling convention syscall_ back to syscall */
	    RemoveResWord( T_SYSCALL );
	    ResWordTable[T_SYSCALL].name = syscallname; /* restore "true" name */
	    ResWordTable[T_SYSCALL].len--;
	    AddResWord( T_SYSCALL );
	}
	b64bit = newmode;
    }
}

void DisableKeyword( unsigned token )
/***********************************/
{
    if ( !( ResWordTable[token].flags & RWF_DISABLED ) ) {
	RemoveResWord( token );
	ResWordTable[token].next = 0;
	ResWordTable[token].flags |= RWF_DISABLED;
	if ( Removed.Head == 0 )
	    Removed.Head = Removed.Tail = token;
	else {
	    ResWordTable[Removed.Tail].next = token;
	    Removed.Tail = token;
	}
    }
}

/* check if a keyword is in the list of disabled words.
 */

bool IsKeywordDisabled( const char *name, int len )
/*************************************************/
{
    unsigned token;
    for ( token = Removed.Head; token != 0; token = ResWordTable[token].next )
	if( ResWordTable[token].name[ len ] == NULLC && _memicmp( name, ResWordTable[token].name, len ) == 0 )
	    return( TRUE );
    return( FALSE );
}

/* get current name of a reserved word.
 * max size is 255.
 */

char *GetResWName( unsigned resword, char *buff )
/***********************************************/
{
    static char intbuff[256];
    if ( !buff )
	buff = intbuff;
    memcpy( buff, ResWordTable[resword].name, ResWordTable[resword].len );
    buff[ResWordTable[resword].len] = NULLC;
    return( buff );
}

/* ResWordsInit() initializes the reserved words hash array ( resw_table[] )
 * and also the reserved words string pointers ( ResWordTable[].name + ResWordTable[].len )
 */

void ResWordsInit( void )
/***********************/
{
    int i;
    const char *p = resw_strings;

    /* exit immediately if table is already initialized */
    if ( ResWordTable[1].name )
	return;

    /* clear hash table */
    memzero( &resw_table, sizeof( resw_table ) );

    /* currently these flags must be set manually, since the
     * RWF_ flags aren't contained in instravx.h */
    ResWordTable[T_VPEXTRQ].flags |= RWF_X64;
    ResWordTable[T_VPINSRQ].flags |= RWF_X64;

    /* initialize ResWordTable[].name and .len.
     * add keyword to hash table ( unless it is 64-bit only ).
     * v2.09: start with index = 1, since index 0 is now T_NULL
     */
    for( i = 1; i < sizeof( ResWordTable ) / sizeof( ResWordTable[0] ); i++ ) {
	ResWordTable[i].name = p;
	p += ResWordTable[i].len;
	if ( !(ResWordTable[i].flags & RWF_X64 ) )
	    AddResWord( i );
    }
    return;
}

/* ResWordsFini() is called once per module
 * it restores the resword table
 */

void ResWordsFini( void )
/***********************/
{
    int i;
    int next;
    struct rename_node	*rencurr;

    /* restore renamed keywords.
     * the keyword has to removed ( and readded ) from the hash table,
     * since its position most likely will change.
     */
    for ( rencurr = renamed_keys.head; rencurr; ) {
	struct rename_node *tmp = rencurr->next;
	RemoveResWord( rencurr->token );
	/* v2.06: this is the correct name to free */
	ResWordTable[rencurr->token].name = rencurr->name;
	ResWordTable[rencurr->token].len = rencurr->length;
	AddResWord( rencurr->token );
	rencurr = tmp;
    }
    renamed_keys.head = NULL;

    /* reenter disabled keywords */
    for( i = Removed.Head; i != 0; i = next ) {
	next = ResWordTable[i].next;
	ResWordTable[i].flags &= ~RWF_DISABLED;
	if ( !(ResWordTable[i].flags & RWF_X64 ) )
	    AddResWord( i );
    }
    Removed.Head = Removed.Tail = 0;

    return;
}

