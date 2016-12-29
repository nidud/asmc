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
* Description:	prototypes for macro stuff
*
****************************************************************************/

#ifndef _MACRO_H_
#define _MACRO_H_

#define PLACEHOLDER_CHAR '\n' /* "escape" char for macro placeholders */

enum macro_flags {
    MF_LABEL  = 0x01,	/* a label exists at pos 0 */
    MF_NOSAVE = 0x02,	/* no need to save/restore input status */
    MF_IGNARGS = 0x04	/* ignore additional arguments (for FOR directive) */
};

/* functions in expans.c */

int  GetLiteralValue( char *, const char * );
int  RunMacro( struct dsym *, int, struct asm_tok[], char *, int, bool * );
int  ExpandText( char *, struct asm_tok[], unsigned int );
int  ExpandLineItems( char *, int, struct asm_tok[], int, int );
int  ExpandLine( char *, struct asm_tok[] );
void ExpandLiterals( int i, struct asm_tok[] );

/* functions in macro.c */

extern struct dsym *CreateMacro( const char * );/* create a macro symbol */
extern void	ReleaseMacroData( struct dsym * );
extern void	fill_placeholders( char *, const char *, unsigned, unsigned, char * * );
extern void	SkipCurrentQueue( struct asm_tok[] );
extern ret_code StoreMacro( struct dsym *, int, struct asm_tok[], bool );  /* store macro content */
extern ret_code MacroInit( int );

/* functions in string.c */

extern struct asym *SetTextMacro( struct asm_tok[], struct asym *, const char *, const char * ); /* EQU for texts */
extern struct asym *AddPredefinedText( const char *, const char * );
extern int	   TextItemError( struct asm_tok * );

extern void	StringInit( void );

#endif
