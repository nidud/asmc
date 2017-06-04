//
// .for <initialization>: <condition>: <increment/decrement>
//
#include <string.h>
#include <globals.h>
#include <hllext.h>

#ifndef _ASMC

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

static int ParseAssignment( char *buffer, struct asm_tok tokenarray[] )
{
	char *p, *q, *cp;
	char a, b;

	q = tokenarray[0].tokpos;

	if ( !(p = strchr(q, '+')) ) {
	    if ( !(p = strchr(q, '-')) )
		p = strchr(q, '=');
	}
	if ( !p ) {

	    asmerr( 2008, q );
	    return 0;
	}

	while ( p[1] == ' ' || p[1] == 9 )
	    strcpy( p + 1, p + 2 );

	if ( q[0] == '-' && q[1] == '-' ) {

	    strcat( buffer, "dec " );
	    strcat( buffer, q + 2 );
	    strcat( buffer, "\n" );
	    return 1;
	}

	if ( q[0] == '+' && q[1] == '+' ) {

	    strcat( buffer, "inc " );
	    strcat( buffer, q + 2 );
	    strcat( buffer, "\n" );
	    return 1;
	}

	a = p[0];
	b = p[1];
	p[0] = NULLC;
	p += 2;

	if ( a == '+' && b == '+' )
	    q = "inc ";
	else if ( a == '-' && b == '-' )
	    q = "dec ";
	else if ( a == '=' && b == '&' )
	    q = "lea ";
	else if ( a == '+' && b == '=' )
	    q = "add ";
	else if ( a == '-' && b == '=' )
	    q = "sub ";
	else if ( a == '=' && b == '~' )
	    q = "mov ";
	else if ( a == '=' ) {
	    q = "mov ";
	    p--;
	} else {
	    asmerr( 2008, q );
	    return 0;
	}

	while ( *p == ' ' || *p == 9 )
	    p++;
	cp = p + strlen(p) - 1;
	while ( cp > p && (*cp == ' ' || *cp == 9) )
	    *cp-- = NULLC;

	cp = tokenarray[0].tokpos;

	if ( a == '=' && b == '~' ) {
	    /* = ~# -->
	     * mov reg,#
	     * not reg
	     */
	    strcat( buffer, q );
	    strcat( buffer, cp );
	    strcat( buffer, ", " );
	    strcat( buffer, p );
	    strcat( buffer, "\n" );
	    *p = NULLC;
	    q = "not ";

	} else if ( a == '=' && p[0] == '0' && p[1] == 0 ) {

	    /* mov reg,0 --> xor reg,reg */
	    int tv = tokenarray[0].tokval;

	    if ( ( tv >= T_AL && tv <= T_EDI) ||
		( ModuleInfo.Ofssize == USE64 && tv >= T_R8B && tv <= T_R15 ) ) {

		q = "xor ";
		p = cp;
	    }
	}

	strcat( buffer, q );
	strcat( buffer, cp );
	if ( *p ) {
	    strcat( buffer, ", " );
	    strcat( buffer, p );
	}
	strcat( buffer, "\n" );
	return 1;
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

	    ModuleInfo.token_count = Tokenize(
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
