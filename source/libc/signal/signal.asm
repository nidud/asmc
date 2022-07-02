; SIGNAL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include signal.inc
include winbase.inc

define EH_NONCONTINUABLE    0x01
define EH_UNWINDING         0x02
define EH_EXIT_UNWIND       0x04
define EH_STACK_INVALID     0x08
define EH_NESTED_CALL       0x10

    .data
     __crtCurrentException PEXCEPTION_POINTERS 0
     __crtExceptionReg PEXCEPTION_REGISTRATION 0
     sig_table sigfunc_t NSIG dup(0)

    .code

__pxcptinfoptrs proc

    .return( __crtCurrentException )

__pxcptinfoptrs endp


raise proc index:int_t

  local sigp:sigfunc_t

ifndef _WIN64
    mov ecx,index
endif
    lea rax,sig_table
    mov rax,[rax+rcx*size_t]
    .if rax
        mov sigp,rax
        sigp( ecx )
    .endif
    ret

raise endp


signal proc uses rbx index:int_t, func:sigfunc_t

ifndef _WIN64
    mov ecx,index
    mov edx,func
endif
    lea rbx,sig_table
    mov rax,[rbx+rcx*size_t]
    mov [rbx+rcx*size_t],rdx
    ret

signal endp


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
    mov eax,[rcx].EXCEPTION_RECORD.ExceptionFlags

    .switch
    .case ( eax & ( EH_UNWINDING or EH_EXIT_UNWIND ) )
        raise( SIGTERM )
       .endc
    .case ( eax & ( EH_STACK_INVALID or EH_NONCONTINUABLE ) )
        raise( SIGSEGV )
       .endc
    .case ( eax & EH_NESTED_CALL )
        exit( 1 )
    .default
        mov eax,[rcx].EXCEPTION_RECORD.ExceptionCode
        .switch eax
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
    .return( ExceptionContinueSearch )

__crtExceptionHandler endp


Install proc private
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
Install endp


Remove proc private
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
Remove endp

.pragma init( Install,  1 )
.pragma exit( Remove, 200 )

    end
