; _PIPE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include stdlib.inc
include stddef.inc
include fcntl.inc
include io.inc
include process.inc
include tchar.inc

.data

handles label int_t
handle0 int_t 0
handle1 int_t 0
pid int_t 0

.code

create_pipe proc

    .ifd ( _pipe( &handles, 2048, _O_BINARY ) == -1 )
        perror( "create_pipe" )
        exit( EXIT_FAILURE )
    .endif
    ret

create_pipe endp


create_child proc name:string_t

   .new buff[10]:char_t

    _itoa( handle0, &buff, 10 )
    mov pid,_spawnl( P_NOWAIT, name, "_pipe", &buff, NULL )
    _close( handle0 )
    .if ( pid == -1 )
        perror( "create_child" )
        _close( handle1 )
        exit( EXIT_FAILURE )
    .endif
    ret

create_child endp


fill_pipe proc

    .new i:int_t
    .new rc:int_t

    .for ( i = 1 : i <= 10 : i++ )
        printf( "Child, what is 5 times %d\n", i )
        mov rc,_write( handle1, &i, sizeof( int_t ) )
        .if ( rc < sizeof( int_t ) )
            perror( "fill_pipe" )
            _close( handle1 )
            exit( EXIT_FAILURE )
        .endif
    .endf
    ; indicate that we are done
    mov i,-1
    _write( handle1, &i, sizeof( int_t ) )
    _close( handle1 )
    ret

fill_pipe endp


empty_pipe proc in_pipe:int_t

    .new i:int_t
    .new amt:int_t

    .for ( :: )
        mov amt,_read( in_pipe, &i, sizeof( int_t ) )
        .if ( amt != sizeof( int_t ) || i == -1 )
            .break
        .endif
        imul ecx,i,5
        printf( "Parent, 5 times %d is %d\n", i, ecx )
    .endf
    .if ( amt == -1 )

        perror( "empty_pipe" )
        exit( EXIT_FAILURE )
    .endif
    _close( in_pipe )
    ret

empty_pipe endp


_tmain proc argc:int_t, argv:array_t

    .if ( argc <= 1 )

        ; we are the spawning process

        create_pipe()
        mov rcx,argv
        create_child( [rcx] )
        fill_pipe()
    .else

        ; we are the spawned process

        mov rcx,argv
        empty_pipe( atoi( [rcx+size_t] ) )
    .endif
    exit( EXIT_SUCCESS )

_tmain endp

    end _tstart
