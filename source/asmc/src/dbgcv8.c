/***************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
* Description:	Generate CodeView symbolic debug info ( Version 8 format )
*
****************************************************************************/

#define CV_SIGNATURE 4

#include <stddef.h>

#include <globals.h>
#include <memalloc.h>
#include <parser.h>
#include <segment.h>
#include <fixup.h>
#include <dbgcv.h>

#ifdef CODEVIEW8

extern char szCVCompiler[];

uint_32 GetTyperef( struct asym *, uint_8 );
uint_16 cv_get_x64_regno( uint_16 );
uint_16 cv_get_register( struct asym * );

#define EQUATESYMS 1 /* 1=generate info for EQUates ( -Zi3 ) */
#define SIZE_CV_SEGBUF ( MAX_LINE_LEN * 2 ) /* assumed size of codeview sections temp buffer */
#define checkflush( seg, curr, size, param ) seg->e.seginfo->flushfunc( seg, curr, size, param )
#define SetPrefixName( p, name, len ) memcpy( p, name, len ); p += len; *p++ = '\0';

#pragma pack(push, 1)

typedef struct {
    char *name;
    uint_32 offset; /* offset into string table */
    /* uint_8 checksum[16]; MD5 digest of source file */
    } cv_file;

typedef struct {
    union {
	uint_8 *ps;
	struct cv_symrec_compile  *ps_cp;  /* S_COMPILE	 */
	struct cv_symrec_register *ps_reg; /* S_REGISTER */
	struct cv_symrec_constant *ps_con; /* S_CONSTANT */
	struct cv_symrec_udt	  *ps_udt; /* S_UDT	 */
	struct cv_symrec_endblk	  *ps_eb;  /* S_ENDBLK	 */
	struct cv_symrec_objname  *ps_on;  /* S_OBJNAME	 */
	struct cv_symrec_bprel32  *ps_br32;/* S_BPREL32	 */
	struct cv_symrec_ldata32  *ps_d32; /* S_xDATA32	 */
	struct cv_symrec_lproc32  *ps_p32; /* S_xPROC32	 */
	struct cv_symrec_regrel32 *ps_rr32;/* S_REGREL32 */
	struct cv_symrec_label32  *ps_l32; /* S_LABEL32	 */
    };
    struct dsym *symbols;
    union {
	uint_8 *pt;
	struct cv_typerec_array	    *pt_ar;
	struct cv_typerec_pointer   *pt_ptr;
	struct cv_typerec_bitfield  *pt_bf;
	struct cv_typerec_union	    *pt_un;
	struct cv_typerec_structure *pt_st;
	struct cv_typerec_procedure *pt_pr;
	struct cv_typerec_arglist   *pt_al;
	struct cv_typerec_fieldlist *pt_fl;
	struct cv_typerec_member    *pt_mbr;
    };
    struct dsym *types;
    void *param;
    uint_32 level;	/* nesting level */
    cv_typeref currtype; /* current type ( starts with 0x1000 ) */
    cv_file *files;
    uint_8 *base;
    } dbgcv8;

struct leaf32 {
    uint_16 leaf;
    uint_32 value32;
};

#pragma pack(pop)

/* calc size of a codeview item in symbols segment */

static uint_16 GetCVStructLen( struct asym *sym, uint_8 Ofssize )
{
    uint_16 len;
    switch ( sym->state ) {
    case SYM_TYPE:
	len = sizeof( struct cv_symrec_udt );
	break;
    default:
	if ( sym->isproc && Options.debug_ext >= CVEX_REDUCED ) {
	    len = sizeof( struct cv_symrec_lproc32 );
	} else if ( sym->mem_type == MT_NEAR || sym->mem_type == MT_FAR ) {
	    len = sizeof( struct cv_symrec_label32 );
#if EQUATESYMS
	} else if ( sym->isequate ) {
	    len = sizeof( struct cv_symrec_constant ) + ( sym->value >= LF_NUMERIC ? 2 : 0 );
#endif
	} else {
	    len = sizeof( struct cv_symrec_ldata32 );
	}
    }
    return( len );
}

static void PadBytes( uint_8 *curr, uint_8 *base )
{
    for( ;( curr - base ) & 3; curr++ )
	*curr = '\0';
}

/* write a bitfield to $$TYPES */

static void cv_write_bitfield( dbgcv8 *cv, struct dsym *type, struct asym *sym )
{
    cv->pt = checkflush( cv->types, cv->pt, sizeof( struct cv_typerec_bitfield ), cv->param );
    sym->cvtyperef = cv->currtype++;
    cv->pt_bf->tr.size = sizeof( struct cv_typerec_bitfield ) - sizeof(uint_16);
    cv->pt_bf->tr.leaf = LF_BITFIELD;
    cv->pt_bf->length = sym->total_size;
    cv->pt_bf->position = sym->offset;
    cv->pt_bf->type = GetTyperef( (struct asym *)type, USE16 );
    cv->pt += sizeof( struct cv_typerec_bitfield );
    return;
}

