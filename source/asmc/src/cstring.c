#include <stdio.h>
#include <string.h>

#include <globals.h>
#include <hllext.h>
#include <fastpass.h>
#include <quadmath.h>

#define MACRO_CSTRING 1

extern int list_pos;

struct str_item {
int	count;
int	index;
void *	next;
char	unicode;
char	flags;
char	string[1];
};

static int InsertLine( char *line )
{
	struct input_status oldstat;
	int rc, GeneratedCode;

	PushInputStatus( &oldstat );
	GeneratedCode = ModuleInfo.GeneratedCode;
	ModuleInfo.GeneratedCode = 0;
	strcpy( CurrSource, line );
	ModuleInfo.token_count = Tokenize(
	    ModuleInfo.currsource, 0, ModuleInfo.tokenarray, TOK_DEFAULT );
	rc = ParseLine( ModuleInfo.tokenarray );
	ModuleInfo.GeneratedCode = GeneratedCode;
	PopInputStatus( &oldstat );
	return rc;
}

static int ParseCString( char *lbuf, char *buffer, char *string,
	char **pStringOffset, char *pUnicode )
{
	char sbuf[MAX_LINE_LEN]; /* "binary" string */
	char Unicode;
	char *src,*des,*sbp;
	char *p;
	char a,b;
	int  ch;
	long dw;
	struct str_item *sp;

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
		//
		// escape char
		//
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
		    dw = 0x33312C22; // <",13>
		    goto case_format;
		case 'v':
		    *sbp = 11;
		    dw = 0x31312C22; // <",11>
		    goto case_format;
		case 0x27:
		    *sbp = 39;
		    dw = 0x39332C22; // <",39>
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

		case '"': // <",'"',">
		    p = &buffer[1];
		    //
		    // db '"',xx",'"',0
		    //
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
		p = src + 1;
		while ( *p == ' ' || *p == 9 ) p++;
		if ( *p == '"' ) { // "string1" "string2"
		    src = p;
		    des--;
		    sbp--;
		} else {
		    *des++ = *src++;
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
	char b_line[MAX_LINE_LEN];
	char b_data[MAX_LINE_LEN];
	char buffer[MAX_LINE_LEN];
	char *StringOffset;
	int brackets = 0;
	char Unicode;
	char a,b;
	int lineflags;

	if ( ModuleInfo.strict_masm_compat == 0 && Parse_Pass == PASS_1 ) {
	    //
	    // need "quote"
	    // proc( "", ( ... ), "" )
	    //
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
		    c++; // need one open bracket
		}
		i++;
	    }
	    if ( e == 0 || c == 0 )
		return 0;

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
			//
			// strip "string" from LineStoreCurr
			//
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

			strcat( strcpy( b_seg, ModuleInfo.currseg->sym.name ), " segment" );
			if ( (rc = InsertLine( ".data" )) )
			    break;
			if ( (rc = InsertLine( b_data )) )
			    break;
			if ( (rc = InsertLine( "_DATA ends" )) )
			    break;
			if ( (rc = InsertLine( b_seg )) )
			    break;
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
	return rc;
}

#ifdef MACRO_CSTRING

int CString( char *buffer, struct asm_tok tokenarray[] )
{
	char string[MAX_LINE_LEN];
	char cursrc[MAX_LINE_LEN];
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
		    x = 0;
		    p = ModuleInfo.currseg->sym.name;
		    if ( _stricmp( p, "_DATA" ) ) {
			x++;
			InsertLine( ".data" );
		    } else if ( equal ) {
			x = 2;
			InsertLine(".const");
		    }
		    InsertLine( cursrc );
		    if ( x ) {
			if ( !_stricmp( p, "CONST" ) )
			    InsertLine(".const");
			else if ( x == 2 )
			    InsertLine(".data");
			else
			    InsertLine(".code");
		    }
		}
		rc = 1;
		break;
	    }
	    i++;
	}
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

	if ( ModuleInfo.currseg ) {
	    strcat( strcpy( segm, ModuleInfo.currseg->sym.name ), " segment" );
	} else {
	    strcpy( segm, ".code" );
	}

	InsertLine( ".data" );
	if ( size == 10 )
	    size = 16;

	sprintf( temp, "align %d", size );
	InsertLine( temp );

	switch ( size ) {
	case 4:
	    sprintf( temp, "%s dd 0x%08X", buffer, opc.value );
	    break;
	case 8:
	    sprintf( temp, "%s dq 0x%08X%08X", buffer, opc.hvalue, opc.value );
	    break;
	case 16:
	    sprintf( temp, "%s label real%d", buffer, size );
	    InsertLine( temp );
	    sprintf( temp, "oword 0x%016" I64_SPEC "X%016" I64_SPEC "X", opc.hlvalue, opc.llvalue );
	    break;
	}
	InsertLine( temp );
	InsertLine( "_DATA ends" );
	InsertLine( segm );
    }
    return 0;
}

#endif
