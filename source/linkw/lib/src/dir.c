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
* Description:  DOS implementation of directory functions.
*
****************************************************************************/


#include <io.h>
#include "variety.h"
//#include "widechar.h"
#include <stdlib.h>
#include <string.h>
#include <mbstring.h>
#include <direct.h>
#include <dos.h>
//#include "strdup.h"
//#include "liballoc.h"
//#include "tinyio.h"
//#include "seterrno.h"
//#include "msdos.h"
//#include "rtdata.h"

#define NULLCHAR 0

#define _A_NORMAL	0x00	/* Normal file - read/write permitted */
#define _A_RDONLY	0x01	/* Read-only file */
#define _A_HIDDEN	0x02	/* Hidden file */
#define _A_SYSTEM	0x04	/* System file */
#define _A_VOLID	0x08	/* Volume-ID entry */
#define _A_SUBDIR	0x10	/* Subdirectory */
#define _A_ARCH		0x20	/* Archive file */
#define SEEK_ATTRIB (_A_HIDDEN | _A_SYSTEM | _A_SUBDIR)

#define NAME_MAX	259	/* maximum filename for NTFS and FAT LFN */

struct dirent {
    int			h;
    char		d_dta[21-sizeof(int)];
    char		d_attr;		    /* file's attribute */
    unsigned short int  d_time;		    /* file's time */
    unsigned short int  d_date;		    /* file's date */
    long		d_size;		    /* file's size */
    char		d_name[NAME_MAX+1]; /* file's name */
    unsigned short	d_ino;		    /* serial number (not used) */
    char		d_first;	    /* flag for 1st time */
    char		*d_openpath;	    /* path specified to opendir */
};

#define DIR_TYPE struct dirent

#include "_direct.h"

static int is_directory( const char *name )
/**********************************************/
{
    UINT_WC_TYPE    curr_ch;
    UINT_WC_TYPE    prev_ch;

    curr_ch = NULLCHAR;
    for(;;) {
	prev_ch = curr_ch;
#if defined( __WIDECHAR__ ) || defined( __UNIX__ )
	curr_ch = *name;
#else
	curr_ch = _mbsnextc( name );
#endif
	if( curr_ch == NULLCHAR )
	    break;
	if( prev_ch == '*' )
	    break;
	if( prev_ch == '?' )
	    break;
#if defined( __WIDECHAR__ ) || defined( __UNIX__ )
	++name;
#else
	name = _mbsinc( name );
#endif
    }
    if( curr_ch == NULLCHAR ) {
	if( prev_ch == '\\' || prev_ch == '/' || prev_ch == '.' ) {
	    return( 1 );
	}
    }
    return( 0 );
}


_WCRTLINK DIR_TYPE *_opendir( const char *dirname,
					    unsigned attr, DIR_TYPE *dirp )
