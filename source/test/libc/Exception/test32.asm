include stdio.inc
include stdlib.inc
include signal.inc

    .code

GeneralFailure proc signo:int_t

    mov eax,signo
    .if eax != SIGTERM
        mov eax,pCurrentException
        PrintContext(
            [eax].EXCEPTION_POINTERS.ContextRecord,
            [eax].EXCEPTION_POINTERS.ExceptionRecord )
    .endif
    exit( 1 )
    ret

GeneralFailure endp

main proc

    lea ebx,GeneralFailure

    signal( SIGINT,   ebx ) ; interrupt
    signal( SIGILL,   ebx ) ; illegal instruction - invalid function image
    signal( SIGFPE,   ebx ) ; floating point exception
    signal( SIGSEGV,  ebx ) ; segment violation
    signal( SIGTERM,  ebx ) ; Software termination signal from kill
    signal( SIGABRT,  ebx ) ; abnormal termination triggered by abort call

    mov ecx,1
    mov edx,2
    xor eax,eax
    mov [eax],eax
    ret

main endp

    END
