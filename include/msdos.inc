ifndef _INC_MSDOS
_INC_MSDOS equ <>

ifndef _CRTBLD
;;
;; This is an internal C runtime header file. It is used when building
;; the C runtimes only. It is not to be used as a public header file.
;;
.err <ERROR: Use of C runtime library internal header file.>
endif

_STACKSLOP              equ 1024

FOPEN                   equ 0x01    ;; file handle open
FEOFLAG                 equ 0x02    ;; end of file has been encountered
FCRLF                   equ 0x04    ;; CR-LF across read buffer (in text mode)
FPIPE                   equ 0x08    ;; file handle refers to a pipe
FNOINHERIT              equ 0x10    ;; file handle opened _O_NOINHERIT
FAPPEND                 equ 0x20    ;; file handle opened O_APPEND
FDEV                    equ 0x40    ;; file handle refers to device
FTEXT                   equ 0x80    ;; file handle is in text mode

;; DOS errno values for setting __doserrno in C routines

E_ifunc                 equ 1       ;; invalid function code
E_nofile                equ 2       ;; file not found
E_nopath                equ 3       ;; path not found
E_toomany               equ 4       ;; too many open files
E_access                equ 5       ;; access denied
E_ihandle               equ 6       ;; invalid handle
E_arena                 equ 7       ;; arena trashed
E_nomem                 equ 8       ;; not enough memory
E_iblock                equ 9       ;; invalid block
E_badenv                equ 10      ;; bad environment
E_badfmt                equ 11      ;; bad format
E_iaccess               equ 12      ;; invalid access code
E_idata                 equ 13      ;; invalid data
E_unknown               equ 14      ;; ??? unknown error ???
E_idrive                equ 15      ;; invalid drive
E_curdir                equ 16      ;; current directory
E_difdev                equ 17      ;; not same device
E_nomore                equ 18      ;; no more files
E_maxerr2               equ 19      ;; unknown error - Version 2.0
E_sharerr               equ 32      ;; sharing violation
E_lockerr               equ 33      ;; locking violation
E_maxerr3               equ 34      ;; unknown error - Version 3.0

;; DOS file attributes

A_RO                    equ 0x1     ;; read only
A_H                     equ 0x2     ;; hidden
A_S                     equ 0x4     ;; system
A_V                     equ 0x8     ;; volume id
A_D                     equ 0x10    ;; directory
A_A                     equ 0x20    ;; archive

A_MOD                   equ (A_RO+A_H+A_S+A_A)      ;; changeable attributes

endif ;; _INC_MSDOS