static void cv_write_array_type( dbgcv8 *cv, struct asym *sym, uint_32 elemtype, uint_8 Ofssize )
{
    uint_8	*tmp;
    int		typelen;
    int		size;

    typelen = ( sym->total_size >= LF_NUMERIC ? sizeof( uint_32 ) : 0 );
    size = ( sizeof( struct cv_typerec_array ) + 2 + typelen + 1 + 3 ) & ~3;
    cv->pt = checkflush( cv->types, cv->pt, size, cv->param );
    cv->pt_ar->tr.size = size - sizeof(uint_16);
    cv->pt_ar->tr.leaf = LF_ARRAY;
    cv->pt_ar->elemtype = ( elemtype ? elemtype : GetTyperef( sym, Ofssize ) );
    cv->pt_ar->idxtype = 0;//cv_idx_type.uvalue; /* ok? */
    tmp = cv->pt + sizeof( struct cv_typerec_array );
    if ( typelen ) {
	cv->pt_ar->length = LF_ULONG;
	*(uint_32 *)tmp = sym->total_size;
	tmp += sizeof( uint_32 );
    } else {
	cv->pt_ar->length = sym->total_size;
    }
    *tmp++ = NULLC; /* the array type name is empty */
    PadBytes( tmp, cv->types->e.seginfo->CodeBuffer );
    cv->pt += size;
    cv->currtype++;
    return;
}

/* create a pointer type for procedure params and locals.
 * the symbol's mem_type is MT_PTR.
 */

static cv_typeref cv_write_ptr_type( dbgcv8 *cv, struct asym *sym )
{
    int size = ( sizeof( struct cv_typerec_pointer ) + sizeof( uint_32 ) );

    /* for untyped pointers & for function pointers don't create a type, just
     * return a void ptr.
     */
    if ( ( sym->ptr_memtype == MT_EMPTY && sym->target_type == NULL ) || sym->ptr_memtype == MT_PROC )
	return( GetTyperef( sym, sym->Ofssize ) );

    cv->pt = checkflush( cv->types, cv->pt, size, cv->param );
    cv->pt_ptr->tr.size = size - sizeof(uint_16);
    cv->pt_ptr->tr.leaf = LF_POINTER;
    cv->pt_ptr->attribute = ( sym->isfar ? CV_TYPE_PTRTYPE_FAR32 : CV_TYPE_PTRTYPE_NEAR32 );

    /* if indirection is > 1, define an untyped pointer - to be improved */
    if ( sym->is_ptr > 1 ) {
	cv->pt_ptr->type = GetTyperef( sym, sym->Ofssize );
    } else if ( sym->target_type ) {
	/* the target's typeref must have been set here */
	if ( sym->target_type->cvtyperef )
	    cv->pt_ptr->type = sym->target_type->cvtyperef;
	else
	    cv->pt_ptr->type = GetTyperef( sym, sym->Ofssize );
    } else { /* pointer to simple type */
	unsigned char tmpmt = sym->mem_type; /* the target type is tmp. copied to mem_type */
	sym->mem_type = sym->ptr_memtype;   /* thus GetTyperef() can be used */
	cv->pt_ptr->type = GetTyperef( sym, sym->Ofssize );
	sym->mem_type = tmpmt;
    }
    *(uint_32 *)( cv->pt + sizeof( struct cv_typerec_pointer ) ) = 0; /* variant */
    cv->pt += size;
    return( cv->currtype++ );
}

/* structure for field enumeration callback function */
struct cv_counters {
    unsigned cnt;     /* number of fields */
    uint_32 size; /* size of field list */
    uint_32 ofs;  /* current start offset for member */
};

static void cv_write_type( dbgcv8 *cv, struct asym *sym );

/* type of field enumeration callback function */
typedef void (* cv_enum_func)( struct dsym *, struct asym *, dbgcv8 *, struct cv_counters * );

/* field enumeration callback, does:
 * - count number of members in a field list
 * - calculate the size LF_MEMBER records inside the field list
 * - create types ( array, structure ) if not defined yet
 */

static void cv_cntproc( struct dsym *type, struct asym *mbr, dbgcv8 *cv, struct cv_counters *cc )
{
    int	     numsize;
    uint_32  offset;

    cc->cnt++;
    offset = ( type->sym.typekind == TYPE_RECORD ? 0 : mbr->offset + cc->ofs );
    numsize = ( offset >= LF_NUMERIC ? sizeof( uint_32 ) : 0 );
    cc->size += ( sizeof( struct cv_typerec_member ) + numsize + mbr->name_size + 1 + 3 ) & ~3;

    /* field cv_typeref can only be queried from SYM_TYPE items! */

    if ( mbr->mem_type == MT_TYPE && mbr->type->cvtyperef == 0 ) {
	cv->level++;
	cv_write_type( cv, mbr->type );
	cv->level--;
    } else if ( mbr->mem_type == MT_BITS && mbr->cvtyperef == 0 ) {
	cv_write_bitfield( cv, type, mbr );
    }
    if ( mbr->isarray ) {
	/* temporarily (mis)use ext_idx1 member to store the type;
	 * this field usually isn't used by struct fields */
	mbr->ext_idx1 = cv->currtype;
	cv_write_array_type( cv, mbr, 0, USE16 );
    }
}

