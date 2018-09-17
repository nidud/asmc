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
* Description:	Open Watcom banner strings and version defines.
*
****************************************************************************/


//#include "bancfg.h"

//#define DOBANSTR( p )	  #p
//#define BANSTR( p )	  DOBANSTR( p )

//#ifndef _BETASTR_
//#define _BETASTR_ "beta"
//#endif

//#ifdef _BETAVER
//#define _BETA_		  _BETASTR_ BANSTR( _BETAVER )	_BANEXTRA
//#else
//#define _BETA_		  _BANEXTRA
//#endif

#define CURR_YEAR	"2017"

#define banner1p1(p)  p
#define banner1p2(v)  "Version " v
#define banner1(p,v) banner1p1(p) " " banner1p2(v)
//#define banner1w(p,v) "Open Watcom " banner1p1(p) " " banner1p2(v)

#define banner2p1(year) "Portions Copyright (c) " year "-2002 Sybase, Inc. All Rights Reserved"
//#define banner2p2() "All rights reserved"
//#define banner2(year) banner2p1(year) ". " banner2p2() "."
#define banner2p2() ""
#define banner2(year) banner2p1(year) "."

#define banner2a() "Portions Copyright (c) 1984-2002 Sybase, Inc. All Rights Reserved."

#define banner3	      "Source code is available under the Sybase Open Watcom Public License."
//#define banner3a	"See http://www.openwatcom.org/ for details."
#define banner3a

/* Used by setupgui/c/guiinit.c */
//#define banner4gui()	  "Copyright © 2002-%s Open Watcom Contributors. All Rights Reserved."
//#define banner2agui() "Portions Copyright © 1984-2002 Sybase, Inc. All Rights Reserved."

// the following macros define the delimiters used by the resource
// compiler when concatenating strings
#define _RC_DELIM_LEFT_		[
#define _RC_DELIM_RIGHT_	]

#define BAN_VER_STR "2.01"
#define _WLINK_VERSION_		BAN_VER_STR


/*
 * Versions of Microsoft tools with OW clones are compatible
 */
#define _MS_CL_VERSION_		"13.0.0"
#define _MS_LINK_VERSION_	"7.0.0"
