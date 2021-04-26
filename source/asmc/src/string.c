/****************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
* Description:	string macro processing routines.
*
* functions:
* - CatStrDir	 handle CATSTR	 directive ( also TEXTEQU )
* - SetTextMacro handle EQU	 directive if expression is text
* - AddPredefinedText() for texts defined by .MODEL
* - SubStrDir	 handle SUBSTR	 directive
* - SizeStrDir	 handle SIZESTR	 directive
* - InStrDir	 handle INSTR	 directive
* - CatStrFunc	 handle @CatStr	 function
* - SubStrFunc	 handle @SubStr	 function
* - SizeStrFunc	 handle @SizeStr function
* - InStrFunc	 handle @InStr	 function
*
****************************************************************************/

#include <globals.h>
#include <memalloc.h>
#include <parser.h>
#include <expreval.h>
#include <equate.h>
#include <input.h>
#include <tokenize.h>
#include <macro.h>
#include <condasm.h>
#include <fastpass.h>
#include <listing.h>
#include <hllext.h>
#include <quadmath.h>

extern int list_pos;

struct str_item {
int	count;
int	index;
void *	next;
char	unicode;
char	flags;
char	string[1];
};

int GetTypeId( char *, struct asm_tok[] );

static void GetCurrentSegment( char *buffer )
{
    if ( ModuleInfo.currseg )
	strcat( strcpy( buffer, ModuleInfo.currseg->sym.name ), " segment" );
    else
	strcpy( buffer, ".code" );
    if ( is_linequeue_populated() )
	RunLineQueue();
}


static int ParseCString( char *lbuf, char *buffer, char *string,
	char **pStringOffset, char *pUnicode )
{
	char *sbuf; /* "binary" string */
	char Unicode;
	char *src,*des,*sbp;
	char *p;
	char a,b;
	int  ch;
	long dw;
	struct str_item *sp;

	sbuf = MemAlloc( ModuleInfo.g.max_line_len );
	sbuf[0] = NULLC;

	src = string;
	des = buffer;
	sbp = sbuf;

	Unicode = 0;
	if ( ModuleInfo.xflag & OPT_WSTRING )
	    Unicode = 1;

	if ( *src == 'L' && *(src+1) == '"' ) {

	    ModuleInfo.xflag |= OPT_LSTRING;
	    Unicode = 1;
	    src++;
	}

	*pUnicode = Unicode;
	*des++ = *src++;

	while ( *src ) {

	    ch = *src;
	    if ( ch == '\\' ) {

		/* escape char */

		ch = *++src;
		switch ( ch ) {
		case 'a':
		    *sbp = 7;
		    dw = 0x20372C22; // <",7 >
		    goto case_format;
		case 'b':
		    *sbp = 8;
		    dw = 0x20382C22; // <",8 >
		    goto case_format;
		case 'f':
		    *sbp = 12;
		    dw = 0x32312C22; // <",12>
		    goto case_format;
		case 'n':
		    *sbp = 10;
		    dw = 0x30312C22; // <",10>
		    goto case_format;
		case 't':
		    *sbp = 9;
		    dw = 0x20392C22; // <",9 >
		case_format:
		    a = (char)dw;
		    b = (char)(dw >> 8);
		    p = &buffer[1];
		    if ((p == des && a == *(des-1)) || (a == *(des-1) && b == *(des-2))) {
			des--;
			*(short *)des = (short)(dw >> 16);
			des += 2;
		    } else {
			*(long *)des = dw;
			des += 4;
		    }
		    if ( *(des-1) == ' ' )
			des--;
		    *des++ = 0x2C;
		    *des   = 0x22;
		    break;
		case 'r':
		    *sbp = 13;
		    dw = 0x33312C22; /* <",13>" */
		    goto case_format;
		case 'v':
		    *sbp = 11;
		    dw = 0x31312C22; /* <",11>" */
		    goto case_format;
		case 0x27:
		    *sbp = 39;
		    dw = 0x39332C22; /* <",39>" */
		    goto case_format;
		case 'x':
		    ch = *(src+1);
		    if ( islxdigit(ch) ) {
			src++;
			a = (ch & 0xDF);
			if ( a > 0x19 )
			    a -= 'A' - 0x1A;
			a -= 0x10;
			ch = *(src+1);
			if ( islxdigit(ch) ) {
			    src++;
			    b = (ch & 0xDF);
			    if ( b > 0x19 )
				b -= 'A' - 0x1A;
			    b -= 0x10;
			    a = (a << 4) | b;
			}
			*des = a;
			*sbp = a;
		    } else {
			*des = 'x';
			*sbp = 'x';
		    }
		    break;

		case '0':
		    p = des-1;
		    if ( p == buffer ) {
			des--;
			*des++ = '0';
			*des++ = ',';
		    } else {
			*des++ = '"';
			*des++ = ',';
			*des++ = '0';
			*des++ = ',';
		    }
		    *des = '"';
		    *sbp = '\0';
		    break;

		case '"': /* <",'"',"> */
		    p = &buffer[1];

		    /* db '"',xx",'"',0 */

		    if ((p == des && *(des-1) == '"') ||
		       (*(des-1) == '"' && *(des-2) == ',')) {
			des--;
		    } else {
			*des++ = '"';
			*des++ = ',';
		    }
		    *des++ = 0x27;
		    *des++ = 0x22;
		    *des++ = 0x27;
		    *des++ = 0x2C;
		    ch = '"';
		default:
		    *des = ch;
		    *sbp = ch;
		    break;
		}
	    } else if ( ch == '"' ) {
		src++;
		p = src;
		while ( *p == ' ' || *p == 9 ) p++;
		if ( *p == 'L' )
		    p++;
		if ( *p == '"' ) { /* "string1" "string2" */
		    src = p;
		    des--;
		    sbp--;
		} else {
		    *des++ = '"';
		    break;
		}
	    } else {
		*des = ch;
		*sbp = ch;
	    }
	    des++;
	    sbp++;
	    if ( *src )
		src++;
	}

	*des = NULLC;
	*sbp = NULLC;
	if ( *(des-3) == 0x2C && *(des-2) == 0x22 && *(des-1) == 0x22 )
	    *(des-3) = NULLC;
	*pStringOffset = src;

	dw = strlen( sbuf );
	sp = ModuleInfo.g.StrStack;
	ch = 0;
	/*
	 * Search for a dublicated string in the string stack
	 */
	while ( sp ) {

	    if ( sp->count >= dw && sp->unicode == Unicode ) {

		p = sp->string;
		if ( sp->count > dw ) {

		    p += sp->count;
		    p -= dw;
		}

		if ( !strcmp( sbuf, p ) ) {

		    dw = p - sp->string;
		    if ( dw ) {
			if ( Unicode )
			    dw += dw;
			sprintf( lbuf, "DS%04X[%d]", sp->index, dw );
		    } else {
			sprintf( lbuf, "DS%04X", sp->index );
		    }
		    MemFree(sbuf);
		    return 0;
		}
	    }
	    ch++;
	    sp = sp->next;
	}
	/*
	 * Create a new string
	 */
	sprintf( lbuf, "DS%04X", ch );
	sp = LclAlloc( dw + sizeof(struct str_item) );
	sp->count = dw;
	sp->index = ch;
	sp->unicode = Unicode;
	sp->flags = 0;
	sp->next = ModuleInfo.g.StrStack;
	ModuleInfo.g.StrStack = sp;
	strcpy( sp->string, sbuf );
	MemFree(sbuf);
	return 1;
}

