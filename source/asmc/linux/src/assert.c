#include <string.h>
#include <malloc.h>

#include <globals.h>
#include <hllext.h>
#include <condasm.h>

#define MAXSAVESTACK 124

static int  assert_stid = 0;
static unsigned char save_stacka[MAXSAVESTACK] = { 0 };
static unsigned char save_stackx[MAXSAVESTACK] = { 0 };


int AssertDirective( int i, struct asm_tok tokenarray[] )
{
	int rc = 0;
	int cmd = tokenarray[i].tokval;
	char buff[16];
	char buffer[MAX_LINE_LEN];
	char cmdstr[MAX_LINE_LEN];
	struct hll_item *hll;
	char *p, *q, *name;

	i++;

	if ( HllFree )
	    hll = HllFree;
	else
	    hll = (struct hll_item *)LclAlloc( sizeof( struct hll_item ) );

	hll->flags = 0;
	hll->labels[LEXIT] = 0;
	ExpandCStrings( tokenarray );

	switch ( cmd ) {

	case T_DOT_ASSERTD:
	    hll->flags = HLLF_IFD;
	case T_DOT_ASSERTW:
	    if ( cmd == T_DOT_ASSERTW )
		hll->flags = HLLF_IFW;
	case T_DOT_ASSERTB:
	    if ( cmd == T_DOT_ASSERTB )
		hll->flags = HLLF_IFB;
	case T_DOT_ASSERT:

	    if ( tokenarray[i].token == T_COLON ) {

		i += 2;
		name = tokenarray[i-1].string_ptr;
		if ( tokenarray[i-1].token == T_ID ) {

		    if ( SymFind( name ) ) {

			free( ModuleInfo.assert_proc );
			ModuleInfo.assert_proc = malloc( strlen( name ) + 1 );
			strcpy( ModuleInfo.assert_proc, name );
			break;
		    }
		}

		if ( !_stricmp( name, "CODE" ) ) {

		    if ( !( ModuleInfo.xflag & OPT_ASSERT ) ) {

			CondPrepare( T_IF );
			CurrIfState = BLOCK_DONE;
		    }
		    break;
		}

		if ( !_stricmp( name, "ENDS" ) ) {
		    //
		    // Converted to ENDIF in Tokenize()
		    //
		    break;
		}

		if ( !_stricmp( name, "PUSH" ) ) {

		    if ( assert_stid < MAXSAVESTACK ) {

			save_stacka[assert_stid] = ModuleInfo.xflag;
			assert_stid++;
		    }
		    break;
		}

		if ( !_stricmp( name, "POP" ) ) {

		    ModuleInfo.xflag = save_stackx[assert_stid];
		    if ( assert_stid )
			assert_stid--;
		    break;
		}

		if ( !_stricmp( name, "ON" ) ) {

		    ModuleInfo.xflag |= OPT_ASSERT;
		    break;
		}

		if ( !_stricmp( name, "OFF" ) ) {

		    ModuleInfo.xflag &= ~OPT_ASSERT;
		    break;
		}

		if ( !_stricmp( name, "PUSHF" ) ) {

		    ModuleInfo.xflag |= OPT_PUSHF;
		    break;
		}

		if ( !_stricmp( name, "POPF" ) ) {

		    ModuleInfo.xflag &= ~OPT_PUSHF;
		    break;
		}

		asmerr( 2008, name );
		break;

	    } else if ( tokenarray[i].token == T_FINAL || !(ModuleInfo.xflag & OPT_ASSERT) ) {

		break;
	    }

	    strcpy( cmdstr, tokenarray[i].tokpos );

	    if ( ModuleInfo.xflag & OPT_PUSHF ) {

		if ( ModuleInfo.Ofssize == USE64 ) {

		    AddLineQueueX( "%r", T_PUSHFQ );
		    AddLineQueueX( "%r %r,28h", T_SUB, T_RSP );
		} else {
		    AddLineQueueX( "%r", T_PUSHFD );
		}
	    }

	    hll->cmd = HLL_IF;
	    hll->labels[LSTART] = 0;
	    hll->labels[LTEST] = GetHllLabel();

	    GetLabelStr( GetHllLabel(), buff );
	    rc = EvaluateHllExpression( hll, &i, tokenarray, LTEST, FALSE, buffer );
	    if ( rc != NOT_ERROR )
		break;

	    QueueTestLines( buffer );

	    if ( ModuleInfo.xflag & OPT_PUSHF ) {

		if ( ModuleInfo.Ofssize == USE64 ) {

		    AddLineQueueX( "%r %r,28h", T_ADD, T_RSP );
		    AddLineQueueX( "%r", T_POPFQ );
		} else {
		    AddLineQueueX( "%r", T_POPFD );
		}
	    }

	    AddLineQueueX( "jmp %s", buff );
	    AddLineQueueX( "%s" LABELQUAL, GetLabelStr( hll->labels[LTEST], buffer ) );

	    if ( ModuleInfo.xflag & OPT_PUSHF ) {

		if ( ModuleInfo.Ofssize == USE64 ) {

		    AddLineQueueX( "%r %r,28h", T_ADD, T_RSP );
		    AddLineQueueX( "%r", T_POPFQ );
		} else {
		    AddLineQueueX( "%r", T_POPFD );
		}
	    }

	    if ( buffer[0] == NULLC )
		break;

	    if ( !ModuleInfo.assert_proc )
		ModuleInfo.assert_proc = "assert_exit";

	    AddLineQueueX( "%s()", ModuleInfo.assert_proc );
	    AddLineQueue ( "db @CatStr(!\",%@FileName,<(>,%@Line,<): >,!\")" );

	    q = cmdstr;
	    while ( (p = strchr( q, '"' )) ) {

		*p++ = NULLC;
		if ( *q )
		    AddLineQueueX( "db \"%s\",22h", q );
		else
		    AddLineQueue( "db 22h" );
		q = p;
	    }
	    if ( *q )
		AddLineQueueX( "db \"%s\"", q );
	    AddLineQueue( "db 0" );
	    AddLineQueueX( "%s" LABELQUAL, buff );
	    break;
	}

	if ( ModuleInfo.list )
	    LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), NULL );
	if ( is_linequeue_populated() )
	    RunLineQueue();

	return( rc );
}
