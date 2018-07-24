#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>

#include <globals.h>
#include <hllext.h>


static void addlq_label_b( int id, char *buffer )
{
    AddLineQueueX( "%s" LABELQUAL, GetLabelStr( id, buffer ) );
}

static void addlq_label( int id )
{
    char buffer[32];

    addlq_label_b( id, buffer );
}

static void addlq_jxx_label( int x, int id )
{
    char buffer[32];

    AddLineQueueX( "%r %s", x, GetLabelStr( id, buffer ) );
}

static void addlq_jxx_label64( int x, char *base, int id )
{
    char buffer[32];

    AddLineQueueX( "%r %s-%s", x, base, GetLabelStr( id, buffer ) );
}

static void RenderCase( struct hll_item *hll, struct hll_item *hll_c, char *buffer )
{
    int l;
    char *p;
    char *cp = hll_c->condlines;

    if ( !cp ) {
	addlq_jxx_label( T_JMP, hll_c->labels[LSTART] );
    } else if ( ( p = strchr( cp, '.' ) ) && p[1] == '.' ) {
	*p = NULLC;
	p += 2;
	AddLineQueueX( "cmp %s,%s", hll->condlines, cp );
	l = GetHllLabel();
	addlq_jxx_label( T_JB, l );
	AddLineQueueX( "cmp %s,%s", hll->condlines, p );
	addlq_jxx_label( T_JBE, hll_c->labels[LSTART] );
	addlq_label( l );
    } else {
	AddLineQueueX( "cmp %s,%s", hll->condlines, cp );
	addlq_jxx_label( T_JE, hll_c->labels[LSTART] );
    }
}

static void RenderCCMP( struct hll_item *hll, char *buffer )
{
    struct hll_item *p;

    AddLineQueueX( "%s" LABELQUAL, buffer );

    p = hll->caselist;
    while ( p ) {
	RenderCase( hll, p, buffer );
	p = p->caselist;
    }
}

static int GetLowCount( struct hll_item *hll, int min, int dist )
{
    int rc = 0;

    min += dist;
    hll = hll->caselist;

    while ( hll ) {

	if ( ( hll->flags & HLLF_TABLE ) && min >= hll->labels[0] )
	    rc++;

	hll = hll->caselist;
    }
    return rc;
}

static int GetHighCount( struct hll_item *hll, int max, int dist )
{
    int rc = 0;

    max -= dist;
    hll = hll->caselist;

    while ( hll ) {

	if ( ( hll->flags & HLLF_TABLE ) && max <= hll->labels[0] )
	    rc++;

	hll = hll->caselist;
    }
    return rc;
}

static int SetLowCount( struct hll_item *hll, int *count, int min, int dist )
{
    int rc = 0;

    min += dist;
    hll = hll->caselist;

    while ( hll ) {

	if ( ( hll->flags & HLLF_TABLE ) && min < hll->labels[0] ) {

	    hll->flags &= ~HLLF_TABLE;
	    (*count)--;
	    rc++;
	}
	hll = hll->caselist;
    }
    return rc;
}

static int SetHighCount( struct hll_item *hll, int *count, int max, int dist )
{
    int rc = 0;

    max -= dist;
    hll = hll->caselist;

    while ( hll ) {

	if ( ( hll->flags & HLLF_TABLE ) && max > hll->labels[0] ) {

	    hll->flags &= ~HLLF_TABLE;
	    (*count)--;
	    rc++;
	}
	hll = hll->caselist;
    }
    return rc;
}

static struct hll_item *GetCaseVal( struct hll_item *hll, int val )
{
    struct hll_item *hp;

    hp = hll->caselist;
    while ( hp ) {

	if ( ( hp->flags & HLLF_TABLE ) && val == hp->labels[0] )
	    return hp;

	hp = hp->caselist;
    }
    return NULL;
}

static int RemoveVal( struct hll_item *hll, int val )
{
    struct hll_item *p;

    if ( (p = GetCaseVal( hll, val )) ) {

	p->flags &= ~HLLF_TABLE;
	return 1;
    }
    return 0;
}

static int GetCaseValue( struct hll_item *hll,
    struct asm_tok tokenarray[], int *dcount, int *scount )
{
    int i;
    struct expr opnd;
    struct hll_item *hp;
    struct hll_item *xp;
    unsigned int l,h;


    *scount = 0;
    *dcount = 0;
    hp = hll->caselist;

    while ( hp ) {

	if ( hp->flags & HLLF_NUM ) {

	    hp->flags |= HLLF_TABLE;
	    Token_Count = Tokenize( hp->condlines, 0, tokenarray, TOK_DEFAULT );
	    i = 0;
	    if ( EvalOperand( &i, tokenarray, Token_Count, &opnd, EXPF_NOERRMSG ) != NOT_ERROR )
		break;

	    l = (unsigned int)opnd.value64;
	    h = (unsigned int)(opnd.value64 >> 32);
	    if ( opnd.kind == EXPR_ADDR ) {

		l += opnd.sym->offset;
		h = 0;
	    }
	    hp->labels[LTEST] = l;
	    hp->labels[LEXIT] = h;

	    (*scount)++;

	} else if ( hp->condlines ) {

	    (*dcount)++;
	}
	hp = hp->caselist;
    }

    Token_Count = Tokenize( CurrSource, 0, tokenarray, TOK_DEFAULT );

    /* error A3022 : .CASE redefinition : %s(%d) : %s(%d) */

    if ( *scount && Parse_Pass != PASS_1 ) {

	hll = hll->caselist;
	hp  = hll->caselist;

	while ( hp ) {

	    if ( hll->flags & HLLF_NUM ) {
		if ( (xp = GetCaseVal( hll, hll->labels[0] )) )
		    asmerr( 3022, hll->condlines, hll->labels[0], xp->condlines, xp->labels[0] );
	    }
	    hll = hll->caselist;
	    hp	= hll->caselist;
	}
    }
    return *scount;
}

