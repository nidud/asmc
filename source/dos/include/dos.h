#ifndef __INC_DOS
#define __INC_DOS
#if !defined(__INC_DEFS)
 #include <defs.h>
#endif

extern	int	_argc;
extern	char ** _argv;
#ifndef __f__
extern	char ** _environ;
extern	WORD	_psp;
extern	WORD	_heaplen;
extern	WORD	_stklen;
extern	WORD	_osversion;
extern	BYTE	_osmajor;
extern	BYTE	_osminor;
extern	BYTE	_ifsmgr;
extern	WORD	envseg;
extern	WORD	envlen;
#endif

#ifdef __f__
#define _A_NORMAL	0x80
#define _A_TEMPORARY	0x0100
#define _A_SPARSE_FILE	0x0200
#define _A_REPARSEPOINT 0x0400
#define _A_COMPRESSED	0x0800
#define _A_OFFLINE	0x1000
#define _A_NOT_INDEXED	0x2000
#define _A_ENCRYPTED	0x4000
#else
#define _A_NORMAL	0x00
#endif
#define _A_RDONLY	0x01
#define _A_HIDDEN	0x02
#define _A_SYSTEM	0x04
#define _A_VOLID	0x08
#define _A_SUBDIR	0x10
#define _A_ARCH		0x20

#ifdef __cplusplus
 extern "C" {
#endif

#define	 FP_OFF(__p) ((unsigned)(__p))

#ifdef __BORLANDC__
 #define MK_FP(s,o) ((void _seg *)(s)+(void near *)(o))
 #define FP_SEG(fp) ((unsigned)(void _seg *)(void far *)(fp))
#else
 #define MK_FP(s,o) (((unsigned short)(s)):>((void __near *)(o)))
 #define FP_SEG(p) ((unsigned)((unsigned long)(void __far*)(p) >> 16))
#endif

#ifndef _FFBLK_DEF
#define _FFBLK_DEF
typedef struct {
	char	reserved[21];
	char	ff_attrib;
	WORD	ff_ftime;
	WORD	ff_fdate;
	DWORD	ff_fsize;
	char	ff_name[13];
} ffblk;
#endif

typedef struct {
	WORD	time;
	WORD	date;
	DWORD	high;
      } FTIME;

typedef struct {
	DWORD	attrib;
	FTIME	time_create;
	FTIME	time_access;
	FTIME	time;
	DWORD	sizedx;
	DWORD	sizeax;
	char	reserved[8];
	char	name[260];
	char	shname[14];
      } wfblk;

#ifndef __f__
int	_CType findfirst(char *, ffblk *, int);
int	_CType findnext(ffblk *);
void	_CType beep(int __hz, int __time);
#endif
int	_CType wfindfirst(char *, wfblk *, unsigned);
int	_CType wfindnext(wfblk *, int __handle);
int	_CType wcloseff(int __handle);

int	_CType remove(char *__fn);
void	_CType delay(WORD __milliseconds);
int	_CType filexist(char *__f);
int	_CType _dos_setfileattr(char *, int);
int	_CType _dos_getfileattr(char *, int *);
int	_CType getfattr(char *__f);

/* return -1 on error */
int	_CType setftime(int __handle, FTIME *);
int	_CType getftime(int, FTIME *);
int	_CType setftime_create(int __handle, FTIME *);
int	_CType setftime_access(int __handle, FTIME *);
/* return OS error code on error */
int	_CType _dos_setftime(int __handle, int __date, int __time);
int	_CType _dos_getftime(int __handle, int *__date, int *__time);
int	_CType _dos_setftime_create(int __handle, int __date, int __time);
int	_CType _dos_setftime_access(int __handle, int __date, int __time);

/* 16-bit LFN only */
int	_CType wsetacdate(char *__file, int __date);
int	_CType wsetwrdate(char *__file, int __date, int __time);
int	_CType wsetcrdate(char *__file, int __date, int __time);
int	_CType wgetacdate(char *__file);
long	_CType wgetwrdate(char *__file);
long	_CType wgetcrdate(char *__file);

char *	_CType wlongname(char *__sp, char *__f);
char *	_CType wlongpath(char *__sp, char *__f);
char *	_CType wshortname(char *__sp);
char *	_CType wshortpath(char *__sp);

int	_CType wsetfattr(char *__file, int __attrib);
int	_CType wgetfattr(char *__file);
char *	_CType wgetcwd(char *, int);
char *	_CType wfullpath(char *, int);
int	_CType wvolinfo(char *__drive, char *__buf32);
int	_CType removefile(char *__file); /* clear attrib and remove */

#ifdef __cplusplus
 }
#endif
#endif
