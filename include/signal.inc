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

ifdef __UNIX__
define NSIG		65	; maximum signal number + 1
else
define NSIG		23
endif

define SIGHUP		1	; Hangup
define SIGINT		2	; interrupt
define SIGQUIT		3	; Quit
define SIGILL		4	; illegal instruction
define SIGTRAP		5	; Trace/breakpoint trap
ifdef __UNIX__
define SIGABRT		6	; Abnormal termination
define SIGBUS		7	; Bus error
else
define SIGABRT		22
endif
define SIGABRT_COMPAT	6

define SIGFPE		8	; floating point exception
define SIGKILL		9	; Killed
define SIGUSR1		10	; User-defined signal 1
define SIGSEGV		11	; segment violation
define SIGUSR2		12	; User-defined signal 2
define SIGPIPE		13	; Broken pipe
define SIGALRM		14	; Alarm clock
define SIGTERM		15	; Software termination signal from kill
define SIGSTKFLT	16	; Stack fault (obsolete)
define SIGCHLD		17	; Child terminated or stopped
define SIGCONT		18	; Continue
define SIGSTOP		19	; Stop, unblockable
define SIGTSTP		20	; Keyboard stop
define SIGBREAK		21	; Ctrl-Break sequence
define SIGTTIN		21	; Background read from control terminal
define SIGTTOU		22	; Background write to control terminal
define SIGURG		23	; Urgent data is available at a socket
define SIGXCPU		24	; CPU time limit exceeded
define SIGXFSZ		25	; File size limit exceeded
define SIGVTALRM	26	; Virtual timer expired
define SIGPROF		27	; Profiling timer expired
define SIGWINCH		28	; Window size change (4.3 BSD, Sun)
define SIGPOLL		29	; Pollable event occurred (System V)
define SIGPWR		30	; Power failure imminent
define SIGSYS		31	; Bad system call

define SIGCLD		SIGCHLD ; Old System V name
define SIGIO		SIGPOLL ; I/O now possible (4.2 BSD).
define SIGIOT		SIGABRT ; IOT instruction, abort() on a PDP-11.

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
define SIG_ERR		(-1)	; signal error value
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

