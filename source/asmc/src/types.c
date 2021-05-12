/****************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
* Description:	STRUCT, UNION, RECORD and TYPEDEF directives.
*
****************************************************************************/

#include <globals.h>
#include <memalloc.h>
#include <parser.h>
#include <segment.h>
#include <proc.h>
#include <input.h>
#include <tokenize.h>
#include <types.h>
#include <expreval.h>
#include <label.h>
#include <listing.h>
#include <fastpass.h>

#define ANYNAME 0
#define TYPEOPT 0
#define MAXRECBITS ( ModuleInfo.Ofssize == USE64 ? 64 : 32 )

struct dsym *CurrStruct;
static struct dsym *redef_struct;
/* text constants for 'Non-benign <x> redefinition' error msg */
static const char szStructure[] = "structure";
static const char szRecord[] = "record";

static const char szNonUnique[] = "NONUNIQUE";

void TypesInit( void )
/********************/
{
    CurrStruct	 = NULL;
    redef_struct = NULL;
}

/* create a SYM_TYPE symbol.
 * <sym> must be NULL or of state SYM_UNDEFINED.
 * <name> and <global> are only used if <sym> is NULL.
 * <name> might be an empty string.
 */

struct asym *CreateTypeSymbol( struct asym *sym, const char *name, bool global )
/******************************************************************************/
{
    struct struct_info *si;

    if ( sym )
	sym_remove_table( &SymTables[TAB_UNDEF], (struct dsym *)sym );
    else
	sym = ( global ? SymCreate( name ) : SymAlloc( name ) );

    if ( sym ) {
	sym->state = SYM_TYPE;
	sym->typekind = TYPE_NONE;
	((struct dsym *)sym)->e.structinfo = si = (struct struct_info *)LclAlloc( sizeof( struct struct_info ) );
	si->head = NULL;
	si->tail = NULL;
	si->alignment = 0;
	si->flags = 0;
    }
    return( sym );
}

/* search a name in a struct's fieldlist */

struct asym *SearchNameInStruct( const struct asym *tstruct, const char *name,
    uint_32 *poffset, int level )
{
    int len = strlen( name );
    struct sfield *fl = ((struct dsym *)tstruct)->e.structinfo->head;
    struct asym *sym = NULL;

    if ( level >= MAX_STRUCT_NESTING ) {
	asmerr( 1007 );
	return( NULL );
    }
    level++;
    for ( ; fl; fl = fl->next ) {
	/* recursion: if member has no name, check if it is a structure
	 and scan this structure's fieldlist then */
	if ( *( fl->sym.name ) == NULLC ) {
	    /* there are 2 cases: an anonymous inline struct ... */
	    if ( fl->sym.state == SYM_TYPE ) {
		if ( sym = SearchNameInStruct( &fl->sym, name, poffset, level ) ) {
		    *poffset += fl->sym.offset;
		    break;
		}
	    /* or an anonymous structured field */
	    } else if ( fl->sym.mem_type == MT_TYPE ) {
		if ( sym = SearchNameInStruct( fl->sym.type, name, poffset, level ) ) {
		    *poffset += fl->sym.offset;
		    break;
		}
	    }
	} else if ( len == fl->sym.name_size && SymCmpFunc( name, fl->sym.name, len ) == 0 ) {
	    sym = &fl->sym;
	    break;
	}
    }
    return( sym );
}

/* check if a struct has changed */

static bool AreStructsEqual( const struct dsym *newstr, const struct dsym *oldstr )
/*********************************************************************************/
{
    struct sfield *fold = oldstr->e.structinfo->head;
    struct sfield *fnew = newstr->e.structinfo->head;

    /* kind of structs must be identical */
    if ( oldstr->sym.typekind != newstr->sym.typekind )
	return( FALSE );

    for ( ; fold; fold = fold->next, fnew = fnew->next ) {
	if ( !fnew ) {
	    return( FALSE );
	}
	/* for global member names, don't check the name if it's "" */
	if ( ModuleInfo.oldstructs && *fnew->sym.name == NULLC )
	    ;
	else if ( 0 != strcmp( fold->sym.name, fnew->sym.name ) ) {
	    return( FALSE );
	}
	if ( fold->sym.offset != fnew->sym.offset ) {
	    return( FALSE );
	}
	if ( fold->sym.total_size != fnew->sym.total_size ) {
	    return( FALSE );
	}
    }
    if ( fnew )
	return( FALSE );
    return( TRUE );
}

/* handle STRUCT, STRUC, UNION directives
 * i = index of directive token
 */
