include signal.inc

    .code

main proc

    lea rbx,__crtGeneralFailure

    signal(SIGINT,   rbx) ; interrupt
    signal(SIGILL,   rbx) ; illegal instruction - invalid function image
    signal(SIGFPE,   rbx) ; floating point exception
    signal(SIGSEGV,  rbx) ; segment violation
    signal(SIGTERM,  rbx) ; Software termination signal from kill
    signal(SIGABRT,  rbx) ; abnormal termination triggered by abort call

    mov ebx,-1
    mov rcx,-1
    mov edx,2
    xor rax,rax
    mov [rax],al
    ret

main endp

    end
