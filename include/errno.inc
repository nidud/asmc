ifndef _ERRNO_
define _ERRNO_
ifndef _LIBC_
include libc.inc
endif

.pragma comment(lib, libc, msvcrt)

; Declare reference to errno

ifndef _CRT_ERRNO_DEFINED
define _CRT_ERRNO_DEFINED
if defined(__UNIX__) and not defined(__MSCRT__)
ifdef _WIN64
__errno_location proto __cdecl
define _errno <__errno_location>
else
__get_errno_ptr proto __cdecl
define _errno <__get_errno_ptr>
endif
else
_errno proto __cdecl
endif
_get_errno proto __cdecl :ptr int_t
ifdef __UNIX__
__set_errno proto :int_t
define _set_errno <__set_errno>
else
_set_errno proto __cdecl :int_t
endif
if defined(__UNIX__) or defined(_WIN64) or defined(_MSVCRT)
define errno <errno_t ptr [_errno()]>
else
externdef errno:errno_t
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

define ENOERR		0
define EPERM		1
define ENOENT		2
define ESRCH		3
define EINTR		4
define EIO		5
define ENXIO		6
define E2BIG		7
define ENOEXEC		8
define EBADF		9
define ECHILD		10
define EAGAIN		11
define ENOMEM		12
define EACCES		13
define EFAULT		14
define ENOTBLK		15
define EBUSY		16
define EEXIST		17
define EXDEV		18
define ENODEV		19
define ENOTDIR		20
define EISDIR		21
define ENFILE		23
define EMFILE		24
define ENOTTY		25
define EFBIG		27
define ENOSPC		28
define ESPIPE		29
define EROFS		30
define EMLINK		31
define EPIPE		32
define EDOM		33
define EUCLEAN		35
define EDEADLK		36
define EUNKNOWN		37
define ENAMETOOLONG	38
define ENOLCK		39
define ENOSYS		40
define ENOTEMPTY	41

;; Error codes used in the Secure CRT functions

ifndef _SECURECRT_ERRCODE_VALUES_DEFINED
define _SECURECRT_ERRCODE_VALUES_DEFINED
define EINVAL		22
define ERANGE		34
define EILSEQ		42
define STRUNCATE	80
endif

define EDEADLOCK	EDEADLK

define EADDRINUSE	100
define EADDRNOTAVAIL	101
define EAFNOSUPPORT	102
define EALREADY		103
define EBADMSG		104
define ECANCELED	105
define ECONNABORTED	106
define ECONNREFUSED	107
define ECONNRESET	108
define EDESTADDRREQ	109
define EHOSTUNREACH	110
define EIDRM		111
define EINPROGRESS	112
define EISCONN		113
define ELOOP		114
define EMSGSIZE		115
define ENETDOWN		116
define ENETRESET	117
define ENETUNREACH	118
define ENOBUFS		119
define ENODATA		120
define ENOLINK		121
define ENOMSG		122
define ENOPROTOOPT	123
define ENOSR		124
define ENOSTR		125
define ENOTCONN		126
define ENOTRECOVERABLE	127
define ENOTSOCK		128
define ENOTSUP		129
define EOPNOTSUPP	130
define EOTHER		131
define EOVERFLOW	132
define EOWNERDEAD	133
define EPROTO		134
define EPROTONOSUPPORT	135
define EPROTOTYPE	136
define ETIME		137
define ETIMEDOUT	138
define ETXTBSY		139
define EWOULDBLOCK	140

endif
