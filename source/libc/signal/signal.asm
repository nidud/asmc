; SIGNAL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include errno.inc
include stdlib.inc
include signal.inc
ifdef __UNIX__
define __USE_GNU
include ucontext.inc
include sys/syscall.inc
else
include winbase.inc
endif

define MAXSIG   7

define EH_NONCONTINUABLE    0x01
define EH_UNWINDING         0x02
define EH_EXIT_UNWIND       0x04
define EH_STACK_INVALID     0x08
define EH_NESTED_CALL       0x10

    .data

     __crtCurrentException PVOID 0
ifndef __UNIX__
     __crtExceptionReg PEXCEPTION_REGISTRATION 0
endif
     sig_table sigfunc_t MAXSIG dup(0)

    .code

__pxcptinfoptrs proc

    .return( __crtCurrentException )

__pxcptinfoptrs endp


raise proc index:int_t

  local sigp:sigfunc_t

    ldr ecx,index
    mov rax,-1
    .switch ecx
    .case SIGABRT   : inc eax
    .case SIGBREAK  : inc eax
    .case SIGTERM   : inc eax
    .case SIGSEGV   : inc eax
    .case SIGFPE    : inc eax
    .case SIGILL    : inc eax
    .case SIGINT    : inc eax
    .endsw
    .if ( eax == -1 )

        _set_errno(EINVAL)
        .return(SIG_ERR)
    .endif
    lea rdx,sig_table
    mov rdx,[rdx+rax*size_t]
    mov eax,ExceptionContinueSearch
    .if rdx
        mov sigp,rdx
        sigp( ecx )
    .endif
    ret

raise endp

if defined(__UNIX__) and defined(_AMD64_)

sig_restore::
    assume rbx:ptr mcontext_t
    lea rbx,[rdx+ucontext_t.uc_mcontext]
    mov rax,[rbx].gregs[REG_RAX*8]
    mov rcx,[rbx].gregs[REG_RCX*8]
    mov rdx,[rbx].gregs[REG_RDX*8]
    mov rsi,[rbx].gregs[REG_RSI*8]
    mov rdi,[rbx].gregs[REG_RDI*8]
    mov rbp,[rbx].gregs[REG_RBP*8]
    mov r8, [rbx].gregs[REG_R8*8]
    mov r9, [rbx].gregs[REG_R9*8]
    mov r10,[rbx].gregs[REG_R10*8]
    mov r11,[rbx].gregs[REG_R11*8]
    mov r12,[rbx].gregs[REG_R12*8]
    mov r13,[rbx].gregs[REG_R13*8]
    mov r14,[rbx].gregs[REG_R14*8]
    mov r15,[rbx].gregs[REG_R15*8]
    mov rsp,[rbx].gregs[REG_RSP*8]
    push [rbx].gregs[REG_RIP*8]
    mov rbx,[rbx].gregs[REG_RBX*8]
    assume rbx:nothing
    ret

sig_handler proc sig:int_t, siginfo:ptr siginfo_t, context:ptr ucontext_t

    mov __crtCurrentException,rdx
    raise(edi)
    mov rdx,__crtCurrentException
    ret

sig_handler endp

endif

signal proc uses rbx sig:int_t, func:sigfunc_t

if defined(__UNIX__) and defined(_AMD64_)
   .new ac:compat_sigaction = {0}
endif

    ldr ecx,sig
    ldr rdx,func

    mov eax,-1
    .switch ecx
    .case SIGABRT   : inc eax   ; abnormal termination triggered by abort call
    .case SIGBREAK  : inc eax   ; Ctrl-Break sequence
    .case SIGTERM   : inc eax   ; Software termination signal from kill
    .case SIGSEGV   : inc eax   ; segment violation
    .case SIGFPE    : inc eax   ; floating point exception
    .case SIGILL    : inc eax   ; illegal instruction - invalid function image
    .case SIGINT    : inc eax   ; interrupt
    .endsw

    .if ( eax == -1 )

        _set_errno(EINVAL)
        .return(SIG_ERR)
    .endif

    mov ecx,eax
    lea rbx,sig_table
    mov rax,[rbx+rcx*size_t]
    mov [rbx+rcx*size_t],rdx

if defined(__UNIX__) and defined(_AMD64_)

    mov rbx,rax
    mov ac.sa_handler,&sig_handler
    mov ac.sa_restorer,&sig_restore
    mov ac.sa_flags,SA_SIGINFO or SA_RESTORER

    .ifsd ( sys_rt_sigaction(sig, &ac, 0, compat_sigset_t) < 0 )

        neg eax
        _set_errno(eax)

        lea rcx,sig_table
        mov edx,sig
        mov [rcx+rdx*size_t],rbx
        mov rbx,rax
    .endif
    mov rax,rbx
endif
    ret

signal endp

ifndef __UNIX__

__crtExceptionHandler proc \
    ExceptionRecord   : PEXCEPTION_RECORD,
    EstablisherFrame  : PEXCEPTION_REGISTRATION_RECORD,
    ContextRecord     : PCONTEXT,
    DispatcherContext : LPDWORD

ifndef _WIN64
   .new CurrentException:EXCEPTION_POINTERS
    mov CurrentException.ExceptionRecord,ExceptionRecord
    mov CurrentException.ContextRecord,ContextRecord
    lea ecx,CurrentException