/* field enumeration callback, does:
 * - create LF_MEMBER record
 */

static void cv_memberproc( struct dsym *type, struct asym *mbr, dbgcv8 *cv, struct cv_counters *cc )
{
    uint_32	offset;
    int		typelen;
    int		size;
    uint_8	*tmp;

    offset = ( type->sym.typekind == TYPE_RECORD ? 0 : mbr->offset + cc->ofs );
    typelen = ( offset >= LF_NUMERIC ? sizeof( uint_32 ) : 0 );
    size = ( sizeof( struct cv_typerec_member ) + typelen + 1 + mbr->name_size + 3 ) & ~3;
    cv->pt = checkflush( cv->types, cv->pt, size, cv->param );
    cv->pt_mbr->leaf = LF_MEMBER;
    if ( mbr->isarray ) {
	cv->pt_mbr->type = mbr->ext_idx1;
	mbr->ext_idx1 = 0; /* reset the temporarily used field */
    } else
	cv->pt_mbr->type = GetTyperef( mbr, USE16 );

    cv->pt_mbr->attribute.access = CV_ATTR_ACC_PUBLIC;
    cv->pt_mbr->attribute.mprop = CV_ATTR_MPR_VANILLA;
    cv->pt_mbr->attribute.pseudo = 0;
    cv->pt_mbr->attribute.noinherit = 0;
    cv->pt_mbr->attribute.noconstruct = 0;
    cv->pt_mbr->attribute.reserved = 0;
    tmp = cv->pt + sizeof( struct cv_typerec_member );
    if ( typelen == 0 ) {
	cv->pt_mbr->offset = offset;
    } else {
	cv->pt_mbr->offset = LF_ULONG;
	*(uint_32 *)tmp = offset;
	tmp += sizeof( uint_32 );
    }
    SetPrefixName( tmp, mbr->name, mbr->name_size );
    PadBytes( tmp, cv->types->e.seginfo->CodeBuffer );
    cv->pt += size;
    return;
}

/* field enumeration function.
 * The MS debug engine has problem with anonymous members (both members
 * and embedded structs).
 * If such a member is included, the containing struct can't be "opened".
 * The OW debugger and PellesC debugger have no such problems.
 * However, for Masm-compatibility, anonymous members are avoided and
 * anonymous struct members or embedded anonymous structs are "unfolded"
 * in this function.
 */
static void cv_enum_fields( struct dsym *sym, cv_enum_func enumfunc, dbgcv8 *cv, struct cv_counters *cc )
{
    unsigned i;
    struct sfield  *curr;
    for ( curr = sym->e.structinfo->head, i = 0; curr; curr = curr->next ) {
	if ( curr->sym.name_size ) { /* has member a name? */
	    enumfunc( sym, &curr->sym, cv, cc );
	} else if ( curr->sym.type ) { /* is member a type (struct, union, record)? */
	    cc->ofs += curr->sym.offset;
	    cv_enum_fields( (struct dsym *)curr->sym.type, enumfunc, cv, cc );
	    cc->ofs -= curr->sym.offset;
	} else if ( sym->sym.typekind == TYPE_UNION ) {
	    /* v2.11: include anonymous union members.
	     * to make the MS debugger work with those members, they must have a name -
	     * a temporary name is generated below which starts with "@@".
	     */
	    char *pold = curr->sym.name;
	    char tmpname[8];
	    curr->sym.name_size = sprintf( tmpname, "@@%u", ++i );
	    curr->sym.name = tmpname;
	    enumfunc( sym, &curr->sym, cv, cc );
	    curr->sym.name = pold;
	    curr->sym.name_size = 0;
	}
    }
    return;
}

/* write a LF_PROCEDURE & LF_ARGLIST type for procedures */

static void cv_write_type_procedure( dbgcv8 *cv, struct asym *sym, int cnt )
{
    int		size;
    cv_typeref	*ptr;
    struct dsym *param;

    size = sizeof( struct cv_typerec_procedure );
    cv->pt = checkflush( cv->types, cv->pt, size, cv->param );
    cv->pt_pr->tr.size = size - sizeof(uint_16);
    cv->pt_pr->tr.leaf = LF_PROCEDURE;
    cv->pt_pr->rvtype = 3;
    cv->pt_pr->call = 0;
    cv->pt_pr->rsvd = 0;
    cv->pt_pr->numparams = cnt;
    cv->pt_pr->arglist = cv->currtype++;
    cv->pt += size;
    size = sizeof( struct cv_typerec_arglist ) + cnt * sizeof( cv_typeref );
    cv->pt = checkflush( cv->types, cv->pt, size, cv->param );
    cv->pt_al->tr.size = size - sizeof(uint_16);
    cv->pt_al->tr.leaf = LF_ARGLIST;
    cv->pt_al->argcount = cnt;
    ptr = (cv_typeref *)(cv->pt + sizeof( struct cv_typerec_arglist ) );
    /* fixme: order might be wrong ( is "push" order ) */
    for ( param = ((struct dsym *)sym)->e.procinfo->paralist; param; param = param->nextparam ) {
	*ptr++ = param->sym.ext_idx1;
    }
    cv->pt += size;
    cv->currtype++;
    return;
}
/* write a type. Items are dword-aligned,
 *    cv: debug state
 *   sym: type to dump
 */

