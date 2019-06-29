/****************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
* Description:	implements hll directives:
*		.IF, .WHILE, .REPEAT, .ELSE, .ELSEIF, .ENDIF,
*		.ENDW, .UNTIL, .UNTILCXZ, .BREAK, .CONTINUE.
*		also handles C operators:
*		==, !=, >=, <=, >, <, &&, ||, &, !,
*		and flags:
*		ZERO?, CARRY?, SIGN?, PARITY?, OVERFLOW?
*
****************************************************************************/

#include <globals.h>
#include <hllext.h>
#include <types.h>

static int GetExpression( struct hll_item *hll, int *i, struct asm_tok[], int ilabel, int is_true, char *buffer, struct hll_opnd * );

/* c binary ops.
 * Order of items COP_EQ - COP_LE  and COP_ZERO - COP_OVERFLOW
 * must not be changed.
 */
enum c_bop {
    COP_NONE,
    COP_EQ,   /* == */
    COP_NE,   /* != */
    COP_GT,   /* >  */
    COP_LT,   /* <  */
    COP_GE,   /* >= */
    COP_LE,   /* <= */
    COP_AND,  /* && */
    COP_OR,   /* || */
    COP_ANDB, /* &  */
    COP_NEG,  /* !  */
    COP_ZERO, /* ZERO?	 not really a valid C operator */
    COP_CARRY,/* CARRY?	 not really a valid C operator */
    COP_SIGN, /* SIGN?	 not really a valid C operator */
    COP_PARITY,	 /* PARITY?   not really a valid C operator */
    COP_OVERFLOW, /* OVERFLOW? not really a valid C operator */
};

/* items in table below must match order COP_ZERO - COP_OVERFLOW */
static const char flaginstr[] = { 'z',	'c',  's',  'p',  'o' };

/* items in tables below must match order COP_EQ - COP_LE */
static const char unsigned_cjmptype[] = {  'z',	 'z',  'a',  'b',  'b', 'a' };
static const char signed_cjmptype[]   = {  'z',	 'z',  'g',  'l',  'l', 'g' };
static const char neg_cjmptype[]      = {   0,	  1,	0,    0,    1,	 1  };

/* in Masm, there's a nesting level limit of 20. In JWasm, there's
 * currently no limit.
 */

#ifdef DEBUG_OUT
static unsigned evallvl;
static unsigned cntAlloc;  /* # of allocated hll_items */
static unsigned cntReused; /* # of reused hll_items */
static unsigned cntCond;   /* # of allocated 'condlines'-buffer in .WHILE-blocks */
static unsigned cntCondBytes; /* total size of allocated 'condlines'-buffers */
#endif

int GetHllLabel( void )
{
    return ( ++ModuleInfo.hll_label );
}

/* get a C binary operator from the token stream.
 * there is a problem with the '<' because it is a "string delimiter"
 * which Tokenize() usually is to remove.
 * There has been a hack implemented in Tokenize() so that it won't touch the
 * '<' if .IF, .ELSEIF, .WHILE, .UNTIL, .UNTILCXZ or .BREAK/.CONTINUE has been
 * detected.
 */

#define CHARS_EQ  '=' + ( '=' << 8 )
#define CHARS_NE  '!' + ( '=' << 8 )
#define CHARS_GE  '>' + ( '=' << 8 )
#define CHARS_LE  '<' + ( '=' << 8 )
#define CHARS_AND '&' + ( '&' << 8 )
#define CHARS_OR  '|' + ( '|' << 8 )

static enum c_bop GetCOp( struct asm_tok *item )
/**********************************************/
{
    int size;
    enum c_bop rc;
    char *p = item->string_ptr;

    size = ( item->token == T_STRING ? item->stringlen : 0 );

    if ( size == 2 ) {
	switch ( *(uint_16 *)p ) {
	case CHARS_EQ:	rc = COP_EQ;  break;
	case CHARS_NE:	rc = COP_NE;  break;
	case CHARS_GE:	rc = COP_GE;  break;
	case CHARS_LE:	rc = COP_LE;  break;
	case CHARS_AND: rc = COP_AND; break;
	case CHARS_OR:	rc = COP_OR;  break;
	default: return( COP_NONE );
	}
    } else if ( size == 1 ) {
	switch ( *p ) {
	case '>': rc = COP_GT;	 break;
	case '<': rc = COP_LT;	 break;
	case '&': rc = COP_ANDB; break;
	case '!': rc = COP_NEG;	 break;
	default: return( COP_NONE );
	}
    } else {
	if ( item->token != T_ID )
	    return( COP_NONE );
	/* a valid "flag" string must end with a question mark */
	size = strlen( p );
	if ( *(p+size-1) != '?' )
	    return( COP_NONE );
	if ( size == 5 && ( 0 == _memicmp( p, "ZERO", 4 ) ) )
	    rc = COP_ZERO;
	else if ( size == 6 && ( 0 == _memicmp( p, "CARRY", 5 ) ) )
	    rc = COP_CARRY;
	else if ( size == 5 && ( 0 == _memicmp( p, "SIGN", 4 ) ) )
	    rc = COP_SIGN;
	else if ( size == 7 && ( 0 == _memicmp( p, "PARITY", 6 ) ) )
	    rc = COP_PARITY;
	else if ( size == 9 && ( 0 == _memicmp( p, "OVERFLOW", 8 ) ) )
	    rc = COP_OVERFLOW;
	else
	    return( COP_NONE );
    }
    return( rc );
}

/* render an instruction */

static char *RenderInstr( char *dst, const char *instr, int start1, int end1, int start2,
	int end2, struct asm_tok tokenarray[] )
{
    int i;
    i = strlen( instr );
    /* copy the instruction */
    memcpy( dst, instr, i );
    dst += i;
    /* copy the first operand's tokens */
    *dst++ = ' ';
    i = tokenarray[end1].tokpos - tokenarray[start1].tokpos;
    memcpy( dst, tokenarray[start1].tokpos, i );
    dst += i;
    if ( start2 != EMPTY ) {
	*dst++ = ',';
	/* copy the second operand's tokens */
	*dst++ = ' ';
	i = tokenarray[end2].tokpos - tokenarray[start2].tokpos;
	memcpy( dst, tokenarray[start2].tokpos, i );
	dst += i;
    } else if ( end2 != EMPTY ) {
	dst += sprintf( dst, ", %d", end2 );
    }
    *dst++ = EOLCHAR;
    *dst = NULLC;
    return( dst );
}

char *GetLabelStr( int label, char *buff )
{
    sprintf( buff, LABELFMT, label );
    return( buff );
}

/* render a Jcc instruction */

static char *RenderJcc( char *dst, char cc, int neg, uint_32 label )
{
    /* create the jump opcode: j[n]cc */
    *dst++ = 'j';
    if ( neg )
	*dst++ = 'n';
    *dst++ = cc;
    if ( neg == FALSE )
	*dst++ = ' '; /* make sure there's room for the inverse jmp */

    *dst++ = ' ';
    GetLabelStr( label, dst );
    dst += strlen( dst );
    *dst++ = EOLCHAR;
    *dst = NULLC;
    return( dst );
}

/* a "token" in a C expression actually is an assembly expression */

static int LGetToken( struct hll_item *hll, int *i, struct asm_tok tokenarray[],
	struct expr *opnd )
{
    int end_tok;

    /* scan for the next C operator in the token array.
     * because the ASM evaluator may report an error if such a thing
     * is found ( CARRY?, ZERO? and alikes will be regarded as - not yet defined - labels )
     */
    for ( end_tok = *i; end_tok < Token_Count; end_tok++ ) {
	if ( ( GetCOp( &tokenarray[end_tok] ) ) != COP_NONE )
	    break;
    }
    if ( end_tok == *i ) {
	opnd->kind = EXPR_EMPTY;
	return( NOT_ERROR );
    }
    if ( ERROR == EvalOperand( i, tokenarray, end_tok, opnd, 0 ) )
	return( ERROR );

    /* v2.11: emit error 'syntax error in control flow directive'.
     * May happen for expressions like ".if 1 + CARRY?"
     */
    if ( *i > end_tok ) {
	return( asmerr( 2154 ) );
    }

    return( NOT_ERROR );
}

static uint_32 GetLabel( struct hll_item *hll, int index )
{
    return( hll->labels[index] );
}

/* a "simple" expression is
 * 1. two tokens, coupled with a <cmp> operator: == != >= <= > <
 * 2. two tokens, coupled with a "&" operator
 * 3. unary operator "!" + one token
 * 4. one token (short form for "<token> != 0")
 */
