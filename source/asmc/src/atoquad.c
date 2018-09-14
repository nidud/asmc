#include <globals.h>
#include <token.h>
#include <expreval.h>
#include <symbols.h>
#include <quadmath.h>

void quad_resize( struct expr *opnd, unsigned size )
{
    qerrno = 0;
    if ( size == 10 )
        quadtold( opnd->chararray, opnd->chararray );
    else if ( size == 8 ) {
        if ( opnd->chararray[15] & 0x80 ) {
            opnd->negative = 1;
            opnd->chararray[15] &= 0x7F;
        }
        quadtod( opnd->chararray, opnd->chararray );
        if ( opnd->negative )
            opnd->dvalue *= -1;
        opnd->mem_type = MT_REAL8;
    } else if ( size == 4 )  {
        if ( opnd->chararray[15] & 0x80 ) {
            opnd->negative = 1;
            opnd->chararray[15] &= 0x7F;
        }
        quadtof( opnd->chararray, opnd->chararray );
        if ( opnd->negative )
            opnd->fvalue *= -1;
        opnd->mem_type = MT_REAL4;
    } else {
        if ( opnd->chararray[15] & 0x80 ) {
            opnd->negative = 1;
            opnd->chararray[15] &= 0x7F;
        }
        quadtoh( opnd->chararray, opnd->chararray );
        if ( opnd->negative )
            opnd->chararray[1] |= 0x80;
        opnd->mem_type = MT_REAL2;
    }
    if ( qerrno )
        asmerr( 2071 );
}
