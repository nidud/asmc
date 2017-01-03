/****************************************************************************
*
*                            Open Watcom Project
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
* Description:  Macros for converting segment and offset data 
*               into linear address and subtracting and comparing
*
****************************************************************************/


extern segment Find16MSeg( segment );

#define SUB_ADDR( l, r ) ((((long)(l).seg-(long)(r).seg) << FmtData.SegShift) + ((l).off-(r).off))

#define SUB_16M_ADDR( l, r ) (((long)Find16MSeg((l).seg)-(long)Find16MSeg((r).seg))*16+((l).off-(r).off))

#define LESS_THAN_ADDR( l, r ) ((long)SUB_ADDR( l, r ) < 0L)

#define MK_REAL_ADDR( seg, off )  ( ((unsigned long)(seg) << FmtData.SegShift) + (off) )