endif
    mov __crtCurrentException,rcx
    mov rcx,[rcx].EXCEPTION_POINTERS.ExceptionRecord
    mov edx,[rcx].EXCEPTION_RECORD.ExceptionFlags
    mov eax,ExceptionContinueSearch

    .switch
    .case ( edx & ( EH_UNWINDING or EH_EXIT_UNWIND ) )
        raise( SIGTERM )
       .endc
    .case ( edx & ( EH_STACK_INVALID or EH_NONCONTINUABLE ) )
        raise( SIGSEGV )
       .endc
    .case ( edx & EH_NESTED_CALL )
        exit( 1 )
    .default
        mov edx,[rcx].EXCEPTION_RECORD.ExceptionCode
        .switch edx
        .case EXCEPTION_ACCESS_VIOLATION
        .case EXCEPTION_ARRAY_BOUNDS_EXCEEDED
        .case EXCEPTION_DATATYPE_MISALIGNMENT
        .case EXCEPTION_STACK_OVERFLOW
        .case EXCEPTION_IN_PAGE_ERROR
        .case EXCEPTION_INVALID_DISPOSITION
        .case EXCEPTION_NONCONTINUABLE_EXCEPTION
            raise( SIGSEGV )
           .endc
        .case EXCEPTION_SINGLE_STEP
        .case EXCEPTION_BREAKPOINT
            raise( SIGINT )
           .endc
        .case EXCEPTION_FLT_DENORMAL_OPERAND
        .case EXCEPTION_FLT_DIVIDE_BY_ZERO
        .case EXCEPTION_FLT_INEXACT_RESULT
        .case EXCEPTION_FLT_INVALID_OPERATION
        .case EXCEPTION_FLT_OVERFLOW
        .case EXCEPTION_FLT_STACK_CHECK
        .case EXCEPTION_FLT_UNDERFLOW
            raise( SIGFPE )
           .endc
        .case EXCEPTION_ILLEGAL_INSTRUCTION
        .case EXCEPTION_INT_DIVIDE_BY_ZERO
        .case EXCEPTION_INT_OVERFLOW
        .case EXCEPTION_PRIV_INSTRUCTION
            raise( SIGILL )
           .endc
        .endsw
    .endsw
    .if ( eax == ExceptionContinueExecution )

        mov rcx,__crtCurrentException
        mov rbx,[rcx].EXCEPTION_POINTERS.ContextRecord
ifdef _WIN64
        mov rax,[rbx].CONTEXT._Rax
        mov rcx,[rbx].CONTEXT._Rcx
        mov rdx,[rbx].CONTEXT._Rdx
        mov rsi,[rbx].CONTEXT._Rsi
        mov rdi,[rbx].CONTEXT._Rdi
        mov rbp,[rbx].CONTEXT._Rbp
        mov r8, [rbx].CONTEXT._R8
        mov r9, [rbx].CONTEXT._R9
        mov r10,[rbx].CONTEXT._R10
        mov r11,[rbx].CONTEXT._R11
        mov r12,[rbx].CONTEXT._R12
        mov r13,[rbx].CONTEXT._R13
        mov r14,[rbx].CONTEXT._R14
        mov r15,[rbx].CONTEXT._R15
        mov rsp,[rbx].CONTEXT._Rsp
        push [rbx].CONTEXT._Rip
        mov rbx,[rbx].CONTEXT._Rbx
else
        mov eax,[ebx].CONTEXT._Eax
        mov ecx,[ebx].CONTEXT._Ecx
        mov edx,[ebx].CONTEXT._Edx
        mov esi,[ebx].CONTEXT._Esi
        mov edi,[ebx].CONTEXT._Edi
        mov ebp,[ebx].CONTEXT._Ebp
        mov esp,[ebx].CONTEXT._Esp
        push [ebx].CONTEXT._Eip
        mov ebx,[ebx].CONTEXT._Ebx
endif
        retn
    .endif
    ret

__crtExceptionHandler endp


__initsignal proc private

ifdef _WIN64

    AddVectoredExceptionHandler( 1, &__crtExceptionHandler )
    mov __crtExceptionReg,rax

else

    ; 8 bytes on the stack for EXCEPTION_REGISTRATION
    ; is allocate in mainCRTStartup

    lea     eax,[ebp+7*4]
    mov     __crtExceptionReg,eax
    assume  fs:nothing
    mov     ecx,fs:[0]
    mov     [eax].EXCEPTION_REGISTRATION.prev,ecx
    mov     [eax].EXCEPTION_REGISTRATION.handler,__crtExceptionHandler
    mov     fs:[0],eax
    assume  fs:ERROR
endif
    ret

__initsignal endp


__exitsignal proc private
ifdef _WIN64
    RemoveVectoredContinueHandler( __crtExceptionReg )
else
    mov     eax,__crtExceptionReg
    mov     eax,[eax].EXCEPTION_REGISTRATION.prev
    assume  fs:nothing
    mov     fs:[0],eax
    assume  fs:ERROR
endif
    ret
__exitsignal endp

.pragma init(__initsignal,  1 )
.pragma exit(__exitsignal, 200 )

endif
    end
