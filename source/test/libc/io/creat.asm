include io.inc
include stdio.inc
include fcntl.inc
include sys/stat.inc
include tchar.inc

.code
_tmain proc
   .new fd:int_t = _creat("test.fil",_S_IREAD or _S_IWRITE)
    _tprintf("_creat(): %d\n", fd)
    _tprintf("_close(): %d\n", _close(fd))
    .return( 0 )
    endp
    end _tstart