ret_code StructDirective( int i, struct asm_tok tokenarray[] )
/************************************************************/
{
    char *name;
    unsigned alignment;
    uint_32 offset;
    uint_8 typekind = ( tokenarray[i].tokval == T_UNION ? TYPE_UNION : TYPE_STRUCT );
    struct asym *sym;
    struct dsym *dir;

    /* top level structs/unions must have an identifier at pos 0.
     * for embedded structs, the directive must be at pos 0,
     * an identifier is optional then.
     */
    if (( CurrStruct == NULL && i != 1 ) ||
	( CurrStruct != NULL && i != 0 ) ) {
	return( asmerr(2008, tokenarray[i].string_ptr ) );
    }

    alignment = ( 1 << ModuleInfo.fieldalign );

    i++; /* go past STRUCT/UNION */

    if ( i == 1 ) { /* embedded struct? */
	/* scan for the optional name */
#if ANYNAME
	/* the name might be a reserved word!
	 * Masm won't allow those.
	 */
#else
	if ( tokenarray[i].token == T_ID ) {
#endif
	    name = tokenarray[i].string_ptr;
	    i++;
	} else {
	    name = "";
	}
    } else {
	name = tokenarray[0].string_ptr;
    }

    /* get an optional alignment argument: 1,2,4,8,16 or 32 */
    if ( CurrStruct == NULL && tokenarray[i].token != T_FINAL ) {
	int power;
	struct expr opndx;
	/* get the optional alignment parameter.
	 * forward references aren't accepted, but EXPF_NOUNDEF isn't used here!
	 */
	if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, 0 ) != ERROR ) {
	    /* an empty expression is accepted */
	    if ( opndx.kind == EXPR_EMPTY ) {
		;
	    } else if ( opndx.kind != EXPR_CONST ) {
		/* v2.09: better error msg */
		if ( opndx.sym && opndx.sym->state == SYM_UNDEFINED )
		    asmerr( 2006, opndx.sym->name );
		else
		    asmerr( 2026 );
	    } else if( opndx.value > MAX_STRUCT_ALIGN ) {
		asmerr( 2064 );
	    } else {
		for( power = 1; power < opndx.value; power <<= 1 );
		if( power != opndx.value ) {
		    asmerr( 2063, opndx.value );
		} else
		    alignment = opndx.value;
	    }
	}
	/* there might also be the NONUNIQUE parameter */
	if ( tokenarray[i].token == T_COMMA ) {
	    i++;
	    if ( tokenarray[i].token == T_ID &&
		(_stricmp( tokenarray[i].string_ptr, szNonUnique ) == 0 ) ) {
		/* currently NONUNIQUE is ignored */
		asmerr( 8017, szNonUnique );
		i++;
	    }
	}
    }
    if ( tokenarray[i].token != T_FINAL ) {
	return( asmerr(2008, tokenarray[i].tokpos ) );
    }

    /* does struct have a name? */
    if ( *name ) {
	if ( CurrStruct == NULL ) {
	    /* the "top-level" struct is part of the global namespace */
	    sym = SymSearch( name );
	} else {
	    sym = SearchNameInStruct( (struct asym *)CurrStruct, name, &offset, 0 );
	}
    } else {
	sym = NULL;   /* anonymous struct */
    }

    if ( ModuleInfo.list ) {
	if ( CurrStruct )
	    LstWrite( LSTTYPE_STRUCT, CurrStruct->sym.total_size, NULL );
	else
	    LstWrite( LSTTYPE_STRUCT, 0, NULL );
    }

    /* if pass is > 1, update struct stack + CurrStruct.offset and exit */
    if ( Parse_Pass > PASS_1 ) {
	/* v2.04 changed. the previous implementation was insecure.
	 * See also change in data.c, behind CreateStructField().
	 */
	if ( CurrStruct ) {
	    sym = CurrStruct->e.structinfo->tail->sym.type;
	    CurrStruct->e.structinfo->tail = CurrStruct->e.structinfo->tail->next;
	}
	dir = (struct dsym *)sym;
	dir->e.structinfo->tail = dir->e.structinfo->head;
	sym->offset = 0;
	sym->isdefined = TRUE;
	((struct dsym *)sym)->next = CurrStruct;
	CurrStruct = (struct dsym *)sym;
	return( NOT_ERROR );
    }

    if( sym == NULL ) {

	/* embedded or global STRUCT? */
	if ( CurrStruct == NULL )
	    sym = CreateTypeSymbol( NULL, name, TRUE );
	else {
	    /* an embedded struct is split in an anonymous STRUCT type
	     * and a struct field with/without name
	     */
	    sym = CreateTypeSymbol( NULL, name, FALSE );
	    /* v2: don't create the struct field here. First the
	     * structure must be read in ( because of alignment issues
	     */
	    // sym = CreateStructField( name_loc, -1, MT_TYPE, dir, 0 );

	    alignment = CurrStruct->e.structinfo->alignment;
	}

    } else if( sym->state == SYM_UNDEFINED ) {

	/* forward reference */
	CreateTypeSymbol( sym, NULL, CurrStruct == NULL );

    } else if( sym->state == SYM_TYPE && CurrStruct == NULL ) {

	switch ( sym->typekind ) {
	case TYPE_STRUCT:
	case TYPE_UNION:
	    /* if a struct is redefined as a union ( or vice versa )
	     * do accept the directive and just check if the redefinition
	     * is compatible (usually it isn't) */
	    redef_struct = (struct dsym *)sym;
	    sym = CreateTypeSymbol( NULL, name, FALSE );
	    break;
	case TYPE_NONE:	 /* TYPE_NONE is forward reference */
	    break;
	default:
	    return( asmerr( 2005, sym->name ) );
	}

    } else {
	return( asmerr( 2005, sym->name ) );
    }

    sym->offset = 0;
    sym->typekind = typekind;
    dir = (struct dsym *)sym;
    dir->e.structinfo->alignment = alignment;
    dir->e.structinfo->isOpen = TRUE;
    if ( CurrStruct )
	dir->e.structinfo->isInline = TRUE;

    dir->next = CurrStruct;
    CurrStruct = dir;

    return( NOT_ERROR );
}