static int GetSimpleExpression( struct hll_item *hll, int *i, struct asm_tok tokenarray[],
	int ilabel, bool is_true, char *buffer, struct hll_opnd *hllop )
{
    enum c_bop op;
    char instr;
    int op1_pos;
    int op1_end;
    int op2_pos;
    int op2_end;
    int id;
    char *p;
    struct expr op1;
    struct expr op2;
    uint_32 label;
    bool state;

    while ( tokenarray[*i].string_ptr[0] == '!' && tokenarray[*i].string_ptr[1] == '\0' ) {
	(*i)++;
	is_true = 1 - is_true;
    }

    /* the problem with '()' is that is might enclose just a standard Masm
     * expression or a "hll" expression. The first case is to be handled
     * entirely by the expression evaluator, while the latter case is to be
     * handled HERE!
     */
    if ( tokenarray[*i].token == T_OP_BRACKET ) {
	int brcnt;
	int j;
	for ( brcnt = 1, j = *i + 1; tokenarray[j].token != T_FINAL; j++ ) {
	    if ( tokenarray[j].token == T_OP_BRACKET )
		brcnt++;
	    else if ( tokenarray[j].token == T_CL_BRACKET ) {
		brcnt--;
		if ( brcnt == 0 ) /* a standard Masm expression? */
		    break;
	    } else if ( ( GetCOp( &tokenarray[j] )) != COP_NONE )
		break;
	}
	if ( brcnt ) {
	    (*i)++;
	    if ( ERROR == GetExpression( hll, i, tokenarray, ilabel, is_true, buffer, hllop ) )
		return( ERROR );

	    if ( tokenarray[*i].token != T_CL_BRACKET ) {
		return( asmerr( 2154 ) );
	    }
	    (*i)++;
	    return( NOT_ERROR );
	}
    }

    /* get (first) operand */
    op1_pos = *i;
    if ( ERROR == LGetToken( hll, i, tokenarray, &op1 ) )
	return ( ERROR );
    op1_end = *i;

    op = GetCOp( &tokenarray[*i] ); /* get operator */

    /* lower precedence operator ( && or || ) detected? */
    if ( op == COP_AND || op == COP_OR ) {
	op = COP_NONE;
    } else if ( op != COP_NONE )
	(*i)++;

    label = GetLabel( hll, ilabel );

    /* check for special operators with implicite operand:
     * COP_ZERO, COP_CARRY, COP_SIGN, COP_PARITY, COP_OVERFLOW
     */
    if ( op >= COP_ZERO ) {
	if ( op1.kind != EXPR_EMPTY ) {
	    return( asmerr( 2154 ) );
	}
	p = buffer;
	hllop->lastjmp = p;
	instr = flaginstr[ op - COP_ZERO ];
	state = !is_true;

	/* v2.27.30: ZERO? || CARRY? --> LE */
	id = *i + 1;
	if ( id < ModuleInfo.token_count && ( op == COP_ZERO || op == COP_CARRY ) ) {

	    op = GetCOp( &tokenarray[id] );

	    if ( op == COP_ZERO || op == COP_CARRY ) {

		instr = 'a';
		state = is_true;
		*i = id + 1;
	    }
	}

	RenderJcc( p, instr, state, label );
	return( NOT_ERROR );
    }

    switch ( op1.kind ) {
    case EXPR_EMPTY:
	return( asmerr( 2154 ) ); /* v2.09: changed from NOT_ERROR to ERROR */
    case EXPR_FLOAT:
	return( asmerr( 2050 ) ); /* v2.10: added */
    }

    if ( op == COP_NONE ) {
	switch ( op1.kind ) {
	case EXPR_REG:
	    if ( op1.indirect == FALSE ) {
		if (Options.masm_compat_gencode)
		    p = RenderInstr( buffer, "or", op1_pos, op1_end, op1_pos, op1_end, tokenarray);
		else
		    p = RenderInstr( buffer, "test", op1_pos, op1_end, op1_pos, op1_end, tokenarray);
		hllop->lastjmp = p;
		RenderJcc( p, 'z', is_true, label );
		break;
	    }
	    /* no break */
	case EXPR_ADDR:
	    p = RenderInstr( buffer, "cmp", op1_pos, op1_end, EMPTY, 0, tokenarray );
	    hllop->lastjmp = p;
	    RenderJcc( p, 'z', is_true, label );
	    break;
	case EXPR_CONST:
	    if ( op1.hvalue != 0 && op1.hvalue != -1 )
		return( EmitConstError( &op1 ) );

	    hllop->lastjmp = buffer;

	    if ( ( is_true == TRUE && op1.value ) ||
		( is_true == FALSE && op1.value == 0 ) ) {
		sprintf( buffer, "jmp " LABELFMT EOLSTR, label );
	    } else {
		*buffer = NULLC;
	    }
	    break;
	}
	return( NOT_ERROR );
    }

    /* get second operand for binary operator */
    op2_pos = *i;
    if ( ERROR == LGetToken( hll, i, tokenarray, &op2 ) ) {
	return( ERROR );
    }
    if ( op2.kind != EXPR_CONST && op2.kind != EXPR_ADDR && op2.kind != EXPR_REG ) {
	return( asmerr( 2154 ) );
    }
    op2_end = *i;

    /* now generate ASM code for expression */

    p = "test";
    if ( Options.masm_compat_gencode )
	p = "or";
    if ( op == COP_ANDB ) {
	p = RenderInstr( buffer, p, op1_pos, op1_end, op2_pos, op2_end, tokenarray );
	hllop->lastjmp = p;
	RenderJcc( p, 'e', is_true, label );
    } else if ( op <= COP_LE ) { /* ==, !=, >, <, >= or <= operator */
	/*
	 * optimisation: generate 'or EAX,EAX' instead of 'cmp EAX,0'.
	 * v2.11: use op2.value64 instead of op2.value
	 */
	if ( ( op == COP_EQ || op == COP_NE ) &&
	    op1.kind == EXPR_REG && op1.indirect == FALSE &&
	    op2.kind == EXPR_CONST && op2.value64 == 0 ) {
	    /* v2.22 - switch /Zg to OR */
	    p = RenderInstr(buffer, p, op1_pos, op1_end, op1_pos, op1_end, tokenarray);
	} else {
	    p = RenderInstr( buffer, "cmp", op1_pos, op1_end, op2_pos, op2_end, tokenarray );
	}

	/* v2.22 - signed compare S, SB, SW, SD */
	instr = ( ( hll->flags & HLLF_IFS) || ( IS_SIGNED( op1.mem_type ) || IS_SIGNED( op2.mem_type ) ) ?
		signed_cjmptype[op - COP_EQ] : unsigned_cjmptype[op - COP_EQ] );

	hllop->lastjmp = p;
	RenderJcc( p, instr, neg_cjmptype[op - COP_EQ] ? is_true : !is_true, label );
    } else {
	return( asmerr( 2154 ) );
    }
    return( NOT_ERROR );
}

/* invert a Jump:
 * - Jx	 -> JNx (x = e|z|c|s|p|o )
 * - JNx -> Jx	(x = e|z|c|s|p|o )
 * - Ja	 -> Jbe, Jae -> Jb
 * - Jb	 -> Jae, Jbe -> Ja
 * - Jg	 -> Jle, Jge -> Jl
 * - Jl	 -> Jge, Jle -> Jg
 * added in v2.11:
 * - jmp -> 0
 * - 0	 -> jmp
 */
static void InvertJump( char *p )
{
    if ( *p == NULLC ) { /* v2.11: convert 0 to "jmp" */
	strcpy( p, "jmp " );
	return;
    }

    p++;
    if ( *p == 'e' || *p == 'z' || *p == 'c' || *p == 's' || *p == 'p' || *p == 'o' ) {
	*(p+1) = *p;
	*p = 'n';
	return;
    } else if ( *p == 'n' ) {
	*p = *(p+1);
	*(p+1) = ' ';
	return;
    } else if ( *p == 'a' ) {
	*p++ = 'b';
    } else if ( *p == 'b' ) {
	*p++ = 'a';
    } else if ( *p == 'g' ) {
	*p++ = 'l';
    } else if ( *p == 'l' ) {
	*p++ = 'g';
    } else {
	/* v2.11: convert "jmp" to 0 */
	if ( *p == 'm' ) {
	    p--;
	    *p = NULLC;
	}
	return;
    }
    if ( *p == 'e' )
	*p = ' ';
    else
	*p = 'e';
    return;
}

/* Replace a label in the source lines generated so far.
 * todo: if more than 0xFFFF labels are needed,
 * it may happen that length of nlabel > length of olabel!
 * then the simple memcpy() below won't work!
 */

static void ReplaceLabel( char *p, uint_32 olabel, uint_32 nlabel )
{
    char oldlbl[16];
    char newlbl[16];
    int i;

    GetLabelStr( olabel, oldlbl );
    GetLabelStr( nlabel, newlbl );

    i = strlen( newlbl );

    while ( p = strstr( p, oldlbl ) ) {
	memcpy( p, newlbl, i );
	p += i;
    }
}

/* operator &&, which has the second lowest precedence, is handled here */

static int GetAndExpression( struct hll_item *hll, int *i, struct asm_tok tokenarray[],
	int ilabel, bool is_true, char *buffer, struct hll_opnd *hllop )
{
    char *ptr = buffer;
    uint_32 truelabel = 0;
    uint_32 nlabel;
    uint_32 olabel;
    char buff[16];
    char *p;

    while ( 1 ) {

	if ( ERROR == GetSimpleExpression( hll, i, tokenarray, ilabel, is_true, ptr, hllop ) )
	    return( ERROR );
	if ( COP_AND != GetCOp( &tokenarray[*i] ) )
	    break;
	(*i)++;

	p = hllop->lastjmp;
	if ( is_true && p ) {
	    /* todo: please describe what's done here and why! */
	    InvertJump( p );	  /* step 1 */
	    if ( truelabel == 0 ) /* step 2 */
		truelabel = GetHllLabel();

	    /* v2.11: there might be a 0 at lastjmp */
	    if ( *p )
		strcat( GetLabelStr( truelabel, &p[4] ), EOLSTR );
	    /*
	     * v2.22 .while (eax || edx) && ecx -- failed
	     *	     .while !(eax || edx) && ecx -- failed
	     */
	    p = ptr;
	    if ( hllop->lasttruelabel )
		ReplaceLabel( p, hllop->lasttruelabel, truelabel );

	    nlabel = GetHllLabel();
	    olabel = GetLabel( hll, ilabel );
	    p += strlen( p );
	    sprintf( p, "%s" LABELQUAL EOLSTR, GetLabelStr( olabel, buff ) );
	    ReplaceLabel( buffer, olabel, nlabel );
	    hllop->lastjmp = NULL;
	}
	ptr += strlen( ptr );
	hllop->lasttruelabel = 0; /* v2.08 */
    };

    if ( truelabel > 0 ) {
	ptr += strlen( ptr );
	GetLabelStr( truelabel, ptr );
	strcat( ptr, LABELQUAL EOLSTR );
	hllop->lastjmp = NULL;
    }
    return( NOT_ERROR );
}

