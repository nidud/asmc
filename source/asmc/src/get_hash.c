#include <globals.h>

#define HASH_TABITEMS 1024

unsigned FASTCALL get_hash( const char *s, unsigned char size )
{
    uint_32 h;
    uint_32 g;

    for( h = 0; size; size-- ) {
	/* ( h & ~0x0fff ) == 0 is always true here */
	h = (h << 3) + (*s++ | ' ');
	g = h & ~0x1fff;
	h ^= g;
	h ^= g >> 13;
    }
    return( h & ( HASH_TABITEMS - 1 ) );
}
