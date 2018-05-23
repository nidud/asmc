#include <float.h>

#include <globals.h>
#include <expreval.h>
#include <symbols.h>
#include <atofloat.h>

#if defined(LLONG_MAX) || defined(__GNUC__) || defined(__TINYC__)
#define MAXUI64BIT 0x8000000000000000ULL
#define MAXUI64    0xffffffffffffffffULL
#else
#define MAXUI64BIT 0x8000000000000000ui64
#define MAXUI64    0xffffffffffffffffui64
#endif

#define _OVERFLOW 3 /* overflow range error */

#define Q_SIGBITS   113
#define Q_EXPBITS   15
#define Q_EXPMASK   ((1 << Q_EXPBITS) - 1)
#define Q_EXPBIAS   (Q_EXPMASK >> 1)
#define Q_EXPMAX    (Q_EXPMASK - Q_EXPBIAS)

#pragma pack(push,1)

typedef union {
    struct {
        uint_16 qmw;
        uint_32 qmd;
        uint_64 qmh;
        uint_16 qe;
    };
    struct {
        uint_64 ldm;
        uint_16 lde;
    };
    double d;
    float f;
    uint_8 m8[16];
    uint_16 m16[8];
    uint_32 m32[4];
    uint_64 m64[2];
  } F128, U128;

typedef union {
    uint_64 m64[4];
    uint_32 m32[8];
    uint_16 m16[16];
    uint_8 m8[32];
  } U256;

/* extended (134-bit, 128+16) quad float */

typedef struct {
    union {
        uint_32 m32[4];
        uint_64 m64[2];
        uint_16 m16[8];
        uint_8 m8[16];
    };
    uint_16 e;
  } E128;

#pragma pack(pop)

#define U128ISNOTZERO(x) (x.m64[0] || x.m64[1])
#define MAX_EXP_INDEX 14 /* # of items in tab_plus_exp[] and tab_minus_exp[] */

static E128 tab_plus_exp[MAX_EXP_INDEX] = {
    { { 0x00000000UL, 0x00000000UL, 0x00000000UL, 0xA0000000UL }, 0x4002 }, /* 1e1L    */
    { { 0x00000000UL, 0x00000000UL, 0x00000000UL, 0xC8000000UL }, 0x4005 }, /* 1e2L    */
    { { 0x00000000UL, 0x00000000UL, 0x00000000UL, 0x9C400000UL }, 0x400C }, /* 1e4L    */
    { { 0x00000000UL, 0x00000000UL, 0x00000000UL, 0xBEBC2000UL }, 0x4019 }, /* 1e8L    */
    { { 0x00000000UL, 0x00000000UL, 0x04000000UL, 0x8E1BC9BFUL }, 0x4034 }, /* 1e16L   */
    { { 0x00000000UL, 0xF0200000UL, 0x2B70B59DUL, 0x9DC5ADA8UL }, 0x4069 }, /* 1e32L   */
#if 1
    { { 0xC76B0000UL, 0x3CBF6B71UL, 0xFFCFA6D5UL, 0xC2781F49UL }, 0x40D3 }, /* 1e64L   */
    { { 0x36B10000UL, 0xC66F336CUL, 0x80E98CDFUL, 0x93BA47C9UL }, 0x41A8 }, /* 1e128L  */
    { { 0x98FE8000UL, 0xDDBB901BUL, 0x9DF9DE8DUL, 0xAA7EEBFBUL }, 0x4351 }, /* 1e256L  */
    { { 0xBC500000UL, 0xCC655C54UL, 0xA60E91C6UL, 0xE319A0AEUL }, 0x46A3 }, /* 1e512L  */
    { { 0xF18B0000UL, 0x650D3D28UL, 0x81750C17UL, 0xC9767586UL }, 0x4D48 }, /* 1e1024L */
    { { 0x329A8000UL, 0xA74D28CEUL, 0xC53D5DE4UL, 0x9E8b3B5DUL }, 0x5A92 }, /* 1e2048L */
    { { 0x804A8000UL, 0xC94C153FUL, 0x8A20979AUL, 0xC4605202UL }, 0x7525 }, /* 1e4096L */
#else
    { { 0xC76B25FBUL, 0x3CBF6B71UL, 0xFFCFA6D5UL, 0xC2781F49UL }, 0x40D3 }, /* 1e64L   */
    { { 0x36B10137UL, 0xC66F336CUL, 0x80E98CDFUL, 0x93BA47C9UL }, 0x41A8 }, /* 1e128L  */
    { { 0x98FEEAB7UL, 0xDDBB901BUL, 0x9DF9DE8DUL, 0xAA7EEBFBUL }, 0x4351 }, /* 1e256L  */
    { { 0xBC5058F8UL, 0xCC655C54UL, 0xA60E91C6UL, 0xE319A0AEUL }, 0x46A3 }, /* 1e512L  */
    { { 0xF18B50CEUL, 0x650D3D28UL, 0x81750C17UL, 0xC9767586UL }, 0x4D48 }, /* 1e1024L */
    { { 0x329ACE52UL, 0xA74D28CEUL, 0xC53D5DE4UL, 0x9E8b3B5DUL }, 0x5A92 }, /* 1e2048L */
    { { 0x804AC460UL, 0xC94C153FUL, 0x8A20979AUL, 0xC4605202UL }, 0x7525 }, /* 1e4096L */
#endif
    { { 0x00000000UL, 0x00000000UL, 0x00000000UL, 0x80000000UL }, 0x7FFF }  /* 1e8192L - Infinity */
};