static int GetMaxCaseValue( struct hll_item *hll,
    int *min, int *max, int *min_table, int *max_table, int *tcases )
{
    int i,q;
    struct hll_item *hp;

    i = 0;
    *max = 0x80000000;
    *min = 0x7FFFFFFF;
    hp = hll->caselist;
    while ( hp ) {
	if ( hp->flags & HLLF_TABLE ) {
	    i++;
	    if ( *max <= (int)hp->labels[0] )
		*max = hp->labels[0];
	    if ( *min >= (int)hp->labels[0] )
		*min = hp->labels[0];
	}
	hp = hp->caselist;
    }
    if ( i == 0 ) {
	*max = 0;
	*min = 0;
    }

    q = 1;
    *min_table = MIN_JTABLE;
    if ( !( hll->flags & HLLF_ARGREG ) ) {

	q++;
	*min_table += 2;
	if ( !( hll->flags & ( HLLF_ARG16 | HLLF_ARG32 | HLLF_ARG64 ) ) ) {
	    (*min_table)++;
	    if ( !( ModuleInfo.aflag & _AF_REGAX ) )
		*min_table += 10;
	}
    }

    *max_table = (i << q);
    *tcases = i;
    return (*max - *min + 1);
}

static void RenderCaseExit( struct hll_item *hll )
{
    struct hll_item *p;

    p = hll;
    while ( p->caselist )
	p = p->caselist;

    if ( p != hll ) {

	if ( !( p->flags & HLLF_ENDCOCCUR ) ) {

	    if ( Parse_Pass == PASS_1 && !( ModuleInfo.aflag & _AF_PASCAL ) )
		asmerr( 7007 );

	    addlq_jxx_label( T_JMP, hll->labels[LEXIT] );
	}
    }
}

static int IsCaseColon( int i, struct asm_tok tokenarray[] )
{
    int bracket = 0;

    while ( tokenarray[i].token != T_FINAL ) {
	if ( tokenarray[i].token == T_OP_BRACKET ) {
	    bracket++;
	} else if ( tokenarray[i].token == T_CL_BRACKET ) {
	    bracket--;
	} else if ( tokenarray[i].token == T_COLON && !bracket &&
	    !( tokenarray[i-1].token == T_REG &&
	       tokenarray[i-1].tokval >= T_ES && tokenarray[i-1].tokval <= T_ST ) ) {

	    tokenarray[i].token = T_FINAL;
	    return i;
	}
	i++;
    }
    return 0;
}

static int RenderMultiCase( int *ip, char *buffer, struct asm_tok tokenarray[] )
{
    int i = *ip + 1;
    int result = 0;
    int bracket = 0;
    int colon;
    int base;
    char *p;

    base = i;
    colon = IsCaseColon( i, tokenarray );

    while ( tokenarray[i].token != T_FINAL ) {
       /*
	* Split .case 1,2,3 to
	*
	*	 .case 1
	*	 .case 2
	*	 .case 3
	*/
	if ( tokenarray[i].token == T_OP_BRACKET )
	    bracket++;
	else if ( tokenarray[i].token == T_CL_BRACKET )
	    bracket--;
	else if ( tokenarray[i].token == T_COMMA && !bracket ) {
	    p = tokenarray[i].tokpos;
	    *p = NULLC;
	    strcpy( buffer, tokenarray[base].tokpos );
	    base = i + 1;
	    *p = ',';
	    result++;
	    AddLineQueueX( ".case %s", buffer );
	    tokenarray[i].token = T_FINAL;
	}
	i++;
    }
    if ( colon )
	tokenarray[colon].token = T_COLON;

    if ( result ) {

	AddLineQueueX( ".case %s", tokenarray[base].tokpos );
	while ( tokenarray[*ip].token != T_FINAL )
	    (*ip)++;

	if ( ModuleInfo.aflag & _AF_PASCAL ) {

	    ModuleInfo.aflag &= ~_AF_PASCAL;

	    if ( ModuleInfo.list )
		LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), NULL );

	    RunLineQueue();
	    ModuleInfo.aflag |= _AF_PASCAL;
	}
	return 1;
    }
    return 0;
}

static void CompareMaxMin( char *reg, int max, int min, char *around )
{
    AddLineQueueX( "cmp %s,%d", reg, min );
    AddLineQueueX( "jl %s", around );
    AddLineQueueX( "cmp %s,%d", reg, max );
    AddLineQueueX( "jg %s", around );
}


/* Move .SWITCH <arg> to [R|E]AX */

static void GetSwitchArg( int reg, int flags, char *arg )
{
    char buffer[64];

    if ( !( ModuleInfo.aflag & _AF_REGAX ) )
	AddLineQueueX( "push %r", reg );

    GetResWName( reg, buffer );

    if ( !( flags & ( HLLF_ARG16 | HLLF_ARG32 | HLLF_ARG64 ) ) ) {

	/* BYTE value */

	if ( ( ModuleInfo.curr_cpu & P_CPU_MASK ) >= P_386 ) {
	    if ( flags & HLLF_ARGMEM )
		AddLineQueueX( "movsx %r,BYTE PTR %s", reg, arg );
	    else
		AddLineQueueX( "movsx %r,%s", reg, arg );
	} else {
	    if ( _stricmp( "al", arg ) )
		AddLineQueueX( "mov al,%s", arg );
	    AddLineQueue ( "cbw" );
	}

    } else if ( flags & HLLF_ARG16 ) {

	/* WORD value */

	if ( ModuleInfo.Ofssize == USE16 ) {
	    if ( flags & HLLF_ARGMEM )
		AddLineQueueX( "mov %r,WORD PTR %s", reg, arg );
	    else if ( _stricmp( arg, buffer ) )
		AddLineQueueX( "mov %r,%s", reg, arg );
	} else if ( flags & HLLF_ARGMEM ) {
	    AddLineQueueX( "movsx %r,WORD PTR %s", reg, arg );
	} else {
	    AddLineQueueX( "movsx %r,%s", reg, arg );
	}

    } else if ( flags & HLLF_ARG32 ) {

	/* DWORD value */

	if ( ModuleInfo.Ofssize == USE32 ) {
	    if ( flags & HLLF_ARGMEM )
		AddLineQueueX( "mov %r,DWORD PTR %s", reg, arg );
	    else if ( _stricmp( arg, buffer ) )
		AddLineQueueX( "mov %r,%s", reg, arg );
	} else if ( flags & HLLF_ARGMEM ) {

	    AddLineQueueX( "movsxd %r,DWORD PTR %s", reg, arg );
	} else {
	    AddLineQueueX( "movsxd %r,%s", reg, arg );
	}
    } else {

	/* QWORD value */

	AddLineQueueX( "mov %r,QWORD PTR %s", reg, arg );
    }
}