/* operator ||, which has the lowest precedence, is handled here */

static int GetExpression( struct hll_item *hll, int *i, struct asm_tok tokenarray[],
	int ilabel, bool is_true, char *buffer, struct hll_opnd *hllop )
{
    char *ptr = buffer;
    uint_32 truelabel = 0;

    /* v2.08: structure changed from for(;;) to while() to increase
     * readability and - optionally - handle the second operand differently
     * than the first.
     */

    if ( ERROR == GetAndExpression( hll, i, tokenarray, ilabel, is_true, ptr, hllop ) ) {
	return( ERROR );
    }
    while ( COP_OR == GetCOp( &tokenarray[*i] ) ) {

	uint_32 nlabel;
	uint_32 olabel;
	char buff[16];

	/* the generated code of last simple expression has to be modified
	 1. the last jump must be inverted
	 2. a "is_true" label must be created (it's used to jump "behind" the expr)
	 3. create a new label
	 4. the current "false" label must be generated

	 if it is a .REPEAT, step 4 is slightly more difficult, since the "false"
	 label is already "gone":
	 4a. create a new label
	 4b. replace the "false" label in the generated code by the new label
	 */

	(*i)++;

	if ( is_true == FALSE ) {
	    if ( hllop->lastjmp ) {
		char *p = hllop->lastjmp;
		InvertJump( p );	   /* step 1 */
		if ( truelabel == 0 )	   /* step 2 */
		    truelabel = GetHllLabel();
		if ( *p ) { /* v2.11: there might be a 0 at lastjmp */
		    p += 4;		   /* skip 'jcc ' or 'jmp ' */
		    GetLabelStr( truelabel, p );
		    strcat( p, EOLSTR );
		}
		/* v2.08: if-block added */
		if ( hllop->lasttruelabel )
		    ReplaceLabel( ptr, hllop->lasttruelabel, truelabel );
		hllop->lastjmp = NULL;

		nlabel = GetHllLabel();	 /* step 3 */
		olabel = GetLabel( hll, ilabel );
		if ( hll->cmd == HLL_REPEAT ) {
		    ReplaceLabel( buffer, olabel, nlabel );
		    sprintf( ptr + strlen( ptr ), "%s" LABELQUAL EOLSTR, GetLabelStr( nlabel, buff ) );
		} else {
		    sprintf( ptr + strlen( ptr ), "%s" LABELQUAL EOLSTR, GetLabelStr( olabel, buff ) );
		    ReplaceLabel( buffer, olabel, nlabel );
		}
	    }
	}
	ptr += strlen( ptr );
	hllop->lasttruelabel = 0; /* v2.08 */
	if ( ERROR == GetAndExpression( hll, i, tokenarray, ilabel, is_true, ptr, hllop ) ) {
	    return( ERROR );
	}
    }
    if ( truelabel > 0 ) {
	/* v2.08: this is needed, but ober-hackish. to be improved... */
	if ( hllop->lastjmp && hllop->lasttruelabel ) {
	    ReplaceLabel( ptr, hllop->lasttruelabel, truelabel );
	    *(strchr( hllop->lastjmp, EOLCHAR ) + 1 ) = NULLC;
	}
	ptr += strlen( ptr );
	GetLabelStr( truelabel, ptr );
	strcat( ptr, LABELQUAL EOLSTR );
	hllop->lasttruelabel = truelabel; /* v2.08 */
    }
    return( NOT_ERROR );
}

int ExpandCStrings( struct asm_tok tokenarray[] )
{
    int i,j,k;

    if ( ModuleInfo.strict_masm_compat == 1 )
	return 0;

    for ( i = 0, k = 0; tokenarray[i].token != T_FINAL; i++, k++ ) {
	if ( tokenarray[i].hll_flags & T_HLL_PROC ) {

	    if ( Parse_Pass == PASS_1 )
		return ( GenerateCString( k, tokenarray ) );

	    if ( tokenarray[i].token == T_OP_SQ_BRACKET ) {
		j = 1;
		do {
		    i++;
		    if ( tokenarray[i].token == T_CL_SQ_BRACKET ) {
		       j--;
			if ( j == 0 ) break;
		    } else if ( tokenarray[i].token == T_OP_SQ_BRACKET )
		       j++;
		} while ( tokenarray[i].token != T_FINAL );
		i++;
		if ( tokenarray[i].token == T_DOT )
		    i++;
	    }
	    if ( tokenarray[i+1].token == T_DOT )
		i += 2;

	    i += 2;
	    if ( tokenarray[i-1].token != T_OP_BRACKET )
		return( asmerr( 3018, tokenarray[i-2].string_ptr, tokenarray[i-1].string_ptr ) );

	    for( j = 1; tokenarray[i].token != T_FINAL; i++ ) {
		if ( *tokenarray[i].string_ptr == '"' ) {
		    return ( asmerr( 2004, tokenarray[i].string_ptr ) );
		} else if ( *tokenarray[i].string_ptr == ')' ) {
		    j--;
		    if ( j == 0 )
			break;
		} else if ( *tokenarray[i].string_ptr == '(' ) {
		    j++;
		}
	    }
	    break;
	}
    }
    return 0;
}

/*
 * evaluate the C like boolean expression found in HLL structs
 * like .IF, .ELSEIF, .WHILE, .UNTIL and .UNTILCXZ
 * might return multiple lines (strings separated by EOLCHAR)
 * - i = index for tokenarray[] where expression starts. Is restricted
 *	 to one source line (till T_FINAL)
 * - label: label to jump to if expression is <is_true>!
 * is_true:
 *   .IF:	FALSE
 *   .ELSEIF:	FALSE
 *   .WHILE:	TRUE
 *   .UNTIL:	FALSE
 *   .UNTILCXZ: FALSE
 *   .BREAK .IF:TRUE
 *   .CONT .IF: TRUE
 */

static struct asym *GetProc( char *token )
{
    struct asym *sym,*target;

    if ( !(sym = SymFind( token )) ) {
	asmerr( 2190 );
	return NULL;
    }

    /* the most simple case: symbol is a PROC */
    if ( sym->isproc )
	return sym;

    target = sym->target_type;
    if ( sym->mem_type == MT_PTR && target && target->isproc )
	return target;

    if ( sym->mem_type == MT_PTR && target && target->mem_type == MT_PROC ) {

	sym = target;
	goto isfnproto;
    }

    target = sym->type;
    if ( sym->mem_type == MT_TYPE &&
	( target->mem_type == MT_PTR || target->mem_type == MT_PROC ) ) {

	/* second case: symbol is a (function?) pointer */
	sym = target;
	if ( sym->mem_type != MT_PROC )
	    goto isfnptr;
    }

isfnproto:

    /* pointer target must be a PROTO typedef */

    if ( sym->mem_type != MT_PROC ) {

	asmerr( 2190 );
	return NULL;
    }

isfnptr:

    /* get the pointer target */

    sym = sym->target_type;
    if ( !sym ) {

	asmerr( 2190 );
	return NULL;
    }
    return ( sym );
}

