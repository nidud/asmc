.pragma list(push, 0)

ifndef __LIBC_INC
 include libc.inc
endif
ifndef _WINERROR_
 include winerror.inc
endif
ifdef __PE__
option	dllimport:<msvcrt>
else
includelib libc.lib
endif

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
EINVAL		equ 22
ENFILE		equ 23
EMFILE		equ 24
ENOTTY		equ 25
ETXTBSY		equ 26
EFBIG		equ 27
ENOSPC		equ 28
ESPIPE		equ 29
EROFS		equ 30
EMLINK		equ 31
EPIPE		equ 32
EDOM		equ 33
ERANGE		equ 34
EUCLEAN		equ 35
EDEADLK		equ 36
EUNKNOWN	equ 37
ENAMETOOLONG	equ 38
ENOLCK		equ 39
ENOSYS		equ 40
ENOTEMPTY	equ 41
EILSEQ		equ 42

if defined(__PE__) or defined(_LINUX)
_get_errno proto __cdecl :ptr
ifndef _errno
    .data
    _errno dd 0
    .code
endif
errno equ <_get_errno(addr _errno)>
else
externdef	errno:dword
externdef	_doserrno:dword
externdef	sys_errlist:size_t
endif

osmaperr	proto __cdecl

.pragma list(pop)
