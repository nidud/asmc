.pragma list(push, 0)
ifndef __SIGNAL_INC
define __SIGNAL_INC

ifdef __UNIX__
include sys/types.inc
else
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

ifdef __UNIX__

.pragma pack(push, size_t)

define _NSIG		65
define _NSIG_WORDS	((_NSIG - 1) / 2)

ifndef ____sigset_t_defined
define ____sigset_t_defined
sigset_t		struct ; 128
sig			dd _NSIG_WORDS dup(?)
sigset_t		ends
endif
sighandler_t		typedef sigfunc_t

define SIG_BLOCK	0
define SIG_UNBLOCK	1
define SIG_SETMASK	2

define SA_NOCLDSTOP	0x00000001
define SA_NOCLDWAIT	0x00000002
define SA_SIGINFO	0x00000004
define SA_RESTORER	0x04000000
define SA_ONSTACK	0x08000000
define SA_RESTART	0x10000000
define SA_INTERRUPT	0x20000000
define SA_NODEFER	0x40000000
define SA_RESETHAND	0x80000000

define SA_NOMASK	SA_NODEFER
define SA_ONESHOT	SA_RESETHAND

ifndef ____sigval_t_defined
define ____sigval_t_defined
sigval			union
sival_int		int_t ?
sival_ptr		ptr_t ?
sigval			ends
sigval_t		typedef sigval
endif

ifndef __siginfo_t_defined
define __siginfo_t_defined
siginfo_t		struct
si_signo		int_t ?
si_errno		int_t ?
si_code			int_t ?
si_pid			pid_t ?
si_uid			uid_t ?
si_addr			ptr_t ?
si_status		int_t ?
si_band			long_t ?
si_value		sigval <>
siginfo_t		ends
endif

sigaction_t		struct ; 152
union
 sa_handler		sighandler_t ?
 sa_sigaction		proc :int_t, :ptr siginfo_t, :ptr
ends
sa_flags		int_t ?
sa_restorer		proc
sa_mask			sigset_t <>
sigaction_t		ends

ifdef _AMD64_

define __ARCH_HAS_SA_RESTORER
define _COMPAT_NSIG	(_NSIG - 1)
define _COMPAT_NSIG_BPW 32
define _COMPAT_NSIG_WORDS (_COMPAT_NSIG / _COMPAT_NSIG_BPW)

compat_uptr_t		typedef ptr
compat_ulong_t		typedef qword
compat_uint_t		typedef dword
compat_sigset_word	typedef dword

compat_sigset_t		struct
sig			compat_sigset_word _COMPAT_NSIG_WORDS dup(?)
compat_sigset_t		ends

compat_sigaction	struct
ifndef __ARCH_HAS_IRIX_SIGACTION
sa_handler		compat_uptr_t ?
sa_flags		compat_ulong_t ?
else
sa_flags		compat_uint_t ?
sa_handler		compat_uptr_t ?
endif
ifdef __ARCH_HAS_SA_RESTORER
sa_restorer		compat_uptr_t ?
endif
sa_mask			compat_sigset_t <>
compat_sigaction	ends

sys_rt_sigaction proto syscall :int_t, :ptr compat_sigaction, :ptr compat_sigaction {
    mov eax,13
    mov r10,compat_sigset_t
    syscall
    }
endif
sigaction proto __cdecl :int_t, :ptr sigaction_t, :ptr sigaction_t

.pragma pack(pop)

endif ; __UNIX__

ifndef _MSVCRT
__crtPrintContext   proto __cdecl
__crtGeneralFailure proto __cdecl :int_t
endif

endif
.pragma list(pop)