static int StripSource( int i, int e, struct asm_tok tokenarray[] )
{
    struct asym *a;
    struct dsym *sym;
    struct dsym *dp;
    struct proc_info *info;
    struct dsym *curr;
    int proc_id = 0;
    int parg_id = 0;
    char b[MAX_LINE_LEN];
    char *p;
    int k, j,lang;

    b[0] = NULLC;
    for ( j = 0; j < i; j++ ) {

	if ( j && tokenarray[j].token != T_DOT ) {

	    if ( tokenarray[j].token == T_COMMA ) {

		if ( proc_id )
		    parg_id++;

	    } else {

		if ( tokenarray[j].hll_flags & T_HLL_PROC ) {

		    proc_id = j;
		    parg_id = 0;
		}
		strcat( b, " " );
	    }
	}
	strcat( b, tokenarray[j].string_ptr );
    }

    p = NULL;
    if ( proc_id && tokenarray[proc_id].token != T_OP_SQ_BRACKET ) {

	if ( (sym = (struct dsym *)GetProc( tokenarray[proc_id].string_ptr )) ) {

	    info = sym->e.procinfo;
	    curr = info->paralist;
	    lang = sym->sym.langtype;

	    k = ( lang == LANG_STDCALL || lang == LANG_C || lang == LANG_SYSCALL ||
		  lang == LANG_VECTORCALL || ( lang == LANG_FASTCALL && ModuleInfo.Ofssize != USE16 ) );

	    if ( k ) {
		while ( curr && curr->nextparam )
		    curr = curr->nextparam;
	    }
	    while ( curr && parg_id ) {

		/* set paracurr to next parameter */

		if ( k ) {
		    dp = curr;
		    for ( curr = info->paralist; curr && curr->nextparam != dp;
			curr = curr->nextparam )
			;
		} else {
		    curr = curr->nextparam;
		}
		parg_id--;
	    }

	    if ( curr ) {
		switch ( curr->sym.total_size ) {
		case 1:
		    p = " al";
		    break;
		case 2:
		    p = " ax";
		    break;
		case 4:
		    p = " eax";
		    if ( ModuleInfo.Ofssize == USE64 ) {
			if ( curr->sym.mem_type & MT_FLOAT )
			    p = " xmm0";
		    }
		    break;
		case 8:
		    if ( ModuleInfo.Ofssize == USE64 ) {
			if ( curr->sym.mem_type & MT_FLOAT )
			    p = " xmm0";
			else
			    p = " rax";
		    } else
			p = " edx::eax";
		    break;
		case 16:
		    if ( curr->sym.mem_type & MT_FLOAT )
			p = " xmm0";
		    else if ( ModuleInfo.Ofssize == USE64 )
			p = " rdx::rax";
		    break;
	       }
	    }
	}
    }

    if ( p == NULL ) {

#ifndef __ASMC64__
	p = " eax";
	if ( ModuleInfo.Ofssize == USE64 )
	    p = " rax";
	else if ( ModuleInfo.Ofssize == USE16 )
	    p = " ax";
#else
	p = " rax";
#endif

	if ( !proc_id && i > 1 ) {

	    j = i - 2;
	    if ( tokenarray[j+1].token == T_COMMA && tokenarray[j].token != T_CL_SQ_BRACKET ) {

		/* <op> <reg|id> <,> <proc> */

		k = 0;
		if ( tokenarray[j].token == T_REG )
		    k = SizeFromRegister( tokenarray[j].tokval );
		else if ( ( a = SymFind( tokenarray[j].string_ptr ) ) != NULL ) {

		    /* movsd id,cos(..) */

		    if ( ModuleInfo.Ofssize == USE64 &&
			( a->mem_type == MT_REAL4 || a->mem_type == MT_REAL8 ) )
			k = 16;
		    else
			k = a->total_size;
		}

		if ( k ) {
		    switch ( k ) {
		      case 1: p = " al";  break;
		      case 2: p = " ax";  break;
		      case 4: p = " eax"; break;
		      case 8:
			if ( ModuleInfo.Ofssize == USE64 )
			    p = " rax";
			break;
		      case 16:
			p = " xmm0";
			break;
		    }
		}
	    }
	}
    }

    strcat( b, p );
    if ( tokenarray[e].token != T_FINAL ) {

	strcat( b, " " );
	strcat( b, tokenarray[e].tokpos );
    }

    if ( ModuleInfo.list )
	LstSetPosition();

    strcpy( CurrSource, b );
    Token_Count = Tokenize( b, 0, tokenarray, TOK_DEFAULT );
    return STRING_EXPANDED;
}

static int LKRenderHllProc( char *dst, int i, struct asm_tok tokenarray[] )
{
    char b[MAX_LINE_LEN];
    char ClassVtbl[128];
    int br_count;
    int j, k, x;
    struct asym *tmp;
    struct asym *sym = NULL;
    struct asym *target = NULL;
    int static_struct = 0;
    char *comptr = NULL;
    char *method;
    struct expr opnd;
    int sqbrend = 0;
    uint_32 u;

    strcpy( b, "invoke " );

    if ( tokenarray[i].token == T_OP_SQ_BRACKET ) {
	/*
	 * v2.27 - [reg].Class.Method()
	 *	 - [reg+foo([rax])].Class.Method()
	 *	 - [reg].Method()
	 */
	for ( k = 1, j = i + 1; k && tokenarray[j].token != T_FINAL; j++ ) {

	    if ( tokenarray[j].token == T_OP_SQ_BRACKET )
		k++;
	    else if ( tokenarray[j].token == T_CL_SQ_BRACKET )
		k--;
	    else if ( tokenarray[j].hll_flags & T_HLL_PROC ) {
		if ( LKRenderHllProc( dst, j, tokenarray ) == ERROR )
		    return ERROR;
	    }
	}
	sqbrend = j;

	if ( tokenarray[j].token == T_DOT ) {

	    if ( tokenarray[j+2].token == T_DOT ) {

		/* [reg].Class.Method() */

		method = tokenarray[j+3].string_ptr;
		target = SymFind( tokenarray[j+1].string_ptr );
	    } else if ( tokenarray[j+2].token == T_OP_BRACKET ) {

		/* [reg].Method() -- assume reg:ptr Class */

		method = tokenarray[j+1].string_ptr;
		br_count = i;
		if ( EvalOperand( &br_count, tokenarray, i + 3, &opnd, 0 ) != ERROR )
		    target = opnd.type;
	    }

	    if ( target ) {

		if ( target->state == SYM_TYPE && target->typekind == TYPE_STRUCT ) {

		    /* If Class.Method do not exist assume ClassVtbl.Method do. */

		    u = 0;
		    sym = target;
		    if ( SearchNameInStruct( sym, method, &u, 0 ) ) {
			sym = NULL;
			target = NULL;
		    }
		} else
		    target = NULL;
	    }
	}

    } else {

	sym = SymFind( tokenarray[i].string_ptr );
	if ( tokenarray[i+1].token == T_DOT && tokenarray[i+3].token == T_OP_BRACKET )
	    method = tokenarray[i+2].string_ptr;
	else
	    method = NULL;

	if ( sym && method ) {

	    if ( sym->mem_type == MT_TYPE && sym->type ) {
		target = sym->type;
		if ( target->typekind == TYPE_TYPEDEF )
		    target = target->target_type;
		else if ( target->typekind == TYPE_STRUCT ) {

		    if ( tokenarray[i+1].token == T_DOT && tokenarray[i+3].token == T_OP_BRACKET ) {

			static_struct++;
			sym = target;
			if ( SearchNameInStruct( sym, method, &u, 0 ) ) {
			    sym = NULL;
			    target = NULL;
			}
		    }
		} else
		    target = NULL;
	    } else if ( sym->mem_type == MT_PTR && \
		( sym->state == SYM_STACK || sym->state == SYM_EXTERNAL ) ) {

		target = sym->target_type;
	    }
	}
    }

    if ( target ) {

	if ( target->state == SYM_TYPE && target->typekind == TYPE_STRUCT ) {

	    comptr = target->name;
	    /*
	     * ClassVtbl struct
	     *	 Method()
	     * ClassVtbl ends
	     *
	     * Class struct
	     *	 lpVtbl PClassVtbl ?
	     * Class ends
	     */
	    target = SearchNameInStruct( target, method, &u, 0 );
	    tmp = SymFind( strcat( strcpy( ClassVtbl, comptr ), "Vtbl" ) );
	    if ( tmp ) {
		tmp = SearchNameInStruct( tmp, method, &u, 0 );
		if ( tmp ) {
		    target = tmp;
		    comptr = ClassVtbl;
		}
	    }

	    if ( ModuleInfo.Ofssize == USE64 ) {
		tmp = target;
		if ( tmp->mem_type == MT_TYPE && tmp->type ) {
		    tmp = tmp->type;
		    if ( tmp->typekind == TYPE_TYPEDEF )
			tmp = tmp->target_type;
		}
		if ( tmp->langtype == LANG_SYSCALL )
		    strcat(b, "[r10]." ); /* v2.28: Added for :vararg */
		else
		    strcat(b, "[rax]." );
	    } else
		strcat(b, "[eax]." );

	    comptr = strcat(b, comptr );
	    if ( tokenarray[i].token == T_OP_SQ_BRACKET ) {

		if ( tokenarray[i+2].token == T_CL_SQ_BRACKET )
		    comptr = tokenarray[i+1].string_ptr;
		else {
		    comptr = strcpy( ClassVtbl, "addr [" );
		    for ( j = i + 1; j < sqbrend; j++ )
			strcat( comptr, tokenarray[j].string_ptr );
		}
	    } else
		comptr = tokenarray[i].string_ptr;

	    if ( target )
		target->method = 1;
	}
    }

    if ( !comptr )
	strcat( b, tokenarray[i].string_ptr );

    k = i + 1;
    if ( tokenarray[i].token == T_OP_SQ_BRACKET ) {

	/* invoke [...][.type].x(...) */

	do {
	    if ( !comptr )
		strcat( b, tokenarray[k].string_ptr );
	    k++;
	} while ( k + 1 < sqbrend );

	if ( !comptr )
	    strcat( b, tokenarray[k].string_ptr );

	k++;
	if ( tokenarray[k+2].token == T_DOT ) {
	    if ( !comptr ) {
		strcat( b, tokenarray[k].string_ptr );
		strcat( b, tokenarray[k+1].string_ptr );
	    }
	    k += 2;
	}
    }

    if ( tokenarray[k].token == T_DOT ) {

	/* invoke p.x(...) */

	strcat( b, tokenarray[k].string_ptr );
	strcat( b, tokenarray[k+1].string_ptr );
	k += 2;
    }

    j = k;
    if ( tokenarray[k].token == T_OP_BRACKET ) {

	k++;
	br_count = 0;

	if ( tokenarray[k].token != T_CL_BRACKET ) {

	    strcat( b, "," );
	    if ( comptr ) {
		if ( static_struct )
		    strcat( b, "addr " );
		strcat( b, comptr );
		strcat( b, "," );
	    }

	    while( 1 ) {

		if ( tokenarray[k].token == '&' ) {
		    strcat( b, "addr " );
		    k++;
		}
		if ( tokenarray[k].hll_flags & T_HLL_PROC ) {

		    if ( LKRenderHllProc( dst, k, tokenarray ) == ERROR )
			return ERROR;
		}
		if ( tokenarray[k].token == T_FINAL )
		    break;

		if ( tokenarray[k].token == T_OP_BRACKET ) {
		    br_count++;
		} else if ( tokenarray[k].token == T_CL_BRACKET ) {
		    if ( br_count == 0 )
			break;
		    br_count--;
		} else if ( tokenarray[k].token != T_COMMA &&
			 tokenarray[k].token != T_DOT &&
			 tokenarray[k].token != T_OP_SQ_BRACKET &&
			 tokenarray[k].token != T_CL_SQ_BRACKET &&
			 tokenarray[k-1].token != T_OP_SQ_BRACKET &&
			 tokenarray[k-1].token != T_CL_SQ_BRACKET &&
			 tokenarray[k-1].token != T_DOT ) {
		    strcat( b, " " );
		}
		strcat( b, tokenarray[k].string_ptr );
		k++;
	    }
	} else if ( comptr ) {
	    strcat( b, ", " );
	    if ( static_struct )
		strcat( b, "addr " );
	    strcat( b, comptr );
	}

	if ( br_count || tokenarray[k].token != T_CL_BRACKET )
	    return ERROR;
	k++;
    }

    /* v2.21 -pe dllimport:<dll> external proto <no args> error
     *
     * externals need invoke for the [_]_imp_ prefix
     */

    if ( !comptr && ( ( k == i + 1 && i ) || ( k == i + 3 && br_count == 0 ) ) ) {

	if ( sym && !( sym->state == SYM_EXTERNAL && sym->dll ) )
	    sym = NULL;

	if ( !sym ) {
	    strcpy( b, "call" );
	    strcat( b, &b[6] );
	}
    }

    if ( *dst )
	strcat( dst, EOLSTR );
    strcat( dst, b );
    return StripSource( i, k, tokenarray );
}

