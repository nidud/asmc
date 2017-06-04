#include <globals.h>

void _atoow( void *dst, const char *src, int radix, int size )
{
    unsigned int eax;
    unsigned int ecx;
    unsigned short *w = dst;
    unsigned int   *q = dst;
#ifdef	CHEXPREFIX
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
