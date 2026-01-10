; _FULLPATH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include stdlib.inc
include tchar.inc

.code

_tmain proc argc:int_t, argv:array_t

    .new buffer[_MAX_PATH]:char_t
    .if ( argc != 2 )

        _tprintf("READLINK <path>\n")
        .return(0)
    .endif
    mov rcx,argv
ifdef __UNIX__
    .if ( realpath([rcx+size_t], &buffer) == NULL )
else
    .if ( _fullpath(&buffer, [rcx+size_t], _MAX_PATH) == NULL )
endif
        _tperror("_fullpath")
    .else
        _tprintf("_fullpath(): %s\n", &buffer)
    .endif
    .return( 0 )

_tmain endp

    end _tstart
