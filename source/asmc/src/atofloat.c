/****************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
* Description:	string to float conversion
*
****************************************************************************/

#include <float.h>
//#include <math.h>

#include <globals.h>
#include <tbyte.h>
#include <atofloat.h>

#define USESTRTOF 0 /* 0=use strtod() and convert "manually", 1=use strtof() */

#ifdef _ASMC
void _qftod(void *, void *);
void _qftold(void *, void *);
#endif

/* it's ensured that 'out' points to a buffer with a size of at least 16 */

void atofloat( void *out, const char *inp, unsigned size, bool negative, uint_8 ftype )
/*************************************************************************************/
{
#ifdef _ASMC
    uint_8 mant[16];
#endif
    double double_value;
    float  float_value;
    uint_8 *p;

    /* v2.04: accept and handle 'real number designator' */
    if ( ftype ) {

	uint_8 *end;
	/* convert hex string with float "designator" to float.
	 * this is supposed to work with real4, real8 and real10.
	 * v2.11: use _atoow() for conversion ( this function
	 *	  always initializes and reads a 16-byte number ).
	 *	  then check that the number fits in the variable.
	 */
	_atoow( (uint_64 *)out, inp, 16, strlen( inp ) - 1 );
	for ( p = (uint_8 *)out + size, end = (uint_8 *)out + 16; p < end; p++ )
	    if ( *p != NULLC ) {
		asmerr( 2104, inp );
		break;
	    }
    } else {
	switch ( size ) {
#ifdef _ASMC
	case 4:
	case 8:
	case 10:
	case 16:
	    errno = 0;
	    _strtoq( &mant, inp, NULL );
	    if ( errno == ERANGE )
		asmerr( 2071 );
	    if ( negative ) {
		p = (uint_8 *)&mant;
		p[15] |= 0x80;
	    }
	    if ( size == 16 )
		memcpy(out, mant, 16);
	    else {
		if ( size == 10 )
		    _qftold(out, mant);
		else if ( size == 8 ) {
		    _qftod(out, mant);
		    if ( errno == ERANGE )
			asmerr( 2071 );
		} else {
		    if ( negative )
			p[15] &= 0x7F;
		    _qftod(&double_value, mant);
		    if ( double_value > FLT_MAX ||
		       ( double_value < FLT_MIN && double_value != 0 ) )
			asmerr( 2071 );
		    if ( negative )
			double_value *= -1;
		    float_value = double_value;
		    *(float *)out = float_value;
		}
	    }
	    break;
#else
	case 4:
#if USESTRTOF
	    errno = 0;
	    float_value = strtof( inp, NULL );
	    if ( errno == ERANGE ) {
		asmerr( 2071 );
	    }
	    if( negative )
		float_value *= -1;
#else
	    double_value = strtod( inp, NULL );
	    if ( double_value > FLT_MAX || ( double_value < FLT_MIN && double_value != 0 ) ) {
		asmerr( 2071 );
	    }
	    if( negative )
		double_value *= -1;
	    float_value = double_value;
#endif
	    *(float *)out = float_value;
	    break;
	case 8:
	    errno = 0; /* v2.11: init errno; errno is set on over- and under-flow */
	    double_value = strtod( inp, NULL );
	    /* v2.11: check added */
	    if ( errno == ERANGE ) {
		asmerr( 2071 );
	    }
	    if( negative )
		double_value *= -1;
	    *(double *)out = double_value;
	    break;
	case 10:
	    strtotb( (const char *)inp, (struct TB_LD *)out, (char)negative );
	    break;
#endif
	default:
	    /* sizes != 4,8 or 10 aren't accepted.
	     * Masm ignores silently, JWasm also unless -W4 is set.
	     */
	    if ( Parse_Pass == PASS_1 )
		asmerr( 7004 );
	    memset( (char *)out, 0, size );
	}
    }
    return;
}

