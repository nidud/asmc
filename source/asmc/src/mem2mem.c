#include <string.h>
#include <globals.h>
#include <hllext.h>

int mem2mem( unsigned op1, unsigned op2, struct asm_tok tokenarray[] )
{
	int o1 = op1 & OP_MS;
	int o2 = op2 & OP_MS;
	int r1, r2, ax, i;
	int op;
	char c;

	if ( !o1 || !o2 || ModuleInfo.strict_masm_compat )
	    return asmerr( 2070 );

	ax = T_EAX;
	if ( ModuleInfo.Ofssize == USE64 )
	    ax = T_RAX;
	else if ( ModuleInfo.Ofssize == USE16 )
	    ax = T_AX;

	r1 = ax;
	switch ( o1 ) {
	  case OP_MS:
	  case OP_M08: r1 = T_AL;  break;
	  case OP_M16: r1 = T_AX;  break;
	  case OP_M32: r1 = T_EAX; break;
	}
	r2 = ax;
	switch ( o2 ) {
	  case OP_MS:
	  case OP_M08: r2 = T_AL;  break;
	  case OP_M16: r2 = T_AX;  break;
	  case OP_M32: r2 = T_EAX; break;
	}
	if ( r2 > r1 && o1 == OP_MS )
	    r1 = r2;
	if ( r1 > r2 && o2 == OP_MS )
	    r2 = r1;

	op = tokenarray[0].tokval;
	for ( i = 1; tokenarray[i].token != T_FINAL; i++ ) {
	    if ( tokenarray[i].tokval == ax )
		return asmerr( 2070 );
	    if ( tokenarray[i].token == T_COMMA ) {
		o1 = T_MOV;
		if ( r1 > r2 && r2 < T_EAX ) {
		    o1 = T_MOVZX;
		    r2 = T_EAX;
		}
		AddLineQueueX( " %r %r%s", o1, r2, tokenarray[i].tokpos );
		break;
	    }
	}
	c = tokenarray[i].tokpos[0];
	tokenarray[i].tokpos[0] = '\0';
	AddLineQueueX( " %r %s,%r", op, tokenarray[1].tokpos, r1 );
	tokenarray[i].tokpos[0] = c;
	if ( ModuleInfo.list )
	    LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), NULL );
	RunLineQueue();
	return NOT_ERROR;
}
