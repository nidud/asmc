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
* Description:  Driver for DLLs pluggable into the IDE (and wmake).
*
****************************************************************************/


#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "debug.h"
#include "idedll.h"
#include "idedrv.h"
#include "walloca.h"
#include "bool.h"

#define errout stdout

typedef void (*P_FUN)( void );

typedef int (*USER_DLL_FUN)( char const * );
typedef int (*USER_DLL_FUN_ARGV)( int, char ** );

#ifndef CHAIN_CALLBACK

static IDEBool IDECALL stubPrintMsgFn( IDECBHdl hdl, char const *msg )
{
    hdl = hdl;
    msg = msg;
    return( FALSE );
}

#ifndef NDEBUG
static void IDECALL printProgressIndex( IDECBHdl hdl, unsigned index )
{
    hdl = hdl;
}
#else
#define printProgressIndex      NULL
#endif

static IDEBool IDECALL printMessage( IDECBHdl hdl, char const *msg )
{
    hdl = hdl;
    fputs( msg, errout );
    fputc( '\n', errout );
    return( FALSE );
}

static IDEBool IDECALL printWithInfo( IDECBHdl hdl, IDEMsgInfo *inf )
{
    FILE    *fp;
    char    prt_buffer[ 512 ];

    hdl = hdl;
    IdeMsgFormat( hdl
                , inf
                , prt_buffer
                , sizeof( prt_buffer )
                , &printWithInfo );
    switch( inf->severity ) {
    case IDEMSGSEV_BANNER:
    case IDEMSGSEV_DEBUG:
    case IDEMSGSEV_NOTE_MSG:
        fp = stdout;
        break;
    case IDEMSGSEV_WARNING:
    case IDEMSGSEV_ERROR:
    case IDEMSGSEV_NOTE:
    default:
        fp = errout;
    }
    fputs( prt_buffer, fp );
    fputc( '\n', fp );
    fflush( fp );
    return( FALSE );
}

static IDEBool IDECALL printWithCrLf( IDECBHdl hdl, const char *message )
{
    hdl = hdl;
    fputs( message, errout );
    fflush( errout );
    return( FALSE );
}

static IDEBool IDECALL getInfoCB( IDECBHdl hdl, IDEInfoType type,
                                  unsigned long extra, unsigned long lparam )
{
    int retn;

    extra = extra;
    hdl = hdl;
    switch( type ) {
    default:
        retn = TRUE;
        break;
    case IDE_GET_ENV_VAR:
        {
            char const* env_var;
            char const* env_val;
            char const * * p_env_val;
            env_var = (char const*)extra;
            env_val = getenv( env_var );
            p_env_val = (char const * *)lparam;
            *p_env_val = env_val;
            retn = ( env_val == NULL );
        }
        break;
    }
    return( retn );
}


static IDECallBacks callbacks = {     // CALL-BACK STRUCTURE
    // building functions
    NULL,                       // RunBatch
    printMessage,               // PrintMessage
    printWithCrLf,              // PrintWithCRLF
    printWithInfo,              // PrintWithInfo

    // Query functions
    getInfoCB,                  // GetInfo

    stubPrintMsgFn,             // ProgressMessage
    NULL,                       // RunDll
    NULL,                       // RunBatchCWD
    NULL,                       // OpenJavaSource
    NULL,                       // OpenClassFile
    NULL,                       // PackageExists
    NULL,                       // GetSize
    NULL,                       // GetTimeStamp
    NULL,                       // IsReadOnly
    NULL,                       // ReadData
    NULL,                       // Close
    NULL,                       // ReceiveOutput

    printProgressIndex,         // ProgressIndex
};
static IDECallBacks *CBPtr = &callbacks;
#else
static IDECallBacks *CBPtr = NULL;
#endif

static IDEInitInfo info =           // INFORMATION STRUCTURE
{   IDE_CUR_INFO_VER                // - ver
,   0                               // - ignore_env
,   1                               // - cmd_line_has_files
,   0                               // - console_output
,   0                               // - progress messages
,   0                               // - progress index
};

static IDEInitInfo  *InfoPtr = NULL;

#ifdef __OSI__
#define NO_CTRL_HANDLERS
#endif

#ifndef NO_CTRL_HANDLERS
static void StopRunning( void )
{
// Provide static and dynamic linking
    IDEStopRunning();
}
#endif // NO_CTRL_HANDLERS

#ifndef NO_CTRL_HANDLERS
static void intHandler( int sig_num )
{
    sig_num = sig_num;
    StopRunning();
}
#endif // NO_CTRL_HANDLERS

static void initInterrupt( void )
{
#ifndef NO_CTRL_HANDLERS
    signal( SIGINT, intHandler );
#ifndef __UNIX__
    signal( SIGBREAK, intHandler );
#endif // __UNIX__
#endif // NO_CTRL_HANDLERS
}

