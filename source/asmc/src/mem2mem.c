#include <string.h>
#include <globals.h>
#include <hllext.h>

int mem2mem( unsigned op1, unsigned op2, struct asm_tok tokenarray[] )
{
	int o1 = op1 & OP_MS;
	int o2 = op2 & OP_MS;
	int reg, ax, i;
	char c;

	if ( !o1 || o1 != o2 || ModuleInfo.strict_masm_compat )
	    return asmerr( 2070 );

	reg = T_RAX;
	if ( o1 & OP_M08 )
	    reg = T_AL;
	else if ( o1 & OP_M16 )
	    reg = T_AX;
	else if ( o1 & OP_M32 )
	    reg = T_EAX;

	ax = T_EAX;
	if ( ModuleInfo.Ofssize == USE64 )
	    ax = T_RAX;
	else if ( ModuleInfo.Ofssize == USE16 )
	    ax = T_AX;

	for ( i = 1; tokenarray[i].token != T_FINAL; i++ ) {

	    if ( tokenarray[i].tokval == ax )
		return asmerr( 2070 );
	    if ( tokenarray[i].token == T_COMMA ) {
		AddLineQueueX( " mov %r%s", reg, tokenarray[i].tokpos );
		break;
	    }
	}
	c = tokenarray[i].tokpos[0];
	tokenarray[i].tokpos[0] = '\0';
	AddLineQueueX( " %r %s,%r", tokenarray[0].tokval, tokenarray[1].tokpos, reg );
	tokenarray[i].tokpos[0] = c;
	if ( ModuleInfo.list )
	    LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), NULL );
	RunLineQueue();
	return NOT_ERROR;
}