static int RenderSwitch( struct hll_item *hll, struct asm_tok tokenarray[],
	char *buffer,  /* switch.labels[LSTART] */
	char *l_exit)  /* switch.labels[LEXIT]	*/
{

    int r_dw;		/* dw/dd/dq				*/
    int r_db;		/* "DB"/"DW"				*/
    int r_size;		/* 2/4/8				*/
    int dynamic;	/* number of dynmaic cases		*/
    int nstatic;	/* number of static const values	*/
    int lcount;		/* number of labels in table		*/
    int icount;		/* number of index to labels in table	*/
    int tcases;		/* number of cases in table		*/
    int ncases = 0;	/* number of cases not in table		*/
    int min_table;
    int max_table;
    int min;		/* minimum const value	*/
    int max;		/* maximum const value	*/
    int dist;		/* max - min		*/
    char l_start[16];	/* current start label	*/
    char l_jtab[16];	/* jump table address	*/
    char labelx[16];	/* label symbol		*/
    char use_index;
    struct hll_item *hp,*xp;
    struct hll_item *c_default = NULL;
    int i,x;
    int l,h;
    char *p;
    struct asym *sym;


    /* get static case-count */

    GetCaseValue( hll, tokenarray, &dynamic, &nstatic );

    if ( ModuleInfo.aflag & _AF_NOTABLE || nstatic < MIN_JTABLE ) {
       /*
	* Time NOTABLE/TABLE
	*
	* .case * 3	 4	 7	 8	 9	 10	 16	 60
	* NOTABLE 1401	 2130	 5521	 5081	 7681	 9481	 18218	 158245
	* TABLE	  1521	 3361	 4402	 6521	 7201	 7881	 9844	 68795
	* elseif  1402	 4269	 5787	 7096	 8481	 10601	 22923	 212888
	*/
	RenderCCMP( hll, buffer );
	return 0;
    }

    r_size = 2;
    r_dw = T_DW;
    if ( ModuleInfo.Ofssize != USE16 ) {
	r_size = 4;
	r_dw = T_DD;
    }
    strcpy( l_start, buffer );


    /* flip exit to default if exist */

    if ( hll->flags & HLLF_ELSEOCCURED ) {

	hp = hll;
	for ( xp = hll->caselist; xp; xp = xp->caselist ) {

	    if ( xp->flags & HLLF_DEFAULT ) {

		hp->caselist = NULL;
		c_default = xp;
		GetLabelStr( xp->labels[LSTART], l_exit );
		break;
	    }
	    hp = xp;
	}
    }

    if ( ModuleInfo.casealign )
	AddLineQueueX( "ALIGN %d", (1 << ModuleInfo.casealign) );
    else if ( hll->flags & HLLF_NOTEST && hll->flags & HLLF_JTABLE )
	AddLineQueueX( "ALIGN %d", r_size );

    AddLineQueueX( "%s" LABELQUAL, l_start );

    if ( dynamic ) {

	hp = hll;
	for ( xp = hp->caselist; xp; xp = xp->caselist ) {

	    if ( !( xp->flags & HLLF_NUM ) ) {

		hp->caselist = xp->caselist;
		RenderCase( hll, xp, buffer );
	    }
	    hp = xp;
	}
    }

    while ( hll->condlines ) {

	ncases = 0;
	dist = GetMaxCaseValue( hll, &min, &max, &min_table, &max_table, &tcases );

	if ( tcases < min_table )
	    break;

	for ( i = tcases; i >= min_table && max > min && dist > max_table; i = tcases ) {

	    l = GetLowCount ( hll, min, max_table );
	    h = GetHighCount( hll, max, max_table );

	    if ( l < min_table ) {
		if ( !(x = RemoveVal( hll, min )) )
		    break;
		tcases -= x;
	    } else if ( h < min_table ) {
		if ( !(x = RemoveVal( hll, max )) )
		    break;
		tcases -= x;
	    } else if ( l >= h ) {
		l = tcases;
		h = SetLowCount( hll, &tcases, min, max_table );
	    } else {
		l = tcases;
		h = SetHighCount( hll, &tcases, max, max_table );
	    }
	    ncases += h;
	    dist = GetMaxCaseValue( hll, &min, &max, &min_table, &max_table, &x );
	    if ( l == tcases )
		break;
	}

	if ( tcases < min_table )
	    break;

	use_index = 0;
	if ( tcases < dist && ModuleInfo.Ofssize == USE64 )
	    use_index++;

	/* Create the jump table lable */

	if ( hll->flags & HLLF_NOTEST && hll->flags & HLLF_JTABLE ) {
	    strcpy( l_jtab, l_start );
	    AddLineQueueX( "MIN%s equ %d", l_jtab, min );
	} else
	    GetLabelStr( GetHllLabel(), l_jtab );

	p = l_exit;
	if ( ncases )
	    p = GetLabelStr( GetHllLabel(), l_start );

	if ( !( hll->flags & HLLF_NOTEST ) )
	    CompareMaxMin( hll->condlines, max, min, p );

	if ( !( hll->flags & HLLF_NOTEST && hll->flags & HLLF_JTABLE ) ) {

	    if ( ModuleInfo.Ofssize == USE16 ) {

		if ( !( ModuleInfo.aflag & _AF_REGAX ) )
		    AddLineQueue( "push ax" );

		if ( hll->flags & HLLF_ARGREG ) {
		    if ( ModuleInfo.aflag & _AF_REGAX ) {
			if ( _stricmp( "ax", hll->condlines ) )
			    AddLineQueueX( "mov ax,%s", hll->condlines );
			AddLineQueue( "xchg ax,bx" );
		    } else {
			AddLineQueue( "push bx" );
			AddLineQueue( "push ax" );
			if ( _stricmp( "bx", hll->condlines ) )
			    AddLineQueueX( "mov bx,%s", hll->condlines );
		    }
		} else {
		    if ( !( ModuleInfo.aflag & _AF_REGAX ) )
			AddLineQueue( "push bx" );
		    GetSwitchArg( T_AX, hll->flags, hll->condlines );
		    if ( ModuleInfo.aflag & _AF_REGAX )
			AddLineQueue( "xchg ax,bx" );
		    else
			AddLineQueue( "mov bx,ax" );
		}
		if ( min )
		    AddLineQueueX( "sub bx,%d", min );
		AddLineQueue ( "add bx,bx" );
		if ( ModuleInfo.aflag & _AF_REGAX ) {
		    AddLineQueueX( "mov bx,cs:[bx+%s]", l_jtab );
		    AddLineQueue ( "xchg ax,bx" );
		    AddLineQueue ( "jmp ax" );
		} else {
		    AddLineQueueX( "mov ax,cs:[bx+%s]", l_jtab );
		    AddLineQueue ( "mov bx,sp" );
		    AddLineQueue ( "mov ss:[bx+4],ax" );
		    AddLineQueue ( "pop ax" );
		    AddLineQueue ( "pop bx" );
		    AddLineQueue ( "retn" );
		}

	    } else if ( ModuleInfo.Ofssize == USE32 ) {

		if ( !( hll->flags & HLLF_ARGREG ) ) {
		    GetSwitchArg(T_EAX, hll->flags, hll->condlines);
		    if ( use_index ) {
			if ( dist < 256 )
			    AddLineQueueX("movzx eax,BYTE PTR [eax+IT%s-(%d)]", l_jtab, min);
			else
			    AddLineQueueX("movzx eax,WORD PTR [eax*2+IT%s-(%d*2)]", l_jtab, min);
			if ( ModuleInfo.aflag & _AF_REGAX )
			    AddLineQueueX("jmp [eax*4+%s]", l_jtab);
			else
			    AddLineQueueX("mov eax,[eax*4+%s]", l_jtab);
		    } else if ( ModuleInfo.aflag & _AF_REGAX )
			AddLineQueueX("jmp [eax*4+%s-(%d*4)]", l_jtab, min);
		    else
			AddLineQueueX("mov eax,[eax*4+%s-(%d*4)]", l_jtab, min);

		    if ( !( ModuleInfo.aflag & _AF_REGAX ) ) {
			AddLineQueue("xchg eax,[esp]");
			AddLineQueue("retn");
		    }
		} else {
		    if ( use_index ) {
			if ( !( ModuleInfo.aflag & _AF_REGAX ) )
			    AddLineQueueX("push %s", hll->condlines);

			if ( dist < 256 )
			    AddLineQueueX("movzx %s,BYTE PTR [%s+IT%s-(%d)]",
				hll->condlines, hll->condlines, l_jtab, min);
			else
			    AddLineQueueX("movzx %s,WORD PTR [%s*2+IT%s-(%d*2)]",
				hll->condlines, hll->condlines, &l_jtab, min);

			if ( ModuleInfo.aflag & _AF_REGAX ) {
			    AddLineQueueX("jmp [%s*4+%s]", hll->condlines, l_jtab);
			} else {
			    AddLineQueueX("mov %s,[%s*4+%s]", hll->condlines,
				hll->condlines, l_jtab);
			    AddLineQueueX("xchg %s,[esp]", hll->condlines);
			    AddLineQueue ("retn");
			}
		    } else {
			AddLineQueueX("jmp [%s*4+%s-(%d*4)]", hll->condlines, l_jtab, min);
		    }
		}
	    } else if ( ( min <= ( UINT_MAX / 8 ) ) && !use_index
		   && ( hll->flags & HLLF_ARGREG ) && ModuleInfo.aflag & _AF_REGAX ) {

		if ( !_memicmp( hll->condlines, "r10", 3 ) || !_memicmp( hll->condlines, "r11", 3 ) )
		    asmerr( 2008, "register r10/r11 overwritten by SWITCH" );
		AddLineQueueX( "lea r11,%s", l_exit );
		AddLineQueueX( "mov r10d,[%s*4+r11-(%d*4)+(%s-%s)]", hll->condlines, min, l_jtab, l_exit );
		AddLineQueue ( "sub r11,r10" );
		AddLineQueue ( "jmp r11" );

	    } else {

		if ( !( hll->flags & HLLF_ARGREG ) ) {
		    GetSwitchArg(T_R11, hll->flags, hll->condlines);
		} else {
		    if ( !( ModuleInfo.aflag & _AF_REGAX ) )
			AddLineQueue("push r11");
		    if ( _memicmp(hll->condlines, "r11", 3) )
			AddLineQueueX( "mov r11,%s", hll->condlines );
		}
		if ( !( ModuleInfo.aflag & _AF_REGAX ) )
		    AddLineQueue( "push r10" );
		AddLineQueueX( "lea r10,%s", l_exit );

		if ( use_index ) {

		    if ( dist < 256 )
			AddLineQueueX( "movzx r11d,BYTE PTR [r10+r11-(%d)+(IT%s-%s)]", min, l_jtab, l_exit );
		    else
			AddLineQueueX( "movzx r11d,WORD PTR [r10+r11*2-(%d*2)+(IT%s-%s)]", min, l_jtab, l_exit );
		    AddLineQueueX( "mov r11d,[r10+r11*4+(%s-%s)]", l_jtab, l_exit );

		} else {

		    if ( (unsigned int)min < ( UINT_MAX / 8 ) )
			AddLineQueueX( "mov r11d,[r10+r11*4-(%d*4)+(%s-%s)]", min, l_jtab, l_exit );
		    else {
			AddLineQueueX( "sub r11,%d", min );
			AddLineQueueX( "mov r11d,[r10+r11*4+(%s-%s)]", l_jtab, l_exit );
		    }
		}

		AddLineQueue ( "sub r10,r11" );
		if ( ModuleInfo.aflag & _AF_REGAX ) {
		    AddLineQueue( "jmp r10" );
		} else {
		    AddLineQueue( "mov r11,[rsp+8]" );
		    AddLineQueue( "mov [rsp+8],r10" );
		    AddLineQueue( "mov r10,r11" );
		    AddLineQueue( "pop r11" );
		    AddLineQueue( "retn" );
		}
	    }

	    /* Create the jump table */

	    AddLineQueueX( "ALIGN %d", r_size );
	    AddLineQueueX( "%s" LABELQUAL, l_jtab );
	}

	if ( use_index ) {

	    x = -1; /* offset */
	    i = -1; /* table index */

	    for ( hp = hll->caselist; hp; hp = hp->caselist ) {

		if ( hp->flags & HLLF_TABLE ) {


		    if ( !( sym = SymFind( GetLabelStr( hp->labels[LSTART], labelx ) ) ) )
			break;

		    if ( x != sym->offset ) {

			x = sym->offset;
			i++;
		    }

		    /* use case->index... */

		    hp->index = i;
		}
	    }
	    lcount = i + 1;
	    x = -1;
	    for( hp = hll->caselist; hp; hp = hp->caselist ) {

		if ( ( hp->flags & HLLF_TABLE ) && x != hp->index ) {

		    if ( ModuleInfo.Ofssize == USE64 )
			AddLineQueueX( " dd %s-%s ; .case %s", l_exit,
			    GetLabelStr( hp->labels[LSTART], labelx ), hp->condlines );
		    else
			AddLineQueueX( " %r %s ; .case %s", r_dw,
			    GetLabelStr( hp->labels[LSTART], labelx ), hp->condlines );

		    x = hp->index;
		}
	    }

	    if ( ModuleInfo.Ofssize == USE64 )
		AddLineQueueX( " dd 0 ; .default" );
	    else
		AddLineQueueX(" %r %s ; .default", r_dw, l_exit );

	    r_db = T_DB;
	    icount = max - min + 1;
	    if ( icount > 256 ) {

		if ( ModuleInfo.Ofssize == USE16 )
		    return ( asmerr( 2022, 1, 2 ) ) ;
		 r_db = T_DW;
	    }
	    AddLineQueueX( "IT%s LABEL BYTE", l_jtab );

	    for ( x = 0; x < icount; x++ ) {

		/* loop from min value */

		if ( ( xp = GetCaseVal( hll, min + x ) ) ) {

		    /* Unlink block */

		    hp = hll;
		    do {
			if ( hp->caselist == xp ) {
			    hp->caselist = xp->caselist;
			    break;
			}
			hp = hp->caselist;
		    } while ( hp );

		    /* write block to table */

		    AddLineQueueX( " %r %d", r_db, xp->index );

		} else {

		    /* else make a jump to exit or default label */

		    AddLineQueueX( " %r %d", r_db, lcount );
		}
	    }
	    AddLineQueueX( "ALIGN %d", r_size );
	} else {
	    for ( x = 0; x < dist; x++ ) {

		/* loop from min value */

		if ( ( xp = GetCaseVal( hll, min + x ) ) ) {

		    /* Unlink block */

		    hp = hll;
		    do {
			if ( hp->caselist == xp ) {
			    hp->caselist = xp->caselist;
			    break;
			}
			hp = hp->caselist;
		    } while ( hp );

		    /* write block to table */

		    if ( ModuleInfo.Ofssize == USE64 )
			addlq_jxx_label64( r_dw, l_exit, xp->labels[LSTART] );
		    else
			addlq_jxx_label( r_dw, xp->labels[LSTART] );

		} else {

		    /* else make a jump to exit or default label */

		    if ( ModuleInfo.Ofssize == USE64 )
			AddLineQueue( "dd 0" );
		    else
			AddLineQueueX( "%r %s", r_dw, l_exit );
		}
	    }
	}

	if ( ncases ) {

	    /* Create the new start label */

	    AddLineQueueX( "%s" LABELQUAL, l_start );
	    for ( xp = hll->caselist; xp; xp = xp->caselist )
		xp->flags |= HLLF_TABLE;
	}
    }

    for( xp = hll->caselist; xp; xp = xp->caselist )
	RenderCase( hll, xp, buffer );

    if ( c_default && hll->caselist )
	AddLineQueueX( "jmp %s", l_exit );

    return 0;
}

