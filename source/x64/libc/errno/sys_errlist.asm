include errno.inc

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

sys_errlist	dq	CP_NOERROR
		dq	CP_EPERM
		dq	CP_ENOENT
		dq	CP_ESRCH
		dq	CP_EINTR
		dq	CP_EIO
		dq	CP_ENXIO
		dq	CP_E2BIG
		dq	CP_ENOEXEC
		dq	CP_EBADF
		dq	CP_ECHILD
		dq	CP_EAGAIN
		dq	CP_ENOMEM
		dq	CP_EACCES
		dq	CP_EFAULT
		dq	CP_UNKNOWN
		dq	CP_EBUSY
		dq	CP_EEXIST
		dq	CP_EXDEV
		dq	CP_ENODEV
		dq	CP_ENOTDIR
		dq	CP_EISDIR
		dq	CP_EINVAL
		dq	CP_ENFILE
		dq	CP_EMFILE
		dq	CP_ENOTTY
		dq	CP_UNKNOWN
		dq	CP_EFBIG
		dq	CP_ENOSPC
		dq	CP_ESPIPE
		dq	CP_EROFS
		dq	CP_EMLINK
		dq	CP_EPIPE
		dq	CP_EDOM
		dq	CP_ERANGE
		dq	CP_UNKNOWN
		dq	CP_EDEADLK
		dq	CP_UNKNOWN
		dq	CP_ENAMETOOLONG
		dq	CP_ENOLCK
		dq	CP_ENOSYS
		dq	CP_ENOTEMPTY
		dq	CP_EILSEQ
		dq	CP_UNKNOWN

sys_nerr dq	(($ - offset sys_errlist) / 8)

	END
