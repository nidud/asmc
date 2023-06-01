
include io.inc
include fcntl.inc
include stdio.inc

    .code

main proc

   .new fd:int_t = _open(__FILE__, O_RDONLY)

    printf( "isatty(1): %d\n", _isatty(1))
    printf( "handle: %d\n", fd )
    .if ( fd > 0 )
        printf( "isatty(fd): %d\n", _isatty(fd))
        printf( "close(fd): %d\n", _close(fd))
    .else
        perror("open(\"isatty.asm\", O_RDONLY)")
    .endif
    .return(0)

main endp

    end