int GenerateCString( int i, struct asm_tok tokenarray[] )
{
	int rc = 0;
	int c,x,e;
	int equal;
	int NewString;
	char *p,*q;
	char b_label[64];
	char b_seg[64];
	char *b_line;
	char *b_data;
	char *buffer;
	char *StringOffset;
	int brackets = 0;
	char Unicode;
	char a,b;
	int lineflags;

	buffer = MemAlloc( ModuleInfo.g.max_line_len * 3 );
	b_data = buffer + ModuleInfo.g.max_line_len;
	b_line = b_data + ModuleInfo.g.max_line_len;

	if ( ModuleInfo.strict_masm_compat == 0 ) {
	    /*
	     * need "quote"
	     * proc( "", ( ... ), "" )
	     */
	    e = 0;
	    c = 0;
	    while ( tokenarray[i].token != T_FINAL ) {

		p = tokenarray[i].string_ptr;
		a = p[0];
		b = p[1];
		if ( a == '"' || (a == 'L' && b == '"') ) {
		    e = 1;
		    break;
		} else if ( a == ')' ) {
		    if ( !brackets )
			break;
		    brackets--;
		} else if ( a == '(' ) {
		    brackets++;
		    c++; /* need one open bracket */
		}
		i++;
	    }
	    if ( e == 0 || c == 0 ) {
		MemFree( buffer );
		return 0;
	    }

	    rc++;
	    p = LineStoreCurr->line;
	    q = strcpy( b_line, p );
	    *p = ';';
	    equal = strcmp( q, tokenarray[0].tokpos );
	    lineflags = ModuleInfo.line_flags;

	    while ( tokenarray[i].token != T_FINAL ) {

		p = tokenarray[i].tokpos;
		if ( *p == '"' || *p == 'L' && *(p+1) == '"' ) {

		    NewString = ParseCString( b_label, buffer, p, &StringOffset, &Unicode );

		    if ( equal ) {

			/* strip "string" from LineStoreCurr */

			x = StringOffset - p;
			q = memcpy( b_data, p, x );
			q[x] = NULLC;

			if ( (p = strstr( b_line, q )) ) {

			    q = p;
			    p += x;
			    while ( *p == ' ' || *p == 9 )
				p++;
			    if ( *p != ',' && *p != ')' ) {
				if ( (p = strrchr( q + 1, '"' )) )
				    p++;
			    }
			    if ( p ) {
				strcpy( b_data, p );
				strcpy( q, "addr " );
				strcat( q, b_label );
				strcat( q, b_data );
			    }
			}
		    }

		    if ( NewString ) {

			if ( buffer[0] == '"' && buffer[1] == '"' && buffer[2] == 0 ) {
			    if ( Unicode )
				p = " %s dw 0";
			    else
				p = " %s sbyte 0";
			    sprintf( b_data, p, b_label );
			} else {
			    if ( Unicode )
				p = " %s dw %s,0";
			    else
				p = " %s sbyte %s,0";
			    sprintf( b_data, p, b_label, buffer );
			}

		    } else if ( ModuleInfo.list ) {

			ModuleInfo.line_flags &= ~LOF_LISTED;
		    }

		    *tokenarray[i].tokpos = NULLC;
		    strcat( strcpy( buffer, tokenarray[0].tokpos ), "addr " );
		    strcat( buffer, b_label );

		    while ( *StringOffset == ' ' || *StringOffset == 9 ) StringOffset++;
		    if ( *StringOffset )
			strcat( strcat( buffer, " " ), StringOffset );

		    if ( NewString ) {

			GetCurrentSegment( b_seg );
			AddLineQueue( ".data" );
			AddLineQueue( b_data );
			AddLineQueue( "_DATA ends" );
			AddLineQueue( b_seg );
			InsertLineQueue();
		    }
		    strcpy( CurrSource, buffer );
		    Token_Count = Tokenize( CurrSource, 0, tokenarray, TOK_DEFAULT );
		} else if ( *p == ')' ) {
		    if ( !brackets )
			break;
		    brackets--;
		    if ( !brackets )
			break;
		} else if ( *p == '(' ) {
		    brackets++;
		}
		i++;
	    }

	    if ( equal == 0 ) {

		StoreLine( CurrSource, list_pos, 0 );
	    } else {
		e = ModuleInfo.GeneratedCode;
		ModuleInfo.GeneratedCode = 0;
		StoreLine( b_line, list_pos, 0 );
		ModuleInfo.GeneratedCode = e;
	   }
	   ModuleInfo.line_flags = lineflags;
	}
	MemFree( buffer );
	return rc;
}