static int RenderHllProc( char *dst, int i, struct asm_tok tokenarray[] )
{
    struct input_status oldstat;
    char *p;
    int rc;

    PushInputStatus( &oldstat );
    rc = LKRenderHllProc( dst, i, tokenarray );
    p = LclAlloc( MAX_LINE_LEN );
    strcpy( p, CurrSource );
    PopInputStatus( &oldstat );
    Token_Count = Tokenize( p, 0, tokenarray, TOK_DEFAULT );
    return rc;
}

/*
 * write assembly test lines to line queue.
 * v2.11: local line buffer removed; src pointer has become a parameter.
 */

int QueueTestLines( char *src )
/*****************************************/
{
    char *start;

    while ( src ) {
	start = src;
	if ( src = strchr( src, EOLCHAR ) )
	    *src++ = NULLC;
	if ( *start ) {
#if 1
	    if ( !( src && !_memicmp(src, "jmp ", 4) && !_memicmp(src, start, 4) ) )
#endif
	    AddLineQueue( start );
	}
    }

    return( NOT_ERROR );
}

int ExpandHllProc( char *dst, int i, struct asm_tok tokenarray[] )
{
    int q;

    *dst = 0;
    if ( ModuleInfo.strict_masm_compat == 0 ) {
	for ( q = i; q < Token_Count; q++ ) {
	    if ( tokenarray[q].hll_flags == T_HLL_PROC ) {
		ExpandCStrings( tokenarray );
		if ( RenderHllProc( dst, q, tokenarray ) == ERROR )
		    return ERROR;
		break;
	    }
	}
    }
    return NOT_ERROR;
}

int ExpandHllProcEx( char *dst, int i, struct asm_tok tokenarray[] )
{
    int rc = ExpandHllProc(dst, i, tokenarray);

    if ( rc != ERROR && dst[0] ) {

	strcat(dst, "\n");
	strcat(dst, tokenarray[0].tokpos);
	QueueTestLines(dst);
	rc = STRING_EXPANDED;
    }

    if ( ModuleInfo.list )
	LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), NULL );
    if ( is_linequeue_populated() )
	RunLineQueue();

    return rc;
}

int EvaluateHllExpression( struct hll_item *hll, int *i, struct asm_tok tokenarray[],
	int ilabel, int is_true, char *buffer )
{
    int q;
    struct hll_opnd hllop = {NULL,0};
    char b[MAX_LINE_LEN];
    char *p, *cp, a, d;

    if ( ModuleInfo.strict_masm_compat == 0 && ( hll->flags & HLLF_EXPRESSION ) == 0
	&& tokenarray[0].hll_flags & T_HLL_DELAY ) {

	for ( q = *i; q < Token_Count; q++ ) {

	    if ( tokenarray[q].hll_flags == T_HLL_MACRO ) {

		strcpy( buffer, tokenarray[0].tokpos );
		hll->flags |= HLLF_EXPRESSION;
		if ( tokenarray[0].hll_flags & T_HLL_DELAYED )
		    hll->flags |= HLLF_DELAYED;

		return NOT_ERROR;
	    }
	}
    }

    if (ExpandHllProc( b, *i, tokenarray ) == ERROR)
	return ERROR;

    *buffer = NULLC;
    if ( ERROR == GetExpression( hll, i, tokenarray, ilabel, is_true, buffer, &hllop ) )
	return( ERROR );
    if ( tokenarray[*i].token != T_FINAL ) {
	return( asmerr( 2154 ) );
    }

    if ( (hll->flags & (HLLF_IFD | HLLF_IFW | HLLF_IFB)) && b[0] ) {

	// Parse a "cmp ax" or "test ax,ax" and resize
	// to B/W/D ([r|e]ax).

	p = buffer;
	while ( *p > ' ' ) p++;
	while ( *p == ' ' ) p++;

	cp = p;
	if ( *cp == 'e' || *cp == 'r' )
	    cp++;

	if ( cp[1] == 'x' ) {

	    q = _memicmp( buffer, "test", 4 );
	    cp = p + 4;
	    while ( *cp == ' ' || *cp == ',' ) cp++;

	    a = p[0];
	    d = p[1];

	    switch (hll->flags & (HLLF_IFD | HLLF_IFW | HLLF_IFB)) {
	    case HLLF_IFD:
		if ( ModuleInfo.Ofssize == USE64 ) {
		    *p = 'e';
		    if ( q == 0 && a == cp[0] && d == cp[1] )
			*cp = 'e';
		}
#ifndef __ASMC64__
		else if ( ModuleInfo.Ofssize == USE16 ) {
		    if ( p[2] != ' ' ) {
			if ( q )
			    memcpy( p - 4, " or", 4);
			else
			    memcpy( p - 5, "and ", 4);
			p--;
		    }
		    p[0] = 'e';
		    p[1] = a;
		    p[2] = d;
		    if ( q == 0 )
			*(cp - 1) = 'e';
		}
#endif
		break;
	    case HLLF_IFW:
		if ( ModuleInfo.Ofssize != USE16 ) {
		    p[0] = ' ';
		    if ( q == 0 && a == cp[0] && d == cp[1] )
			*cp = ' ';
		}
		break;
	    case HLLF_IFB:
#ifndef __ASMC64__
		if ( ModuleInfo.Ofssize == USE16 ) {
		    p[1] = 'l';
		    if ( q == 0 && a == cp[0] && d == cp[1] )
			cp[1] = 'l';
		} else {
#endif
		    p[0] = ' ';
		    p[2] = 'l';
		    if ( q == 0 && a == cp[0] && d == cp[1] ) {
			cp[0] = ' ';
			cp[2] = 'l';
		    }
#ifndef __ASMC64__
		}
#endif
		break;
	    }
	}
    }
    if ( b[0] != 0 ) {
	p = b + strlen(b);
	*p++ = EOLCHAR;
	strcpy(p, buffer);
	strcpy(buffer, b);
    }

    return( NOT_ERROR );
}

/* for .UNTILCXZ: check if expression is simple enough.
 * what's acceptable is ONE condition, and just operators == and !=
 * Constants (0 or != 0) are also accepted.
 */

static int CheckCXZLines( char *p )
{
    int lines = 0;
    int i;
    int addchars;
    char *px;
    int NL = TRUE;

    /* syntax ".untilcxz 1" has a problem: there's no "jmp" generated at all.
     * if this syntax is to be supported, activate the #if below.
     */
    for (; *p; p++ ) {
	if ( *p == EOLCHAR ) {
	    NL = TRUE;
	    lines++;
	} else if ( NL ) {
	    NL = FALSE;
	    if ( *p == 'j' ) {
		p++;
		/* v2.06: rewritten */
		if ( *p == 'm' && lines == 0 ) {
		    addchars = 2; /* make room for 2 chars, to replace "jmp" by "loope" */
		    px = "loope";
		} else if ( lines == 1 && ( *p == 'z' || (*p == 'n' && *(p+1) == 'z') ) ) {
		    addchars = 3; /* make room for 3 chars, to replace "jz"/"jnz" by "loopz"/"loopnz" */
		    px = "loop";
		} else
		    return( ERROR ); /* anything else is "too complex" */
		for ( p--, i = strlen( p ); i >= 0; i-- ) {
		    *(p+addchars+i) = *(p+i);
		}
		memcpy( p, px, strlen( px ) );
	    }
	}
    }
    if ( lines > 2 )
	return( ERROR );
    return( NOT_ERROR );
}

