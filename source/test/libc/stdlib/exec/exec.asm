; exec.asm
; Illustrates the different versions of exec, including
;      _execl          _execle          _execlp          _execlpe
;      _execv          _execve          _execvp          _execvpe
;
; Although CRT_EXEC.C can exec any program, you can verify how
; different versions handle arguments and environment by
; compiling and specifying the sample program CRT_ARGS.C. See
; "_spawn, _wspawn Functions" for examples of the similar spawn
; functions.

include stdio.inc
include conio.inc
include process.inc

.code

main proc ac:int_t, av:array_t

  .new h:int_t

   mov rbx,av
   .if ( ac != 3 )

      printf( "Usage: %s <program> <number (1-8)>\n", [rbx] )
     .return 0
   .endif

   ; Arguments for _execv?

   .new args[4]:string_t = { [rbx+size_t], "exec??", "two", NULL }
   .new my_env[4]:string_t = { "THIS=environment will be", "PASSED=to new process by", "the EXEC=functions",  NULL }

   .switch( atoi( [rbx+size_t*2] ) )
   .case 1
      _execl( [rbx+size_t], [rbx+size_t], "_execl", "two", NULL )
      .endc
   .case 2
      _execle( [rbx+size_t], [rbx+size_t], "_execle", "two", NULL, &my_env )
      .endc
   .case 3
      _execlp( [rbx+size_t], [rbx+size_t], "_execlp", "two", NULL )
      .endc
   .case 4
      _execlpe( [rbx+size_t], [rbx+size_t], "_execlpe", "two", NULL, &my_env )
      .endc
   .case 5
      _execv( [rbx+size_t], &args )
      .endc
   .case 6
      _execve( [rbx+size_t], &args, &my_env )
      .endc
   .case 7
      _execvp( [rbx+size_t], &args )
      .endc
   .case 8
      _execvpe( [rbx+size_t], &args, &my_env )
      .endc
   .default
      .endc
   .endsw

   ; This point is reached only if exec fails.

   printf( "\nProcess was not execed." )
   exit( 0 )
   ret

main endp

    end
