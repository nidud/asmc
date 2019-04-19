//
// .for <initialization>: <condition>: <increment/decrement>
//
#include <string.h>
#include <globals.h>
#include <hllext.h>

#ifndef _LIBC

int strtrim( char *string )
{
    char *p = string;

    while ( *p ) p++;
    while ( p > string ) {
	p--;
	if ( *p > ' ' )
	    break;
	*p = NULLC;
    }
    return (p - string + 1);
}

#endif

static char *GetCondition( char *string, char **pp )
{
	char *p;
	int brackets = 0;

	while ( *string == ' ' || *string == 9 )
	    string++;
	p = string;
	while ( 1 ) {
	    if ( *p == NULLC )
		break;
	    else if ( *p == '(' )
		brackets++;
	    else if ( *p == ')' )
		brackets--;
	    else if ( *p == ',' && brackets == 0 ) {
		*p = NULLC;
		if ( *(p - 1) == ' ' || *(p - 1) == 9 )
		    *(p - 1) = NULLC;
		p++;
		while ( *p == ' ' || *p == 9 )
		    p++;
		if ( *string == NULLC && *p ) {
		    string = p;
		    continue;
		}
		break;
	    }
	    p++;
	}
	*pp = p;
	if ( *string )
	    return string;
	return NULL;
}


static int Assignopc( char *buffer, char *opc1, char *opc2, char *string )
{
    if ( opc1 ) {
	strcat( buffer, opc1 );
	strtrim( buffer );
	strcat( buffer, " " );
    }
    if ( opc2 ) {
	strcat( buffer, opc2 );
	strtrim( buffer );
	if ( opc1 && string )
	    strcat( buffer, "," );
	if ( string )
	    strcat( buffer, " " );
    }
    if ( string ) {
	strcat( buffer, string );
	strtrim( buffer );
    }
    strcat( buffer, "\n" );
    return 1;
}

