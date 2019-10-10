#include <globals.h>
#include <quadmath.h>
#include <expreval.h>
#include <symbols.h>

void _atoow( void *dst, const char *src, int radix, int size )
{
    unsigned int eax;
    unsigned int ecx;
    unsigned short *w = dst;
    unsigned int   *q = dst;
#ifdef  CHEXPREFIX
    if (*src == '0' && ( *(src + 1) | 0x20 ) == 'x' ) {
    src += 2;
    size -= 2;
    }
#endif
    q[0] = 0;
    q[1] = 0;
    q[2] = 0;
    q[3] = 0;
    do {
    if ( ((eax = (*(src++) & ~('0'))) & 0x40) )
        eax -= 55;
    for ( ecx = 0; ecx < 8; ecx++ ) {
        eax += *w * radix;
        *w++ = eax;
        eax >>= 16;
    }
    w -= 8;
    } while ( --size );
}

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

        errno = 0;
        __cvta_q(out, inp, NULL);
        if ( errno )
            asmerr( 2104, inp );

        if( negative ) {
            p = out;
            p[15] |= 0x80;
        }

        switch ( size ) {
        case 2:
            __cvtq_h(out, out);
            if ( errno )
                asmerr( 2071 );
            break;
        case 4:
            __cvtq_ss(out, out);
            if ( errno )
                asmerr( 2071 );
            break;
        case 8:
            __cvtq_sd(out, out);
            if ( errno )
                asmerr( 2071 );
            break;
        case 10:
            __cvtq_ld(out, out);
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

void quad_resize( struct expr *opnd, unsigned size )
{
    errno = 0;
    if ( size == 10 )
        __cvtq_ld( opnd->chararray, opnd->chararray );
    else if ( size == 8 ) {
        if ( opnd->chararray[15] & 0x80 ) {
            opnd->negative = 1;
            opnd->chararray[15] &= 0x7F;
        }
        __cvtq_sd( opnd->chararray, opnd->chararray );
        if ( opnd->negative )
            opnd->dvalue *= -1;
        opnd->mem_type = MT_REAL8;
    } else if ( size == 4 )  {
        if ( opnd->chararray[15] & 0x80 ) {
            opnd->negative = 1;
            opnd->chararray[15] &= 0x7F;
        }
        __cvtq_ss( opnd->chararray, opnd->chararray );
        if ( opnd->negative )
            opnd->fvalue *= -1;
        opnd->mem_type = MT_REAL4;
    } else {
        if ( opnd->chararray[15] & 0x80 ) {
            opnd->negative = 1;
            opnd->chararray[15] &= 0x7F;
        }
        __cvtq_h( opnd->chararray, opnd->chararray );
        if ( opnd->negative )
            opnd->chararray[1] |= 0x80;
        opnd->mem_type = MT_REAL2;
    }
    if ( errno )
        asmerr( 2071 );
}
