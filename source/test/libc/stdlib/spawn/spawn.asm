; SPAWN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; This program accepts a number in the range
; 1-8 from the command line. Based on the number it receives,
; it executes one of the eight different procedures that
; spawn the process named child. For some of these procedures,
; the CHILD.EXE file must be in the same directory; for
; others, it only has to be in the same path.
;

include stdio.inc
include process.inc
include tchar.inc

.code

_tmain proc argc:int_t, argv:array_t

    .new my_env[7]:string_t = {
        "THIS=environment will be",
        "PASSED=to child.exe by the",
        "_SPAWNLE=and",
        "_SPAWNLPE=and",
        "_SPAWNVE=and",
        "_SPAWNVPE=functions",
        NULL
        }

    .new args[4]:string_t = { ; Set up parameters to be sent:
        "child",
        "spawn??",
        "two",
        NULL
        }

    .if ( argc <= 2 )

        printf( "SYNTAX: SPAWN <1-8> <childprogram>\n" )
        exit( 1 )
    .endif

    mov rcx,argv
    mov rax,[rcx+string_t]
    movzx eax,byte ptr [rax]
    mov rcx,[rcx+string_t*2]

    .switch eax ; Based on first letter of argument

    .case '1'
        _spawnl( _P_WAIT, rcx, rcx, "_spawnl", "two", NULL )
       .endc
    .case '2'
        _spawnle( _P_WAIT, rcx, rcx, "_spawnle", "two", NULL, &my_env )
       .endc
    .case '3'
        _spawnlp( _P_WAIT, rcx, rcx, "_spawnlp", "two", NULL );
       .endc
    .case '4'
        _spawnlpe( _P_WAIT, rcx, rcx, "_spawnlpe", "two", NULL, &my_env )
       .endc
    .case '5'
        _spawnv( _P_OVERLAY, rcx, &args )
       .endc
    .case '6'
        _spawnve( _P_OVERLAY, rcx, &args, &my_env )
       .endc
    .case '7'
        _spawnvp( _P_OVERLAY, rcx, &args )
       .endc
    .case '8'
        _spawnvpe( _P_OVERLAY, rcx, &args, &my_env )
       .endc
    .default
        printf( "SYNTAX: SPAWN <1-8> <childprogram>\n" )
        exit( 1 )
    .endsw
    printf( "from SPAWN!\n" )
   .return( 0 )

_tmain endp

    end _tstart