static int ParseAssignment( char *buffer, struct asm_tok tokenarray[] )
{
    int k, n, i;
    char *p;
    int bracket = 0; /* assign value: [rdx+8]=rax - @v2.28.15 */

    if ( tokenarray[0].token == T_OP_SQ_BRACKET )
	bracket++;

    if ( tokenarray[0].string_ptr[0] == '~' )
	return Assignopc( buffer, "not", &tokenarray[0].string_ptr[1], NULL );
    if ( tokenarray[0].token == '-' && tokenarray[1].token == '-' )
	return Assignopc( buffer, "dec", tokenarray[2].tokpos, NULL );
    if ( tokenarray[0].token == '+' && tokenarray[1].token == '+' )
	return Assignopc( buffer, "inc", tokenarray[2].tokpos, NULL );

    for ( k = 0, i = 1; i < Token_Count; i++ ) {

	if ( tokenarray[i].token == T_OP_SQ_BRACKET )
	    bracket++;
	else if ( tokenarray[i].token == T_CL_SQ_BRACKET )
	    bracket--;
	else if ( bracket )
	    ;
	else if ( ( tokenarray[i].tokval == T_EQU && tokenarray[i].dirtype == DRT_EQUALSGN ) ||
	    tokenarray[i].token == '+' || tokenarray[i].token == '-' ||
	    tokenarray[i].token == '&' ) {

	    k = tokenarray[i].string_ptr[0];
	    n = tokenarray[i+1].string_ptr[0];
	    p = tokenarray[i+1].tokpos;
	    break;
	} else if ( tokenarray[i].string_ptr[0] == '>' || tokenarray[i].string_ptr[0] == '<' ) {
	    k = tokenarray[i].string_ptr[0];
	    n = tokenarray[i].string_ptr[1];
	    p = &tokenarray[i].tokpos[3];
	    if ( *p == 0 )
		p = tokenarray[i+1].tokpos;
	    break;
	} else if ( tokenarray[i].string_ptr[0] == '^' || tokenarray[i].string_ptr[0] == '~' ||
		    tokenarray[i].string_ptr[0] == '|') {
	    k = tokenarray[i].string_ptr[0];
	    n = tokenarray[i].string_ptr[1];
	    p = &tokenarray[i].string_ptr[2];
	    if ( p[0] == 0 )
		p = tokenarray[i+1].tokpos;
	    break;
	}
    }

    switch ( k ) {
    case '=':
	if ( n == '&' ) {
	    tokenarray[i].tokpos[0] = 0;
	    return Assignopc( buffer, "lea", tokenarray[0].tokpos, tokenarray[i+2].tokpos );
	}
	if ( tokenarray[i+1].string_ptr[0] == '~' ) {
	    tokenarray[i].tokpos[0] = 0;
	    Assignopc( buffer, "mov", tokenarray[0].tokpos, &tokenarray[i+1].tokpos[1] );
	    return Assignopc( buffer, "not", tokenarray[0].tokpos, NULL );
	}
	tokenarray[i].tokpos[0] = 0;
	/* mov reg,0 --> xor reg,reg */
	if ( tokenarray[i+1].token == T_NUM &&
	     tokenarray[i+1].stringlen == 1 &&
	     tokenarray[i+1].string_ptr[0] == '0' &&
	     ( ( tokenarray[0].tokval >= T_AL &&
		 tokenarray[0].tokval <= T_EDI ) ||
	       ( ModuleInfo.Ofssize == USE64 &&
		 tokenarray[0].tokval >= T_R8B &&
		 tokenarray[0].tokval <= T_R15 ) ) ) {

	    return Assignopc( buffer, "xor", tokenarray[0].string_ptr, tokenarray[0].string_ptr );
	}
	return Assignopc( buffer, "mov", tokenarray[0].tokpos, tokenarray[i+1].tokpos );
    case '~':
	if ( n == '=' ) {
	    tokenarray[i].tokpos[0] = 0;
	    Assignopc( buffer, "mov", tokenarray[0].tokpos, p );
	    return Assignopc( buffer, "not", tokenarray[0].tokpos, NULL );
	}
	break;
    case '^':
	if ( n == '=' ) {
	    tokenarray[i].tokpos[0] = 0;
	    return Assignopc( buffer, "xor", tokenarray[0].tokpos, p );
	}
	break;
    case '|':
	if ( n == '=' ) {
	    tokenarray[i].tokpos[0] = 0;
	    return Assignopc( buffer, "or ", tokenarray[0].tokpos, p );
	}
	break;
    case '&':
	if ( n == '=' ) {
	    tokenarray[i].tokpos[0] = 0;
	    return Assignopc( buffer, "and", tokenarray[0].tokpos, tokenarray[i+2].tokpos );
	}
	break;
    case '>':
	if ( n == '>' && tokenarray[i].string_ptr[2] == '=' ) {
	    tokenarray[i].tokpos[0] = 0;
	    return Assignopc( buffer, "shr", tokenarray[0].tokpos, p );
	}
	break;
    case '<':
	if ( n == '<' && tokenarray[i].string_ptr[2] == '=' ) {
	    tokenarray[i].tokpos[0] = 0;
	    return Assignopc( buffer, "shl", tokenarray[0].tokpos, p );
	}
	break;
    case '+':
	if ( n == '+' ) {
	    tokenarray[i].tokpos[0] = 0;
	    return Assignopc( buffer, "inc", tokenarray[0].tokpos, NULL );
	}
	if ( n == '=' ) {
	    tokenarray[i].tokpos[0] = 0;
	    return Assignopc( buffer, "add", tokenarray[0].tokpos, tokenarray[i+2].tokpos );
	}
	break;
    case '-':
	if ( n == '-' ) {
	    tokenarray[i].tokpos[0] = 0;
	    return Assignopc( buffer, "dec", tokenarray[0].tokpos, NULL );
	}
	if ( n == '=' ) {
	    tokenarray[i].tokpos[0] = 0;
	    return Assignopc( buffer, "sub", tokenarray[0].tokpos, tokenarray[i+2].tokpos );
	}
	break;
    }
    asmerr( 2008, tokenarray[i].tokpos );
    return 0;
}

static int RenderAssignment( char *dest, char *source, struct asm_tok tokenarray[] )
{
	char *p;
	char buffer[MAX_LINE_LEN];
	char tokbuf[MAX_LINE_LEN];
	/*
	 * <expression1>, <expression2>, ..., [: | 0]
	 */
	while ( (source = GetCondition( source, &p )) ) {

	    Token_Count = Tokenize(
		strcpy( tokbuf, source ), 0, tokenarray, TOK_DEFAULT );
	    if ( ExpandHllProc( buffer, 0, tokenarray ) == ERROR )
		break;

	    if ( buffer[0] ) { /* function calls expanded */

		strcat( strcat( dest, buffer ), "\n" );
		buffer[0] = NULLC;
	    }
	    if ( !ParseAssignment( buffer, tokenarray ) )
		break;

	    strcat( dest, buffer );
	    source = p;
	}
	return *dest;
}


