; _SYS_MAPERR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc
include winerror.inc
include errhandlingapi.inc

errentry    struct
errnocode   errno_t ?
oscode      uint_t ?
errentry    ends

.data

errtable errentry \
    { EPERM,           ERROR_ACCESS_DENIED },
    { ENOENT,          ERROR_FILE_NOT_FOUND },
    { ESRCH,           ERROR_INVALID_THREAD_ID },
    { EINTR,           ERROR_OPERATION_ABORTED },
    { EIO,             ERROR_IO_DEVICE },
    { ENXIO,           ERROR_FILE_INVALID },
    { E2BIG,           ERROR_BAD_ENVIRONMENT },
    { ENOEXEC,         ERROR_BAD_EXE_FORMAT },
    { EBADF,           ERROR_INVALID_HANDLE },
    { ECHILD,          ERROR_WAIT_NO_CHILDREN },
    { EAGAIN,          ERROR_NO_MORE_ITEMS },
    { ENOMEM,          ERROR_NOT_ENOUGH_MEMORY },
    { EACCES,          ERROR_ACCESS_DENIED },
    { EFAULT,          ERROR_INVALID_ADDRESS },
    { ENOTBLK,         ERROR_INVALID_DRIVE },
    { EBUSY,           ERROR_BUSY },
    { EEXIST,          ERROR_ALREADY_EXISTS },
    { EXDEV,           ERROR_NOT_SAME_DEVICE },
    { ENODEV,          ERROR_BAD_UNIT },
    { ENOTDIR,         ERROR_DIRECTORY },
    { EISDIR,          ERROR_ACCESS_DENIED },
    { EINVAL,          ERROR_INVALID_PARAMETER },
    { ENFILE,          ERROR_TOO_MANY_OPEN_FILES },
    { EMFILE,          ERROR_TOO_MANY_OPEN_FILES },
    { ENOTTY,          ERROR_INVALID_FUNCTION },
    { EFBIG,           ERROR_FILE_TOO_LARGE },
    { ENOSPC,          ERROR_DISK_FULL },
    { ESPIPE,          ERROR_NEGATIVE_SEEK },
    { EROFS,           ERROR_WRITE_PROTECT },
    { EMLINK,          ERROR_TOO_MANY_LINKS },
    { EPIPE,           ERROR_BROKEN_PIPE },
    { EDOM,            ERROR_INVALID_PARAMETER },
    { ERANGE,          ERROR_ARITHMETIC_OVERFLOW },
    { EUCLEAN,         ERROR_DISK_CORRUPT },
    { EDEADLK,         ERROR_POSSIBLE_DEADLOCK },
    { EUNKNOWN,        ERROR_GEN_FAILURE },
    { ENAMETOOLONG,    ERROR_FILENAME_EXCED_RANGE },
    { ENOLCK,          ERROR_SHARING_VIOLATION },
    { ENOSYS,          ERROR_CALL_NOT_IMPLEMENTED },
    { ENOTEMPTY,       ERROR_DIR_NOT_EMPTY },
    { EILSEQ,          ERROR_NO_UNICODE_TRANSLATION },
    { STRUNCATE,       ERROR_INSUFFICIENT_BUFFER },
    { EADDRINUSE,      WSAEADDRINUSE },
    { EADDRNOTAVAIL,   WSAEADDRNOTAVAIL },
    { EAFNOSUPPORT,    WSAEAFNOSUPPORT },
    { EALREADY,        WSAEALREADY },
    { EBADMSG,         ERROR_BAD_FORMAT },
    { ECANCELED,       ERROR_OPERATION_ABORTED },
    { ECONNABORTED,    WSAECONNABORTED },
    { ECONNREFUSED,    WSAECONNREFUSED },
    { ECONNRESET,      WSAECONNRESET },
    { EDESTADDRREQ,    WSAEDESTADDRREQ },
    { EHOSTUNREACH,    WSAEHOSTUNREACH },
    { EIDRM,           ERROR_INVALID_HANDLE },
    { EINPROGRESS,     WSAEINPROGRESS },
    { EISCONN,         WSAEISCONN },
    { ELOOP,           ERROR_CANT_RESOLVE_FILENAME },
    { EMSGSIZE,        WSAEMSGSIZE },
    { ENETDOWN,        WSAENETDOWN },
    { ENETRESET,       WSAENETRESET },
    { ENETUNREACH,     WSAENETUNREACH },
    { ENOBUFS,         WSAENOBUFS },
    { ENODATA,         ERROR_NO_DATA },
    { ENOLINK,         ERROR_REM_NOT_LIST },
    { ENOMSG,          ERROR_NO_MORE_ITEMS },
    { ENOPROTOOPT,     WSAENOPROTOOPT },
    { ENOSR,           ERROR_OUT_OF_STRUCTURES },
    { ENOSTR,          ERROR_INVALID_HANDLE },
    { ENOTCONN,        WSAENOTCONN },
    { ENOTRECOVERABLE, ERROR_INTERNAL_DB_CORRUPTION },
    { ENOTSOCK,        WSAENOTSOCK },
    { ENOTSUP,         ERROR_NOT_SUPPORTED },
    { EOPNOTSUPP,      WSAEOPNOTSUPP },
    { EOTHER,          ERROR_GEN_FAILURE },
    { EOVERFLOW,       ERROR_ARITHMETIC_OVERFLOW },
    { EOWNERDEAD,      ERROR_WAIT_1 },
    { EPROTO,          ERROR_PROTOCOL_UNREACHABLE },
    { EPROTONOSUPPORT, WSAEPROTONOSUPPORT },
    { EPROTOTYPE,      WSAEPROTOTYPE },
    { ETIME,           ERROR_SEM_TIMEOUT },
    { ETIMEDOUT,       WSAETIMEDOUT },
    { ETXTBSY,         ERROR_SHARING_VIOLATION },
    { EWOULDBLOCK,     WSAEWOULDBLOCK }

.code

_sys_maperr proc syserr:errno_t
    ldr ecx,syserr
    neg ecx
    .for ( rdx = &errtable, eax = 0 : eax < lengthof(errtable) : eax++ )
        .if ( ecx == [rdx+rax*sizeof(errentry)].errentry.errnocode )
            mov ecx,[rdx+rax*sizeof(errentry)].errentry.oscode
           .break
        .endif
    .endf
    .return( SetLastError(ecx) )
    endp

    end