/* handle ENDS directive when a struct/union definition is active */

ret_code EndstructDirective( int i, struct asm_tok tokenarray[] )
/***************************************************************/
{
    unsigned int size;
    struct dsym *dir;

    dir = CurrStruct; /* cannot be NULL */

    /* if pass is > 1 just do minimal work */
    if ( Parse_Pass > PASS_1 ) {
	CurrStruct->sym.offset = 0;
	size = CurrStruct->sym.total_size;
	CurrStruct = CurrStruct->next;
	if ( CurrStruct )
	    UpdateStructSize( (struct asym *)dir );
	if ( CurrFile[LST] )
	    LstWrite( LSTTYPE_STRUCT, size, dir );
	return( NOT_ERROR );
    }

    /* syntax is either "<name> ENDS" (i=1) or "ENDS" (i=0).
     * first case must be top level (next=NULL), latter case must NOT be top level (next!=NULL)
     */
    if ( ( i == 1 && dir->next == NULL ) ||
	( i == 0 && dir->next != NULL ) ) {
	;
    } else {
	return( asmerr( 1010, i == 1 ? tokenarray[0].string_ptr : "" ) );
    }

    if ( i == 1 ) { /* an global struct ends with <name ENDS> */
	if ( SymCmpFunc( tokenarray[0].string_ptr, dir->sym.name, dir->sym.name_size ) != 0 ) {
	    /* names don't match */
	    return( asmerr( 1010, tokenarray[0].string_ptr ) );
	}
    }

    i++; /* go past ENDS */

    /* v2.07: if ORG was used inside the struct, the struct's size
     * has to be calculated now - there may exist negative offsets.
     */
    if ( dir->e.structinfo->OrgInside ) {
	struct sfield *f;
	int_32 min = 0;
	for ( f = dir->e.structinfo->head; f; f = f->next )
	    if ( f->sym.offset < min )
		min = f->sym.offset;
	dir->sym.total_size = dir->sym.total_size - min;
    }

    /* Pad bytes at the end of the structure. */
#if 1
    /* v2.02: this is to be done in any case, whether -Zg is set or not */
    if ( dir->e.structinfo->alignment > 1 ) {
	size = dir->sym.max_mbr_size;
	if ( size == 0 )
	    size++;
	if ( size > dir->e.structinfo->alignment )
	    size = dir->e.structinfo->alignment;
	dir->sym.total_size = (dir->sym.total_size + size - 1) & (-size);
    }
#endif
    dir->e.structinfo->isOpen = FALSE;
    dir->sym.isdefined = TRUE;

    /* if there's a negative offset, size will be wrong! */
    size = dir->sym.total_size;

    /* reset offset, it's just used during the definition */
    dir->sym.offset = 0;

    CurrStruct = dir->next;
    if ( i == 1 ) {
	struct asym *sym;
	sym = CreateStructField( -1, NULL, *dir->sym.name ? dir->sym.name : NULL, MT_TYPE, &dir->sym, dir->sym.total_size );
	sym->total_size = dir->sym.total_size;
	dir->sym.name = ""; /* the type becomes anonymous */
	dir->sym.name_size = 0;
    }

    if ( CurrFile[LST] ) {
	LstWrite( LSTTYPE_STRUCT, size, dir );
    }
#if 1
    /* to allow direct structure access */
    switch ( dir->sym.total_size ) {
    case 1:  dir->sym.mem_type = MT_BYTE;   break;
    case 2:  dir->sym.mem_type = MT_WORD;   break;
    case 4:  dir->sym.mem_type = MT_DWORD;  break;
    case 6:  dir->sym.mem_type = MT_FWORD;  break;
    case 8:  dir->sym.mem_type = MT_QWORD;  break;
    default: dir->sym.mem_type = MT_EMPTY;
    }
#endif
    /* reset redefine */
    if ( CurrStruct == NULL ) {
	if ( redef_struct ) {
	    if ( AreStructsEqual( dir, redef_struct) == FALSE ) {
		asmerr( 2007, szStructure, dir->sym.name );
	    }
	    SymFree( (struct asym *)dir );
	    redef_struct = NULL;
	}
    } else {

	if ( dir->sym.max_mbr_size > CurrStruct->sym.max_mbr_size )
	    CurrStruct->sym.max_mbr_size = dir->sym.max_mbr_size;

	UpdateStructSize( (struct asym *)dir );
    }
    if ( tokenarray[i].token != T_FINAL ) {
	return( asmerr(2008, tokenarray[i].string_ptr ) );
    }
    return( NOT_ERROR );
}

/* v2.06: new function to check fields of anonymous struct members */

static ret_code CheckAnonymousStruct( struct dsym *type )
/*******************************************************/
{
    uint_32 disp;
    struct asym	 *sym;
    struct sfield *f;

    for ( f = type->e.structinfo->head; f; f = f->next ) {
	if ( *f->sym.name ) {
	    sym = SearchNameInStruct((struct asym *)CurrStruct, f->sym.name, &disp, 0 );
	    if ( sym ) {
		return( asmerr( 2005, sym->name ) );
	    }
	} else if ( f->sym.type ) {
	    struct dsym *stype = (struct dsym *)f->sym.type;
	    if ( stype->sym.typekind == TYPE_STRUCT ||
		stype->sym.typekind == TYPE_UNION ) {
		if ( CheckAnonymousStruct( stype ) == ERROR )
		    return( ERROR );
	    }
	}
    }
    return( NOT_ERROR );
}

