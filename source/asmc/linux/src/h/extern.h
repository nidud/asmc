/****************************************************************************
*
* Description:	prototypes of extern.c
*
****************************************************************************/

#ifndef _EXTERN_H_
#define _EXTERN_H_

extern struct asym *MakeExtern( const char *name, unsigned char type, struct asym * vartype, struct asym *, unsigned char );
extern void  AddPublicData( struct asym *sym );

#define FreePubQueue() ModuleInfo.g.PubQueue.head = NULL

#endif