static void cv_write_type( dbgcv8 *cv, struct asym *sym )
{
    struct dsym *type = (struct dsym *)sym;
    uint_8	*tmp;
    int		namesize;
    int		typelen;
    int		size;
    uint_16	property;
    struct cv_counters count;

    /* v2.10: handle typedefs. when the types are enumerated,
     * typedefs are ignored.
     */
    if ( sym->typekind == TYPE_TYPEDEF ) {

	if ( sym->mem_type == MT_PTR ) {
#if GENPTRTYPE
	    /* for untyped void pointers use ONE generic definition */
	    if ( !sym->isfar ) {
		if ( cv->ptrtype[sym->Ofssize] ) {
		    sym->cv_typeref = cv->ptrtype[sym->Ofssize];
		    return;
		}
		cv->ptrtype[sym->Ofssize] = cv->currtype;
	    }
#endif
	    if ( sym->ptr_memtype != MT_PROC && sym->target_type && sym->target_type->cvtyperef == 0 ) {
		if ( cv->level == 0 ) /* avoid circles */
		    cv_write_type( cv, sym->target_type );
	    }
	    sym->cvtyperef = cv_write_ptr_type( cv, sym );
	}
	return;
    } else if ( sym->typekind == TYPE_NONE ) {
	return;
    }

    typelen = ( sym->total_size >= LF_NUMERIC ? sizeof( uint_32 ) : 0 );
    property = ( cv->level ? CVTSP_ISNESTED : 0 );

    /* Count the member fields. If a member's type is unknown, create it! */
    count.cnt = 0;
    count.size = 0;
    count.ofs = 0;
    cv_enum_fields( type, cv_cntproc, cv, &count );

    /* WinDbg wants embedded structs to have a name - else it won't allow to "open" it. */
    namesize = ( sym->name_size ? sym->name_size : 9 );	 /* 9 is sizeof("__unnamed") */

    sym->cvtyperef = cv->currtype++;
    switch ( type->sym.typekind ) {
    case TYPE_UNION:
	size = ( sizeof( struct cv_typerec_union ) + typelen + 1 + namesize + 3 ) & ~3;
	cv->pt = checkflush( cv->types, cv->pt, size, cv->param );
	cv->pt_un->tr.size = size - sizeof(uint_16);
	cv->pt_un->tr.leaf = LF_UNION;
	cv->pt_un->count = count.cnt;
	cv->pt_un->field = cv->currtype++;
	cv->pt_un->property = property;
	tmp = (uint_8 *)&cv->pt_un->length;
	break;
    case TYPE_RECORD:
	property |= CVTSP_PACKED; /* is "packed" */
	/* no break */
    case TYPE_STRUCT:
	size = ( sizeof( struct cv_typerec_structure ) + typelen + 1 + namesize + 3 ) & ~3;
	cv->pt = checkflush( cv->types, cv->pt, size, cv->param );
	cv->pt_st->tr.size = size - sizeof(uint_16);
	cv->pt_st->tr.leaf = LF_STRUCTURE;
	cv->pt_st->count = count.cnt;
	cv->pt_st->field = cv->currtype++;
	cv->pt_st->property = property;
	cv->pt_st->dList = 0;
	cv->pt_st->vshape = 0;
	tmp = (uint_8 *)&cv->pt_st->length;
	break;
    }
    if ( typelen ) {
	((struct leaf32 *)tmp)->leaf = LF_ULONG;
	((struct leaf32 *)tmp)->value32 = sym->total_size;
	tmp += sizeof( struct leaf32 );
    } else {
	*(uint_16 *)tmp = sym->total_size;
	tmp += sizeof( uint_16 );
    }
    SetPrefixName( tmp, sym->name_size ? sym->name : "__unnamed", namesize );

    PadBytes( tmp, cv->types->e.seginfo->CodeBuffer );
    cv->pt += size;

    /* write the fieldlist record */
    cv->pt = checkflush( cv->types, cv->pt, sizeof( struct cv_typerec_fieldlist ), cv->param );
    size = sizeof( struct cv_typerec_fieldlist) + count.size;
    cv->pt_fl->tr.size = size - sizeof(uint_16);
    cv->pt_fl->tr.leaf = LF_FIELDLIST;
    cv->pt += sizeof( struct cv_typerec_fieldlist );

    /* add the struct's members to the fieldlist. */
    count.ofs = 0;
    cv_enum_fields( type, cv_memberproc, cv, &count );
    return;
}