/* CreateStructField() - creates a symbol of state SYM_STRUCT_FIELD.
 * this function is called in pass 1 only.
 * - loc: initializer index location, -1 means no initializer (is an embedded struct)
 * - name: field name, may be NULL
 * - mem_type: mem_type of item
 * - vartype: user-defined type of item if memtype is MT_TYPE
 * - size: size of type - used for alignment only
 */
//struct asym *CreateStructField( int loc, struct asm_tok tokenarray[], const char *name, enum memtype mem_type, struct asym *vartype, uint_32 size )
struct asym *CreateStructField( int loc, struct asm_tok tokenarray[], const char *name, unsigned char mem_type, struct asym *vartype, uint_32 size )
/*************************************************************************************************************************************************/
{
    int_32 offset;
    int i;
    int len;
    uint_32 disp;
    char *init;
    struct struct_info *si;
    struct sfield *f;
    struct asym	 *gsym;

    si = CurrStruct->e.structinfo;
    offset = CurrStruct->sym.offset;

    if ( name ) {
	struct asym  *sym;
	len = strlen( name );
	if( len > MAX_ID_LEN ) {
	    asmerr(2043);
	    return( NULL );
	}
	sym = SearchNameInStruct((struct asym *)CurrStruct, name, &disp, 0 );
	if ( sym ) {
	    asmerr(2005, sym->name );
	    return( NULL );
	}
    } else {
	/* v2.06: check fields of anonymous struct member */
	if ( vartype &&
	    ( vartype->typekind == TYPE_STRUCT ||
	     vartype->typekind == TYPE_UNION ) ) {
	    CheckAnonymousStruct( (struct dsym *)vartype );
	}
	name = "";
	len = 0;
    }

    if ( loc != -1 ) {

	init = StringBufferEnd;
	for ( i = loc+1; tokenarray[i].token != T_FINAL; i++ ) {
	    if ( tokenarray[i].token == T_ID ) {
		struct asym *sym2 = SymSearch( tokenarray[i].string_ptr );
		if ( sym2 && sym2->variable ) {
		    if ( sym2->predefined && sym2->sfunc_ptr )
			sym2->sfunc_ptr( sym2, NULL );
		    myltoa( sym2->uvalue, init, ModuleInfo.radix, sym2->value3264 < 0, TRUE );
		    init += strlen( init );
		    *init++= ' ';
		    continue;
		}
	    }
	    memcpy( init, tokenarray[i].tokpos, tokenarray[i+1].tokpos - tokenarray[i].tokpos );
	    init += tokenarray[i+1].tokpos - tokenarray[i].tokpos;
	}
	*init = NULLC;
	f = (struct sfield *)LclAlloc( sizeof( struct sfield ) + ( init - StringBufferEnd ) );
	memset( f, 0, sizeof( struct sfield ) );
	strcpy( f->ivalue, StringBufferEnd );

    } else {
	f = (struct sfield *)LclAlloc( sizeof( struct sfield ) );
	memset( f, 0, sizeof( struct sfield ) );
	f->ivalue[0] = NULLC;
    }

    /* create the struct field symbol */

    f->sym.name_size = len;
    if ( len ) {
	f->sym.name = (char *)LclAlloc( len + 1 );
	memcpy( f->sym.name, name, len );
	f->sym.name[len] = NULLC;
    } else
	f->sym.name = "";
    f->sym.state = SYM_STRUCT_FIELD;
    f->sym.list = ModuleInfo.cref;
    f->sym.isdefined = TRUE;
    f->sym.mem_type = mem_type;
    f->sym.type = vartype;
    f->next = NULL;

    if( si->head == NULL ) {
	si->head = si->tail = f;
    } else {
	si->tail->next = f;
	si->tail = f;
    }

#if 1
    /* v2.0: for STRUCTs, don't use the struct's size for alignment calculations,
     * instead use the size of the "max" member!
     */
    if ( mem_type == MT_TYPE &&
	( vartype->typekind == TYPE_STRUCT ||
	 vartype->typekind == TYPE_UNION ) ) {
	size = vartype->max_mbr_size;
    }
#endif
    /* align the field if an alignment argument was given */
    if ( si->alignment > 1 ) {
	/* if it's the first field to add, use offset of the parent's current field */
	{
	    if ( si->alignment < size )
		offset = (offset + (si->alignment - 1)) & ( - si->alignment);
	    else if ( size )
		offset = (offset + (size - 1)) & (-size);
	}
	/* adjust the struct's current offset + size.
	 The field's size is added in UpdateStructSize()
	 */
	if ( CurrStruct->sym.typekind != TYPE_UNION ) {
	    CurrStruct->sym.offset = offset;
	    if ( offset > CurrStruct->sym.total_size )
		CurrStruct->sym.total_size = offset;
	}
    }
    if ( size > CurrStruct->sym.max_mbr_size ) {
	CurrStruct->sym.max_mbr_size = size;
    }
    f->sym.offset = offset;

    /* if -Zm is on, create a global symbol */
    if ( ModuleInfo.oldstructs == TRUE && *name != NULLC ) {
	gsym  = SymLookup( name );
	    if ( gsym->state == SYM_UNDEFINED )
		gsym->state = SYM_STRUCT_FIELD;
	    if ( gsym->state == SYM_STRUCT_FIELD ) {
		struct dsym *dir;
		gsym->mem_type = mem_type;
		gsym->type = vartype;
		gsym->offset = offset; /* added v2.0 */
		/* v2.01: must be the full offset.
		 * (there's still a problem if alignment is > 1!)
		 */
		for ( dir = CurrStruct->next; dir; dir = dir->next )
		    gsym->offset += dir->sym.offset;
		gsym->isdefined = TRUE;
	    }
    }

    return( &f->sym );
}