static E128 tab_minus_exp[MAX_EXP_INDEX] = {
#if 1
    { { 0xCCCCCCCCUL, 0xCCCCCCCCUL, 0xCCCCCCCCUL, 0xCCCCCCCCUL }, 0x3FFB }, /* 1e-1L   */
    { { 0x0A3D0000UL, 0x3D70A3D7UL, 0x70A3D70AUL, 0xA3D70A3DUL }, 0x3FF8 }, /* 1e-2L   */
    { { 0x404E0000UL, 0xD3C36113UL, 0xE219652BUL, 0xD1B71758UL }, 0x3FF1 }, /* 1e-4L   */
    { { 0x36BA0000UL, 0xFDC20D2AUL, 0x8461CEFCUL, 0xABCC7711UL }, 0x3FE4 }, /* 1e-8L   */
    { { 0x79890000UL, 0x4C2EBE68UL, 0xC44DE15BUL, 0xE69594BEUL }, 0x3FC9 }, /* 1e-16L  */
    { { 0xA5810000UL, 0x67DE18EDUL, 0x453994BAUL, 0xCFB11EADUL }, 0x3F94 }, /* 1e-32L  */
    { { 0x47B30000UL, 0x3F2398D7UL, 0xA539E9A5UL, 0xA87FEA27UL }, 0x3F2A }, /* 1e-64L  */
    { { 0xD05D0000UL, 0xAC7CB3F6UL, 0x64BCE4A0UL, 0xDDD0467CUL }, 0x3E55 }, /* 1e-128L */
    { { 0xFEFB0000UL, 0xFA911155UL, 0x637A1939UL, 0xC0314325UL }, 0x3CAC }, /* 1e-256L */
    { { 0xE3F10000UL, 0x7132D332UL, 0xDB23D21CUL, 0x9049EE32UL }, 0x395A }, /* 1e-512L */
    { { 0x6BD30000UL, 0x87A60158UL, 0xDA57C0BDUL, 0xA2A682A5UL }, 0x32B5 }, /* 1e-1024L*/
    { { 0xF2EA0000UL, 0x492512D4UL, 0x34362DE4UL, 0xCEAE534FUL }, 0x256B }, /* 1e-2048L*/
    { { 0xA1C30000UL, 0x2DE38123UL, 0xD2CE9FDEUL, 0xA6DD04C8UL }, 0x0AD8 }, /* 1e-4096L*/
#else
    { { 0xCCCCCCCCUL, 0xCCCCCCCCUL, 0xCCCCCCCCUL, 0xCCCCCCCCUL }, 0x3FFB }, /* 1e-1L   */
    { { 0x0A3D70A3UL, 0x3D70A3D7UL, 0x70A3D70AUL, 0xA3D70A3DUL }, 0x3FF8 }, /* 1e-2L   */
    { { 0x404E8000UL, 0xD3C36113UL, 0xE219652BUL, 0xD1B71758UL }, 0x3FF1 }, /* 1e-4L   */
    { { 0x36BA0000UL, 0xFDC20D2AUL, 0x8461CEFCUL, 0xABCC7711UL }, 0x3FE4 }, /* 1e-8L   */
    { { 0x79898000UL, 0x4C2EBE68UL, 0xC44DE15BUL, 0xE69594BEUL }, 0x3FC9 }, /* 1e-16L  */
    { { 0xA5810000UL, 0x67DE18EDUL, 0x453994BAUL, 0xCFB11EADUL }, 0x3F94 }, /* 1e-32L  */
    { { 0x47B38000UL, 0x3F2398D7UL, 0xA539E9A5UL, 0xA87FEA27UL }, 0x3F2A }, /* 1e-64L  */
    { { 0xD05D8000UL, 0xAC7CB3F6UL, 0x64BCE4A0UL, 0xDDD0467CUL }, 0x3E55 }, /* 1e-128L */
    { { 0xFEFB0000UL, 0xFA911155UL, 0x637A1939UL, 0xC0314325UL }, 0x3CAC }, /* 1e-256L */
    { { 0xE3F18000UL, 0x7132D332UL, 0xDB23D21CUL, 0x9049EE32UL }, 0x395A }, /* 1e-512L */
    { { 0x6BD38000UL, 0x87A60158UL, 0xDA57C0BDUL, 0xA2A682A5UL }, 0x32B5 }, /* 1e-1024L*/
    { { 0xF2EA8000UL, 0x492512D4UL, 0x34362DE4UL, 0xCEAE534FUL }, 0x256B }, /* 1e-2048L*/
    { { 0xA1C38000UL, 0x2DE38123UL, 0xD2CE9FDEUL, 0xA6DD04C8UL }, 0x0AD8 }, /* 1e-4096L*/
#endif
    { { 0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL }, 0x7FFF }  /* 1e-8192L - Infinity */
};

