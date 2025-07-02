.pragma list(push, 0)
ifdef __UNIX__
include libc.inc
else
include crtdefs.inc
endif
include winerror.inc
.pragma comment(lib, libc, msvcrt)

;; Declare reference to errno

ifndef _CRT_ERRNO_DEFINED
define _CRT_ERRNO_DEFINED
_errno		proto __cdecl
ifdef __UNIX__
__set_errno proto :int_t
_set_errno equ <__set_errno>
else
_set_errno	proto __cdecl :int_t
endif
_get_errno	proto __cdecl :ptr int_t
ifdef __UNIX__
__get_errno_ptr proto __cdecl
errno		equ <errno_t ptr [__get_errno_ptr()]>
elseif defined(_WIN64) or defined(_MSVCRT)
errno		equ <errno_t ptr [_errno()]>
else
externdef	errno:errno_t
endif
endif

__doserrno	proto __cdecl
_set_doserrno	proto __cdecl :uint_t
_get_doserrno	proto __cdecl :ptr uint_t
__sys_errlist	proto __cdecl
if defined(_WIN64) or defined(_MSVCRT)
_doserrno	equ <errno_t ptr [__doserrno()]>
_sys_errlist	equ <__sys_errlist()>
_sys_nerr	equ <[__sys_nerr()]>
else
externdef	_doserrno:errno_t
externdef	_sys_errlist:array_t
externdef	_sys_nerr:int_t
endif
__sys_nerr	proto __cdecl
_dosmaperr	proto __cdecl :uint_t

ENOERR		equ 0
EPERM		equ 1
ENOENT		equ 2
ESRCH		equ 3
EINTR		equ 4
EIO		equ 5
ENXIO		equ 6
E2BIG		equ 7
ENOEXEC		equ 8
EBADF		equ 9
ECHILD		equ 10
EAGAIN		equ 11
ENOMEM		equ 12
EACCES		equ 13
EFAULT		equ 14
ENOTBLK		equ 15
EBUSY		equ 16
EEXIST		equ 17
EXDEV		equ 18
ENODEV		equ 19
ENOTDIR		equ 20
EISDIR		equ 21
ENFILE		equ 23
EMFILE		equ 24
ENOTTY		equ 25
EFBIG		equ 27
ENOSPC		equ 28
ESPIPE		equ 29
EROFS		equ 30
EMLINK		equ 31
EPIPE		equ 32
EDOM		equ 33
EUCLEAN		equ 35
EDEADLK		equ 36
EUNKNOWN	equ 37
ENAMETOOLONG	equ 38
ENOLCK		equ 39
ENOSYS		equ 40
ENOTEMPTY	equ 41

;; Error codes used in the Secure CRT functions

ifndef RC_INVOKED
ifndef _SECURECRT_ERRCODE_VALUES_DEFINED
define _SECURECRT_ERRCODE_VALUES_DEFINED
EINVAL		equ 22
ERANGE		equ 34
EILSEQ		equ 42
STRUNCATE	equ 80
endif
endif

;; Support EDEADLOCK for compatibility with older MS-C versions
EDEADLOCK	equ EDEADLK

;; POSIX SUPPLEMENT
EADDRINUSE	equ 100
EADDRNOTAVAIL	equ 101
EAFNOSUPPORT	equ 102
EALREADY	equ 103
EBADMSG		equ 104
ECANCELED	equ 105
ECONNABORTED	equ 106
ECONNREFUSED	equ 107
ECONNRESET	equ 108
EDESTADDRREQ	equ 109
EHOSTUNREACH	equ 110
EIDRM		equ 111
EINPROGRESS	equ 112
EISCONN		equ 113
ELOOP		equ 114
EMSGSIZE	equ 115
ENETDOWN	equ 116
ENETRESET	equ 117
ENETUNREACH	equ 118
ENOBUFS		equ 119
ENODATA		equ 120
ENOLINK		equ 121
ENOMSG		equ 122
ENOPROTOOPT	equ 123
ENOSR		equ 124
ENOSTR		equ 125
ENOTCONN	equ 126
ENOTRECOVERABLE equ 127
ENOTSOCK	equ 128
ENOTSUP		equ 129
EOPNOTSUPP	equ 130
EOTHER		equ 131
EOVERFLOW	equ 132
EOWNERDEAD	equ 133
EPROTO		equ 134
EPROTONOSUPPORT equ 135
EPROTOTYPE	equ 136
ETIME		equ 137
ETIMEDOUT	equ 138
ETXTBSY		equ 139
EWOULDBLOCK	equ 140

.pragma list(pop)