static void finiInterrupt( void )
{
#ifndef NO_CTRL_HANDLERS
    signal( SIGINT, SIG_DFL );
#ifndef __UNIX__
    signal( SIGBREAK, SIG_DFL );
#endif // __UNIX__
#endif // NO_CTRL_HANDLERS
}

#ifndef NDEBUG
#define _SET_PROGRESS \
    if( getenv( "__idedrv_progress_messages" ) ) { info.progress_messages = 1; } \
    if( getenv( "__idedrv_progress_index" ) ) { info.progress_index = 1; }
#else
#define _SET_PROGRESS
#endif

static int ensureLoaded( IDEDRV *inf, int *p_runcode )
{
    int runcode = 0;
    int retcode = IDEDRV_SUCCESS;

    if( !inf->loaded ) {
        if( NULL == inf->ent_name ) {
            runcode = IDEInitDLL( NULL, CBPtr, &inf->ide_handle );
            if( 0 == runcode ) {
                if( NULL == InfoPtr ) {
                    InfoPtr = &info;
                    info.console_output = isatty( fileno( stdout ) );
                }
                _SET_PROGRESS;
                runcode = IDEPassInitInfo( inf->ide_handle, InfoPtr );
                if( 0 != runcode ) {
                    retcode = IDEDRV_ERR_INFO_EXEC;
                }
            } else {
                retcode = IDEDRV_ERR_INIT_EXEC;
            }
        }
        if( IDEDRV_SUCCESS == retcode ) {
            inf->loaded = TRUE;
        }
    }
    *p_runcode = runcode;
    return( retcode );
}

static int retcodeFromFatal( IDEBool fatal, int runcode, int retcode )
{
    if( fatal ) {
        retcode = IDEDRV_ERR_RUN_FATAL;
    } else if( 0 != runcode ) {
        retcode = IDEDRV_ERR_RUN_EXEC;
    }
    return( retcode );
}

static void initConsole( void )
{
    if( info.console_output ) {
        initInterrupt();
    }
}

static void finiConsole( void )
{
    if( info.console_output ) {
        finiInterrupt();
    }
}

#define stashCodes( _inf, _run, _ret ) \
    (_inf)->dll_status = (_run); (_inf)->drv_status = (_ret);

int IdeDrvExecDLL               // EXECUTE THE DLL ONE TIME (LOAD IF REQ'D)
    ( IDEDRV *inf               // - driver control information
    , char const *cmd_line )    // - command line
// Execute DLL
//
// One mode (with static linkage):
//
//  (1) WATCOM IDE interface is used.
//
{
    int runcode;
    int retcode;

	DEBUG(("idedrv:IdeDrvExecDLL\n"))
    retcode = ensureLoaded( inf, &runcode );
    if( retcode == IDEDRV_SUCCESS ) {
        IDEBool fatal = FALSE;
        initConsole();
        runcode = IDERunYourSelf( inf->ide_handle, cmd_line, &fatal );
        finiConsole();
        retcode = retcodeFromFatal( fatal, runcode, retcode );
    }
    stashCodes( inf, runcode, retcode );
    return( retcode );
}

#ifdef __UNIX__

int IdeDrvExecDLLArgv           // EXECUTE THE DLL ONE TIME (LOAD IF REQ'D)
    ( IDEDRV *inf               // - driver control information
    , int argc                  // - # of arguments
    , char **argv )             // - argument vector
// Execute DLL
//
// One mode (with static linkage):
//
//  (1) WATCOM IDE interface is used.
//
{
    int runcode;
    int retcode;

    retcode = ensureLoaded( inf, &runcode );
    if( retcode == IDEDRV_SUCCESS ) {
        IDEBool fatal = FALSE;
        initConsole();
        runcode = IDERunYourSelfArgv( inf->ide_handle, argc, argv, &fatal );
        finiConsole();
        retcode = retcodeFromFatal( fatal, runcode, retcode );
    }
    stashCodes( inf, runcode, retcode );
    return( retcode );
}

#endif


int IdeDrvUnloadDLL             // UNLOAD THE DLL
    ( IDEDRV *inf )             // - driver control information
// Static Linkage: nothing to unload
{
    if( inf->loaded ) {
        inf->loaded = FALSE;
        IDEFiniDLL( inf->ide_handle );
    }
    return( IDEDRV_SUCCESS );
}


int IdeDrvStopRunning           // SIGNAL A BREAK
    ( IDEDRV *inf )             // - driver control information
// Static Linkage: direct call
{
    if( inf->loaded ) {
        inf->loaded = FALSE;
        IDEStopRunning();
    }
    return( IDEDRV_SUCCESS );
}

#if 0 /* jwlib: needed for IDE version only */
static char const *msgs[] =
{
#define _IDEDRV(e,m) m
__IDEDRV
#undef _IDEDRV
};
#endif