int qerrno = 0;
/*
 *  compare u128 with maximum value before u128
 *  overflow after multiply by 10
 */
static int cmp_u128_max( const U128 *x )
{
    if( x->m32[3] > 0x19999999UL ) {
        return( 1 );
    } else if( x->m32[3] < 0x19999999UL ) {
        return( -1 );
    } else if( x->m32[2] > 0x99999999UL ) {
        return( 1 );
    } else if( x->m32[2] < 0x99999999UL ) {
        return( -1 );
    } else if( x->m32[1] > 0x99999999UL ) {
        return( 1 );
    } else if( x->m32[1] < 0x99999999UL ) {
        return( -1 );
    } else if( x->m32[0] > 0x99999998UL ) {
        return( 1 );
    } else if( x->m32[0] < 0x99999998UL ) {
        return( -1 );
    } else {
        return( 0 );
    }
}

/*
 *  test u128 overflow after multiply by 10
 *  add one decimal digit to u128
 */
static int add_check_u128_overflow( U128 *x, unsigned int c )
{
    uint_64 cy;
    int i;

    if( cmp_u128_max( x ) > 0 ) {
        return( 1 );
    } else {
        cy = c;
        for( i = 0; i < 4; i++ ) {
            cy += (uint_64)x->m32[i] * 10;
            x->m32[i] = cy;
            cy >>= 32;
        }
        return( 0 );
    }
}

/* calculate bitsize for uint_32 */
static int bitsize32( uint_32 x )
{
    int i;

    for( i = 32; i > 0 ; i-- ) {
        if( x & 0x80000000U ) break;
        x <<= 1;
    }
    return( i );
}

/* calculate bitsize for uint_64 */
static int bitsize64( uint_64 x )
{
    int i;

    for( i = 64; i > 0 ; i-- ) {
        if( x & MAXUI64BIT ) break;
        x <<= 1;
    }
    return( i );
}

/* convert U128 into internal extended quad float */
static int U128_to_exquad( E128 *res, U128 *op )
{
    int bs, shft;

    memcpy( res, op, sizeof( U128 ) );
    bs = bitsize32( res->m32[3] ) + 96;
    if( bs == 96 ) {
        res->m32[3] = res->m32[2];
        res->m32[2] = res->m32[1];
        res->m32[1] = res->m32[0];
        res->m32[0] = 0;
        bs = bitsize32( res->m32[3] ) + 64;
    }
    if( bs == 64 ) {
        res->m32[3] = res->m32[2];
        res->m32[2] = res->m32[1];
        res->m32[1] = 0;
        bs = bitsize32( res->m32[3] ) + 32;
    }
    if( bs == 32 ) {
        res->m32[3] = res->m32[2];
        res->m32[2] = 0;
        bs = bitsize32( res->m32[3] );
    }
    if( bs == 0 ) {
        res->e = 0;
    } else {
        res->e = bs - 1 + Q_EXPBIAS;
        bs %= 32;
        if( bs ) {
            shft = 32 - bs;
            res->m32[3] <<= shft;
            res->m32[3] |= res->m32[2] >> bs;
            res->m32[2] <<= shft;
            res->m32[2] |= res->m32[1] >> bs;
            res->m32[1] <<= shft;
            res->m32[1] |= res->m32[0] >> bs;
            res->m32[0] <<= shft;
        }
    }
    return( 0 );
}

