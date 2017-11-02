/****************************************************************************
*
*			     Open Watcom Project
*
*    Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
*
*  ========================================================================
*
*    This file contains Original Code and/or Modifications of Original
*    Code as defined in and that are subject to the Sybase Open Watcom
*    Public License version 1.0 (the 'License'). You may not use this file
*    except in compliance with the License. BY USING THIS FILE YOU AGREE TO
*    ALL TERMS AND CONDITIONS OF THE LICENSE. A copy of the License is
*    provided with the Original Code and Modifications, and is also
*    available at www.sybase.com/developer/opensource.
*
*    The Original Code and all software distributed under the License are
*    distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
*    EXPRESS OR IMPLIED, AND SYBASE AND ALL CONTRIBUTORS HEREBY DISCLAIM
*    ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR
*    NON-INFRINGEMENT. Please see the License for the specific language
*    governing rights and limitations under the License.
*
*  ========================================================================
*
* Description:	interface to instruction hash table.
*
****************************************************************************/


#ifndef _RESWORDS_H_INCLUDED
#define _RESWORDS_H_INCLUDED

enum reservedword_flags {
    RWF_DISABLED = 0x01, /* keyword disabled */
    RWF_IA32	 = 0x02, /* keyword specific to IA32 mode */
    RWF_X64	 = 0x04, /* keyword specific to IA32+ mode */
    RWF_VEX	 = 0x08, /* keyword triggers VEX encoding */
    RWF_EVEX	 = 0x10, /* keyword triggers EVEX encoding */
};

/* structure of items in the "reserved names" table ResWordTable[] */

struct ReservedWord {
    uint_16 next;	/* index next entry (used for hash table) */
    uint_8 len;		/* length of reserved word, i.e. 'AX' = 2 */
    uint_8 flags;	/* see enum reservedword_flags */
    const char *name;	/* reserved word (char[]) */
};

unsigned FASTCALL FindResWord( char *name, unsigned size );
extern char	*GetResWName( unsigned, char * );
extern bool	IsKeywordDisabled( const char *, int );
extern void	DisableKeyword( unsigned );
extern void	RenameKeyword( unsigned, const char *, uint_8 );
extern void	Set64Bit( bool );
extern void	ResWordsInit( void );
extern void	ResWordsFini( void );

#endif