int ForDirective( int i, struct asm_tok tokenarray[] )
{
	int rc = NOT_ERROR;
	int cmd = tokenarray[i].tokval;
	int size;
	char *p, *q, *bp, *cp;
	char buff[16];
	char buffer[MAX_LINE_LEN];
	char cmdstr[MAX_LINE_LEN];
	char tokbuf[MAX_LINE_LEN];
	struct hll_item *hll;

	i++;
	if ( cmd == T_DOT_ENDF ) {

	    if ( HllStack == NULL )
		return ( asmerr( 1011 ) );

	    hll = HllStack;
	    HllStack = hll->next;
	    hll->next = HllFree;
	    HllFree = hll;

	    if ( hll->cmd != HLL_WHILE )
		return ( asmerr( 1011 ) );

	    if ( hll->labels[LTEST] )
		AddLineQueueX( "%s" LABELQUAL, GetLabelStr( hll->labels[LTEST], buff ) );
	    if ( hll->condlines )
		QueueTestLines( hll->condlines );
	    AddLineQueueX( "jmp %s", GetLabelStr( hll->labels[LSTART], buff ) );
	    if ( hll->labels[LEXIT] )
		AddLineQueueX( "%s" LABELQUAL, GetLabelStr( hll->labels[LEXIT], buff ) );

	    if ( tokenarray[i].token != T_FINAL )
		rc = asmerr( 2008, tokenarray[i].tokpos );

	} else {

	    if ( HllFree )
		hll = HllFree;
	    else
		hll = (struct hll_item *)LclAlloc( sizeof( struct hll_item ) );

	    hll->flags = 0;
	    hll->labels[LEXIT] = 0;
	    ExpandCStrings( tokenarray );

	    if ( cmd == T_DOT_FORS )
		hll->flags = HLLF_IFS;
	    hll->cmd = HLL_WHILE;

	    // create the loop labels

	    hll->labels[LSTART] = GetHllLabel();
	    hll->labels[LTEST] = GetHllLabel();
	    hll->labels[LEXIT] = GetHllLabel();

	    if ( tokenarray[i].token == T_OP_BRACKET )
		i++;

	    if ( !(p = strchr(strcpy( buffer, tokenarray[i].tokpos), ':')) )
		return ( asmerr( 2206 ) );

	    *p++ = NULLC;
	    while ( *p == ' ' || *p == 9 )
		p++;
	    if ( !(q = strchr(p, ':')) )
		return ( asmerr( 2206 ) );
	    *q++ = NULLC;
	    while ( *q == ' ' || *q == 9 )
		q++;
	    strtrim( q );
	    bp = buffer;
	    while ( *bp == ' ' || *bp == 9 )
		bp++;
	    strtrim( bp );
	    strtrim( p );

	    if ( tokenarray[i-1].token == T_OP_BRACKET ) {

		if ( (cp = strrchr(q, ')')) ) {

			*cp = NULLC;
			strtrim( q );
		}
	    }

	    cmdstr[0] = NULLC;
	    if ( RenderAssignment( cmdstr, bp, tokenarray ) )
		QueueTestLines( cmdstr );

	    AddLineQueueX( "%s" LABELQUAL, GetLabelStr( hll->labels[LSTART], buff ) );

	    cmdstr[0] = NULLC;
	    hll->condlines = NULL;

	    if ( RenderAssignment( cmdstr, q, tokenarray ) ) {

		size = strlen( cmdstr ) + 1;
		hll->condlines = LclAlloc( size );
		memcpy( hll->condlines, cmdstr, size );
	    }

	    cmdstr[0] = NULLC;
	    while ( (p = GetCondition( p, &q )) ) {

		ModuleInfo.token_count = Tokenize(
		    strcat( strcpy( tokbuf, ".if " ), p ), 0, tokenarray, TOK_DEFAULT );
		i = 1;
		rc = EvaluateHllExpression( hll, &i, tokenarray, LEXIT, 0, cmdstr );
		if ( rc == NOT_ERROR )
		    QueueTestLines( cmdstr );
		p = q;
	    }

	    if ( hll == HllFree )
		HllFree = hll->next;
	    hll->next = HllStack;
	    HllStack = hll;

	}


	if ( ModuleInfo.list )
	    LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), NULL );
	if ( is_linequeue_populated() )
	    RunLineQueue();

	return( rc );
}
