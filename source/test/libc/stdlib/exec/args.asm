
include stdio.inc
include tchar.inc

.code

_tmain proc argc:int_t, argv:array_t, envp:array_t

    _tprintf( "\nCommand-line arguments:\n" )
    .for ( ebx = 0 : ebx < argc : ebx++ )

        mov rcx,argv
        _tprintf( "  argv[%d]: %s\n", ebx, [rcx+rbx*array_t] )
    .endf

    _tprintf( "\nEnvironment variables:\n" )
    .for ( argc = 6, rbx = envp : argc && size_t ptr [rbx] != NULL : argc--, rbx += size_t )

        _tprintf( "  %s\n", [rbx] )
    .endf
    .return( 0 )

_tmain endp

    end _tstart

