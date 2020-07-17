.pragma list(push, 0)

include winnt.inc

ifndef _SIG_ATOMIC_T_DEFINED
_SIG_ATOMIC_T_DEFINED equ <>
sig_atomic_t typedef int_t
endif

NSIG		equ 23	; maximum signal number + 1

SIGINT		equ 2	; interrupt
SIGILL		equ 4	; illegal instruction - invalid function image
SIGFPE		equ 8	; floating point exception
SIGSEGV		equ 11	; segment violation
SIGTERM		equ 15	; Software termination signal from kill
SIGBREAK	equ 21	; Ctrl-Break sequence
SIGABRT		equ 22	; abnormal termination triggered by abort call

SIGABRT_COMPAT	equ 6	; SIGABRT compatible with other platforms, same as SIGABRT

ifndef _M_CEE_PURE
;; signal action codes

SIG_DFL		equ 0 ;; default signal action
SIG_IGN		equ 1 ;; ignore signal
SIG_GET		equ 2 ;; return current value
SIG_SGE		equ 3 ;; signal gets error
SIG_ACK		equ 4 ;; acknowledge

ifdef _CRTBLD
;; internal use only! not valid as an argument to signal()

SIG_DIE		equ 5 ;; terminate process
endif
;; signal error value (returned by signal call on error)

SIG_ERR		equ -1 ;; signal error value
endif

;; pointer to exception information pointers structure

__pxcptinfoptrs proto
 _pxcptinfoptrs macro
	exitm<[__pxcptinfoptrs()]>
	endm

;; Function prototypes

ifndef _M_CEE_PURE
signal	proto __cdecl :int_t, :ptr_t
endif
raise	proto __cdecl :int_t

;; Exception disposition return values.

.enum EXCEPTION_DISPOSITION {
    ExceptionContinueExecution,
    ExceptionContinueSearch,
    ExceptionNestedException,
    ExceptionCollidedUnwind
    }

ifndef _MSVCRT

 externdef pCurrentException:PEXCEPTION_POINTERS
 externdef pExceptionReg:PEXCEPTION_REGISTRATION

 PrintContext proto __cdecl :PCONTEXT, :PEXCEPTION_RECORD
 ifdef _WIN64
  ExceptionHandler proto __cdecl :PEXCEPTION_RECORD, :LPDWORD, :PCONTEXT, :LPDWORD
 endif
endif

.pragma list(pop)
