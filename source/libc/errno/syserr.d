; SYSERR.D--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include cruntime.inc
include stdlib.inc

    .data

    T equ <@CStr>
sys_errlist string_t \
    T("No error"),
    T("Operation not permitted"),               ;  1 EPERM
    T("No such file or directory"),             ;  2 ENOENT
    T("No such process"),                       ;  3 ESRCH
    T("Interrupted function call"),             ;  4 EINTR
    T("Input/output error"),                    ;  5 EIO
    T("No such device or address"),             ;  6 ENXIO
    T("Arg list too long"),                     ;  7 E2BIG
    T("Exec format error"),                     ;  8 ENOEXEC
    T("Bad file descriptor"),                   ;  9 EBADF
    T("No child processes"),                    ; 10 ECHILD
    T("Resource temporarily unavailable"),      ; 11 EAGAIN
    T("Not enough space"),                      ; 12 ENOMEM
    T("Permission denied"),                     ; 13 EACCES
    T("Bad address"),                           ; 14 EFAULT
    T("Unknown error"),                         ; 15 ENOTBLK
    T("Resource device"),                       ; 16 EBUSY
    T("File exists"),                           ; 17 EEXIST
    T("Improper link"),                         ; 18 EXDEV
    T("No such device"),                        ; 19 ENODEV
    T("Not a directory"),                       ; 20 ENOTDIR
    T("Is a directory"),                        ; 21 EISDIR
    T("Invalid argument"),                      ; 22 EINVAL
    T("Too many open files in system"),         ; 23 ENFILE
    T("Too many open files"),                   ; 24 EMFILE
    T("Inappropriate I/O control operation"),   ; 25 ENOTTY
    T("Unknown error"),                         ; 26 ETXTBSY
    T("File too large"),                        ; 27 EFBIG
    T("No space left on device"),               ; 28 ENOSPC
    T("Invalid seek"),                          ; 29 ESPIPE
    T("Read-only file system"),                 ; 30 EROFS
    T("Too many links"),                        ; 31 EMLINK
    T("Broken pipe"),                           ; 32 EPIPE
    T("Domain error"),                          ; 33 EDOM
    T("Result too large"),                      ; 34 ERANGE
    T("Unknown error"),                         ; 35 EUCLEAN
    T("Resource deadlock avoided"),             ; 36 EDEADLK
    T("Unknown error"),                         ; 37 UNKNOWN
    T("Filename too long"),                     ; 38 ENAMETOOLONG
    T("No locks available"),                    ; 39 ENOLCK
    T("Function not implemented"),              ; 40 ENOSYS
    T("Directory not empty"),                   ; 41 ENOTEMPTY
    T("Illegal byte sequence"),                 ; 42 EILSEQ
    T("Unknown error")

_sys_errlist array_t sys_errlist
_sys_nerr int_t lengthof(sys_errlist) - 1

    .code

_sys_err_msg proc uses bx m:int_t

    lesl bx,_sys_errlist
    mov ax,m
    .ifs ( ax < 0 || ax > _sys_nerr )
        mov ax,_sys_nerr
    .endif
    shl ax,string_t/2
    add bx,ax
    mov ax,esl[bx]
    movl dx,esl[bx+2]
    ret

_sys_err_msg endp

    end