int CString( char *buffer, struct asm_tok tokenarray[] )
{
	char *string;
	char *cursrc;
	char dlabel[32];
	char *StringOffset;
	char Unicode;
	char *p;
	int equal;
	int i = 0;
	int rc = 0;
	int d, x;
	struct asym *sym;
	struct expr opnd;
	struct str_item *sp;

	equal = _stricmp( tokenarray[0].string_ptr, "@CStr" );

	if ( equal ) {

	    while ( tokenarray[i].token != T_FINAL ) {
		if ( !_stricmp(tokenarray[i].string_ptr, "@CStr") )
		    break;
		i++;
	    }
	    if ( tokenarray[i].token == T_FINAL && tokenarray[i+1].token == T_OP_BRACKET )
		i++;
	    else if ( tokenarray[i].token != T_FINAL )
		i++;
	    else
		i = 0;
	}

	if ( tokenarray[i].token == T_OP_BRACKET &&
	     tokenarray[i+1].token == T_NUM &&
	     tokenarray[i+2].token == T_CL_BRACKET ) {

	     /* v2.31 - return label[-value] */

	    i++;

	    _atoow( &opnd, tokenarray[i].string_ptr, tokenarray[i].numbase, tokenarray[i].itemlen );

	    /* the number must be 32-bit */

	    if ( opnd.hlvalue ) {

		asmerr( 2156 );
		return 0;
	    }

	    for ( x = opnd.value, sp = ModuleInfo.g.StrStack; x && sp; x--, sp = sp->next );

	    if ( sp == NULL ) {

		asmerr( 2156 );
		return 0;
	    }

	    sprintf(buffer, "DS%04X", sp->index);
	    return 1;
	}

	string = MemAlloc( ModuleInfo.g.max_line_len * 3 );
	cursrc = string + ModuleInfo.g.max_line_len;

	while ( tokenarray[i].token != T_FINAL ) {

	    p = tokenarray[i].tokpos;
	    /*
	     * v2.28 - .data --> .const
	     *
	     * - dq @CStr(L"CONST")
	     * - dq @CStr(ID)
	     */
	    if ( tokenarray[i].token == T_ID && tokenarray[i-1].token == T_OP_BRACKET ) {

		if ( ( sym = SymFind( tokenarray[i].string_ptr ) ) != NULL ) {

		    if ( sym->string_ptr[0] == '"' ||
			( sym->string_ptr[0] == 'L' && sym->string_ptr[1] == '"' ) )
			p = sym->string_ptr;
		}
	    }

	    if ( *p == '"' || ( p[0] == 'L' && p[1] == '"' ) ) {

		rc = ParseCString( dlabel, string, p, &StringOffset, &Unicode );

		if ( equal ) {
		    if ( ModuleInfo.Ofssize != USE64 )
			strcpy( buffer, "offset " );
		    strcat( buffer, dlabel );
		} else {

		    /* v2.24 skip return value if @CStr is first token */

		    dlabel[0] = ' ';
		    dlabel[1] = NULLC;
		}

		if ( rc ) {

		    if ( string[0] == '"' && string[1] == '"' && string[2] == NULLC ) {

			if ( Unicode )
			    p = " %s dw 0";
			else
			    p = " %s sbyte 0";
			sprintf( cursrc, p, dlabel );
		    } else {
			if ( Unicode )
			    p = " %s dw %s,0";
			else
			    p = " %s sbyte %s,0";
			sprintf( cursrc, p, dlabel, string );
		    }

		    /* v2.24 skip .data/.code if already in .data segment */

		    if ( is_linequeue_populated() )
			RunLineQueue();

		    x = 0;
		    p = ModuleInfo.currseg->sym.name;
		    if ( _stricmp( p, "_DATA" ) ) {
			x++;
			AddLineQueue( ".data" );
		    } else if ( equal ) {
			x = 2;
			AddLineQueue(".const");
		    }
		    AddLineQueue( cursrc );
		    if ( x ) {
			if ( !_stricmp( p, "CONST" ) )
			    AddLineQueue(".const");
			else if ( x == 2 )
			    AddLineQueue(".data");
			else
			    AddLineQueue(".code");
		    }
		    InsertLineQueue();
		}
		rc = 1;
		break;
	    }
	    i++;
	}
	MemFree( string );
	return rc;
}

