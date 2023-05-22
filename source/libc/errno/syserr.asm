
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

ifndef _WIN64
_sys_errlist array_t sys_errlist
_sys_nerr label int_t
endif
sys_nerr int_t lengthof(sys_errlist) - 1

    .code

__sys_nerr proc

    lea rax,sys_nerr
    ret

__sys_nerr endp

__sys_errlist proc

    lea rax,sys_errlist
    ret

__sys_errlist endp

_sys_err_msg proc m:int_t

    ldr ecx,m
    .ifs ( ecx < 0 || ecx > sys_nerr )

        mov ecx,sys_nerr
    .endif
    lea rax,sys_errlist
    mov rax,[rax+rcx*string_t]
    ret

_sys_err_msg endp

    end
