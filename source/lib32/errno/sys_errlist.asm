; SYS_ERRLIST.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc

public	CP_ENOMEM
public	CP_EIO
public	CP_ENOSYS
public	CP_ENOSPC
public	CP_ENOENT

	.data

CP_NOERROR	db	'No '
CP_ERROR	db	'Error',0
CP_EPERM	db	"Operation not permitted",0
CP_ENOENT	db	"No such file or directory",0
CP_ESRCH	db	"No such process",0
CP_EINTR	db	"Interrupted function call",0
CP_EIO		db	"Input/output error",0
CP_ENXIO	db	"No such device or address",0
CP_E2BIG	db	"Arg list too long",0
CP_ENOEXEC	db	"Exec format error",0
CP_EBADF	db	"Bad file descriptor",0
CP_ECHILD	db	"No child processes",0
CP_EAGAIN	db	"Resource temporarily unavailable",0
CP_ENOMEM	db	"Not enough space",0
CP_EACCES	db	"Permission denied",0
CP_EFAULT	db	"Bad address",0
CP_EBUSY	db	"Resource device",0
CP_EEXIST	db	"File exists",0
CP_EXDEV	db	"Improper link",0
CP_ENODEV	db	"No such device",0
CP_ENOTDIR	db	"Not a directory",0
CP_EISDIR	db	"Is a directory",0
CP_EINVAL	db	"Invalid argument",0
CP_ENFILE	db	"Too many open files in system",0
CP_EMFILE	db	"Too many open files",0
CP_ENOTTY	db	"Inappropriate I/O control operation",0
CP_EFBIG	db	"File too large",0
CP_ENOSPC	db	"No space left on device",0
CP_ESPIPE	db	"Invalid seek",0
CP_EROFS	db	"Read-only file system",0
CP_EMLINK	db	"Too many links",0
CP_EPIPE	db	"Broken pipe",0
CP_EDOM		db	"Domain error",0
CP_ERANGE	db	"Result too large",0
CP_EDEADLK	db	"Resource deadlock avoided",0
CP_ENAMETOOLONG db	"Filename too long",0
CP_ENOLCK	db	"No locks available",0
CP_ENOSYS	db	"Function not implemented",0
CP_ENOTEMPTY	db	"Directory not empty",0
CP_EILSEQ	db	"Illegal byte sequence",0
CP_UNKNOWN	db	"Unknown error",0

sys_errlist	dd	CP_NOERROR
		dd	CP_EPERM
		dd	CP_ENOENT
		dd	CP_ESRCH
		dd	CP_EINTR
		dd	CP_EIO
		dd	CP_ENXIO
		dd	CP_E2BIG
		dd	CP_ENOEXEC
		dd	CP_EBADF
		dd	CP_ECHILD
		dd	CP_EAGAIN
		dd	CP_ENOMEM
		dd	CP_EACCES
		dd	CP_EFAULT
		dd	CP_UNKNOWN
		dd	CP_EBUSY
		dd	CP_EEXIST
		dd	CP_EXDEV
		dd	CP_ENODEV
		dd	CP_ENOTDIR
		dd	CP_EISDIR
		dd	CP_EINVAL
		dd	CP_ENFILE
		dd	CP_EMFILE
		dd	CP_ENOTTY
		dd	CP_UNKNOWN
		dd	CP_EFBIG
		dd	CP_ENOSPC
		dd	CP_ESPIPE
		dd	CP_EROFS
		dd	CP_EMLINK
		dd	CP_EPIPE
		dd	CP_EDOM
		dd	CP_ERANGE
		dd	CP_UNKNOWN
		dd	CP_EDEADLK
		dd	CP_UNKNOWN
		dd	CP_ENAMETOOLONG
		dd	CP_ENOLCK
		dd	CP_ENOSYS
		dd	CP_ENOTEMPTY
		dd	CP_EILSEQ
		dd	CP_UNKNOWN

sys_nerr dd	(($ - offset sys_errlist) / 4)

	END
