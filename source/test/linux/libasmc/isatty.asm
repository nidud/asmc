; ISATTY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include fcntl.inc
include stdio.inc

    .code

main proc

    printf( "isatty(1): %d\n", isatty(1))
   .new fd:int_t = open("isatty.asm", O_RDONLY)
    printf( "handle: %d\n", fd )
    .if ( fd > 0 )
        printf( "isatty(fd): %d\n", isatty(fd))
        printf( "close(fd): %d\n", close(fd))
    .else
        perror("open(\"isatty.asm\", O_RDONLY)")
    .endif
    ret

main endp

    end