/*
 *  normalize internal extended quad float u256
 *  return exponent shift
 */
static int normalize( U256 *res )
{
    int shft, bs, bs1;

    bs = bitsize64( res->m64[3] ) + 192;
    if ( bs == 192 ) {

        res->m64[3] = res->m64[2];
        res->m64[2] = res->m64[1];
        res->m64[1] = res->m64[0];
        res->m64[0] = 0;
        bs = bitsize64( res->m64[3] ) + 128;

        if ( bs == 128 ) {

            res->m64[3] = res->m64[2];
            res->m64[2] = res->m64[1];
            res->m64[1] = 0;
            bs = bitsize64( res->m64[3] ) + 64;

            if ( bs == 64 ) {

                res->m64[3] = res->m64[2];
                res->m64[2] = 0;
                bs = bitsize64( res->m64[3] );
            }
        }
    }
    if ( bs == 0 )
        return( 0 );

    bs1 = bs % 64;
    if ( bs1 ) {
        shft = 64 - bs1;
        res->m64[3] <<= shft;
        res->m64[3] |= res->m64[2] >> bs1;
        res->m64[2] <<= shft;
        res->m64[2] |= res->m64[1] >> bs1;
        res->m64[1] <<= shft;
        res->m64[1] |= res->m64[0] >> bs1;
        res->m64[0] <<= shft;
    }
    return( bs - 256 );
}

/*
 *  multiply u128 by u128 into u128
 *  normalize and round result
 */
static void multiply( E128 *op1, E128 *op2 )
{
    U256 r1;
    uint_64 x;
    uint_32 c, z, *p;
    int_32 exp,i,q;

    static uint_8 r32[] = { 1,1,2,2,3,3,3,3,4,4,5,5 };
    static uint_8 a32[] = { 1,0,0,2,1,2,0,3,1,3,2,3 };
    static uint_8 b32[] = { 0,1,2,0,2,1,3,0,3,1,3,2 };

    exp = (int_32)(op1->e & Q_EXPMASK) + (int_32)(op2->e & Q_EXPMASK) - Q_EXPBIAS + 1;

    r1.m64[0] = (uint_64)(op1->m32[0]) * (uint_64)(op2->m32[0]);
    r1.m64[1] = (uint_64)(op1->m32[1]) * (uint_64)(op2->m32[1]);
    r1.m64[2] = (uint_64)(op1->m32[2]) * (uint_64)(op2->m32[2]);
    r1.m64[3] = (uint_64)(op1->m32[3]) * (uint_64)(op2->m32[3]);

    for ( q = 0; q < sizeof(r32); q++ ) {
        if ( ( x = (uint_64)(op1->m32[a32[q]]) * (uint_64)(op2->m32[b32[q]]) ) ) {
            p = &r1.m32[r32[q]];
            c = ( ( p[0] + (uint_32)x ) < p[0] );
            z = p[1] + (uint_32)(x >> 32) + c;
            c = ( z < p[1] );
            p[0] += (uint_32)x;
            p[1] = z;
            for ( p += 2, i = r32[q] + 2; c && i < 8; i++, p++ ) {
                c = ( *p + 1 < *p );
                (*p)++;
            }
        }
    }

    exp += normalize( &r1 );

    if( r1.m8[15] & 0x80U ) {
        if( r1.m32[4] == 0xffffffffU && r1.m32[5] == 0xffffffffU &&
            r1.m32[6] == 0xffffffffU && r1.m32[7] == 0xffffffffU ) {
            r1.m32[4] = 0;
            r1.m32[5] = 0;
            r1.m32[6] = 0;
            r1.m32[7] = 0x80000000U;
            exp++;
        } else {
            c = ( ( r1.m32[4] + 1 ) < r1.m32[4] );
            r1.m32[4] += 1;
            for ( i = 5; c && i < 8; i++ ) {
                c = ( r1.m32[i] + 1 < r1.m32[i] );
                r1.m32[i] += 1;
            }
        }
    }
    op1->m64[0] = r1.m64[2];
    op1->m64[1] = r1.m64[3];
    op1->e = exp;
}