/* write a symbol
 *    cv: debug state
 *   sym: symbol to write
 * the symbol has either state SYM_INTERNAL or SYM_TYPE.
 */

static void cv_write_symbol( dbgcv8 *cv, struct asym *sym )
{
    int	       len;
    unsigned   ofs;
    enum fixup_types rlctype;
    uint_8     Ofssize;
    struct fixup *fixup;
    struct dsym *proc;
    struct dsym *lcl;
    int	       i;
    int	       cnt[2];
    struct     dsym *locals[2];

    Ofssize = GetSymOfssize( sym );
    len = GetCVStructLen( sym, Ofssize );
    cv->ps = checkflush( cv->symbols, cv->ps, 1 + sym->name_size + len, cv->param );

    if ( sym->state == SYM_TYPE ) {
	/* Masm does only generate an UDT for typedefs
	 * if the underlying type is "used" somewhere.
	 * example:
	 * LPSTR typedef ptr BYTE
	 * will only generate an S_UDT for LPSTR if either
	 * "LPSTR" or "ptr BYTE" is used in the source.
	 */
	cv->ps_udt->sr.size = sizeof( struct cv_symrec_udt ) - sizeof(uint_16) + 1 + sym->name_size;
	cv->ps_udt->sr.type = S_UDT;
	/* v2.10: pointer typedefs will now have a cv_typeref */

	if ( sym->cvtyperef ) {
	    cv->ps_udt->type = sym->cvtyperef;
	} else {
	    cv->ps_udt->type = GetTyperef( sym, Ofssize );
	}

	/* Some typedefs won't get a valid type (<name> TYPEDEF PROTO ...).
	 * In such cases just skip the type!
	 */
	if ( cv->ps_udt->type == 0 )
	    return;

	cv->ps += len;
	SetPrefixName( cv->ps, sym->name, sym->name_size );
	return;
    }

    /* rest is SYM_INTERNAL */
    /* there are 3 types of INTERNAL symbols:
     * - numeric constants ( equates, memtype MT_EMPTY )
     * - code labels, memtype == MT_NEAR | MT_FAR
     *	 - procs
     *	 - simple labels
     * - data labels, memtype != MT_NEAR | MT_FAR
     */

    if ( sym->isproc && Options.debug_ext >= CVEX_REDUCED ) { /* v2.10: no locals for -Zi0 */

	proc = (struct dsym *)sym;

	/* for PROCs, scan parameters and locals and create their types. */

	/* scan local symbols */
	locals[0] = proc->e.procinfo->paralist;
	locals[1] = proc->e.procinfo->locallist;
	for ( i = 0; i < 2; i++ ) {
	    cnt[i] = 0;
	    for ( lcl = locals[i]; lcl; lcl = lcl->nextparam ) {
		cv_typeref typeref;
		cnt[i]++;
		typeref = ( lcl->sym.mem_type == MT_PTR ? cv_write_ptr_type( cv, &lcl->sym ) : GetTyperef( &lcl->sym, Ofssize ) );
		if ( lcl->sym.isarray ) {
		    cv_write_array_type( cv, &lcl->sym, typeref, Ofssize );
		    typeref = cv->currtype - 1;
		}
		lcl->sym.ext_idx1 = typeref;
	    }
	}

	cv->ps_p32->sr.size = sizeof( struct cv_symrec_lproc32 ) - sizeof(uint_16) + 1 + sym->name_size;
	cv->ps_p32->sr.type = (sym->ispublic ? S_GPROC32 : S_LPROC32 );
	cv->ps_p32->pParent = 0; /* filled by CVPACK */
	cv->ps_p32->pEnd = 0;	 /* filled by CVPACK */
	cv->ps_p32->pNext = 0;	 /* filled by CVPACK */
	cv->ps_p32->proc_length = sym->total_size;
	cv->ps_p32->debug_start = ((struct dsym *)sym)->e.procinfo->size_prolog;
	cv->ps_p32->debug_end = sym->total_size;
	cv->ps_p32->offset = 0;
	cv->ps_p32->segment = 0;
	cv->ps_p32->proctype = cv->currtype; /* typeref LF_PROCEDURE */
	cv->ps_p32->flags = ( ( sym->mem_type == MT_FAR ? CV_PROCF_FAR : 0 ) | ( proc->e.procinfo->fpo ? CV_PROCF_FPO : 0 ) );
	rlctype = FIX_PTR32;
	ofs = offsetof( struct cv_symrec_lproc32, offset );
	cv_write_type_procedure( cv, sym, cnt[0] );

    } else if ( sym->mem_type == MT_NEAR || sym->mem_type == MT_FAR ) {

	cv->ps_l32->sr.size = sizeof( struct cv_symrec_label32 ) - sizeof(uint_16) + 1 + sym->name_size;
	cv->ps_l32->sr.type = S_LABEL32;
	cv->ps_l32->offset = 0;
	cv->ps_l32->segment = 0;
	cv->ps_l32->flags = ( sym->mem_type == MT_FAR ? CV_PROCF_FAR : 0 );
	rlctype = FIX_PTR32;
	ofs = offsetof( struct cv_symrec_label32, offset );

#if EQUATESYMS
    } else if ( sym->isequate ) {
	cv->ps_con->sr.size = len - sizeof(uint_16) + 1 + sym->name_size;
	cv->ps_con->sr.type = S_CONSTANT;
	cv->ps_con->type = 0;//cv_abs_type.uvalue;
	if ( sym->value >= LF_NUMERIC ) {
	    uint_8 *tmp;
	    cv->ps_con->value = LF_ULONG;
	    tmp = (uint_8 *)&cv->ps_con->value;
	    *(uint_32 *)tmp = sym->value;
	} else {
	    cv->ps_con->value = sym->value;
	}
	cv->ps += len;
	SetPrefixName( cv->ps, sym->name, sym->name_size );
	return;
#endif
    } else {
	/* v2.10: set S_GDATA[16|32] if symbol is public */
	cv_typeref typeref;
	typeref = GetTyperef( sym, Ofssize );

	cv->ps_d32->sr.size = sizeof( struct cv_symrec_ldata32 ) - sizeof(uint_16) + 1 + sym->name_size;
	if ( ( ModuleInfo.cv_opt & CVO_STATICTLS ) && ((struct dsym *)sym->segment)->e.seginfo->clsym &&
	    strcmp( ((struct dsym *)sym->segment)->e.seginfo->clsym->name, "TLS" ) == 0 )
	    cv->ps_d32->sr.type = (sym->ispublic ? S_GTHREAD32 : S_LTHREAD32 );
	else
	    cv->ps_d32->sr.type = (sym->ispublic ? S_GDATA32 : S_LDATA32 );
	cv->ps_d32->offset = 0;
	cv->ps_d32->segment = 0;
	cv->ps_d32->type = typeref;
	rlctype = FIX_PTR32;
	ofs = offsetof( struct cv_symrec_ldata32, offset );

    }
    cv->ps += ofs;
    cv->symbols->e.seginfo->current_loc = cv->symbols->e.seginfo->start_loc + ( cv->ps - cv->base );
    fixup = CreateFixup( sym, FIX_OFF32_SECREL, OPTJ_NONE );
    fixup->locofs = cv->symbols->e.seginfo->current_loc;
    store_fixup( fixup, cv->symbols, (int_32 *)cv->ps );
    fixup = CreateFixup( sym, FIX_SEG, OPTJ_NONE );
    fixup->locofs = cv->symbols->e.seginfo->current_loc + ( rlctype == FIX_PTR32 ? sizeof( int_32 ) : sizeof ( int_16 ) );
    store_fixup( fixup, cv->symbols, (int_32 *)cv->ps );
    cv->ps += len - ofs;

    SetPrefixName( cv->ps, sym->name, sym->name_size );

    /* for PROCs, scan parameters and locals.
     * to mark the block's end, write an ENDBLK item.
     */
    if ( sym->isproc && Options.debug_ext >= CVEX_REDUCED ) { /* v2.10: no locals for -Zi0 */

	/* scan local symbols again */
	for ( i = 0; i < 2 ; i++ ) {
	    for ( lcl = locals[i]; lcl; lcl = lcl->nextparam ) {

		/* FASTCALL register argument? */
		if ( lcl->sym.state == SYM_TMACRO ) {
		    len = sizeof( struct cv_symrec_register );
		    cv->ps = checkflush( cv->symbols, cv->ps, 1 + lcl->sym.name_size + len, cv->param );
		    cv->ps_reg->sr.size = sizeof( struct cv_symrec_register ) - sizeof(uint_16) + 1 + lcl->sym.name_size;
		    cv->ps_reg->sr.type = S_REGISTER;
		    cv->ps_reg->type = lcl->sym.ext_idx1;
		    cv->ps_reg->registr = cv_get_register( &lcl->sym );
		} else {
		    /* v2.11: use S_REGREL if 64-bit or frame reg != [E|BP */
		    if ( Ofssize == USE64 || ( GetRegNo( proc->e.procinfo->basereg ) != 5 )) {
			len = sizeof( struct cv_symrec_regrel32 );
			cv->ps = checkflush( cv->symbols, cv->ps, 1 + lcl->sym.name_size + len, cv->param );
			cv->ps_rr32->sr.size = sizeof( struct cv_symrec_regrel32 ) - sizeof(uint_16) + 1 + lcl->sym.name_size;
			cv->ps_rr32->sr.type = S_REGREL32;
			cv->ps_rr32->offset = lcl->sym.offset ;
			cv->ps_rr32->type = lcl->sym.ext_idx1;
			/* x64 register numbers are different */
			if ( SpecialTable[ proc->e.procinfo->basereg ].cpu == P_64 )
			    cv->ps_rr32->reg = cv_get_x64_regno( proc->e.procinfo->basereg );
			else
			    cv->ps_rr32->reg = GetRegNo( proc->e.procinfo->basereg ) + CV_REG_START32;
		    } else {
			len = sizeof( struct cv_symrec_bprel32 );
			cv->ps = checkflush( cv->symbols, cv->ps, 1 + lcl->sym.name_size + len, cv->param );
			cv->ps_br32->sr.size = sizeof( struct cv_symrec_bprel32 ) - sizeof(uint_16) + 1 + lcl->sym.name_size;
			cv->ps_br32->sr.type = S_BPREL32;
			cv->ps_br32->offset = lcl->sym.offset;
			cv->ps_br32->type = lcl->sym.ext_idx1;
		    }
		}
		lcl->sym.ext_idx1 = 0; /* to be safe, clear the temp. used field */
		cv->ps += len;
		SetPrefixName( cv->ps, lcl->sym.name, lcl->sym.name_size );
	    }
	}

	cv->ps = checkflush( cv->symbols, cv->ps, sizeof( struct cv_symrec_endblk ), cv->param );
	cv->ps_eb->sr.size = sizeof( struct cv_symrec_endblk ) - sizeof(uint_16);
	cv->ps_eb->sr.type = S_ENDBLK;
	cv->ps += sizeof( struct cv_symrec_endblk );
    }
    return;
}

