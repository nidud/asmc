#ifndef __INC_ERRNO
#define __INC_ERRNO
#if !defined(__INC_DEFS)
 #include <defs.h>
#endif

#define EPERM		1
#define ENOENT		2
#define ESRCH		3
#define EINTR		4
#define EIO		5
#define ENXIO		6
#define E2BIG		7
#define ENOEXEC		8
#define EBADF		9
#define ECHILD		10
#define EAGAIN		11
#define ENOMEM		12
#define EACCES		13
#define EFAULT		14
#define ENOTBLK		15
#define EBUSY		16
#define EEXIST		17
#define EXDEV		18
#define ENODEV		19
#define ENOTDIR		20
#define EISDIR		21
#define EINVAL		22
#define ENFILE		23
#define EMFILE		24
#define ENOTTY		25
#define EFBIG		27
#define ENOSPC		28
#define ESPIPE		29
#define EROFS		30
#define EMLINK		31
#define EPIPE		32
#define EDOM		33
#define ERANGE		34
#define EDEADLK		36
#define ENAMETOOLONG	38
#define ENOLCK		39
#define ENOSYS		40
#define ENOTEMPTY	41
#define EILSEQ		42

#define __DISK_DOS	0x00
#define __DISK_FAT	0x02
#define __DISK_ROOT	0x04
#define __DISK_DATA	0x06

#define __ISWRITE	0x01
#define __DISKAREA	0x06
#define __FAILALLOWED	0x08
#define __RETRYALLOWED	0x10
#define __IGNOREALLOWED 0x20
#define __ISDEVICE	0x80

#ifdef __cplusplus
 extern "C" {
#endif

#ifndef __f__
#ifndef __DEVHDR
#define __DEVHDR
typedef struct {
	long	dh_next;
	int	dh_attr;
	int	dh_strat;
	int	dh_inter;
	char	dh_name[8];
} devhdr;

extern devhdr far *sys_erdevice;
extern char sys_erflag;
extern char sys_erdrive;
extern int sys_ercode;
#endif
#endif

extern int errno;
extern int doserrno;
extern int sys_nerr;

extern char *sys_errlist[];
extern char *dos_errlist[];

int _CType trace(void);
int _CType notsup(void);
int _CType eropen(char *);
int _cdecl ermsg(char *__title, char *, ...);

#ifdef __cplusplus
 }
#endif
#endif