/**************************************************************************/
{
    DIR_TYPE	    tmp;
    int		    i,h;
    char	    pathname[ _MAX_PATH + 6 ];
    const char *p;
    UINT_WC_TYPE    curr_ch;
    UINT_WC_TYPE    prev_ch;
    int		    flag_opendir = ( dirp == NULL );
    int		    opened;
#ifndef __WATCOM__
    struct _finddata_t ff;
#endif

    /*** Convert a wide char string to a multibyte string ***/
#ifdef __WIDECHAR__
    char	    mbcsName[ MB_CUR_MAX * _MAX_PATH ];

    if( wcstombs( mbcsName, dirname, sizeof( mbcsName ) ) == (size_t)-1 ) {
	return( NULL );
    }
#endif

    tmp.d_attr = _A_SUBDIR;
    opened = 0;
    if( !is_directory( dirname ) ) {
	if( (h = _findfirst(dirname, &ff)) == -1 ) {
	    return( NULL );
	}
	tmp.h = h;	
	tmp.d_attr = ff.attrib;
	strcpy(tmp.d_name, ff.name);
	opened = 1;
    }
    if( tmp.d_attr & _A_SUBDIR ) {
	prev_ch = NULLCHAR;
	p = dirname;
	for( i = 0; i < _MAX_PATH; i++ ) {
	    pathname[i] = *p;
#if defined( __WIDECHAR__ ) || defined( __UNIX__ )
	    curr_ch = *p;
#else
	    curr_ch = _mbsnextc( p );
	    if( curr_ch > 256 ) {
		++i;
		++p;
		pathname[i] = *p;	/* copy second byte */
	    }
#endif
	    if( curr_ch == NULLCHAR ) {
		if( i != 0  &&  prev_ch != '\\' && prev_ch != '/' ) {
		    pathname[i++] = '\\';
		}
		strcpy( &pathname[i], "*.*" );
#ifdef __WIDECHAR__
		if( wcstombs( mbcsName, pathname, sizeof( mbcsName ) ) == (size_t)-1 )
		    return( NULL );
#endif
		if( opened ) {
		    _findclose( h );
		}
		if( (h = _findfirst( pathname, &ff )) ) {
		    return( NULL );
		}		
		tmp.h = h;
		tmp.d_attr = ff.attrib;
		strcpy(tmp.d_name, ff.name);
		opened = 1;
		break;
	    }
	    if( curr_ch == '*' )
		break;
	    if( curr_ch == '?' )
		break;
	    ++p;
	    prev_ch = curr_ch;
	}
    }
    if( flag_opendir ) {
//	 dirp = lib_malloc( sizeof( *dirp ) );
	dirp = malloc( sizeof( *dirp ) );
	if( dirp == NULL ) {
	    if( opened ) {
		_findclose( h );
	    }
//	    __set_errno( ENOMEM );
	    return( NULL );
	}
//	 tmp.d_openpath = __clib_strdup( dirname );
	tmp.d_openpath = malloc(strlen(dirname)+1);
	strcpy(tmp.d_openpath, dirname);
    } else {
	_findclose( h );
	tmp.d_openpath = dirp->d_openpath;
    }
    tmp.d_first = _DIR_ISFIRST;
    memcpy(dirp, &tmp, sizeof(struct dirent));
    return( dirp );
}


_WCRTLINK DIR_TYPE *opendir( const char *dirname )
{
    return _opendir(dirname, SEEK_ATTRIB, NULL);
}


_WCRTLINK DIR_TYPE *readdir( DIR_TYPE *dirp )
{
    struct _finddata_t ff;

    if( dirp == NULL || dirp->d_first >= _DIR_INVALID )
	return( NULL );
    if( dirp->d_first == _DIR_ISFIRST ) {
	dirp->d_first = _DIR_NOTFIRST;
    } else {
	if( _findnext( dirp->h, &ff ) ) {
	    return( NULL );
	}
	dirp->d_attr = ff.attrib;
	strcpy(dirp->d_name, ff.name);
    }
#ifdef __WIDECHAR__
    filenameToWide( dirp );
#endif
    return( dirp );
}


_WCRTLINK int closedir( DIR_TYPE *dirp )
{
    unsigned	rc;

    if( dirp == NULL || dirp->d_first == _DIR_CLOSED ) {
	return 2;//( __set_errno( 2 ) );
    }
    rc =_findclose( dirp->h );
    if( rc ) {
	return( rc );
    }
    dirp->d_first = _DIR_CLOSED;
    if( dirp->d_openpath != NULL )
	free( dirp->d_openpath );
    free( dirp );
    return( 0 );
}


_WCRTLINK void rewinddir( DIR_TYPE *dirp )
{
    if( dirp == NULL || dirp->d_openpath == NULL )
	return;
    if( _opendir( dirp->d_openpath, SEEK_ATTRIB, dirp ) == NULL ) {
	dirp->d_first = _DIR_INVALID;	 /* so reads won't work any more */
    }
}