/* called by AlignDirective() if ALIGN/EVEN has been found inside
 * a struct. It's already verified that <value> is a power of 2.
 */
ret_code AlignInStruct( int value )
/*********************************/
{
    if ( CurrStruct->sym.typekind != TYPE_UNION ) {
	int offset;
	offset = CurrStruct->sym.offset;
	offset = (offset + (value - 1)) & (-value);
	CurrStruct->sym.offset = offset;
	if ( offset > CurrStruct->sym.total_size )
	    CurrStruct->sym.total_size = offset;
    }
    return( NOT_ERROR );
}

/* called by data_dir() when a structure field has been created.
 */
void UpdateStructSize( struct asym *sym )
/***************************************/
{
    if ( CurrStruct->sym.typekind == TYPE_UNION ) {
	if ( sym->total_size > CurrStruct->sym.total_size )
	    CurrStruct->sym.total_size = sym->total_size;
    } else {
	CurrStruct->sym.offset += sym->total_size;
	if ( CurrStruct->sym.offset > (int_32)CurrStruct->sym.total_size )
	    CurrStruct->sym.total_size = CurrStruct->sym.offset;
    }
    return;
}

/* called if ORG occurs inside STRUCT/UNION definition */

ret_code SetStructCurrentOffset( int_32 offset )
/**********************************************/
{
    if ( CurrStruct->sym.typekind == TYPE_UNION ) {
	return( asmerr( 2200 ) );
    }
    CurrStruct->sym.offset = offset;
    /* if an ORG is inside the struct, it cannot be instanced anymore */
    CurrStruct->e.structinfo->OrgInside = TRUE;
    if ( offset > (int_32)CurrStruct->sym.total_size )
	CurrStruct->sym.total_size = offset;

    return( NOT_ERROR );
}

/* get a qualified type.
 * Used by
 * - TYPEDEF
 * - PROC/PROTO params and LOCALs
 * - EXTERNDEF
 * - EXTERN
 * - LABEL
 * - ASSUME for GPRs
 */