static void RenderJTable( struct hll_item *hll	 )
{
    char l_exit[16];
    char l_jtab[16];  /* jump table address */

    if ( hll->labels[LEXIT] == 0 )
	hll->labels[LEXIT] = GetHllLabel();

    GetLabelStr( hll->labels[LSTART], l_jtab );
    GetLabelStr( hll->labels[LEXIT], l_exit );

    if ( ModuleInfo.Ofssize == USE16 ) {

	if ( ModuleInfo.aflag & _AF_REGAX ) {
	    if ( _stricmp( "ax", hll->condlines ) )
		AddLineQueueX( "mov ax,%s", hll->condlines );

	    AddLineQueue ( "xchg ax,bx" );
	    AddLineQueue ( "add bx,bx" );
	    AddLineQueueX( "mov bx,cs:[bx+%s]", l_jtab );
	    AddLineQueue ( "xchg ax,bx" );
	    AddLineQueue ( "jmp ax" );
	} else {
	    AddLineQueue( "push ax" );
	    AddLineQueue( "push bx" );
	    AddLineQueue( "push ax" );
	    if ( _stricmp( "bx", hll->condlines ) )
		AddLineQueueX( "mov bx,%s", hll->condlines );
	    AddLineQueue ( "add bx,bx" );
	    AddLineQueueX( "mov ax,cs:[bx+%s]", l_jtab );
	    AddLineQueue ( "mov bx,sp" );
	    AddLineQueue ( "mov ss:[bx+4],ax" );
	    AddLineQueue ( "pop ax" );
	    AddLineQueue ( "pop bx" );
	    AddLineQueue ( "retn" );
	}

    } else if ( ModuleInfo.Ofssize == USE32 ) {

	AddLineQueueX( "jmp [%s*4+%s-(MIN%s*4)]", hll->condlines, l_jtab, l_jtab );

    } else if ( ModuleInfo.aflag & _AF_REGAX ) {
	if ( !_memicmp( hll->condlines, "r10", 3 ) || !_memicmp( hll->condlines, "r11", 3 ) )
	    asmerr( 2008, "register r10/r11 overwritten by SWITCH" );

	AddLineQueueX( "lea r11,%s", l_exit );
	AddLineQueueX( "mov r10d,[%s*4+r11-(MIN%s*4)+(%s-%s)]", hll->condlines, l_jtab, l_jtab, l_exit );
	AddLineQueue ( "sub r11,r10" );
	AddLineQueue ( "jmp r11" );
    } else {
	AddLineQueue( "push r11" );
	AddLineQueue( "push r10" );
	if ( _memicmp( hll->condlines, "r11", 3 ) )
	    AddLineQueueX( "mov r11,%s", hll->condlines );
	AddLineQueueX( "lea r10,%s", l_exit );
	AddLineQueueX( "mov r11d,[r10+r11*4-(MIN%s*4)+(%s-%s)]", l_jtab, l_jtab, l_exit );
	AddLineQueue( "sub r10,r11" );
	AddLineQueue( "mov r11,[rsp+8]" );
	AddLineQueue( "mov [rsp+8],r10" );
	AddLineQueue( "mov r10,r11" );
	AddLineQueue( "pop r11" );
	AddLineQueue( "retn" );
    }
}