int CreateFloat(int size, struct expr *opnd, char *buffer)
{
  char segm[64];
  char temp[128];
  struct expr opc;
  struct flt_item *si;
  struct flt_item *fp;
  int q;

    opc.llvalue = opnd->llvalue;
    opc.hlvalue = opnd->hlvalue;

    switch ( size ) {
    case 4:
	if ( opnd->mem_type == MT_REAL4 )
	    break;
	opc.flags1 = 0;
	if ( opnd->chararray[15] & 0x80 ) {
	    opc.negative = 1;
	    opc.chararray[15] &= 0x7F;
	}
	__cvtq_ss(&opc.chararray[0], opnd);
	if ( opc.negative )
	    opc.chararray[3] |= 0x80;
	break;
    case 8:
	if ( opnd->mem_type == MT_REAL8 )
	    break;
	opc.flags1 = 0;
	if ( opnd->chararray[15] & 0x80 ) {
	    opc.negative = 1;
	    opc.chararray[15] &= 0x7F;
	}
	__cvtq_sd(&opc, opnd);
	if ( opc.negative )
	    opc.chararray[7] |= 0x80;
	break;
    case 10:
	__cvtq_ld(&opc, opnd);
	opc.hlvalue &= 0xFFFF;
    case 16:
	break;
    }

    for ( q = 0, si = ModuleInfo.g.FltStack; si; q++, si = si->next ) {
	if ( size == si->count ) {
	    if (memcmp(&opc, si->string, size) == 0 ) {
		sprintf( buffer, "F%04X", si->index );
		return 1;
	    }
	}
    }

    sprintf( buffer, "F%04X", q );
    if ( Parse_Pass == PASS_1 ) {

	fp = LclAlloc( sizeof(struct flt_item ) + 16 );
	fp->index = q;
	fp->count = size;
	fp->next = ModuleInfo.g.FltStack;
	ModuleInfo.g.FltStack = fp;
	fp->string = (char*)&fp[1];
	memcpy(fp->string, &opc, 16);

	GetCurrentSegment( segm );

	AddLineQueue( ".data" );
	if ( size == 10 )
	    size = 16;
	AddLineQueueX( "align %d", size );

	switch ( size ) {
	case 4:
	    sprintf( temp, "%s dd 0x%08X", buffer, opc.value );
	    break;
	case 8:
	    sprintf( temp, "%s dq 0x%08X%08X", buffer, opc.hvalue, opc.value );
	    break;
	case 16:
	    AddLineQueueX( "%s label real%d", buffer, size );
	    sprintf( temp, "oword 0x%016" I64_SPEC "X%016" I64_SPEC "X", opc.hlvalue, opc.llvalue );
	    break;
	}
	AddLineQueue( temp );
	AddLineQueue( "_DATA ends" );
	AddLineQueue( segm );
	InsertLineQueue();
    }
    return 0;
}

/* generic parameter names. In case the parameter name is
 * displayed in an error message ("required parameter %s missing")
 * v2.05: obsolete
 */
//static const char * parmnames[] = {"p1","p2","p3"};

int TextItemError( struct asm_tok *item )
/***************************************/
{
    if ( item->token == T_STRING && *item->string_ptr == '<' ) {
	return( asmerr( 2045 ) );
    }
    /* v2.05: better error msg if (text) symbol isn't defined */
    if ( item->token == T_ID ) {
	struct asym *sym = SymSearch( item->string_ptr );
	if ( sym == NULL || sym->state == SYM_UNDEFINED ) {
	    return( asmerr( 2006, item->string_ptr ) );
	}
    }
    return( asmerr( 2051 ) );
}

/* CATSTR directive.
 * defines a text equate
 * syntax <name> CATSTR [<string>,...]
 * TEXTEQU is an alias for CATSTR
 */

ret_code CatStrDir( int i, struct asm_tok tokenarray[] )
/******************************************************/
{
    struct asym *sym;
    int count;
    char *p;
    /* struct expr opndx; */

    i++; /* go past CATSTR/TEXTEQU */

    /* v2.08: don't copy to temp buffer */
    //*StringBufferEnd = NULLC;
    /* check correct syntax and length of items */
    for ( count = 0; i < Token_Count; ) {
	if ( tokenarray[i].token != T_STRING || tokenarray[i].string_delim != '<' ) {
	    return( TextItemError( &tokenarray[i] ) );
	}
	/* v2.08: using tokenarray.stringlen is not quite correct, since some chars
	 * are stored in 2 bytes (!) */
	if ( ( count + tokenarray[i].stringlen ) >= MAX_LINE_LEN ) {
	    return( asmerr( 2041 ) );
	}
	/* v2.08: don't copy to temp buffer */
	count = count + tokenarray[i].stringlen;
	i++;
	if ( ( tokenarray[i].token != T_COMMA ) &&
	    ( tokenarray[i].token != T_FINAL ) ) {
	    return( asmerr(2008, tokenarray[i].string_ptr ) );
	}
	i++;
    }

    sym = SymSearch( tokenarray[0].string_ptr );
    if ( sym == NULL ) {
	sym = SymCreate( tokenarray[0].string_ptr );
    } else if( sym->state == SYM_UNDEFINED ) {
	/* v2.01: symbol has been used already. Using
	 * a textmacro before it has been defined is
	 * somewhat problematic.
	 */
	sym_remove_table( &SymTables[TAB_UNDEF], (struct dsym *)sym );
	SkipSavedState(); /* further passes must be FULL! */
	/* v2.21: changed from 8016 to 6005 */
	asmerr( 6005, sym->name );
    } else if( sym->state != SYM_TMACRO ) {
	/* it is defined as something else, get out */
	return( asmerr( 2005, sym->name ) );
    }


    sym->state = SYM_TMACRO;
    sym->isdefined = TRUE;
    /* v2.08: reuse string space if fastmem is on */
    if ( sym->total_size < ( count+1 ) ) {
	sym->string_ptr = (char *)LclAlloc( count + 1 );
	sym->total_size = count + 1;
    }
    /* v2.08: don't use temp buffer */
    for ( i = 2, p = sym->string_ptr; i < Token_Count; i += 2 ) {
	memcpy( p, tokenarray[i].string_ptr, tokenarray[i].stringlen );
	p += tokenarray[i].stringlen;
    }
    *p = NULLC;

    if ( ModuleInfo.list )
	LstWrite( LSTTYPE_TMACRO, 0, sym );

    return( NOT_ERROR );
}