ret_code GetQualifiedType( int *pi, struct asm_tok tokenarray[], struct qualified_type *pti )
/*******************************************************************************************/
{
    int		    type;
    int		    tmp;
    //enum memtype    mem_type;
    unsigned char    mem_type;
    int		    i = *pi;
    int		    distance = FALSE;
    struct asym	    *sym;

    /* convert PROC token to a type qualifier */
    for ( tmp = i; tokenarray[tmp].token != T_FINAL && tokenarray[tmp].token != T_COMMA; tmp++ )
	if ( tokenarray[tmp].token == T_DIRECTIVE && tokenarray[tmp].tokval == T_PROC ) {
	    tokenarray[tmp].token = T_STYPE;
	    /* v2.06: avoid to use ST_PROC */
	    tokenarray[tmp].tokval = ( ( SIZE_CODEPTR & ( 1 << ModuleInfo.model ) ) ? T_FAR : T_NEAR );
	}
    /* with NEAR/FAR, there are several syntax variants allowed:
     * 1. NEARxx | FARxx
     * 2. PTR NEARxx | FARxx
     * 3. NEARxx | FARxx PTR [<type>]
     */
    /* read qualified type */
    for ( type = ERROR; tokenarray[i].token == T_STYPE || tokenarray[i].token == T_BINARY_OPERATOR; i++ ) {
	if ( tokenarray[i].token == T_STYPE ) {
	    tmp = tokenarray[i].tokval;
	    if ( type == ERROR )
		type = tmp;
	    mem_type = GetMemtypeSp( tmp );
	    if ( mem_type == MT_FAR || mem_type == MT_NEAR ) {
		if ( distance == FALSE ) {
		    uint_8 Ofssize = GetSflagsSp( tmp );
		    pti->is_far = ( mem_type == MT_FAR );
		    if ( Ofssize != USE_EMPTY )
			pti->Ofssize = Ofssize;
		    distance = TRUE;
		} else if ( tokenarray[i-1].tokval != T_PTR )
		    break;
	    } else {
		if ( pti->is_ptr )
		    pti->ptr_memtype = mem_type;
		i++;
		break;
	    }
	} else if ( tokenarray[i].tokval == T_PTR ) {
	    type = EMPTY;
	    pti->is_ptr++;
	} else
	    break;
    }

    if ( type == EMPTY ) {
	if ( tokenarray[i].token == T_ID && tokenarray[i-1].tokval == T_PTR ) {
	    pti->symtype = SymSearch( tokenarray[i].string_ptr );
	    if ( pti->symtype == NULL || pti->symtype->state == SYM_UNDEFINED )
		pti->symtype = CreateTypeSymbol( pti->symtype, tokenarray[i].string_ptr, TRUE );
	    else if ( pti->symtype->state != SYM_TYPE ) {
		return( asmerr( 2004, tokenarray[i].string_ptr ) );
	    } else {
		sym = pti->symtype;
		/* if it's a typedef, simplify the info */
		if ( sym->typekind == TYPE_TYPEDEF ) {
		    pti->is_ptr	    += sym->is_ptr;
		    if ( sym->is_ptr == 0 ) {
			pti->ptr_memtype = ( sym->mem_type != MT_TYPE ? sym->mem_type : MT_EMPTY );
			if ( distance == FALSE && pti->is_ptr == 1 &&
			    ( sym->mem_type == MT_NEAR ||
			     sym->mem_type == MT_PROC ||
			     sym->mem_type == MT_FAR ) )
			    pti->is_far = sym->isfar;
			    if ( sym->Ofssize != USE_EMPTY )
				pti->Ofssize = sym->Ofssize;
		    } else {
			pti->ptr_memtype = sym->ptr_memtype;
			if ( distance == FALSE && pti->is_ptr == 1 ) {
			    pti->is_far = sym->isfar;
			    if ( sym->Ofssize != USE_EMPTY )
				pti->Ofssize = sym->Ofssize;
			}
		    }
		    if ( sym->mem_type == MT_TYPE )
			pti->symtype  = sym->type;
		    else {
			pti->symtype  = sym->target_type;
		    }
		}
	    }
	    i++;
	}
    }

    if( type == ERROR ) {
	if ( tokenarray[i].token != T_ID ) {
	    if ( tokenarray[i].token == T_FINAL || tokenarray[i].token == T_COMMA )
		asmerr( 2175 );
	    else {
		asmerr(2008, tokenarray[i].string_ptr );
		i++;
	    }
	    return( ERROR );
	}
	pti->symtype = SymSearch( tokenarray[i].string_ptr );
	if( pti->symtype == NULL || pti->symtype->state != SYM_TYPE ) {
	    if ( pti->symtype == NULL || pti->symtype ->state == SYM_UNDEFINED )
		asmerr( 2006, tokenarray[i].string_ptr );
	    else
		asmerr( 2004, tokenarray[i].string_ptr );
	    return( ERROR );
	}
	sym = pti->symtype;
	if ( sym->typekind == TYPE_TYPEDEF ) {
	    pti->mem_type = sym->mem_type;
	    pti->is_far	  = sym->isfar;
	    pti->is_ptr	  = sym->is_ptr;
	    pti->Ofssize  = sym->Ofssize;
	    pti->size	  = sym->total_size;
	    pti->ptr_memtype = sym->ptr_memtype;
	    if ( sym->mem_type == MT_TYPE )
		pti->symtype  = sym->type;
	    else {
		pti->symtype  = sym->target_type;
	    }
	} else {
	    pti->mem_type = MT_TYPE;
	    pti->size = sym->total_size;
	}
	i++;
    } else {
	if ( pti->is_ptr )
	    pti->mem_type = MT_PTR;
	else
	    pti->mem_type = GetMemtypeSp( type );
	if ( pti->mem_type == MT_PTR )
	    pti->size = SizeFromMemtype( (unsigned char)(pti->is_far ? MT_FAR : MT_NEAR), pti->Ofssize, NULL );
	else
	    pti->size = SizeFromMemtype( pti->mem_type, pti->Ofssize, NULL );
    }
    *pi = i;
    return( NOT_ERROR );
}

/* TYPEDEF directive. Syntax is:
 * <type name> TYPEDEF [proto|[far|near [ptr]]<qualified type>]
 */