int SwitchStart( int i, struct asm_tok tokenarray[] )
{
    int rc = 0;
    char buffer[MAX_LINE_LEN];
    struct hll_item *hll;
    struct asym *sym;
    int size;

    i++;

    if ( HllFree )
	hll = HllFree;
    else
	hll = (struct hll_item *)LclAlloc( sizeof( struct hll_item ) );

    ExpandCStrings( tokenarray );

    hll->cmd = HLL_SWITCH;
    hll->labels[LEXIT] = 0;
    hll->flags = HLLF_WHILE;
    if ( ModuleInfo.aflag & _AF_NOTEST ) {
	hll->flags |= HLLF_NOTEST;
	ModuleInfo.aflag &= ~_AF_NOTEST;
    }

    hll->labels[LSTART] = 0; // set by .CASE
    hll->labels[LTEST]	= 0; // set by .CASE
    hll->labels[LEXIT]	= 0; // set by .BREAK
    hll->condlines = 0;
    hll->caselist = 0;

    if ( tokenarray[i].token != T_FINAL ) {

	if ( ExpandHllProc( buffer, i, tokenarray ) == ERROR )
	    return ERROR;

	if ( buffer[0] ) {

	    QueueTestLines( buffer );
	    hll->flags |= HLLF_ARGREG;
	    goto set_arg_size;

	} else {

	    switch ( tokenarray[i].tokval ) {

	    case T_AX:
	    case T_CX:
	    case T_DX:
	    case T_BX:
	    case T_SP:
	    case T_BP:
	    case T_SI:
	    case T_DI:

		hll->flags |= HLLF_ARG16;
		if ( ModuleInfo.Ofssize == USE16 ) {
		    hll->flags |= HLLF_ARGREG;
		    if ( hll->flags & HLLF_NOTEST )
			hll->flags |= HLLF_JTABLE;
		}

	    case T_AL:
	    case T_CL:
	    case T_DL:
	    case T_BL:
	    case T_AH:
	    case T_CH:
	    case T_DH:
	    case T_BH:
		break;

	    case T_EAX:
	    case T_ECX:
	    case T_EDX:
	    case T_EBX:
	    case T_ESP:
	    case T_EBP:
	    case T_ESI:
	    case T_EDI:
		hll->flags |= HLLF_ARG32;
		if ( ModuleInfo.Ofssize == USE32 ) {
		    hll->flags |= HLLF_ARGREG;
		    if ( hll->flags & HLLF_NOTEST )
			hll->flags |= HLLF_JTABLE;
		}
		if ( ModuleInfo.Ofssize == USE64 )
		    hll->flags |= HLLF_ARG3264;
		break;

	    case T_RAX:
	    case T_RCX:
	    case T_RDX:
	    case T_RBX:
	    case T_RSP:
	    case T_RBP:
	    case T_RSI:
	    case T_RDI:
	    case T_R8:
	    case T_R9:
	    case T_R10:
	    case T_R11:
	    case T_R12:
	    case T_R13:
	    case T_R14:
	    case T_R15:
		hll->flags |= HLLF_ARG64;
		if ( ModuleInfo.Ofssize == USE64 ) {
		    hll->flags |= HLLF_ARGREG;
		    if ( hll->flags & HLLF_NOTEST )
			hll->flags |= HLLF_JTABLE;
		}
		break;
	    default:
		hll->flags |= HLLF_ARGMEM;
		if ( ( sym = SymFind( tokenarray[i].string_ptr ) ) ) {

		    if ( sym->total_size == 2 )
			hll->flags |= HLLF_ARG16;
		    else if ( sym->total_size == 4 )
			hll->flags |= HLLF_ARG32;
		    else if ( sym->total_size == 8 )
			hll->flags |= HLLF_ARG64;
		} else {

		    set_arg_size:

		    if ( ModuleInfo.Ofssize == USE16 )
			hll->flags |= HLLF_ARG16;
		    else if ( ModuleInfo.Ofssize == USE32 )
			hll->flags |= HLLF_ARG32;
		    else
			hll->flags |= HLLF_ARG64;
		}
	    }
	}
	strcpy( buffer, tokenarray[i].tokpos );
	size = strlen( buffer ) + 1;
	hll->condlines = LclAlloc( size );
	memcpy( hll->condlines, buffer, size );
    }

    if ( !hll->flags && (tokenarray[i].token != T_FINAL && rc == NOT_ERROR) )
	rc = asmerr( 2008, tokenarray[i].tokpos );

    if ( hll == HllFree )
	HllFree = hll->next;
    hll->next = HllStack;
    HllStack = hll;

    if ( ModuleInfo.list )
	LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), NULL );
    if ( is_linequeue_populated() )
	RunLineQueue();

    return( rc );
}

