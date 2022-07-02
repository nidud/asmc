; _GET_ERRNO_FROM_OSERR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc

errentry    struct
oscode      ulong_t ?   ; OS return value
errnocode   int_t ?     ; System V error code
errentry    ends

.data

errtable errentry \
    { ERROR_INVALID_FUNCTION,       EINVAL    }, ;; 1
    { ERROR_FILE_NOT_FOUND,         ENOENT    }, ;; 2
    { ERROR_PATH_NOT_FOUND,         ENOENT    }, ;; 3
    { ERROR_TOO_MANY_OPEN_FILES,    EMFILE    }, ;; 4
    { ERROR_ACCESS_DENIED,          EACCES    }, ;; 5
    { ERROR_INVALID_HANDLE,         EBADF     }, ;; 6
    { ERROR_ARENA_TRASHED,          ENOMEM    }, ;; 7
    { ERROR_NOT_ENOUGH_MEMORY,      ENOMEM    }, ;; 8
    { ERROR_INVALID_BLOCK,          ENOMEM    }, ;; 9
    { ERROR_BAD_ENVIRONMENT,        E2BIG     }, ;; 10
    { ERROR_BAD_FORMAT,             ENOEXEC   }, ;; 11
    { ERROR_INVALID_ACCESS,         EINVAL    }, ;; 12
    { ERROR_INVALID_DATA,           EINVAL    }, ;; 13
    { ERROR_INVALID_DRIVE,          ENOENT    }, ;; 15
    { ERROR_CURRENT_DIRECTORY,      EACCES    }, ;; 16
    { ERROR_NOT_SAME_DEVICE,        EXDEV     }, ;; 17
    { ERROR_NO_MORE_FILES,          ENOENT    }, ;; 18
    { ERROR_LOCK_VIOLATION,         EACCES    }, ;; 33
    { ERROR_BAD_NETPATH,            ENOENT    }, ;; 53
    { ERROR_NETWORK_ACCESS_DENIED,  EACCES    }, ;; 65
    { ERROR_BAD_NET_NAME,           ENOENT    }, ;; 67
    { ERROR_FILE_EXISTS,            EEXIST    }, ;; 80
    { ERROR_CANNOT_MAKE,            EACCES    }, ;; 82
    { ERROR_FAIL_I24,               EACCES    }, ;; 83
    { ERROR_INVALID_PARAMETER,      EINVAL    }, ;; 87
    { ERROR_NO_PROC_SLOTS,          EAGAIN    }, ;; 89
    { ERROR_DRIVE_LOCKED,           EACCES    }, ;; 108
    { ERROR_BROKEN_PIPE,            EPIPE     }, ;; 109
    { ERROR_DISK_FULL,              ENOSPC    }, ;; 112
    { ERROR_INVALID_TARGET_HANDLE,  EBADF     }, ;; 114
    { ERROR_INVALID_HANDLE,         EINVAL    }, ;; 124
    { ERROR_WAIT_NO_CHILDREN,       ECHILD    }, ;; 128
    { ERROR_CHILD_NOT_COMPLETE,     ECHILD    }, ;; 129
    { ERROR_DIRECT_ACCESS_HANDLE,   EBADF     }, ;; 130
    { ERROR_NEGATIVE_SEEK,          EINVAL    }, ;; 131
    { ERROR_SEEK_ON_DEVICE,         EACCES    }, ;; 132
    { ERROR_DIR_NOT_EMPTY,          ENOTEMPTY }, ;; 145
    { ERROR_NOT_LOCKED,             EACCES    }, ;; 158
    { ERROR_BAD_PATHNAME,           ENOENT    }, ;; 161
    { ERROR_MAX_THRDS_REACHED,      EAGAIN    }, ;; 164
    { ERROR_LOCK_FAILED,            EACCES    }, ;; 167
    { ERROR_ALREADY_EXISTS,         EEXIST    }, ;; 183
    { ERROR_FILENAME_EXCED_RANGE,   ENOENT    }, ;; 206
    { ERROR_NESTING_NOT_ALLOWED,    EAGAIN    }, ;; 215
    { ERROR_NOT_ENOUGH_QUOTA,       ENOMEM    } ;; 1816

ERRTABLESIZE equ lengthof(errtable)

MIN_EXEC_ERROR equ ERROR_INVALID_STARTING_CODESEG
MAX_EXEC_ERROR equ ERROR_INFLOOP_IN_RELOC_CHAIN

MIN_EACCES_RANGE equ ERROR_WRITE_PROTECT
MAX_EACCES_RANGE equ ERROR_SHARING_BUFFER_EXCEEDED

    .code

_get_errno_from_oserr proc oserrno:ulong_t

    mov ecx,oserrno
    .for ( rdx = &errtable, eax = 0: eax < ERRTABLESIZE: ++eax )

        .if ( ecx == [rdx+rax*sizeof(errentry)].errentry.oscode )

            .return( [rdx+rax*sizeof(errentry)].errentry.errnocode )
        .endif
    .endf

    .if ( ecx >= MIN_EACCES_RANGE && ecx <= MAX_EACCES_RANGE )
        mov eax,EACCES
    .elseif ( ecx >= MIN_EXEC_ERROR && ecx <= MAX_EXEC_ERROR )
        mov eax,ENOEXEC
    .else
        mov eax,EINVAL
    .endif
    ret

_get_errno_from_oserr endp

    end
