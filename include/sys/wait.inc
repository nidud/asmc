; WAIT.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __WAIT_INC
define __WAIT_INC

include time.inc

ifdef __UNIX__
rusage      struct
ru_utime    timeval <>
ru_stime    timeval <>
ru_maxrss   size_t ?
ru_ixrss    size_t ?
ru_idrss    size_t ?
ru_isrss    size_t ?
ru_minflt   size_t ?
ru_majflt   size_t ?
ru_nswap    size_t ?
ru_inblock  size_t ?
ru_oublock  size_t ?
ru_msgsnd   size_t ?
ru_msgrcv   size_t ?
ru_nsignals size_t ?
ru_nvcsw    size_t ?
ru_nivcsw   size_t ?
rusage      ends
endif

ifndef _ID_T_DEFINED
define _ID_T_DEFINED
id_t typedef dword
endif
ifndef _PID_T_DEFINED
define _PID_T_DEFINED
pid_t typedef sdword
endif

define WAIT_ANY         (-1)    ; Any process
define WAIT_MYPGRP      0       ; Any process in my process group

define WNOHANG          1       ; Don't block waiting
define WUNTRACED        2       ; Report status of stopped children

; Bits in the fourth argument to waitid

define WSTOPPED         2       ; Report stopped child
define WCONTINUED       4       ; Report continued child
define WNOWAIT          8       ; Don't reap, just poll status
define WEXITED          16      ; Report dead child

define WCOREFLAG        0x80
define __W_CONTINUED    0xffff

W_EXITCODE proto watcall retval:int_t, sig:int_t {
    shl     eax,8
    or      eax,edx
    }

W_STOPCODE proto watcall sig:int_t {
    shl     eax,8
    or      eax,0x7F
    }

WEXITSTATUS proto watcall status:int_t {
    movzx   eax,ah
    }

WTERMSIG proto watcall status:int_t {
    and     eax,0x7f
    }

WSTOPSIG proto watcall status:int_t {
    WEXITSTATUS(eax)
    }

WIFEXITED proto watcall status:int_t {
    WTERMSIG(eax)
    setz    al
    }

WIFSIGNALED proto watcall status:int_t {
    and     eax,0x7F
    add     eax,1
    cmp     al,1
    setg    al
    }

WIFSTOPPED proto watcall status:int_t {
    and     eax,0xFF
    cmp     eax,0x7F
    setz    al
    }

WIFCONTINUED proto watcall status:int_t {
    cmp     eax,__W_CONTINUED
    mov     eax,0
    setz    al
    }

WCOREDUMP proto watcall status:int_t {
    and     eax,WCOREFLAG
    }

.enum idtype_t {
  P_ALL,        ; Wait for any child
  P_PID,        ; Wait for specified process
  P_PGID,       ; Wait for members of process group
  P_PIDFD,      ; Wait for the child referred by the PID file descriptor
  }


_wait       proto __cdecl :ptr int_t
waitpid     proto __cdecl :pid_t, :ptr int_t, :int_t
waitid      proto __cdecl :idtype_t, :id_t, :ptr siginfo_t, :int_t
wait3       proto __cdecl :ptr int_t, :int_t, :ptr rusage
wait4       proto __cdecl :pid_t, :ptr int_t, :int_t, :ptr rusage

endif
