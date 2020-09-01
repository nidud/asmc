; EXCEPTIONHANDLER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include signal.inc
include winbase.inc

EH_STACK_INVALID    equ 08h
EH_NONCONTINUABLE   equ 01h
EH_UNWINDING	    equ 02h
EH_EXIT_UNWIND	    equ 04h
EH_NESTED_CALL	    equ 10h

    .data
    pCurrentException PEXCEPTION_POINTERS 0

    .code

    option  win64:0
    option  stackbase:rsp

ExceptionHandler proc ExceptionRecord:PEXCEPTION_RECORD, EstablisherFrame:ptr dword,
    ContextRecord:PCONTEXT, DispatcherContext:LPDWORD

  local CurrentException:EXCEPTION_POINTERS

    mov CurrentException.ExceptionRecord,rcx
    mov CurrentException.ContextRecord,r8
    lea rax,CurrentException
    mov pCurrentException,rax

    mov eax,[rcx].EXCEPTION_RECORD.ExceptionFlags
    .switch
      .case eax & EH_UNWINDING
      .case eax & EH_EXIT_UNWIND
	raise(SIGTERM)
	.endc
      .case eax & EH_STACK_INVALID
      .case eax & EH_NONCONTINUABLE
	raise(SIGSEGV)
	.endc
      .case eax & EH_NESTED_CALL
	exit(1)

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
	    raise(SIGSEGV)
	    .endc

	  .case EXCEPTION_SINGLE_STEP
	  .case EXCEPTION_BREAKPOINT
	    raise(SIGINT)
	    .endc

	  .case EXCEPTION_FLT_DENORMAL_OPERAND
	  .case EXCEPTION_FLT_DIVIDE_BY_ZERO
	  .case EXCEPTION_FLT_INEXACT_RESULT
	  .case EXCEPTION_FLT_INVALID_OPERATION
	  .case EXCEPTION_FLT_OVERFLOW
	  .case EXCEPTION_FLT_STACK_CHECK
	  .case EXCEPTION_FLT_UNDERFLOW
	    raise(SIGFPE)
	    .endc

	  .case EXCEPTION_ILLEGAL_INSTRUCTION
	  .case EXCEPTION_INT_DIVIDE_BY_ZERO
	  .case EXCEPTION_INT_OVERFLOW
	  .case EXCEPTION_PRIV_INSTRUCTION
	    raise(SIGILL)
	    .endc
	.endsw
    .endsw
    mov rax,ExceptionContinueSearch
    ret

ExceptionHandler endp

    END