int ExpandHllExpression( struct hll_item *hll, int *i, struct asm_tok tokenarray[],
	int ilabel, int is_true, char *buffer )
{
    int rc = NOT_ERROR;
    struct input_status oldstat;
    char *p;

    PushInputStatus( &oldstat );

    if ( hll->flags & HLLF_WHILE )
	p = hll->condlines;
    else
	p = buffer;

    strcpy( CurrSource, p );
    Token_Count = Tokenize( CurrSource, 0, tokenarray, TOK_DEFAULT );

    if ( Parse_Pass == PASS_1 ) {

	if ( ModuleInfo.g.line_queue.head )
	    RunLineQueue();

	if ( hll->flags & HLLF_DELAYED ) {
	    NoLineStore = 1;
	    rc = ExpandLine( CurrSource, tokenarray );
	    NoLineStore = 0;
	    if ( rc != NOT_ERROR )
		return rc;
	}

	hll->flags &= ~HLLF_WHILE;
	rc = EvaluateHllExpression( hll, i, tokenarray, ilabel, is_true, buffer );
	QueueTestLines( buffer );

    } else {

	if ( ModuleInfo.list )
	    LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), NULL );

	RunLineQueue(); /* before macro's expanded */

	if ( (rc = ExpandLine( CurrSource, tokenarray )) == NOT_ERROR ) {
	    hll->flags &= ~HLLF_WHILE;
	    rc = EvaluateHllExpression( hll, i, tokenarray, ilabel, is_true, buffer );
	    QueueTestLines( buffer );
	}
    }
    PopInputStatus( &oldstat );
    Token_Count = Tokenize(CurrSource, 0, tokenarray, TOK_DEFAULT);
    hll->flags &= ~HLLF_EXPRESSION;
    return rc;
}

static void RenderUntilXX( struct hll_item *hll, unsigned cmd )
{
    char buffer[32];
    int T = T_CX - T_AX;

#ifndef __ASMC64__
    if ( ModuleInfo.Ofssize == USE16 )
	T += T_AX;
    else if ( ModuleInfo.Ofssize == USE32 )
	T += T_EAX;
    else
#endif
	T += T_RAX;

    AddLineQueueX( " %r %r", T_DEC, T );
    AddLineQueueX( " jnz %s", GetLabelStr( hll->labels[LSTART], buffer ) );
}

static char *GetJumpString( int cmd, char *buffer )
{
    int x = 0;

    switch ( cmd ) {
    case T_DOT_IFA:
    case T_DOT_UNTILA:
    case T_DOT_WHILEA:
	x = T_JBE;
	break;
    case T_DOT_IFB:
    case T_DOT_IFC:
    case T_DOT_UNTILB:
    case T_DOT_WHILEB:
	x = T_JAE;
	break;
    case T_DOT_IFG:
    case T_DOT_UNTILG:
    case T_DOT_WHILEG:
	x = T_JLE;
	break;
    case T_DOT_IFL:
    case T_DOT_UNTILL:
    case T_DOT_WHILEL:
	x = T_JGE;
	break;
    case T_DOT_IFO:
    case T_DOT_UNTILO:
    case T_DOT_WHILEO:
	x = T_JNO;
	break;
    case T_DOT_IFP:
    case T_DOT_UNTILP:
    case T_DOT_WHILEP:
	x = T_JNP;
	break;
    case T_DOT_IFS:
    case T_DOT_UNTILS:
    case T_DOT_WHILES:
	x = T_JNS;
	break;
    case T_DOT_IFZ:
    case T_DOT_WHILEZ:
    case T_DOT_UNTILZ:
	x = T_JNE;
	break;
    case T_DOT_IFNA:
    case T_DOT_UNTILNA:
    case T_DOT_WHILENA:
	x = T_JA;
	break;
    case T_DOT_IFNC:
    case T_DOT_IFNB:
    case T_DOT_UNTILNB:
    case T_DOT_WHILENB:
	x = T_JB;
	break;
    case T_DOT_IFNG:
    case T_DOT_UNTILNG:
    case T_DOT_WHILENG:
	x = T_JG;
	break;
    case T_DOT_IFNL:
    case T_DOT_UNTILNL:
    case T_DOT_WHILENL:
	x = T_JL;
	break;
    case T_DOT_IFNO:
    case T_DOT_UNTILNO:
    case T_DOT_WHILENO:
	x = T_JO;
	break;
    case T_DOT_IFNP:
    case T_DOT_UNTILNP:
    case T_DOT_WHILENP:
	x = T_JP;
	break;
    case T_DOT_IFNS:
    case T_DOT_UNTILNS:
    case T_DOT_WHILENS:
	x = T_JS;
	break;
    case T_DOT_IFNZ:
    case T_DOT_WHILENZ:
    case T_DOT_UNTILNZ:
	x = T_JZ;
	break;
    default:
	asmerr( 1011 );
    }
    buffer[0] = NULLC;
    GetResWName( x, buffer );
    if (buffer[2] == 0) {
	buffer[2] = ' ';
	buffer[3] = 0;
    }
    return( buffer );
}

/* .IF, .WHILE, .SWITCH or .REPEAT directive */

