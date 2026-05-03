include signal.inc

    .code

main proc

    lea ebx,__crtGeneralFailure

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
