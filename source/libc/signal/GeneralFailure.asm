include stdio.inc
include stdlib.inc
include signal.inc

    .code

__crtGeneralFailure proc signo:int_t

    .if ( signo != SIGTERM )

        printf("EXCEPTION: ")

        mov eax,signo
        .switch pascal eax
          .case SIGINT:  printf("Interrupt\n")
          .case SIGILL:  printf("Illegal instruction - invalid function ime\n")
          .case SIGFPE:  printf("Floating point exception\n")
          .case SIGSEGV: printf("Segment violation\n")
          .case SIGABRT: printf("Abnormal termination triggered by abort call\n")
        .endsw
        __crtPrintContext()
    .endif
    exit(1)
    ret

__crtGeneralFailure endp

    end
