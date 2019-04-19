#include <globals.h>
#include <reswords.h>

#define HASH_TABITEMS 1024

extern uint_16 resw_table[ HASH_TABITEMS ];
extern struct ReservedWord ResWordTable[];

unsigned FASTCALL get_hash( const char *s, unsigned char size );

unsigned FASTCALL FindResWord( char *name, unsigned size )
/* search reserved word in hash table */
{
    struct ReservedWord *inst;
    unsigned i,l;
#ifdef BASEPTR
    __segment seg = FP_SEG( resw_strings );
#endif

    for( i = resw_table[ get_hash( (const char *)name, (unsigned char)size ) ]; i != 0; i = inst->next ) {
	inst = &ResWordTable[i];
	/* check if the name matches the entry for this inst in AsmChars */
	if( inst->len == size ) {
	    for (l = 0; l < size && inst->name[l] == ( name[l] | ' ' ); l++ );
	    if ( l == size )
		return( i );
	}
    }
    return( 0 );
}