/* Each major portion of DEBUG$S starts with 4 byte type, 4 byte length
 * (in bytes following the length field). Each set is 4-byte aligned with 0s at
 * the end (not included in length).
 */
static int cv_init( dbgcv8 *cv, struct dsym *symbols, struct dsym *types, void *pv )
{
    int i;

    if ((cv->files = MemAlloc( ModuleInfo.g.cnt_fnames * sizeof( cv_file ) )) == NULL)
	return 0;
    cv->base = symbols->e.seginfo->CodeBuffer;
    cv->ps = cv->base;
    cv->symbols = symbols;
    cv->pt = types->e.seginfo->CodeBuffer;
    cv->types = types;
    cv->currtype = 0x1000; /* user-defined types start at 0x1000 */
    cv->level = 0;
    cv->param = pv;
    for( i = 0; i < ModuleInfo.g.cnt_fnames; i++ ) {
	cv->files[i].name = ModuleInfo.g.FNames[i];
	cv->files[i].offset = 0;
    }
    *(uint_32 *)cv->pt = CV_SIGNATURE;
    *(uint_32 *)cv->ps = CV_SIGNATURE;
    cv->pt += sizeof(uint_32);
    cv->ps += sizeof(uint_32);
    return i;
}

/* 0x000000F3: source filename string table
 * 1 byte - 0 (0th filename)
 * 0-terminated filename strings, 1 for each source file
 */
