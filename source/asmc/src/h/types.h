
/* prototypes of TYPES.C */

#ifndef _TYPES_H_INCLUDED
#define _TYPES_H_INCLUDED

/* qualified_type us used for parsing a qualified type. */
struct qualified_type {
    int		    size;
    struct asym	    *symtype;
    unsigned char   mem_type;
    uint_8	    is_ptr; /* contains level of indirection */
    uint_8	    is_far;
    uint_8	    Ofssize;
    unsigned char   ptr_memtype;
};

extern struct dsym *CurrStruct; /* start of current STRUCT list */

extern int	   CreateType( int, struct asm_tok[], char *, struct asym ** );
extern struct asym *CreateTypeSymbol( struct asym *, const char *, bool );
extern struct asym *SearchNameInStruct( const struct asym *, const char *, uint_32 *, int level );
extern int	   GetQualifiedType( int *, struct asm_tok[], struct qualified_type * );
extern struct asym *CreateStructField( int, struct asm_tok[], const char *, unsigned char, struct asym *, uint_32 );
extern void	   UpdateStructSize( struct asym * );
extern int	   SetStructCurrentOffset( int_32 );
extern int	   AlignInStruct( int );
extern void	   TypesInit( void );

#define DeleteType( t )
#endif