int HllStartDir( int i, struct asm_tok tokenarray[] )
/********************************************************/
{
    struct hll_item *hll;
    int	 rc = NOT_ERROR;
    int	 cmd = tokenarray[i].tokval;
    int	 token;
    char buff[16];
    char buffer[MAX_LINE_LEN*2];

    i++; /* skip directive */
    /* added v2.22 to seperate:
     *
     * .IFS from .IFS <expression>
     * .IFB from .IFB <expression>
     */
    token = tokenarray[i].token;

    /* v2.06: is there an item on the free stack? */
    if ( HllFree ) {
	hll = HllFree;
    } else {
	hll = (struct hll_item *)LclAlloc( sizeof( struct hll_item ) );
    }

    /* structure for .IF .ELSE .ENDIF
     *	  cond jump to LTEST-label
     *	  ...
     *	  jmp LEXIT
     *	LTEST:
     *	  ...
     *	LEXIT:

     * structure for .IF .ELSEIF
     *	  cond jump to LTEST
     *	  ...
     *	  jmp LEXIT
     *	LTEST:
     *	  cond jump to (new) LTEST
     *	  ...
     *	  jmp LEXIT
     *	LTEST:
     *	  ...

     * structure for .WHILE, .SWITCH and .REPEAT:
     *	 jmp LTEST (for .WHILE and .SWITCH only)
     * LSTART:
     *	 ...
     * LTEST: (jumped to by .continue)
     *	 a) test end condition, cond jump to LSTART label
     *	 b) unconditional jump to LSTART label
     * LEXIT: (jumped to by .BREAK)
     */

    hll->labels[LEXIT]	= 0;
    hll->flags		= 0;

    switch ( cmd ) {

    DOT_IF:
    case T_DOT_IF:

	hll->cmd = HLL_IF;
	hll->labels[LSTART] = 0; /* not used by .IF */
	hll->labels[LTEST] = GetHllLabel();

	/* get the C-style expression, convert to ASM code lines */
	rc = EvaluateHllExpression( hll, &i, tokenarray, LTEST, FALSE, buffer );
	if ( rc == NOT_ERROR ) {
	    QueueTestLines( buffer );
	    /* if no lines have been created, the LTEST label isn't needed */
	    if ( buffer[0] == NULLC ) {
		hll->labels[LTEST] = 0;
	    }
	}
	break;

    case T_DOT_WHILEA:
    case T_DOT_WHILEG:
    case T_DOT_WHILEL:
    case T_DOT_WHILEO:
    case T_DOT_WHILEP:
    case T_DOT_WHILEZ:
    case T_DOT_WHILENA:
    case T_DOT_WHILENB:
    case T_DOT_WHILENG:
    case T_DOT_WHILENL:
    case T_DOT_WHILENO:
    case T_DOT_WHILENP:
    case T_DOT_WHILENS:
    case T_DOT_WHILENZ:
    case T_DOT_WHILEB:
    case T_DOT_WHILES:
    case T_DOT_WHILEW:
    case T_DOT_WHILED:
    case T_DOT_WHILESB:
    case T_DOT_WHILESW:
    case T_DOT_WHILESD:

    case T_DOT_WHILE:
	hll->flags |= HLLF_WHILE;
    case T_DOT_REPEAT:
	/* create the label to start of loop */
	hll->labels[LSTART] = GetHllLabel();
	hll->labels[LTEST] = 0; /* v2.11: test label is created only if needed */

	if ( cmd != T_DOT_REPEAT ) {

	    hll->cmd = HLL_WHILE;
	    hll->condlines = NULL;

	    if ( tokenarray[i].token != T_FINAL ) {

		switch ( cmd ) {
		case T_DOT_WHILESB:
		    hll->flags |= HLLF_IFS;
		case T_DOT_WHILEB:
		    hll->flags |= HLLF_IFB;
		    break;
		case T_DOT_WHILESW:
		    hll->flags |= HLLF_IFS;
		case T_DOT_WHILEW:
		    hll->flags |= HLLF_IFW;
		    break;
		case T_DOT_WHILESD:
		    hll->flags |= HLLF_IFS;
		case T_DOT_WHILED:
		    hll->flags |= HLLF_IFD;
		    break;
		case T_DOT_WHILES:
		    hll->flags |= HLLF_IFS;
		    break;
		}

		rc = EvaluateHllExpression( hll, &i, tokenarray, LSTART, TRUE, buffer );
		if ( rc == NOT_ERROR ) {
		    int size;

		    alloc_cond:

		    size = strlen( buffer ) + 1;
		    hll->condlines = (char *)LclAlloc( size );
		    memcpy( hll->condlines, buffer, size );
		}
	    } else if ( cmd != T_DOT_WHILE ) {

		GetLabelStr( hll->labels[LSTART], &buffer[20] );
		GetJumpString( cmd, buffer );
		strcat( buffer, " " );
		strcat( buffer, &buffer[20] );
		InvertJump( buffer );
		goto alloc_cond;

	    } else
		buffer[0] = NULLC;  /* just ".while" without expression is accepted */

	    /* create a jump to test label */
	    /* optimisation: if line at 'test' label is just a jump, dont create label and don't jump! */
	    if ( _memicmp( buffer, "jmp", 3 ) ) {
		hll->labels[LTEST] = GetHllLabel();
		AddLineQueueX( JMPPREFIX "jmp %s", GetLabelStr( hll->labels[LTEST], buff ) );
	    }
	} else {
	    hll->cmd = HLL_REPEAT;
	}
	if ( ModuleInfo.loopalign )
	    AddLineQueueX( "ALIGN %d", 1 << ModuleInfo.loopalign );
	AddLineQueueX( "%s" LABELQUAL, GetLabelStr( hll->labels[LSTART], buff ) );
	break;
    case T_DOT_IFS:
	if ( token != T_FINAL ) {
	    hll->flags |= HLLF_IFS;
	    goto DOT_IF;
	}
    case T_DOT_IFC:
    case T_DOT_IFB:
	if ( token != T_FINAL ) {
	    hll->flags |= HLLF_IFB;
	    goto DOT_IF;
	}
    case T_DOT_IFA:
    case T_DOT_IFG:
    case T_DOT_IFL:
    case T_DOT_IFO:
    case T_DOT_IFP:
    case T_DOT_IFZ:
    case T_DOT_IFNA:
    case T_DOT_IFNB:
    case T_DOT_IFNC:
    case T_DOT_IFNG:
    case T_DOT_IFNL:
    case T_DOT_IFNO:
    case T_DOT_IFNP:
    case T_DOT_IFNS:
    case T_DOT_IFNZ:
	hll->cmd = HLL_IF;
	hll->labels[LSTART] = 0;
	hll->labels[LTEST] = GetHllLabel();
	GetLabelStr( hll->labels[LTEST], buff );
	GetJumpString( cmd, buffer );
	strcat( buffer, " " );
	strcat( buffer, buff );
	AddLineQueue( buffer );
	break;
    case T_DOT_IFSD:
	hll->flags |= HLLF_IFS;
    case T_DOT_IFD:
	hll->flags |= HLLF_IFD;
	goto DOT_IF;
    case T_DOT_IFSW:
	hll->flags |= HLLF_IFS;
    case T_DOT_IFW:
	hll->flags |= HLLF_IFW;
	goto DOT_IF;
    case T_DOT_IFSB:
	hll->flags |= (HLLF_IFB | HLLF_IFS);
	goto DOT_IF;
    }

    if (!hll->flags && (tokenarray[i].token != T_FINAL && rc == NOT_ERROR) ) {
	asmerr(2008, tokenarray[i].tokpos );
	rc = ERROR;
    }
    /* v2.06: remove the item from the free stack */
    if ( hll == HllFree )
	HllFree = hll->next;
    hll->next = HllStack;
    HllStack = hll;

    if ( ModuleInfo.list )
	LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), NULL );

    if ( is_linequeue_populated() ) /* might be NULL! (".if 1") */
	RunLineQueue();

    return( rc );
}

/*
 * .ENDIF, .ENDW, .UNTIL and .UNTILCXZ directives.
 * These directives end a .IF, .WHILE or .REPEAT block.
 */
int HllEndDir( int i, struct asm_tok tokenarray[] )
{
    struct hll_item *hll;
    int	   rc = NOT_ERROR;
    int	   cmd = tokenarray[i].tokval;
    int	   x;
    char   buff[16];
    char   buffer[MAX_LINE_LEN];

    if ( HllStack == NULL )
	return( asmerr( 1011 ) );

    hll = HllStack;
    HllStack = hll->next;
    /* v2.06: move the item to the free stack */
    hll->next = HllFree;
    HllFree = hll;

    switch ( cmd ) {

    case T_DOT_ENDIF:
	if ( hll->cmd != HLL_IF )
	    return( asmerr( 1011 ) );
	i++;
	/* if a test label isn't created yet, create it */
	if ( hll->labels[LTEST] )
	    AddLineQueueX( "%s" LABELQUAL, GetLabelStr( hll->labels[LTEST], buff ) );
	break;

    case T_DOT_ENDW:
	if ( hll->cmd != HLL_WHILE )
	    return( asmerr( 1011 ) );
	/* create test label */
	if ( hll->labels[LTEST] )
	    AddLineQueueX( "%s" LABELQUAL, GetLabelStr( hll->labels[LTEST], buff ) );
	i++;
	if ( hll->flags & HLLF_EXPRESSION )
	    ExpandHllExpression( hll, &i, tokenarray, LSTART, TRUE, buffer );
	else
	    QueueTestLines( hll->condlines );
	break;

    case T_DOT_UNTILCXZ:
	if ( hll->cmd != HLL_REPEAT ) {
	    return( asmerr( 1010, tokenarray[i].string_ptr ) );
	}
	i++;
	if ( hll->labels[LTEST] ) /* v2.11: LTEST only needed if .CONTINUE has occured */
	    AddLineQueueX( "%s" LABELQUAL, GetLabelStr( hll->labels[LTEST], buff ) );

	/* read in optional (simple) expression */
	if ( tokenarray[i].token != T_FINAL ) {

	    x = LSTART;
	    if ( !Options.masm_compat_gencode && !ModuleInfo.strict_masm_compat ) {

		/* <expression> ? .BREAK */
		if ( !hll->labels[LEXIT] )
		    hll->labels[LEXIT] = GetHllLabel();

		x = LEXIT;
	    }
	    rc = EvaluateHllExpression( hll, &i, tokenarray, x, FALSE, buffer );
	    if ( rc == NOT_ERROR ) {

		if ( ModuleInfo.strict_masm_compat ||
		     ( Options.masm_compat_gencode && cmd == T_DOT_UNTILCXZ ) )
		    rc = CheckCXZLines( buffer );

		if ( rc == NOT_ERROR ) {
		    QueueTestLines( buffer ); /* write condition lines */
		    if ( !Options.masm_compat_gencode && !ModuleInfo.strict_masm_compat )
			RenderUntilXX( hll, cmd );
		} else {
		    asmerr( 2062 );
		}
	    }
	} else {
	    if ( ModuleInfo.strict_masm_compat || Options.masm_compat_gencode )
		AddLineQueueX( JMPPREFIX "loop %s", GetLabelStr( hll->labels[LSTART], buff ) );
	    else
		RenderUntilXX( hll, cmd );
	}
	break;

    case T_DOT_UNTILA:
    case T_DOT_UNTILG:
    case T_DOT_UNTILL:
    case T_DOT_UNTILO:
    case T_DOT_UNTILP:
    case T_DOT_UNTILZ:
    case T_DOT_UNTILNA:
    case T_DOT_UNTILNB:
    case T_DOT_UNTILNG:
    case T_DOT_UNTILNL:
    case T_DOT_UNTILNO:
    case T_DOT_UNTILNP:
    case T_DOT_UNTILNS:
    case T_DOT_UNTILNZ:
    case T_DOT_UNTILB:
    case T_DOT_UNTILS:
    case T_DOT_UNTILW:
    case T_DOT_UNTILD:
    case T_DOT_UNTILSB:
    case T_DOT_UNTILSW:
    case T_DOT_UNTILSD:

    case T_DOT_UNTIL:
	if ( hll->cmd != HLL_REPEAT ) {
	    return( asmerr( 1010, tokenarray[i].string_ptr ) );
	}
	i++;
	if ( hll->labels[LTEST] ) /* v2.11: LTEST only needed if .CONTINUE has occured */
	    AddLineQueueX( "%s" LABELQUAL, GetLabelStr( hll->labels[LTEST], buff ) );

	/* read in (optional) expression */
	/* if expression is missing, just generate nothing */
	if ( tokenarray[i].token != T_FINAL ) {

	    switch ( cmd ) {
	    case T_DOT_UNTILSB:
		hll->flags |= HLLF_IFS;
	    case T_DOT_UNTILB:
		hll->flags |= HLLF_IFB;
		break;
	    case T_DOT_UNTILSW:
		hll->flags |= HLLF_IFS;
	    case T_DOT_UNTILW:
		hll->flags |= HLLF_IFW;
		break;
	    case T_DOT_UNTILSD:
		hll->flags |= HLLF_IFS;
	    case T_DOT_UNTILD:
		hll->flags |= HLLF_IFD;
		break;
	    case T_DOT_UNTILS:
		hll->flags |= HLLF_IFS;
		break;
	    }
	    rc = EvaluateHllExpression( hll, &i, tokenarray, LSTART, FALSE, buffer );
	    if ( rc == NOT_ERROR )
		QueueTestLines( buffer ); /* write condition lines */
	} else if ( cmd != T_DOT_UNTIL ) {

	    GetLabelStr( hll->labels[LSTART], &buffer[20] );
	    GetJumpString( cmd, buffer );
	    strcat( buffer, " " );
	    strcat( buffer, &buffer[20] );
	    AddLineQueue( buffer );
	}
	break;
    }

    /* create the exit label if it has been referenced */
    if ( hll->labels[LEXIT] )
	AddLineQueueX( "%s" LABELQUAL, GetLabelStr( hll->labels[LEXIT], buff ) );

    if ( tokenarray[i].token != T_FINAL && rc == NOT_ERROR ) {
	asmerr(2008, tokenarray[i].tokpos );
	rc = ERROR;
    }
    if ( ModuleInfo.list )
	LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), NULL );

    /* v2.11: always run line-queue if it's not empty. */
    if ( is_linequeue_populated() )
	RunLineQueue();

    return( rc );
}