int SwitchEnd( int i, struct asm_tok tokenarray[] )
{
    int rc = 0;
    int cmd;
    char buffer[MAX_LINE_LEN];
    char l_exit[16]; // exit or default label
    struct hll_item *hp;
    struct hll_item *hll;

    if ( HllStack == NULL )
	    return( asmerr( 1011 ) );

    hll = HllStack;
    HllStack = hll->next;
    hll->next = HllFree;
    HllFree = hll;
    cmd = hll->cmd;

    if ( cmd != HLL_SWITCH )
	return ( asmerr( 1011 ) );

    i++;
    if ( hll->labels[LTEST] ) {

	if ( hll->labels[LSTART] == 0 )
	    hll->labels[LSTART] = GetHllLabel();
	if ( hll->labels[LEXIT] == 0 )
	    hll->labels[LEXIT] = GetHllLabel();

	GetLabelStr( hll->labels[LEXIT], buffer );
	RenderCaseExit( hll );
	strcpy( l_exit, buffer );
	GetLabelStr( hll->labels[LSTART], buffer );

	if ( ModuleInfo.casealign )
		AddLineQueueX( "ALIGN %d", ( 1 <<  ModuleInfo.casealign ) );

	if ( !hll->condlines ) {

	    AddLineQueueX( "%s" LABELQUAL, buffer );

	    hp = hll->caselist;
	    while ( hp ) {
		if ( !hp->condlines ) {
		    addlq_jxx_label( T_JMP, hp->labels[LSTART] );
		} else if ( hp->flags & HLLF_EXPRESSION ) {
		    i = 1;
		    hp->flags |= HLLF_WHILE;
		    ExpandHllExpression( hp, &i, tokenarray, LSTART, TRUE, buffer );
		} else {
		    QueueTestLines( hp->condlines );
		}
		hp = hp->caselist;
	    }
	} else {
	    RenderSwitch( hll, tokenarray, buffer, l_exit );
	}
    }
    if ( hll->labels[LEXIT] )
	addlq_label( hll->labels[LEXIT] );

    return rc;
}

