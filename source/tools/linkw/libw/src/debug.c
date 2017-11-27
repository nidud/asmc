/****************************************************************************
*
* Description:  Debug display support for wlib - Public Domain
*
****************************************************************************/


#include <signal.h>
#include <setjmp.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>

#ifdef __DEBUG__

#include <stdio.h>

//---------------------------------------------------------------

int Debug = 1;

void _Debug( const char *format, ... )
/****************************************/
{
    va_list args;

    if( Debug ) {
        va_start( args, format );
        vprintf( format, args );
        va_end( args );
        fflush( stdout );
    }
}
#endif
