ifndef _INC_LOCKING
_INC_LOCKING equ <>

ifndef _WIN32
.err <ERROR: Only Win32 target supported!>
endif

_LK_UNLCK       equ 0 ;; unlock the file region
_LK_LOCK        equ 1 ;; lock the file region
_LK_NBLCK       equ 2 ;; non-blocking lock
_LK_RLCK        equ 3 ;; lock for writing
_LK_NBRLCK      equ 4 ;; non-blocking lock for writing

if !__STDC__
;; Non-ANSI names for compatibility
LK_UNLCK        equ _LK_UNLCK
LK_LOCK         equ _LK_LOCK
LK_NBLCK        equ _LK_NBLCK
LK_RLCK         equ _LK_RLCK
LK_NBRLCK       equ _LK_NBRLCK
endif

endif