int CreateType( int i, struct asm_tok tokenarray[], char *name, struct asym **pp )
{
    struct asym *sym;
    struct qualified_type ti;

    sym = SymSearch( name );
    if ( sym == NULL || sym->state == SYM_UNDEFINED ) {
	sym = CreateTypeSymbol( sym, name, TRUE );
	if ( sym == NULL )
	    return( ERROR );
#if TYPEOPT
	/* release the structinfo data extension */
	((struct dsym *)sym)->e.structinfo = NULL;
#endif
    } else {
	/* MASM allows to have the TYPEDEF included multiple times */
	/* but the types must be identical! */
	if ( ( sym->state != SYM_TYPE ) ||
	    ( sym->typekind != TYPE_TYPEDEF &&
	     sym->typekind != TYPE_NONE ) ) {
	    return( asmerr( 2005, sym->name ) );
	}
    }
    if ( pp )
	*pp = sym;

    sym->isdefined = TRUE;
    if ( pp == NULL && Parse_Pass > PASS_1 )
	return( NOT_ERROR );
    sym->typekind = TYPE_TYPEDEF;

    /* PROTO is special */
    if ( tokenarray[i].token == T_DIRECTIVE && tokenarray[i].tokval == T_PROTO ) {
	struct dsym *proto;  /* create a PROTOtype item without name */
	/* v2.04: added check if prototype is set already */
	if ( sym->target_type == NULL && sym->mem_type == MT_EMPTY ) {
	    proto = (struct dsym *)CreateProc( NULL, "", SYM_TYPE );
	} else if ( sym->mem_type == MT_PROC ) {
	    proto = (struct dsym *)sym->target_type;
	} else {
	    return( asmerr( 2004, sym->name ) );
	}
	i++;
	if( ParseProc( proto, i, tokenarray, FALSE, ModuleInfo.langtype ) == ERROR )
	    return( ERROR );
	sym->mem_type = MT_PROC;
	sym->Ofssize = proto->sym.seg_ofssize;
	/* v2.03: set value of field total_size (previously was 0) */
	sym->total_size = ( 2 << sym->Ofssize );
	if( proto->sym.mem_type != MT_NEAR ) {
	    sym->isfar = TRUE; /* v2.04: added */
	    sym->total_size += 2;
	}
	sym->target_type = (struct asym *)proto;
	return( NOT_ERROR );
    }

    ti.size = 0;
    ti.is_ptr = 0;
    ti.is_far = FALSE;
    ti.mem_type = MT_EMPTY;
    ti.ptr_memtype = MT_EMPTY;
    ti.symtype = NULL;
    ti.Ofssize = ModuleInfo.Ofssize;

    /* "empty" type is ok for TYPEDEF */
    if ( tokenarray[i].token == T_FINAL || tokenarray[i].token == T_COMMA )
	;
    else if ( GetQualifiedType( &i, tokenarray, &ti ) == ERROR )
	return( ERROR );

    /* if type did exist already, check for type conflicts
     * v2.05: this code has been rewritten */
    if ( sym->mem_type != MT_EMPTY ) {
	struct asym *to;
	struct asym *tn;
	char oo;
	char on;
	for( tn = ti.symtype; tn && tn->type; tn = tn->type );
	to = ( sym->mem_type == MT_TYPE ) ? sym->type : sym->target_type;
	for( ; to && to->type; to = to->type );
	oo = ( sym->Ofssize != USE_EMPTY ) ? sym->Ofssize : ModuleInfo.Ofssize;
	on = ( ti.Ofssize != USE_EMPTY ) ? ti.Ofssize : ModuleInfo.Ofssize;
	if ( ti.mem_type != sym->mem_type ||
	    ( ti.mem_type == MT_TYPE && tn != to ) ||
	    ( ti.mem_type == MT_PTR &&
	     ( ti.is_far != sym->isfar ||
	      on != oo ||
	      ti.ptr_memtype != sym->ptr_memtype ||
	      tn != to ))) {
	    return( asmerr( 2004, name ) );
	}
    }

    sym->mem_type = ti.mem_type;
    sym->Ofssize = ti.Ofssize;
    sym->total_size = ti.size;
    sym->is_ptr = ti.is_ptr;
    sym->isfar = ti.is_far;
    if ( ti.mem_type == MT_TYPE )
	sym->type = ti.symtype;
    else
	sym->target_type = ti.symtype;
    sym->ptr_memtype = ti.ptr_memtype;

    if ( pp == NULL && tokenarray[i].token != T_FINAL ) {
	return( asmerr(2008, tokenarray[i].string_ptr ) );
    }
    return( NOT_ERROR );
}

int TypedefDirective( int i, struct asm_tok tokenarray[] )
{
    if( i != 1 ) {
	return( asmerr(2008, tokenarray[i].string_ptr ) );
    }
    i++;
    return( CreateType( i, tokenarray, tokenarray[0].string_ptr, NULL ) );
}

/* RECORD directive
 * syntax: <label> RECORD <bitfield_name>:<size>[,...]
 * defines a RECORD type (state=SYM_TYPE).
 * the memtype will be MT_BYTE, MT_WORD, MT_DWORD [, MT_QWORD in 64-bit].
 */

