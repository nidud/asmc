#include <globals.h>
#include <quadmath.h>

void atofloat( void *out, const char *inp, unsigned size, int negative, uint_8 ftype )
{
    uint_8 *p;

    /* v2.04: accept and handle 'real number designator' */
    if ( ftype ) {

        uint_8 *end;
        /* convert hex string with float "designator" to float.
         * this is supposed to work with real4, real8 and real10.
         * v2.11: use _atoow() for conversion ( this function
         *    always initializes and reads a 16-byte number ).
         *    then check that the number fits in the variable.
         */
        _atoow( (uint_64 *)out, inp, 16, strlen( inp ) - 1 );
        for ( p = (uint_8 *)out + size, end = (uint_8 *)out + 16; p < end; p++ )
            if ( *p != NULLC ) {
            asmerr( 2104, inp );
            break;
        }
    } else {

        qerrno = 0;
        atoquad(out, inp, NULL);
        if ( qerrno )
            asmerr( 2104, inp );

        if( negative ) {
            p = out;
            p[15] |= 0x80;
        }

        switch ( size ) {
        case 4:
            quadtof(out, out);
            if ( qerrno )
                asmerr( 2071 );
            break;
        case 8:
            quadtod(out, out);
            if ( qerrno )
                asmerr( 2071 );
            break;
        case 10:
            quadtold(out, out);
        case 16:
            break;
        default:
            /* sizes != 4,8,10 or 16 aren't accepted.
             * Masm ignores silently, JWasm also unless -W4 is set.
             */
            if ( Parse_Pass == PASS_1 )
                asmerr( 7004 );

            memset( (char *)out, 0, size );
        }
    }
}
