
include io.inc
include fcntl.inc
include stdio.inc
include tchar.inc

    .code

_tmain proc

   .new fd:int_t = _topen(__FILE__, O_RDONLY)

    _tprintf( "isatty(1): %d\n", _isatty(1))
    _tprintf( "handle: %d\n", fd )
    .if ( fd > 0 )
        _tprintf( "isatty(fd): %d\n", _isatty(fd))
        _tprintf( "close(fd): %d\n", _close(fd))
    .else
        _tperror("open(\"isatty.asm\", O_RDONLY)")
    .endif
    .return(0)

_tmain endp

    end _tstart
