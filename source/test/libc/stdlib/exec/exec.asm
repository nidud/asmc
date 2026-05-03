; EXEC.ASM--
;
; https://learn.microsoft.com/en-us/cpp/c-runtime-library/exec-wexec-functions?view=msvc-170
;
; Illustrates the different versions of exec, including
;
;      _execl      _execle      _execlp      _execlpe
;      _execv      _execve      _execvp      _execvpe
;
; Although CRT_EXEC.C can exec any program, you can verify how
; different versions handle arguments and environment by
; compiling and specifying the sample program CRT_ARGS.C. See
; "_spawn, _wspawn Functions" for examples of the similar spawn
; functions.
;
include stdio.inc
include process.inc
include tchar.inc

.code

_tmain proc argc:int_t, argv:tarray_t

   .if ( argc != 3 )

      _tprintf( "Usage: EXEC <program> <number (1-8)>\n" )
     .return( 0 )
   .endif

    mov rbx,argv
    mov rcx,[rbx+size_t*2]
    mov rbx,[rbx+size_t]

   .new args[4]:tstring_t = {
        rbx,
        "exec??",
        "two",
        NULL
        }
   .new my_env[4]:tstring_t = {
        "THIS=environment will be",
        "PASSED=to new process by",
        "the EXEC=functions",
        NULL
        }

   .switch atoi( rcx )
   .case 1
      _texecl( rbx, rbx, "_execl", "two", NULL )
      .endc
   .case 2
      _texecle( rbx, rbx, "_execle", "two", NULL, &my_env )
      .endc
   .case 3
      _texeclp( rbx, rbx, "_execlp", "two", NULL )
      .endc
   .case 4
      _texeclpe( rbx, rbx, "_execlpe", "two", NULL, &my_env )
      .endc
   .case 5
      _texecv( rbx, &args )
      .endc
   .case 6
      _texecve( rbx, &args, &my_env )
      .endc
   .case 7
      _texecvp( rbx, &args )
      .endc
   .case 8
      _texecvpe( rbx, &args, &my_env )
      .endc
   .endsw

    ; This point is reached only if exec fails.

    _tprintf( "\nProcess was not execed." )
   .return( 0 )

_tmain endp

    end _tstart
