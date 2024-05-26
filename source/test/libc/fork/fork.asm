; FORK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include stdlib.inc
include unistd.inc

.code

main proc argc:int_t, argv:array_t

    .new pid:pid_t = fork()

    .if ( pid == 0 )

        ; child process

        puts("Child exiting.")
        exit(EXIT_SUCCESS)

    .elseif ( pid > 0 )

        ; parent process

        printf("Child is PID %d\n", pid)
        puts("Parent exiting.")
        exit(EXIT_SUCCESS)
    .endif

    ; fork failed

    perror("fork")
    exit(EXIT_FAILURE)

main endp

    end