static void cv_write_filename_string_table( dbgcv8 *cv )
{
    int i,o,len;
    uint_8 *p;

    *(uint_32 *)cv->ps = 0x000000F3;
    cv->ps += sizeof(uint_32);
    p = cv->ps;
    cv->ps += sizeof(uint_32) + 1;
    p[4] = '\0';
    for( o = 1, i = 0; i < ModuleInfo.g.cnt_fnames; i++ ) {
	cv->files[i].offset = o;
	len = strlen( cv->files[i].name ) + 1;
	memcpy( cv->ps, cv->files[i].name, len );
	cv->ps += len;
	o += len;
    }
    *(uint_32 *)p = (uint_32)(cv->ps - p - sizeof(uint_32));
    for( ;( cv->ps - cv->base ) & 3; )
	*cv->ps++ = '\0';
}

/* 0x000000F4: source file info
 * for each source file:
 *	 4 bytes - offset of filename in source filename string table
 *	{2 bytes - checksum type/length? (0x0110)
 *	 16 bytes - MD5 checksum of source file} OR
 *	{2 bytes - no checksum (0)}
 *	2 bytes - 0 (padding?)
 */
static void cv_write_source_file_info( dbgcv8 *cv )
{
    int i,o,len;
    uint_8 *p;

    *(uint_32 *)cv->ps = 0x000000F4;
    cv->ps += sizeof(uint_32);
    p = cv->ps;
    cv->ps += sizeof(uint_32);
    for( i = 0; i < ModuleInfo.g.cnt_fnames; i++ ) {
	*(uint_32 *)cv->ps = cv->files[i].offset;
	cv->ps += sizeof(uint_32);
	*(uint_32 *)cv->ps = 0x00000000;
	cv->ps += sizeof(uint_32);
    }
    *(uint_32 *)p = (uint_32)(cv->ps - p - sizeof(uint_32));
}