/*
 * used by EQU if the value to be assigned to a symbol is text.
 * - sym:   text macro name, may be NULL
 * - name:  identifer ( if sym == NULL )
 * - value: value of text macro ( original line, BEFORE expansion )
 */
struct asym *SetTextMacro( struct asm_tok tokenarray[], struct asym *sym, const char *name, const char *value )
/*************************************************************************************************************/
{
    int count;

    if ( sym == NULL )
	sym = SymCreate( name );
    else if ( sym->state == SYM_UNDEFINED ) {
	sym_remove_table( &SymTables[TAB_UNDEF], (struct dsym *)sym );
	/* the text macro was referenced before being defined.
	 * this is valid usage, but it requires a full second pass.
	 * just simply deactivate the fastpass feature for this module!
	 */
	SkipSavedState();
	/* v2.21: changed from 8016 to 6005 */
	asmerr( 6005, sym->name );
    } else if ( sym->state != SYM_TMACRO ) {
	asmerr( 2005, name );
	return( NULL );
    }

    sym->state = SYM_TMACRO;
    sym->isdefined = TRUE;

    if ( tokenarray[2].token == T_STRING && tokenarray[2].string_delim == '<' ) {

	/* the simplest case: value is a literal. define a text macro! */
	/* just ONE literal is allowed */
	if ( tokenarray[3].token != T_FINAL ) {
	    asmerr(2008, tokenarray[3].tokpos );
	    return( NULL );
	}
	value = tokenarray[2].string_ptr;
	count = tokenarray[2].stringlen;
    } else {
	/*
	 * the original source is used, since the tokenizer has
	 * deleted some information.
	 */
	//while ( isspace( *value ) ) value++; /* probably obsolete */
	count = strlen( value );
	/* skip trailing spaces */
	for ( ; count; count-- )
	    if ( islspace( *( value + count - 1 ) ) == FALSE )
		break;
    }
    if ( sym->total_size < ( count + 1 ) ) {
	sym->string_ptr = (char *)LclAlloc( count + 1 );
	sym->total_size = count + 1;
    }
    memcpy( sym->string_ptr, value, count );
    *(sym->string_ptr + count) = NULLC;

    return( sym );
}

/* create a (predefined) text macro.
 * used to create @code, @data, ...
 * there are 2 more locations where predefined text macros may be defined:
 * - assemble.c, add_cmdline_tmacros()
 * - symbols.c, SymInit()
 * this should be changed eventually.
 */
struct asym *AddPredefinedText( const char *name, const char *value )
/*******************************************************************/
{
    struct asym *sym;

    /* v2.08: ignore previous setting */
    if ( NULL == ( sym = SymSearch( name ) ) )
	sym = SymCreate( name );
    sym->state = SYM_TMACRO;
    sym->isdefined = TRUE;
    sym->predefined = TRUE;
    sym->string_ptr = (char *)value;
    /* to ensure that a new buffer is used if the string is modified */
    sym->total_size = 0;
    return( sym );
}

/* SubStr()
 * defines a text equate.
 * syntax: name SUBSTR <string>, pos [, size]
 */
