include signal.inc

    .code

main proc

    lea r10,__crtGeneralFailure

    signal(SIGINT,   r10) ; interrupt
    signal(SIGILL,   r10) ; illegal instruction - invalid function image
    signal(SIGFPE,   r10) ; floating point exception
    signal(SIGSEGV,  r10) ; segment violation
    signal(SIGTERM,  r10) ; Software termination signal from kill
    signal(SIGABRT,  r10) ; abnormal termination triggered by abort call

    mov ebx,-1
    mov rcx,-1
    mov edx,2
    xor rax,rax
    mov [rax],al
    ret

main endp

    end
