/****************************************************************************
*
* Description:	listing interface.
*
****************************************************************************/


#ifndef _LISTING_H_INCLUDED
#define _LISTING_H_INCLUDED

enum lsttype {
 LSTTYPE_DATA,
 LSTTYPE_CODE,
 LSTTYPE_EQUATE,
 LSTTYPE_TMACRO,
 LSTTYPE_DIRECTIVE,
 LSTTYPE_MACRO,
 LSTTYPE_STRUCT,
 LSTTYPE_LABEL,
 LSTTYPE_MACROLINE,
};

extern void __stdcall LstInit( void );
extern void __stdcall LstWrite( enum lsttype, uint_32 ofs, void * sym );
extern void LstWriteSrcLine( void );
extern void __stdcall LstWriteCRef( void );
extern void __cdecl   LstPrintf( const char *format, ... );
extern void __stdcall LstNL( void );
extern void __stdcall LstSetPosition( void );

#endif