ret_code SubStrDir( int i, struct asm_tok tokenarray[] )
/******************************************************/
{
    struct asym		*sym;
    char		*name;
    char		*p;
    int			pos;
    int			size;
    int			cnt;
    bool		chksize;
    struct expr		opndx;

    /* at least 5 items are needed
     * 0  1	 2	3 4    5   6
     * ID SUBSTR SRC_ID , POS [, LENGTH]
     */
    name = tokenarray[0].string_ptr;

    i++; /* go past SUBSTR */

    /* third item must be a string */

    if ( tokenarray[i].token != T_STRING || tokenarray[i].string_delim != '<' ) {
	return( TextItemError( &tokenarray[i] ) );
    }
    p = tokenarray[i].string_ptr;
    cnt = tokenarray[i].stringlen;

    i++;

    if ( tokenarray[i].token != T_COMMA ) {
	return( asmerr( 2008, tokenarray[i].tokpos ) );
    }
    i++;

    /* get pos, must be a numeric value and > 0 */
    /* v2.11: flag NOUNDEF added - no forward ref possible */

    if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, EXPF_NOUNDEF ) == ERROR ) {
	return( ERROR );
    }

    /* v2.04: "string" constant allowed as second argument */
    if ( opndx.kind != EXPR_CONST ) {
	return( asmerr( 2026 ) );
    }

    /* pos is expected to be 1-based */
    pos = opndx.value;
    if ( pos <= 0 ) {
	return( asmerr( 2090 ) );
    }
    if ( tokenarray[i].token != T_FINAL ) {
	if ( tokenarray[i].token != T_COMMA ) {
	    return( asmerr( 2008, tokenarray[i].tokpos ) );
	}
	i++;
	if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, EXPF_NOUNDEF ) == ERROR ) {
	    return( ERROR );
	}
	if ( opndx.kind != EXPR_CONST ) {
	    return( asmerr( 2026 ) );
	}
	size = opndx.value;
	if ( tokenarray[i].token != T_FINAL ) {
	    return( asmerr(2008, tokenarray[i].string_ptr ) );
	}
	if ( size < 0 ) {
	    return( asmerr( 2092 ) );
	}
	chksize = TRUE;
    } else {
	size = -1;
	chksize = FALSE;
    }
    if ( pos > cnt ) {
	return( asmerr( 2091, pos ) );
    }
    if ( chksize && (pos+size-1) > cnt )  {
	return( asmerr( 2093 ) );
    }
    p += pos - 1;
    if ( size == -1 )
	size = cnt - pos + 1;

    sym = SymSearch( name );

    /* if we've never seen it before, put it in */
    if( sym == NULL ) {
	sym = SymCreate( name );
    } else if( sym->state == SYM_UNDEFINED ) {
	/* it was referenced before being defined. This is
	 * a bad idea for preprocessor text items, because it
	 * will require a full second pass!
	 */
	sym_remove_table( &SymTables[TAB_UNDEF], (struct dsym *)sym );
	SkipSavedState();
	/* v2.21: changed from 8016 to 6005 */
	asmerr( 6005, sym->name );
    } else if( sym->state != SYM_TMACRO ) {
	/* it is defined as something incompatible, get out */
	return( asmerr( 2005, sym->name ) );
    }

    sym->state = SYM_TMACRO;
    sym->isdefined = TRUE;

    if ( sym->total_size < ( size + 1 ) ) {
	sym->string_ptr = (char *)LclAlloc ( size + 1 );
	sym->total_size = size + 1;
    }
    memcpy( sym->string_ptr, p, size );
    *(sym->string_ptr + size) = NULLC;

    LstWrite( LSTTYPE_TMACRO, 0, sym );

    return( NOT_ERROR );
}

/* SizeStr()
 * defines a numeric variable which contains size of a string
 */
ret_code SizeStrDir( int i, struct asm_tok tokenarray[] )
/*******************************************************/
{
    struct asym *sym;
    int sizestr;

    if ( i != 1 ) {
	return( asmerr(2008, tokenarray[i].string_ptr ) );
    }
    if ( tokenarray[2].token != T_STRING || tokenarray[2].string_delim != '<' ) {
	return( TextItemError( &tokenarray[2] ) );
    }
    if ( Token_Count > 3 ) {
	return( asmerr(2008, tokenarray[3].string_ptr ) );
    }

    sizestr = tokenarray[2].stringlen;

    if ( sym = CreateVariable( tokenarray[0].string_ptr, sizestr ) ) {
	LstWrite( LSTTYPE_EQUATE, 0, sym );
	return( NOT_ERROR );
    }
    return( ERROR );

}

/* InStr()
 * defines a numeric variable which contains position of substring.
 * syntax:
 * name INSTR [pos,]string, substr
 */
ret_code InStrDir( int i, struct asm_tok tokenarray[] )
/*****************************************************/
{
    struct asym *sym;
    int sizestr;
    int j;
    /* int commas; */
    char *src;
    char *p;
    char *q;
    char *string1;
    struct expr opndx;
    int start = 1;
    int strpos;

    if ( i != 1) {
	return( asmerr(2008, tokenarray[i].string_ptr ) );
    }

    i++; /* go past INSTR */

    if ( tokenarray[i].token != T_STRING || tokenarray[i].string_delim != '<' ) {
	/* v2.11: flag NOUNDEF added - no forward reference accepted */
	if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, EXPF_NOUNDEF ) == ERROR )
	    return( ERROR );
	if ( opndx.kind != EXPR_CONST ) {
	    return( asmerr( 2026 ) );
	}
	start = opndx.value;
	if ( start <= 0 ) {
	    /* v2.05: don't change the value. if it's invalid, the result
	     * is to be 0. Emit a level 3 warning instead.
	     */
	    asmerr( 7001 );
	}
	if ( tokenarray[i].token != T_COMMA ) {
	    return( asmerr( 2008, tokenarray[i].tokpos ) );
	}
	i++; /* skip comma */
    }

    if ( tokenarray[i].token != T_STRING || tokenarray[i].string_delim != '<' ) {
	return( TextItemError( &tokenarray[i] ) );
    }

    /* to compare the strings, the "visible" format is needed, since
     * the possible '!' operators inside the strings is optional and
     * must be ignored.
     */
    //src = StringBufferEnd;
    //sizestr = GetLiteralValue( src, tokenarray[i].string_ptr );
    src = tokenarray[i].string_ptr;
    sizestr = tokenarray[i].stringlen;

    if ( start > sizestr ) {
	return( asmerr( 2091, start ) );
    }
    p = src + start - 1;

    i++;
    if ( tokenarray[i].token != T_COMMA ) {
	return( asmerr( 2008, tokenarray[i].tokpos ) );
    }
    i++;

    if ( tokenarray[i].token != T_STRING || tokenarray[i].string_delim != '<' ) {
	return( TextItemError( &tokenarray[i] ) );
    }
    q = tokenarray[i].string_ptr;
    j = tokenarray[i].stringlen;
    i++;
    if ( tokenarray[i].token != T_FINAL ) {
	return( asmerr(2008, tokenarray[i].string_ptr ) );
    }

    strpos = 0;
    if ( ( start > 0 ) && ( sizestr >= j ) && j && ( string1 = strstr( p, q ) ))
	strpos = string1 - src + 1;

    if ( sym = CreateVariable( tokenarray[0].string_ptr, strpos ) ) {
	LstWrite( LSTTYPE_EQUATE, 0, sym );
	return ( NOT_ERROR );
    }
    return( ERROR );
}