int HllContinueIf( struct hll_item *hll, int *i, char *buffer,
	struct asm_tok tokenarray[], int label, struct hll_item *hll_0 )
{
	int  rc = 0;
	char buff[16];
	char *condlines;
	int  x, cmd, flags;

	if ( tokenarray[*i].token != T_FINAL ) {

	    if ( tokenarray[*i].token == T_DIRECTIVE ) {

		x = 0;
		switch ( tokenarray[*i].tokval ) {
		case T_DOT_IFSD:
		    x |= HLLF_IFS;
		case T_DOT_IFD:
		    x |= HLLF_IFD;
		DOT_IF:
		case T_DOT_IF:
		    cmd = hll->cmd;
		    condlines = hll->condlines;
		    flags = hll->flags;
		    hll->flags = x;
		    hll->cmd = HLL_BREAK;
		    (*i)++;
		    rc = EvaluateHllExpression( hll, i, tokenarray, label, 1, buffer );
		    if ( rc == NOT_ERROR )
			QueueTestLines( buffer );
		    hll->flags = flags;
		    hll->condlines = condlines;
		    hll->cmd = cmd;
		    break;

		case T_DOT_IFSB:
		    x |= (HLLF_IFS | HLLF_IFB);
		    goto DOT_IF;
		case T_DOT_IFSW:
		    x |= HLLF_IFS;
		case T_DOT_IFW:
		    x |= HLLF_IFW;
		    goto DOT_IF;
		case T_DOT_IFS:
		    if ( tokenarray[*i+1].token != T_FINAL ) {
			x |= HLLF_IFS;
			goto DOT_IF;
		    }
		case T_DOT_IFC:
		case T_DOT_IFB:
		    if ( tokenarray[*i+1].token != T_FINAL ) {
			x |= HLLF_IFB;
			goto DOT_IF;
		    }
		case T_DOT_IFA:
		case T_DOT_IFG:
		case T_DOT_IFL:
		case T_DOT_IFO:
		case T_DOT_IFP:
		case T_DOT_IFZ:
		case T_DOT_IFNA:
		case T_DOT_IFNB:
		case T_DOT_IFNC:
		case T_DOT_IFNG:
		case T_DOT_IFNL:
		case T_DOT_IFNO:
		case T_DOT_IFNP:
		case T_DOT_IFNS:
		case T_DOT_IFNZ:
		    (*i)++;
		    GetLabelStr( hll->labels[label], buff );
		    GetJumpString( tokenarray[*i-1].tokval, buffer );
		    strcat( buffer, " " );
		    strcat( buffer, buff );
		    InvertJump( buffer );
		    AddLineQueue( buffer );
		    break;
		}
	    }
	} else {
		AddLineQueueX("jmp %s", GetLabelStr( hll->labels[label], buffer ) );

		if ( hll_0->cmd == HLL_SWITCH ) {
			//
			// unconditional jump from .case
			// - set flag to skip exit-jumps
			//
			hll = hll_0;
			while ( hll_0->caselist )
			    hll_0 = hll_0->caselist;
			if ( hll != hll_0 )
			    hll_0->flags |= HLLF_ENDCOCCUR;
		}
	}
	return rc;
}

/*
 * .ELSE, .ELSEIF, .CONTINUE and .BREAK directives.
 * .ELSE, .ELSEIF:
 *    - create a jump to exit label
 *    - render test label if it was referenced
 *    - for .ELSEIF, create new test label and evaluate expression
 * .CONTINUE, .BREAK:
 *    - jump to test / exit label of innermost .WHILE/.REPEAT block
 *
 */
int HllExitDir( int i, struct asm_tok tokenarray[] )
{
    struct hll_item *hll, *n;
    int rc = NOT_ERROR;
    int count = 0;
    int level = 0;
    int idx;
    int cmd = tokenarray[i].tokval;
    char buff[16];
    char buffer[MAX_LINE_LEN];

    hll = HllStack;
    if ( hll == NULL )
	return( asmerr( 1011 ) );

    ExpandCStrings( tokenarray );

    switch ( cmd ) {

    case T_DOT_ELSEIF:
	hll->flags |= HLLF_ELSEIF;
    case T_DOT_ELSE:
	if ( hll->cmd != HLL_IF ) {
	    return( asmerr( 1010, tokenarray[i].string_ptr ) );
	}
	/* v2.08: check for multiple ELSE clauses */
	if ( hll->flags & HLLF_ELSEOCCURED ) {
	    return( asmerr( 2142 ) );
	}

	/* the 'exit'-label is only needed if an .ELSE branch exists.
	 * That's why it is created delayed.
	 */
	if ( hll->labels[LEXIT] == 0 )
	    hll->labels[LEXIT] = GetHllLabel();
	AddLineQueueX( JMPPREFIX "jmp %s", GetLabelStr( hll->labels[LEXIT], buff ) );

	if ( hll->labels[LTEST] > 0 ) {
	    AddLineQueueX( "%s" LABELQUAL, GetLabelStr( hll->labels[LTEST], buff ) );
	    hll->labels[LTEST] = 0;
	}

	i++;
	if ( cmd == T_DOT_ELSEIF ) {
	    /* create new labels[LTEST] label */
	    hll->labels[LTEST] = GetHllLabel();
	    rc = EvaluateHllExpression( hll, &i, tokenarray, LTEST, FALSE, buffer );
	    if ( rc == NOT_ERROR ) {
		if ( hll->flags & HLLF_EXPRESSION ) {
		    rc = ExpandHllExpression( hll, &i, tokenarray, LTEST, FALSE, buffer );
		    i = Token_Count;
		} else {
		    QueueTestLines( buffer );
		}
	    }
	} else
	    hll->flags |= HLLF_ELSEOCCURED;
	break;

    case T_DOT_BREAK:
    case T_DOT_CONTINUE:
	if ( tokenarray[i+1].token == T_OP_BRACKET && tokenarray[i+3].token == T_CL_BRACKET ) {

	    if ( cmd == T_DOT_CONTINUE ) {
		if ( tokenarray[i+2].string_ptr[0] == '0' )
		    count = 1;
	    }
	    level = atol( tokenarray[i+2].string_ptr );
	    i += 3;
	}

	n = hll;
	for ( ; hll && ( hll->cmd == HLL_IF || hll->cmd == HLL_SWITCH ); hll = hll->next )
	    ;

	while ( hll && level ) {
	    for ( hll = hll->next; hll &&
		( hll->cmd == HLL_IF || hll->cmd == HLL_SWITCH); hll = hll->next );
	    level--;
	}
	if ( hll == NULL )
	    return( asmerr( 1011 ) );

	/* v2.11: create 'exit' and 'test' labels delayed.
	 */
	if ( cmd == T_DOT_BREAK ) {
	    if ( hll->labels[LEXIT] == 0 )
		hll->labels[LEXIT] = GetHllLabel();
	    idx = LEXIT;
	} else {
	    /* 'test' is not created for .WHILE loops here; because
	     * if it doesn't exist, there's no condition to test.
	     */
	    if ( hll->cmd == HLL_REPEAT && hll->labels[LTEST] == 0 )
		hll->labels[LTEST] = GetHllLabel();

	    idx = LTEST;
	    if ( count == 1 )
		idx = LSTART;
	    else if ( hll->labels[LTEST] == 0 )
		idx = LSTART;
	}

	/* .BREAK .IF ... or .CONTINUE .IF ? */
	i++;
	rc = HllContinueIf( hll, &i, buffer, tokenarray, idx, n );
	break;
    }
    if ( tokenarray[i].token != T_FINAL && rc == NOT_ERROR ) {
	asmerr(2008, tokenarray[i].tokpos );
	rc = ERROR;
    }

    if ( ModuleInfo.list )
	LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), NULL );

    /* v2.11: always run line-queue if it's not empty. */
    if ( is_linequeue_populated() )
	RunLineQueue();

    return( rc );
}

/* check if an hll block has been left open. called after pass 1 */

void HllCheckOpen( void )
/***********************/
{
    if ( HllStack ) {
	asmerr( 1010, ".if-.repeat-.while" );
    }
}

/* HllInit() is called for each pass */

void HllInit( int pass )
/**********************/
{
    ModuleInfo.hll_label = 0; /* init hll label counter */
    return;
}