/* convert REAL16 into internal extended quad float */

static void quad_to_exquad( E128 *res, F128 *q )
{
    res->m16[0] = 0;
    res->m16[1] = q->qmw;
    res->m32[1] = q->qmd;
    res->m64[1] = q->qmh;
    res->e      = q->qe;

    res->m64[0] >>= 1;
    if ( res->m16[4] & 1 )
        res->m16[3] |= 0x8000U;

    res->m64[1] >>= 1;
    if ( res->e )
        res->m16[7] |= 0x8000U;
}

static void exquad_to_quad( F128 *q, E128 *res )
{
    q->qmw = res->m16[1];
    q->qmd = res->m32[1];
    q->qmh = res->m64[1];
    q->qe  = res->e;

    q->qmh <<= 1;
    if ( q->m8[5] & 0x80U )
        q->m8[6] |= 1;
    q->qmd <<= 1;
    if ( q->m8[1] & 0x80U )
        q->m8[2] |= 1;
    q->qmw <<= 1;
    if ( res->m8[1] & 0x80U )
        q->qmw |= 1;
    if ( res->m8[1] & 0x40U ) {
        /*if( q->m32[0] == 0xfffffffeU && q->m32[1] == 0xffffffffU &&
            q->m32[2] == 0xffffffffU && q->m16[6] == 0xffffU ) {
            q->m32[0] = 0;
            q->m32[1] = 0;
            q->m32[2] = 0;
            q->m16[6] = 0;
            q->qe++;
        } else*/ if ( (uint_16)(q->qmw + 1) < q->qmw++ ) {
            if ( (q->qmd + 1) < q->qmd++ ) {
                if ( (q->qmh + 1) < q->qmh++ )
                    q->qe++;
            }
        }
    }
}

static void exquad_to_ldouble( F128 *q, E128 *res )
{
    uint_16 cx = res->m16[1];
    q->ldm = res->m64[1];
    q->lde = res->e;
    if ( cx & 0x8000U ) {
        if( q->ldm == MAXUI64 ) {
            q->ldm = MAXUI64BIT;
            q->lde++;
        } else
            q->ldm++;
    }
}

static int exquad_to_double( F128 *q, E128 *res )
{
    uint_16 cx;
    uint_32 eax, edx, esi, ebx;
    int convert_error = 0;

    exquad_to_ldouble( q, res );

    eax = q->m32[0];
    edx = q->m32[1];
    cx  = q->m16[4];
    esi = 0xFFFFF800;
    ebx = eax << 22;

    if ( eax & ( 1 << ( 32 - 22 ) ) ) {
        if ( !ebx )
            esi <<= 1;
        if ( eax > eax + 0x0800 ) {
            if ( edx > edx + 1 ) {
                edx = 0x80000000;
                cx++;
            } else
                edx++;
        }
        eax += 0x0800;
    }

    eax &= esi;
    ebx = cx;
    cx &= 0x7FFF;
    cx += 0x03FF-0x3FFF;

    if ( cx < 0x07FF ) {
        if ( cx == 0 ) {
            eax >>= 12;
            eax |= ( edx & ( ( 1 << 12 ) - 1 ) ) << 20;
            edx <<= 1;
            edx >>= 12;
        } else {
            eax >>= 11;
            eax |= ( edx & ( ( 1 << 11 ) - 1 ) ) << 21;
            edx <<= 1;
            edx >>= 11;
            edx |= ( cx & ( ( 1 << 11 ) - 1 ) ) << 21;
        }
        edx >>= 1;
        if ( ebx & 0x8000 )
            edx |= 0x80000000;
    } else if ( cx < 0xC400 ) {
        eax >>= 11;
        eax |= ( edx & ( ( 1 << 11 ) - 1 ) ) << 21;
        edx <<= 1;
        edx >>= 11;
        edx >>= 1;
        if ( ebx & 0x8000 )
            edx |= 0x80000000;
        edx |= 0x7FF00000;
        if ( cx != 0x43FF )
            convert_error = _OVERFLOW;
    } else if ( (short)cx < -52 ) {
        eax = 0;
        edx = 0;
        if ( ebx & 0x8000 )
            edx |= 0x80000000;
    } else {
        cx -= 12;
        cx = (-cx & 0xFF);
        if ( cx >= 32 ) {
            cx -= 32;
            esi = eax;
            eax = edx;
            edx = 0;
        }
        esi >>= cx;
        esi |= ( eax & ( ( 1 << cx ) - 1 ) ) << ( 32 - cx );
        eax >>= cx;
        eax |= ( edx & ( ( 1 << cx ) - 1 ) ) << ( 32 - cx );
        edx >>= cx;
        if ( esi & 0x80000000U ) {
            if ( eax < eax + 1 )
                edx++;
            eax++;
        }
    }
    cx = ( q->m16[4] & Q_EXPMASK );
    if ( cx < 0x3BCC ) {
        if ( !( !cx && res->m32[2] == 0 && res->m32[3] == 0 ) ) {
            eax = 0;
            edx = 0;
            convert_error = ERANGE;
        }
    } else if ( cx >= 0x3BCD ) {
        convert_error = ERANGE;
        if ( ( edx & 0x7FF00000 ) && ( edx & 0x7FF00000 ) != 0x7FF00000 )
            convert_error = 0;
    } else if ( cx >= 0x3BCC ) {
        convert_error = ERANGE;
        if ( ( edx & eax ) && ( edx & 0x7FF00000 ) )
            convert_error = 0;
    }
    if ( convert_error )
        asmerr( 2071 );

    q->m32[0] = eax;
    q->m32[1] = edx;
    q->m64[1] = 0;

    return convert_error;
}

