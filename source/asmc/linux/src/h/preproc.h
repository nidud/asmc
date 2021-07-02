
#ifndef _PREPROC_H_INCLUDED
#define _PREPROC_H_INCLUDED

/* v2.11: preprocessor functions moved from input.c to preproc.c */

extern int PreprocessLine( struct asm_tok[] );
extern int WriteCodeLabel( char *, struct asm_tok[] );

#endif