/* internal @CatStr macro function
 * syntax: @CatStr( literal [, literal ...] )
 */

static ret_code CatStrFunc( struct macro_instance *mi, char *buffer, struct asm_tok tokenarray[] )
/************************************************************************************************/
{
    int i;
    char *p;

    for ( p = mi->parm_array[0]; mi->parmcnt; mi->parmcnt-- ) {
	i = strlen( p );
	memcpy( buffer, p, i );
	p = GetAlignedPointer( p, i );
	buffer += i;
    }
    *buffer = NULLC;
    return( NOT_ERROR );
}


static ret_code TypeIdFunc( struct macro_instance *mi, char *buffer, struct asm_tok tokenarray[] )
{
    if ( GetTypeId( buffer, tokenarray ) == 0 )
	strcpy( buffer, mi->parm_array[0] );
    return( NOT_ERROR );
}

/* internal @CStr macro function
 * syntax:  @CStr( "\tstring\n" )
 */
static ret_code CStringFunc( struct macro_instance *mi, char *buffer, struct asm_tok tokenarray[] )
/************************************************************************************************/
{
    if ( CString( buffer, tokenarray ) == 0 )
	strcpy( buffer, mi->parm_array[0] );
    return( NOT_ERROR );
}

/* convert string to a number.
 * used by @SubStr() for arguments 2 and 3 (start and size),
 * and by @InStr() for argument 1 ( start )
 */

static ret_code GetNumber( char *string, int *pi, struct asm_tok tokenarray[] )
/*****************************************************************************/
{
    struct expr opndx;
    int i;
    int last;

    last = Tokenize( string, Token_Count+1, tokenarray, TOK_RESCAN );
    i = Token_Count+1;
    if( EvalOperand( &i, tokenarray, last, &opndx, EXPF_NOUNDEF ) == ERROR ) {
	return( ERROR );
    }
    if( opndx.kind != EXPR_CONST || tokenarray[i].token != T_FINAL ) {
	return( asmerr(2008, string ) );
    }
    *pi = opndx.value;
    return( NOT_ERROR );
}

/* internal @InStr macro function
 * syntax: @InStr( [num], literal, literal )
 * the result is returned as string in current radix
 */
static ret_code InStrFunc( struct macro_instance *mi, char *buffer, struct asm_tok tokenarray[] )
/***********************************************************************************************/
{
    int pos = 1;
    char *p;
    uint_32 found;

    /* init buffer with "0" */
    *buffer = '0';
    *(buffer+1) = NULLC;

    if ( mi->parm_array[0] ) {
	if ( GetNumber( mi->parm_array[0], &pos, tokenarray ) == ERROR )
	    return( ERROR );
	if ( pos == 0 ) {
	    /* adjust index 0. Masm also accepts 0 (and any negative index),
	     * but the result will always be 0 then */
	    pos++;
	}
    }

    if ( pos > strlen( mi->parm_array[1] ) ) {
	return( asmerr( 2091, pos ) );
    }
    /* v2.08: if() added, empty searchstr is to return 0 */
    if ( *(mi->parm_array[2]) != NULLC ) {
	p = strstr( mi->parm_array[1] + pos - 1, mi->parm_array[2] );
	if ( p ) {
	    found = p - mi->parm_array[1] + 1;
	    myltoa( found, buffer, ModuleInfo.radix, FALSE, TRUE );
	}
    }

    return( NOT_ERROR );
}

/* internal @SizeStr macro function
 * syntax: @SizeStr( literal )
 * the result is returned as string in current radix
 */
static ret_code SizeStrFunc( struct macro_instance *mi, char *buffer, struct asm_tok tokenarray[] )
/*************************************************************************************************/
{
    if ( mi->parm_array[0] )
	myltoa( strlen( mi->parm_array[0] ), buffer, ModuleInfo. radix, FALSE, TRUE );
    else {
	buffer[0] = '0';
	buffer[1] = NULLC;
    }
    return( NOT_ERROR );
}

/* internal @SubStr macro function
 * syntax: @SubStr( literal, num [, num ] )
 */