ret_code RecordDirective( int i, struct asm_tok tokenarray[] )
{
    char *name;
    struct asym *sym;
    struct dsym *newr;
    struct dsym *oldr = NULL;
    struct sfield *f;
    int cntBits;
    int define;
    int len;
    int redef_err;
    int count;
    int name_loc;
    int init_loc;
    struct expr opndx;
    uint_32 offset;
#if 1
    if ( i != 1 ) {
	return( asmerr(2008, tokenarray[i].string_ptr ) );
    }
    name = tokenarray[0].string_ptr;
    sym = SymSearch( name );
#else
    if (( CurrStruct == NULL && i != 1 ) ||
	( CurrStruct != NULL && i != 0 ) ) {
	return( asmerr(2008, tokenarray[i].string_ptr ) );
    }
    if ( i == 0 )
	name = "";
    else
	name = tokenarray[0].string_ptr;

    if ( *name ) {
	if ( CurrStruct == NULL )
	    sym = SymSearch( name );
	else
	    sym = SearchNameInStruct( (struct asym *)CurrStruct, name, &offset, 0 );
    } else {
	sym = NULL;
    }
#endif
    if ( sym == NULL || sym->state == SYM_UNDEFINED ) {
	sym = CreateTypeSymbol( sym, name, TRUE );
    } else if ( sym->state == SYM_TYPE &&
	       ( sym->typekind == TYPE_RECORD ||
	       sym->typekind == TYPE_NONE ) ) {
	/* v2.04: allow redefinition of record and forward references.
	 * the record redefinition may have different initial values,
	 * but those new values are IGNORED! ( Masm bug? )
	 */
	if ( Parse_Pass == PASS_1 && sym->typekind == TYPE_RECORD ) {
	    oldr = (struct dsym *)sym;
	    sym = CreateTypeSymbol( NULL, name, FALSE );
	    redef_err = 0;
	}
    } else {
	return( asmerr( 2005, name ) );
    }
    sym->isdefined = TRUE;

    if ( Parse_Pass > PASS_1 )
	return( NOT_ERROR );

    newr = (struct dsym *)sym;
    newr->sym.typekind = TYPE_RECORD;

    i++; /* go past RECORD */

    cntBits = 0; /* counter for total of bits in record */
    /* parse bitfields */
    do {
	if ( tokenarray[i].token != T_ID ) {
	    asmerr(2008, tokenarray[i].string_ptr );
	    break;
	}
	len = strlen( tokenarray[i].string_ptr );
	if( len > MAX_ID_LEN ) {
	    asmerr(2043);
	    break;
	}
	name_loc = i;
	i++;
	if ( tokenarray[i].token != T_COLON ) {
	    asmerr( 2065, "" );
	    break;
	}
	i++;
	/* get width */
	if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, 0 ) == ERROR )
	    break;
	if ( opndx.kind != EXPR_CONST ) {
	    asmerr( 2026 );
	    opndx.value = 1;
	}
	if ( opndx.value == 0 ) {
	    asmerr( 2172, tokenarray[name_loc].string_ptr );
	    break;
	} else if ( ( opndx.value + cntBits ) > MAXRECBITS ) {
	    asmerr( 2089, tokenarray[name_loc].string_ptr );
	    break;
	}
	count = 0;
	/* is there an initializer? ('=') */
	if ( tokenarray[i].token == T_DIRECTIVE &&
	    tokenarray[i].dirtype == DRT_EQUALSGN ) {
	    i++;
	    for( init_loc = i; tokenarray[i].token != T_FINAL && tokenarray[i].token != T_COMMA; i++ );
	    /* no value? */
	    if ( init_loc == i ) {
		asmerr(2008, tokenarray[name_loc].tokpos );
		break;
	    }
	    /* v2.09: initial values of record redefinitions are ignored! */
	    if ( oldr == NULL )
		count = tokenarray[i].tokpos - tokenarray[init_loc].tokpos;
	}
	/* record field names are global! (Masm design flaw) */
	sym = SymSearch( tokenarray[name_loc].string_ptr );
	define = TRUE;
	if ( oldr ) {
	    if ( sym == NULL ||
		sym->state != SYM_STRUCT_FIELD ||
		sym->mem_type != MT_BITS ||
		sym->total_size != opndx.value ) {
		asmerr( 2007, szRecord, tokenarray[name_loc].string_ptr );
		redef_err++;
		define = FALSE; /* v2.06: added */
	    }
	} else {
	    if ( sym ) {
		asmerr( 2005, sym->name );
		break;
	    }
	}

	if ( define ) { /* v2.06: don't add field if there was an error */
	    cntBits += opndx.value;
	    f = (struct sfield *)LclAlloc( sizeof( struct sfield ) + count );
	    memset( f, 0, sizeof( struct sfield ) );
	    f->sym.name_size = len;
	    f->sym.name = (char *)LclAlloc( len + 1 );
	    memcpy( f->sym.name, tokenarray[name_loc].string_ptr, len + 1 );
	    f->sym.list = ModuleInfo.cref;
	    f->sym.state = SYM_STRUCT_FIELD;
	    f->sym.mem_type = MT_BITS;
	    f->sym.total_size = opndx.value;
	    if ( !oldr ) {
		SymAddGlobal( &f->sym );
	    }
	    f->next = NULL;
	    f->ivalue[0] = NULLC;
	    if( newr->e.structinfo->head == NULL ) {
		newr->e.structinfo->head = newr->e.structinfo->tail = f;
	    } else {
		newr->e.structinfo->tail->next = f;
		newr->e.structinfo->tail = f;
	    }
	    if ( count ) {
		memcpy( f->ivalue, tokenarray[init_loc].tokpos, count );
		f->ivalue[count] = NULLC;
	    }
	}

	if ( i < Token_Count ) {
	    if ( tokenarray[i].token != T_COMMA || tokenarray[i+1].token == T_FINAL ) {
		asmerr(2008, tokenarray[i].tokpos );
		break;
	    }
	    i++;
	}

    } while ( i < Token_Count );

    /* now calc size in bytes and set the bit positions */

    if ( cntBits > 16 ) {
	if ( cntBits > 32 ) {
	    newr->sym.total_size = sizeof( uint_64 );
	    newr->sym.mem_type = MT_QWORD;
	} else {
	    newr->sym.total_size = sizeof( uint_32 );
	    newr->sym.mem_type = MT_DWORD;
	}
    } else if ( cntBits > 8 ) {
	newr->sym.total_size = sizeof( uint_16 );
	newr->sym.mem_type = MT_WORD;
    } else {
	newr->sym.total_size = sizeof( uint_8 );
	newr->sym.mem_type = MT_BYTE;
    }
    /* if the BYTE/WORD/DWORD isn't used fully, shift bits to the right! */
    /* set the bit position */
    for ( f = newr->e.structinfo->head; f; f = f->next ) {
	cntBits = cntBits - f->sym.total_size;
	f->sym.offset = cntBits;
    }
    if ( oldr ) {
	if ( redef_err > 0 ||
	    AreStructsEqual( newr, oldr ) == FALSE )
	    asmerr( 2007, szRecord, newr->sym.name );
	/* record can be freed, because the record's fields are global items.
	 * And initial values of the new definition are ignored!
	 */
	SymFree( (struct asym *)newr );
    }
    return( NOT_ERROR );
}

