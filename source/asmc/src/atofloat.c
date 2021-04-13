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
    uint_8 *end;
    int len;

    errno = 0;

    /* v2.04: accept and handle 'real number designator' */
    if ( ftype ) {

        /* convert hex string with float "designator" to float.
         * this is supposed to work with real4, real8 and real10.
         * v2.11: use _atoow() for conversion ( this function
         *    always initializes and reads a 16-byte number ).
         *    then check that the number fits in the variable.
         */

        /* v2.31.24: the size is 2,4,8,10,16
         * real4 3ff0000000000000r is allowed: real8 -> real16 -> real4
         */

        len = strlen(inp) - 1;
        switch ( len ) {
        case 4:
        case 8:
        case 16:
        case 20:
        case 32:
            break;
        case 5:
        case 9:
        case 17:
        case 21:
        case 33:
            if ( inp[0] == '0' ) {
                inp++;
                len--;
                break;
            }
        default:
            asmerr( 2104, inp );
        }

        _atoow( (uint_64 *)out, inp, 16, len );

        for ( p = (uint_8 *)out + size, end = (uint_8 *)out + 16; p < end; p++ )
            if ( *p != NULLC ) {
                asmerr( 2104, inp );
                break;
            }

        if ( ( len / 2 ) != size ) {
            switch ( len / 2 ) {
            case 2  : __cvth_q(out, out);  break;
            case 4  : __cvtss_q(out, out); break;
            case 8  : __cvtsd_q(out, out); break;
            case 10 : __cvtld_q(out, out); break;
            case 16 : break;
            default:
                if ( Parse_Pass == PASS_1 )
                    asmerr( 7004 );
                memset( out, 0, size );
            }
            if ( errno )
                asmerr( 2071 );
        }

    } else {

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
    unsigned short exp = *(unsigned short *)&opnd->chararray[14];

    errno = 0;
    exp &= 0x7FFF;
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
    } else if ( size == 2 )  {
        if ( opnd->chararray[15] & 0x80 ) {
            opnd->negative = 1;
            opnd->chararray[15] &= 0x7F;
        }
        __cvtq_h( opnd->chararray, opnd->chararray );
        if ( opnd->negative )
            opnd->chararray[1] |= 0x80;
        opnd->mem_type = MT_REAL2;
    }
    if ( errno && exp != 0x7FFF )
        asmerr( 2071 );
}
