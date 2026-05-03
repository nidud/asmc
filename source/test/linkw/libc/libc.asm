
include stdio.inc
include tchar.inc

.code

_tprintf proc format:tstring_t, argptr:vararg

    .new buffing:int_t = _stbuf( stdout )
    .new retval:int_t = _toutput( stdout, format, &argptr )

    _ftbuf( buffing, stdout )
    .return( retval )

_tprintf endp

_tmain proc

    _tprintf( "Static LIBC application\n" )
    .return( 0 )

_tmain endp

    end
