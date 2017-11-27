ifndef __LIBC_INC
 include libc.inc
endif

.xlist

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

ER_ZIP		equ 2
ER_BADERR	equ 3
ER_MEM		equ 4
ER_CRCERR	equ 5
ER_NOZIP	equ 9
ER_FIND		equ 11
ER_OPEN		equ 12
ER_DISK		equ 50
ER_USERABORT	equ 66
ER_READARCH	equ -2
ER_DISK_FULL	equ 112
ER_NEGATIVE_SEEK equ 131

__ISWRITE	equ 01h
__DISKAREA	equ 06h
__FAILALLOWED	equ 08h
__RETRYALLOWED	equ 10h
__IGNOREALLOWED equ 20h
__ISDEVICE	equ 80h

externdef	errno:		WORD
externdef	doserrno:	WORD
externdef	sys_errlist:	DWORD
externdef	dos_errlist:	DWORD

externdef	sys_erdevice:	DWORD
externdef	sys_ercode:	WORD
externdef	sys_erflag:	BYTE
externdef	sys_erdrive:	BYTE
externdef	sys_erproc:	size_p

trace		PROTO _CType
osmaperr	PROTO
notsup		PROTO _CType
eropen		PROTO _CType :DWORD
ermkdir		PROTO _CType :DWORD
erdelete	PROTO _CType :DWORD
errnomsg	PROTO _CType :DWORD, :DWORD, :DWORD
ermsg		PROTO _CDecl :DWORD, :DWORD, :VARARG

.list
