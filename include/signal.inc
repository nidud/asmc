.pragma list(push, 0)

ifndef __UNIX__
include winnt.inc
endif

ifndef _SIG_ATOMIC_T_DEFINED
define _SIG_ATOMIC_T_DEFINED
sig_atomic_t typedef int_t
endif

define NSIG		23	; maximum signal number + 1

define SIGINT		2	; interrupt
define SIGILL		4	; illegal instruction - invalid function image
define SIGFPE		8	; floating point exception
define SIGSEGV		11	; segment violation
define SIGTERM		15	; Software termination signal from kill
define SIGBREAK		21	; Ctrl-Break sequence
define SIGABRT		22	; abnormal termination triggered by abort call
define SIGABRT_COMPAT	6	; SIGABRT compatible with other platforms, same as SIGABRT

ifndef _M_CEE_PURE		; signal action codes
define SIG_DFL		0	; default signal action
define SIG_IGN		1	; ignore signal
define SIG_GET		2	; return current value
define SIG_SGE		3	; signal gets error
define SIG_ACK		4	; acknowledge
ifdef _CRTBLD			; internal use only! not valid as an argument to signal()
define SIG_DIE		5	; terminate process
endif
; signal error value (returned by signal call on error)
define SIG_ERR		-1	; signal error value
endif

__sigfunc typedef proto __cdecl :int_t
sigfunc_t typedef ptr __sigfunc

; pointer to exception information pointers structure

__pxcptinfoptrs proto

; Function prototypes

ifndef _M_CEE_PURE
signal	proto __cdecl :int_t, :sigfunc_t
endif
raise	proto __cdecl :int_t

; Exception disposition return values.

.enum EXCEPTION_DISPOSITION {
    ExceptionContinueExecution,
    ExceptionContinueSearch,
    ExceptionNestedException,
    ExceptionCollidedUnwind
    }

ifndef __UNIX__
ifndef _MSVCRT
__crtPrintContext   proto __cdecl
__crtGeneralFailure proto __cdecl :int_t
endif
endif

.pragma list(pop)
