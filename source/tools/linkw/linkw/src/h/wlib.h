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
* Description:  Master include for librarian.
*
****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <limits.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#ifdef __WATCOMC__
#include <process.h>
#include <conio.h>
#else
#define S_IRWXU 0000700
#define S_IRUSR 0000400
#define S_IWUSR 0000200
#define S_IXUSR 0000100
#define S_IRWXG 0000070
#define S_IRGRP 0000040
#define S_IWGRP 0000020
#define S_IXGRP 0000010
#define S_IRWXO 0000007
#define S_IROTH 0000004
#define S_IWOTH 0000002
#define S_IXOTH 0000001
#define S_ISUID 0004000
#define S_ISGID 0002000
#define S_ISVTX 0001000
#define F_OK	0	/*  Test for existence of file  */
#endif

#include "watcom.h"
#include "debug.h"
#include "orl.h"
#include "ar.h"
#include "lib.h"
#include "watcom.h"
#include "bool.h"
#include "wressetr.h"
#include "wreslang.h"
#include "demangle.h"

#include "wlibio.h"
#include "types.h"
#include "optdef.h"
#include "ops.h"
#include "memfuncs.h"
#include "objfile.h"
#include "inlib.h"

#include "exeelf.h"
#include "convert.h"
#include "wlibutil.h"
#include "libwalk.h"
#include "liblist.h"
#include "cmdline.h"
#include "orlrtns.h"
#include "error.h"
#include "errnum.h"
#include "ext.h"
#include "proclib.h"
#include "filetab.h"
#include "implib.h"
#include "symlist.h"
#include "writelib.h"
#include "coff.h"
#include "coffwrt.h"
#include "pcobj.h"
#include "omfutil.h"
#include "omfproc.h"
#include "exedos.h"
#include "exeos2.h"
#include "exeflat.h"
#include "exepe.h"
#include "exenov.h"
#include "main.h"
#include "wresset2.h"
