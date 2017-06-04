/****************************************************************************
*
* Description:	prototypes of extern.c
*
****************************************************************************/

#ifndef _EXTERN_H_
#define _EXTERN_H_

/*---------------------------------------------------------------------------*/
extern struct asym   *MakeExtern( const char *name, unsigned char type, struct asym * vartype, struct asym *, unsigned char );
extern void  FASTCALL AddPublicData( struct asym *sym );
//extern void  FreePubQueue( void );
#define FreePubQueue() ModuleInfo.g.PubQueue.head = NULL

#endif