/* 0x000000F2: line numbers for section
 *   4 bytes - start offset in section (SECREL to section start)
 *   2 bytes - section index (SECTION to section start)
 *   2 bytes - pad/align (0)
 *   4 bytes - section length covered by line number info
 *
 *   followed by one or more source mappings:
 *     4 bytes - offset of source file in source file info table
 *     4 bytes - number of line number pairs
 *     4 bytes - number of bytes this mapping takes, i.e. 12 + pair-count * 8.
 *
 *     followed by pairs of:
 *	 4 bytes - offset in section
 *	 4 bytes - line number; if high bit is set,
 *		   end of statement/breakpointable (?) - e.g. lines containing
 *		   just labels should have line numbers
 */
static void cv_write_line_numbers( dbgcv8 *cv )
{
}

/* 0x000000F1: symbol information
 *   enclosed data per below
 *   (each element starts with 2 byte length, 2 byte type)
 *   basically slightly updated versions of CV5 symbol info with 0-terminated
 *   rather than length-prefixed strings
 */

/* 0x1101 : Name of object file
 *   4 byte signature (0 for asm)
 *   0-terminated object filename
 */
static void cv_write_object_name( dbgcv8 *cv )
{
    char *name = CurrFName[OBJ];
    uint_16 len = strlen( name );
    cv->ps_on->sr.size = sizeof( struct cv_symrec_objname ) - sizeof(uint_16) + 1 + len;
    cv->ps_on->sr.type = CV8_S_OBJNAME;
    cv->ps_on->Signature = 1;
    cv->ps += sizeof( struct cv_symrec_objname );
    SetPrefixName( cv->ps, name, len );
}

/* 0x3c11: creator signature (compile flag)
 *   4 bytes - language (3=Masm)
 *   4 bytes - target processor (0xD0 = AMD64)
 *   4 bytes - flags
 *   4 bytes - version
 *   2 bytes - ?
 *   0-terminated string containing creator name
 *   pairs of 0-terminated strings - keys/values
 *   from CL:
 *	cwd - current working directory
 *	cl - full path of compiler executable
 *	cmd - full args (one long string, double-quoted args if needed)
 *	src - relative path to source (from cwd)
 *	pdb - full path to pdb file
 *   ML doesn't output any pairs
 *   pairs list terminated with two empty strings
 */
static void cv_write_signature( dbgcv8 *cv )
{
    int len = strlen( szCVCompiler );

    cv->ps_cp->sr.size	= sizeof( struct cv_symrec_compile ) - sizeof(uint_16) + 1 + len;
    cv->ps_cp->sr.type	= CV8_S_COMPILE;
    cv->ps_cp->Language = CV_LANG_MASM;
    cv->ps_cp->machine	= CV_MACH_AMD64;
    cv->ps_cp->flags	= 0;
    cv->ps_cp->version	= 0x00C00000; /* v12 ? */
    cv->ps_cp->Reserved = 0;
    cv->ps += sizeof( struct cv_symrec_compile );
    SetPrefixName( cv->ps, szCVCompiler, len );
}

static void cv_write_symbol_information( dbgcv8 *cv )
{
    int i;
    struct asym *sym;
    uint_8 *p;

    *(uint_32 *)cv->ps = 0x000000F1;
    cv->ps += sizeof(uint_32);
    p = cv->ps;
    cv->ps += sizeof(uint_32);

    cv_write_object_name( cv );
    cv_write_signature( cv );

    sym = NULL;
    while ( sym = SymEnum( sym, &i ) ) {
	if ( sym->state == SYM_TYPE && sym->typekind != TYPE_TYPEDEF && sym->cvtyperef == 0 ) {
	    cv_write_type( cv, sym );
	}
    }
    sym = NULL;
    while ( sym = SymEnum( sym, &i ) ) {
	switch ( sym->state ) {
	case SYM_TYPE: /* may create an S_UDT entry in the symbols table */
	    if ( Options.debug_ext < CVEX_NORMAL ) /* v2.10: no UDTs for -Zi0 and -Zi1 */
		break;
	case SYM_INTERNAL:
	    if (
#if EQUATESYMS
		( Options.debug_ext < CVEX_MAX ? sym->isequate : sym->variable )
#else
		sym->isequate
#endif
		|| sym->predefined ) { /* EQUates? */
		break;
	    }
	    cv_write_symbol( cv, sym );
	    break;
	}
    }
    *(uint_32 *)p = (uint_32)(cv->ps - p - sizeof(uint_32));
    for( ;( cv->ps - cv->base ) & 3; )
	*cv->ps++ = '\0';
}

void cv8_write_debug_tables( struct dsym *symbols, struct dsym *types, void *pv )
{
    dbgcv8 cv;

    if ( cv_init( &cv, symbols, types, pv ) == 0 )
	return;

    cv_write_filename_string_table( &cv );
    cv_write_source_file_info( &cv );
    cv_write_line_numbers( &cv );
    cv_write_symbol_information( &cv );

    checkflush( cv.types, cv.pt, SIZE_CV_SEGBUF, cv.param );
    checkflush( cv.symbols, cv.ps, SIZE_CV_SEGBUF, cv.param );
    MemFree(cv.files);
}

#endif