static int exquad_to_float( F128 *q, E128 *res )
{
    float float_value;
    int convert_error;

    convert_error = exquad_to_double( q, res );

    if ( convert_error == 0 ) {

        if ( q->d > FLT_MAX || ( q->d < FLT_MIN && q->d != 0 ) )
            convert_error = asmerr( 2071 );

        float_value = q->d;
        q->f = float_value;
        q->m32[1] = 0;
    }
    return convert_error;
}

#if 0
static int float_to_quad( void *q, void *f )
{
    uint_16 cx;
    uint_32 eax;
    F128 *p = (F128 *)q;
    int convert_error = 0;

    eax = *(uint_32 *)f;
    cx = (eax >> 32-9) & 0xFF;
    eax <<= 8;

    if ( cx ) {
        if ( cx != 0xFF )
            cx += 0x3FFF-0x7F;
        else {
            cx |= 0x7F00;
            if ( !( eax & 0x7FFFFFFF ) ) {

                /* Invalid exception */
                eax |= 0x40000000; /* QNaN */
                convert_error = ERANGE;
            }
        }
        eax |= 0x80000000;

    } else if ( eax ) {

        cx |= 0x3FFF-0x7F+1; /* set exponent */
        while ( !( eax & 0x80000000 ) ) {

            /* normalize number */
            eax <<= 1;
            cx--;
        }
    }
    p->m64[0] = 0;
    p->m64[1] = 0;
    eax <<= 1;
    if ( cx & 0x8000 )
        cx = (( cx & Q_EXPMASK ) | 1);
    p->m16[5] = eax;
    p->m16[6] = eax >> 16;
    p->m16[7] = cx;

    return convert_error;
}
#endif

void *quadadd( void *a, void *b )
{
    asmerr( 2050 );
    return a;
}

void *quadsub( void *a, void *b )
{
    asmerr( 2050 );
    return a;
}

void *quadmul( void *a, void *b )
{
    E128 xa, xb;

    quad_to_exquad( &xa, (F128 *)a );
    quad_to_exquad( &xb, (F128 *)b );

    multiply( &xa, &xb );
    exquad_to_quad( (F128 *)a, &xa );
    return a;
}

void *quaddiv( void *a, void *b )
{
    asmerr( 2050 );
    return a;
}

void quad_resize( struct expr *opnd, unsigned size )
{
    E128 res;

    quad_to_exquad(&res, (F128 *)opnd->chararray);
    if ( size == 10 )
        exquad_to_ldouble( (F128 *)opnd->chararray, &res );
    else if ( size == 8 ) {
        if ( res.e & 0x8000 ) {
            opnd->negative = 1;
            res.e &= Q_EXPMASK;
        }
        exquad_to_double( (F128 *)opnd->chararray, &res );
        if ( opnd->negative )
            opnd->dvalue *= -1;
        opnd->mem_type = MT_REAL8;
    } else {
        if ( res.e & 0x8000 ) {
            opnd->negative = 1;
            res.e &= Q_EXPMASK;
        }
        exquad_to_float( (F128 *)opnd->chararray, &res );
        if ( opnd->negative )
            opnd->fvalue *= -1;
        opnd->mem_type = MT_REAL4;
    }
}

