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
* Description:	Symbol name mangling routines.
*
****************************************************************************/

#include <globals.h>
#include <memalloc.h>
#include <parser.h>
#include <mangle.h>

typedef int (*mangle_func)( const struct asym *, char * );

static int ms32_decorate( const struct asym *sym, char *buffer );
static int ow_decorate( const struct asym *sym, char *buffer );
static int ms64_decorate( const struct asym *sym, char *buffer );
static int vect_decorate( const struct asym *sym, char *buffer );

/* VoidMangler: no change to symbol name */

static int VoidMangler( const struct asym *sym, char *buffer )
{
    memcpy( buffer, sym->name, sym->name_size + 1 );
    return( sym->name_size );
}

/* UCaseMangler: convert symbol name to upper case */

static int UCaseMangler( const struct asym *sym, char *buffer )
{
    memcpy( buffer, sym->name, sym->name_size + 1 );
    _strupr( buffer );
    return( sym->name_size );
}

/* UScoreMangler: add '_' prefix to symbol name */

static int UScoreMangler( const struct asym *sym, char *buffer )
{
    buffer[0] = '_';
    memcpy( buffer+1, sym->name, sym->name_size + 1 );
    return( sym->name_size + 1 );
}

/* StdcallMangler: add '_' prefix and '@size' suffix to proc names */
/*		   add '_' prefix to other symbols */

static int StdcallMangler( const struct asym *sym, char *buffer )
{
    const struct dsym *dir = (struct dsym *)sym;

    if( Options.stdcall_decoration == STDCALL_FULL && sym->isproc ) {
	return( sprintf( buffer, "_%s@%d", sym->name, dir->e.procinfo->parasize ) );
    } else {
	return( UScoreMangler( sym, buffer ) );
    }
}

/* MS FASTCALL 32bit */

static int ms32_decorate( const struct asym *sym, char *buffer )
{
    return ( sprintf( buffer, "@%s@%u", sym->name, ((struct dsym *)sym)->e.procinfo->parasize ) );
}

/* flag values used by the OW fastcall name mangler ( changes ) */
enum changes {
    NORMAL	     = 0,
    USCORE_FRONT     = 1,
    USCORE_BACK	     = 2
};

/* FASTCALL OW style:
 *  add '_' suffix to proc names and labels
 *  add '_' prefix to other symbols
 */

static int ow_decorate( const struct asym *sym, char *buffer )
{
    char		*name;
    enum changes	changes = NORMAL;

    if( sym->isproc ) {
	changes |= USCORE_BACK;
    } else {
	switch( sym->mem_type ) {
	case MT_NEAR:
	case MT_FAR:
	case MT_EMPTY:
	    changes |= USCORE_BACK;
	    break;
	default:
	    changes |= USCORE_FRONT;
	}
    }

    name = buffer;

    if( changes & USCORE_FRONT )
	*name++ = '_';
    memcpy( name, sym->name, sym->name_size + 1 );
    name += sym->name_size;
    if( changes & USCORE_BACK ) {
	*name++ = '_';
	*name = NULLC;
    }
    return( name - buffer );
}

/* MS FASTCALL 64bit */

static int ms64_decorate( const struct asym *sym, char *buffer )
{
    memcpy( buffer, sym->name, sym->name_size + 1 );
    return( sym->name_size );
}

static int vect_decorate( const struct asym *sym, char *buffer )
{
    const struct dsym *dir = (struct dsym *)sym;

    if ( !sym->isproc || !_stricmp( sym->name, "main" ) ) {
	strcpy( buffer, sym->name );
	return( sym->name_size );
    }
    return ( sprintf( buffer, "%s@@%u", sym->name, dir->e.procinfo->parasize ) );
}

int Mangle( struct asym *sym, char *buffer )
{
    mangle_func mangler;

    switch( sym->langtype ) {
    case LANG_C:
	/* leading underscore for C? */
	mangler = Options.no_cdecl_decoration ? VoidMangler : UScoreMangler;
	break;
    case LANG_SYSCALL:
	mangler = VoidMangler;
	break;
    case LANG_STDCALL:
	mangler = ( Options.stdcall_decoration == STDCALL_NONE ) ? VoidMangler : StdcallMangler;
	break;
    case LANG_PASCAL:
    case LANG_FORTRAN:
    case LANG_BASIC:
	mangler = UCaseMangler;
	break;
    case LANG_WATCALL:
	mangler = ow_decorate;
	break;
    case LANG_FASTCALL:		 /* registers passing parameters */
	if ( ModuleInfo.Ofssize == USE64 )
	    mangler = ms64_decorate;
	else if ( ModuleInfo.fctype == FCT_WATCOMC )
	    mangler = ow_decorate;
	else
	    mangler = ms32_decorate;
	break;
    case LANG_VECTORCALL:
	mangler = vect_decorate;
	break;
    default: /* LANG_NONE */
	mangler = VoidMangler;
	break;
    }
    return( mangler( sym, buffer ) );
}

/* the "mangle_type" is an extension inherited from OW Wasm
 * accepted are "C" and "N". It's NULL if MANGLESUPP == 0 (standard)
 */
void SetMangler( struct asym *sym, int langtype, const char *mangle_type )
{
    if( langtype != LANG_NONE )
	sym->langtype = langtype;
}
