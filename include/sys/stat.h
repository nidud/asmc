#ifndef __INC_STAT
#define __INC_STAT
#if !defined(__INC_DEFS)
 #include <defs.h>
#endif
#ifdef __cplusplus
 extern "C" {
#endif

#define _S_IFMT		0xF000
#define _S_IFDIR	0x4000
#define _S_IFIFO	0x1000
#define _S_IFCHR	0x2000
#define _S_IFBLK	0x3000
#define _S_IFREG	0x8000
#define _S_IREAD	0x0100
#define _S_IWRITE	0x0080
#define _S_IEXEC	0x0040

struct _stat {
	_dev_t	st_dev;
	_ino_t	st_ino;
	WORD	st_mode;
	short	st_nlink;
	short	st_uid;
	short	st_gid;
	_dev_t	st_rdev;
	_off_t	st_size;
	time_t	st_atime;
	time_t	st_mtime;
	time_t	st_ctime;
};

int __cdecl _stat(const char *, struct _stat *);

#ifdef __cplusplus
 }
#endif
#endif