void *quadtof( void *f, void *q )
{
    E128 res;
    int negative = 0;
    float *fvalue = (float *)q;

    quad_to_exquad(&res, q);
    if ( res.e & 0x8000 ) {
        negative = 1;
        res.e &= 0x7FFF;
    }
    exquad_to_float( q, &res );
    if ( negative )
        *fvalue *= -1;

    return f;
}

void *quadtod( void *d, void *q )
{
    E128 res;
    int negative = 0;
    double *dvalue = (double *)q;

    quad_to_exquad(&res, q);
    if ( res.e & 0x8000 ) {
        negative = 1;
        res.e &= 0x7FFF;
    }
    exquad_to_double( q, &res );
    if ( negative )
        *dvalue *= -1;

    return d;
}

void *quadtold( void *ld, void *q )
{
    E128 res;

    quad_to_exquad(&res, q);
    exquad_to_ldouble( q, &res );
    return ld;
}

/*
 *  create quad float from u128 value and
 *  decimal exponent, round result
 */
static void TB_create( U128 *value, int_32 exponent, F128 *q )
{
    int i;
    E128 res, *tabExp;

    if( exponent < 0 ) {
        exponent = -exponent;
        tabExp = tab_minus_exp;
    } else
        tabExp = tab_plus_exp;
    U128_to_exquad(&res, value);
    for( i = 0; i < MAX_EXP_INDEX; i++ ) {
        if ( exponent & 1 )
            multiply(&res, tabExp + i);
        exponent >>= 1;
        if( exponent == 0 )
            break;
    }
    exquad_to_quad( q, &res );
}

/*
 *  convert string into tbyte/long double
 *  set result sign
 */
void *atoquad( void *pqf, const char *p, char **endptr  )
{
    int     sign = +1;
    int     exp_sign = +1;
    int_32  exp_value;
    int     overflow;
    int_32  exp1;
    int_32  exponent;
    int_32  exponent_tmp;
    F128    value;
    F128    value_tmp;
    F128    *q = pqf;

    while ( islspace( *p ) ) p++;
    switch (*p) {
    case '-':
        sign = -1;
    case '+':
        p++;
    default :
        break;
    }

    memset( &value, 0, sizeof( value ) );
    memset( &value_tmp, 0, sizeof( value_tmp ) );

    exp1 = 0;
    exponent_tmp = 0;
    overflow = 0;

    while ( (unsigned int)(*p - '0') < 10u ) {
        if( overflow ) {
            exponent_tmp++;
            exp1++;
        } else {
            if( add_check_u128_overflow( &value_tmp, *p - '0' ) ) {
                overflow = 1;
                exponent_tmp++;
                exp1++;
            } else if( *p != '0' ) {
                memcpy( &value, &value_tmp, sizeof( value ) );
                exp1 = 0;
            } else if( U128ISNOTZERO(value) ) {
                exp1++;
            }
        }
        p++;
    }
    exponent = exp1;
    if ( *p == '.' ) {
        p++;
        while ( (unsigned int)(*p - '0') < 10u ) {
            if( overflow == 0 ) {
                if( add_check_u128_overflow( &value_tmp, *p - '0' ) ) {
                    overflow = 1;
                } else {
                    exponent_tmp--;
                    if( *p != '0' ) {
                        memcpy( &value, &value_tmp, sizeof( value ) );
                        exponent = exponent_tmp;
                    }
                }
            }
            p++;
        }
    }
    exp_value   = 0;
    if ( (*p | 0x20) == 'e' ) {
        switch ( *++p ) {
        case '-':
            exp_sign = -1;
        case '+': p++;
            break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            break;
        default :
            q->m64[0] = 0L;
            q->m64[1] = 0L;
            return( q );
        }
        while ( (unsigned int)(*p - '0') < 10u )
            exp_value = 10 * exp_value + (*p++ - '0');
        if( exp_sign < 0 )
            exp_value = -exp_value;
    }
    exp_value += exponent;
    TB_create( &value, exp_value, q );
    return( q );
}