static ret_code SubStrFunc( struct macro_instance *mi, char *buffer, struct asm_tok tokenarray[] )
/************************************************************************************************/
{
    int pos;
    int size;
    char *src = mi->parm_array[0];

    if ( GetNumber( mi->parm_array[1], &pos, tokenarray ) == ERROR )
	return( ERROR );

    if ( pos <= 0 ) {
	/* Masm doesn't check if index is < 0;
	 * might cause an "internal assembler error".
	 * v2.09: negative index no longer silently changed to 1.
	 */
	if ( pos ) {
	    return( asmerr( 2091, pos ) );
	}
	pos = 1;
    }

    size = strlen( src );
    if ( pos > size ) {
	return( asmerr( 2091, pos ) );
    }

    size = size - pos + 1;

    if ( mi->parm_array[2] ) {
	int sizereq;
	if ( GetNumber( mi->parm_array[2], &sizereq, tokenarray ) == ERROR )
	    return( ERROR );
	if ( sizereq < 0 ) {
	    return( asmerr( 2092 ) );
	}
	if ( sizereq > size ) {
	    return( asmerr( 2093 ) );
	}
	size = sizereq;
    }
    memcpy( buffer, src + pos - 1, size );
    *(buffer+size) = NULLC;

    return( NOT_ERROR );
}

/* string macro initialization
 * this proc is called once per module
 */
void StringInit( void )
/*********************/
{
    int i;
    struct dsym *macro;

    /* add @TypeId() macro func */

    macro = CreateMacro( "typeid" );
    macro->sym.isdefined = TRUE;
    macro->sym.predefined = TRUE;
    macro->sym.func_ptr = TypeIdFunc;
    macro->sym.isfunc = TRUE;
    macro->e.macroinfo->parmcnt = 2;
    macro->e.macroinfo->parmlist = (struct mparm_list *)LclAlloc( sizeof( struct mparm_list )  * 2 );
    macro->e.macroinfo->parmlist[0].deflt = NULL;
    macro->e.macroinfo->parmlist[0].required = FALSE;
    macro->e.macroinfo->parmlist[1].deflt = NULL;
    macro->e.macroinfo->parmlist[1].required = FALSE;

    /* add @CStr() macro func */

    macro = CreateMacro( "@CStr" );
    macro->sym.isdefined = TRUE;
    macro->sym.predefined = TRUE;
    macro->sym.func_ptr = CStringFunc;
    macro->sym.isfunc = TRUE;
    macro->e.macroinfo->parmcnt = 1;
    macro->e.macroinfo->parmlist = (struct mparm_list *)LclAlloc( sizeof( struct mparm_list )  * 1 );
    macro->e.macroinfo->parmlist[0].deflt = NULL;
    macro->e.macroinfo->parmlist[0].required = TRUE;

    /* add @CatStr() macro func */

    macro = CreateMacro( "@CatStr" );
    macro->sym.isdefined = TRUE;
    macro->sym.predefined = TRUE;
    macro->sym.func_ptr = CatStrFunc;
    macro->sym.isfunc = TRUE;
    macro->sym.mac_vararg = TRUE;
    macro->e.macroinfo->parmcnt = 1;
    macro->e.macroinfo->parmlist = (struct mparm_list *)LclAlloc( sizeof( struct mparm_list ) * 1 );
    macro->e.macroinfo->parmlist[0].deflt = NULL;
    macro->e.macroinfo->parmlist[0].required = FALSE;

    /* add @InStr() macro func */

    macro = CreateMacro( "@InStr" );
    macro->sym.isdefined = TRUE;
    macro->sym.predefined = TRUE;
    macro->sym.func_ptr = InStrFunc;
    macro->sym.isfunc = TRUE;
    macro->e.macroinfo->parmcnt = 3;
    macro->e.macroinfo->autoexp = 1; /* param 1 (pos) is expanded */
    macro->e.macroinfo->parmlist = (struct mparm_list *)LclAlloc(sizeof( struct mparm_list) * 3);
    for (i = 0; i < 3; i++) {
	macro->e.macroinfo->parmlist[i].deflt = NULL;
	macro->e.macroinfo->parmlist[i].required = (i != 0);
    }

    /* add @SizeStr() macro func */

    macro = CreateMacro( "@SizeStr" );
    macro->sym.isdefined = TRUE;
    macro->sym.predefined = TRUE;
    macro->sym.func_ptr = SizeStrFunc;
    macro->sym.isfunc = TRUE;
    macro->e.macroinfo->parmcnt = 1;
    macro->e.macroinfo->parmlist = (struct mparm_list *)LclAlloc(sizeof( struct mparm_list));
    macro->e.macroinfo->parmlist[0].deflt = NULL;
    /* macro->e.macroinfo->parmlist[0].required = TRUE; */
    /* the string parameter is NOT required, '@SizeStr()' is valid */
    macro->e.macroinfo->parmlist[0].required = FALSE;

    /* add @SubStr() macro func */

    macro = CreateMacro( "@SubStr" );
    macro->sym.isdefined = TRUE;
    macro->sym.predefined = TRUE;
    macro->sym.func_ptr = SubStrFunc;
    macro->sym.isfunc = TRUE;
    macro->e.macroinfo->parmcnt = 3;
    macro->e.macroinfo->autoexp = 2 + 4; /* param 2 (pos) and 3 (size) are expanded */
    macro->e.macroinfo->parmlist = (struct mparm_list *)LclAlloc(sizeof( struct mparm_list) * 3);
    for (i = 0; i < 3; i++) {
	macro->e.macroinfo->parmlist[i].deflt = NULL;
	macro->e.macroinfo->parmlist[i].required = (i < 2);
    }

    return;
}