int SwitchExit( int i, struct asm_tok tokenarray[] )
{
    int rc = 0;
    int cmd = tokenarray[i].tokval;
    int exit_level = 0;
    int case_label;
    int t1,t2;
    int bracket;
    int size;
    char buffer[MAX_LINE_LEN];
    char *token_str,*p;
    struct hll_item *hll;
    struct hll_item *caseitem;
    struct hll_item *hp;
    struct asym *sym;


    if ( HllStack == NULL )
	return ( asmerr( 1011 ) );

    hll = HllStack;
    ExpandCStrings( tokenarray );

    switch( cmd ) {

    case T_DOT_DEFAULT:

	if ( hll->flags & HLLF_ELSEOCCURED )
	    return ( asmerr( 2142 ) );

	if ( tokenarray[1].token != T_FINAL )
	    return ( asmerr( 2008, tokenarray[i].tokpos ) );

	hll->flags |= HLLF_ELSEOCCURED;

    case T_DOT_CASE:

	while ( hll && hll->cmd != HLL_SWITCH )
	    hll = hll->next;
	if ( hll->cmd != HLL_SWITCH )
	    return ( asmerr( 1010, tokenarray[i].string_ptr ) );

	if ( hll->labels[LSTART] == 0 ) {

	    /* first case */

	    hll->labels[LSTART] = GetHllLabel();
	    if ( hll->flags & HLLF_NOTEST && hll->flags & HLLF_JTABLE )
		RenderJTable( hll );
	    else
		addlq_jxx_label( T_JMP, hll->labels[LSTART] );

	} else if ( ModuleInfo.aflag & _AF_PASCAL ) {

	    if ( hll->labels[LEXIT] == 0 )
		hll->labels[LEXIT] = GetHllLabel();

	    RenderCaseExit( hll );

	} else if ( Parse_Pass == PASS_1 ) {

	    /* error A7007: .CASE without .ENDC: assumed fall through */

	    hp = hll;
	    while ( hp->caselist )
		hp = hp->caselist;

	    if ( hp != hll && !( hp->flags & HLLF_ENDCOCCUR ) )
		asmerr( 7007 );
	}

	/* .case a, b, c, ... */

	if ( RenderMultiCase( &i, buffer, tokenarray ) )
	    break;

	/* add case label */

	if ( ModuleInfo.casealign )
	    AddLineQueueX( "ALIGN %d", ( 1 << ModuleInfo.casealign ) );

	case_label = GetHllLabel();
	addlq_label( case_label );

	/* add new case item */

	caseitem = LclAlloc( sizeof( struct hll_item ) );
	caseitem->labels[LSTART] = case_label;
	hll->labels[LTEST]++; /* case count++ */
	hp = hll;	      /* add item to end of list */
	while ( hp->caselist )
	    hp = hp->caselist;
	hp->caselist = caseitem;

	/* parse case string */

	i++; /* skip past the .case token */

	/* handle .case <expression> : ... */

	t1 = i;
	token_str = NULL;
	while ( (t2 = IsCaseColon( t1, tokenarray )) ) {

	    if ( token_str ) {

		tokenarray[t2].tokpos[0] = NULLC;
		AddLineQueue( token_str );
		tokenarray[t2].tokpos[0] = ':';

	    } else
		Token_Count = t2 - i + 1;

	    t1 = t2 + 1;
	    token_str = tokenarray[t1].tokpos;
	}
	if ( token_str )
	    AddLineQueue( token_str );

	if ( hll->condlines && cmd != T_DOT_DEFAULT ) {

	    t1 = i;
	    t2 = 1;
	    bracket = 0;
	    while ( t2 ) {
		/*
		 * .CASE BYTE PTR [reg+-*imm]
		 * .CASE ('A'+'L') SHR (8 - H_BITS / ... )
		 */
		switch ( tokenarray[t1].token ) {
		case T_CL_BRACKET:
		    if ( bracket == 1 ) {
			if ( tokenarray[t1+1].token == T_FINAL ) {
			    caseitem->flags |= HLLF_NUM;
			    t2 = 0;
			    break;
			}
		    }
		    bracket -= 2;
		case T_OP_BRACKET:
		    bracket++;
		case T_PERCENT:	      // %
		case T_INSTRUCTION:   // XOR, OR, NOT,...
		case '+':
		case '-':
		case '*':
		case '/':
		    break;

		case T_STYPE:		// BYTE, WORD, ...
		    if ( tokenarray[t1+1].tokval == T_PTR ) {
			t2 = 0;
			break;
		    }
		    goto STRING;

		case T_FLOAT:		// 1..3 ?
		    if ( tokenarray[t1+1].token == T_DOT ) {
			t2 = 0;
			break;
		    }
		    goto STRING;

		case T_UNARY_OPERATOR:	// offset x
		    if ( tokenarray[t1].tokval != T_OFFSET ) {
			t2 = 0;
			break;
		    }
		    goto STRING;

		case T_ID:
		    if ( (sym = SymFind( tokenarray[t1].string_ptr )) ) {
			if ( sym->state != SYM_INTERNAL ||
			  !( sym->mem_type == MT_NEAR || sym->mem_type == MT_EMPTY ) ) {
			    t2 = 0;
			    break;
			}
		    } else if ( Parse_Pass != PASS_1 ) {
			t2 = 0;
			break;
		    }

		case T_NUM:
		case T_STRING:
		    STRING:

		    if ( tokenarray[t1+1].token == T_FINAL ) {
			caseitem->flags |= HLLF_NUM;
			t2 = 0;
		    }
		    break;

		default:
		    // T_REG
		    // T_OP_SQ_BRACKET
		    // T_DIRECTIVE
		    // T_QUESTION_MARK
		    // T_BAD_NUM
		    // T_DBL_COLON
		    // T_CL_SQ_BRACKET
		    // T_COMMA
		    // T_COLON
		    // T_FINAL
		    t2 = 0;
		    break;
		}
		t1++;
	    }
	}

	if ( cmd == T_DOT_DEFAULT ) {

	    caseitem->flags |= HLLF_DEFAULT;
	} else {

	    if ( tokenarray[i].token == T_FINAL )
		return ( asmerr( 2008, tokenarray[i-1].tokpos ) );

	    if ( !hll->condlines ) {

		rc = EvaluateHllExpression( caseitem, &i, tokenarray, LSTART, TRUE, buffer );
		if ( rc == ERROR )
		    break;

	    } else {

		size = (tokenarray[Token_Count].tokpos - tokenarray[i].tokpos);
		memcpy( buffer, tokenarray[i].tokpos, size );
		buffer[size] = NULLC;
	    }
	    size = strlen( buffer ) + 1;
	    caseitem->condlines = LclAlloc( size );
	    memcpy( caseitem->condlines, buffer, size );
	}

	i = Token_Count;
	break;

    case T_DOT_GOTOSW3:
	exit_level++;
    case T_DOT_GOTOSW2:
	exit_level++;
    case T_DOT_GOTOSW1:
	exit_level++;
    case T_DOT_GOTOSW:
    case T_DOT_ENDC:

	for ( hp = hll; hll && hll->cmd != HLL_SWITCH; hll = hll->next )
	    ;
	for ( ; hll && exit_level; exit_level-- )
	    for ( hll = hll->next; hll && hll->cmd != HLL_SWITCH; hll = hll->next )
		;
	if ( !hll )
	    return( asmerr( 1011 ) );

	if ( hll->labels[LEXIT] == 0 )
	    hll->labels[LEXIT] = GetHllLabel();

	case_label = LEXIT;
	if ( cmd != T_DOT_ENDC )
	    case_label = LSTART;

	i++;
	cmd = T_DOT_ENDC;

	if ( case_label == LSTART && tokenarray[i].token == T_OP_BRACKET ) {
	    if ( ( p = strrchr( strcpy( buffer, tokenarray[i+1].tokpos ), ')' ) ) ) {
		while ( p > buffer && (*(p-1) == ' ' || *(p-1) == 9) )
		    p++;
		*p = NULLC;
		hp = hll->caselist;
		while ( hp ) {
		    if ( hp->condlines ) {
			if ( !strcmp( buffer, hp->condlines ) ) {
			    addlq_jxx_label( T_JMP, hp->labels[LSTART] );
			    break;
			}
		    }
		    hp = hp->caselist;
		}
		if ( !hp && hll->condlines ) {
		    AddLineQueueX( "mov %s,%s", hll->condlines, buffer );
		    addlq_jxx_label( T_JMP, hll->labels[LSTART] );
		}
		i = Token_Count;
	    }
	} else {
	    HllContinueIf( hll, &i, buffer, tokenarray, case_label, hp );
	}
	break;
    }

    if ( tokenarray[i].token != T_FINAL && rc == NOT_ERROR )
	return ( asmerr( 2008, tokenarray[i].tokpos ) );

    return rc;
}

int SwitchDirective( int i, struct asm_tok tokenarray[] )
{
    int rc = 0;

    switch ( tokenarray[i].tokval ) {
    case T_DOT_CASE:
    case T_DOT_GOTOSW:
    case T_DOT_GOTOSW1:
    case T_DOT_GOTOSW2:
    case T_DOT_GOTOSW3:
    case T_DOT_DEFAULT:
    case T_DOT_ENDC:
	rc = SwitchExit( i, tokenarray );
	break;
    case T_DOT_ENDSW:
	rc = SwitchEnd( i, tokenarray );
	break;
    case T_DOT_SWITCH:
	rc = SwitchStart( i, tokenarray );
	break;
    }

    if ( ModuleInfo.list )
	    LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), NULL );

    if ( is_linequeue_populated() )
	    RunLineQueue();

    return( rc );
}
