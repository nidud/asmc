#ifndef __INC_IO
#define __INC_IO
#if !defined(__INC_DEFS)
 #include <defs.h>
#endif
#if !defined(_NFILE_)
 #include <_nfile.h>
#endif

#define SEEK_CUR    1
#define SEEK_END    2
#define SEEK_SET    0

#define _A_RDONLY	0x01
#define _A_HIDDEN	0x02
#define _A_SYSTEM	0x04
#define _A_VOLID	0x08
#define _A_SUBDIR	0x10
#define _A_ARCH		0x20
#define _A_NORMAL	0x80

#define _A_TEMPORARY	0x0100
#define _A_SPARSE_FILE	0x0200
#define _A_DELETE	0x0400
#define _A_REPARSEPOINT 0x0400
#define _A_SEQSCAN	0x0800
#define _A_COMPRESSED	0x0800
#define _A_RANDOM	0x1000
#define _A_OFFLINE	0x1000
#define _A_NOT_INDEXED	0x2000
#define _A_ENCRYPTED	0x4000

#define FH_OPEN		0x01
#define FH_EOF		0x02
#define FH_CRLF		0x04
#define FH_PIPE		0x08
#define FH_APPEND	0x20
#define FH_DEVICE	0x40
#define FH_TEXT		0x80
#define FH_INVALID	0xFF

#define A_CREATE	1 /* fails if exists */
#define A_CREATETRUNC	2 /* trunc if exists */
#define A_OPEN		3 /* fails if not exists */
#define A_OPENCREATE	4 /* open if exists or create */
#define A_TRUNC		5 /* fails if not exists */

#define M_RDONLY	0x80000000
#define M_WRONLY	0x40000000
#define M_RDWR		(M_RDONLY | M_WRONLY)

#define SHARE_READ	1
#define SHARE_WRITE	2
#define GENERIC_WRITE	M_WRONLY
#define GENERIC_READ	M_RDONLY

#define DEV_UNKNOWN	0x0000
#define DEV_DISK	0x0001
#define DEV_CHAR	0x0002
#define DEV_PIPE	0x0003
#define DEV_REMOTE	0x8000

#define _MINIOBUF	0x0200
#define _INTIOBUF	0x1000
#define _MAXIOBUF	0x4000

#ifdef __cplusplus
 extern "C" {
#endif

extern int _nfile;
extern int _umaskval;
extern BYTE _osfile[_NFILE_];

struct _finddata_t {
	unsigned attrib;
	time_t	time_create;
	time_t	time_access;
	time_t	time_write;
	size_t	size;
	char	name[260];
      };

struct _wfinddata_t {
	unsigned attrib;
	time_t	time_create;
	time_t	time_access;
	time_t	time_write;
	size_t	size;
	wchar_t name[260];
      };

int _CType _access(const char *, int);
int _CType _chmod(const char *, int);
int _CType _chsize(int, long);
int _CType _close(int);
int _CType _commit(int);
int _CType _creat(const char *, int);
int _CType _dup(int);
int _CType _dup2(int);
int _CType _eof(int);
long _CType _filelength(int);
long _CType _findfirst(char *, struct _finddata_t *);
int _CType _findnext(long, struct _finddata_t *);
int _CType _findclose(long);
int _CType _isatty(int);
long _CType _lseek(int, long, int);
char *_CType _mktemp(char *);
int _CDecl _open(const char *, int, ...);
int _CType _pipe(int *, unsigned int, int);
int _CType _read(int, void *, unsigned);
int _CType remove(const char *);
int _CType rename(const char *, const char *);
int _CType _setmode(int, int);
int _CDecl _sopen(const char *, int, int, ...);
long _CType _tell(int);
int _CType _umask(int);
int _CType _unlink(const char *);
int _CType _write(int, const void *, unsigned int);

int _CType getosfhnd(int);
int _CType osopen(const char *, int, int, int);
int _CType osread(int, void *, unsigned);
int _CType oswrite(int, const void *, unsigned);

#if !__STDC__
#define access _access
#define chmod _chmod
#define chsize _chsize
#define close _close
#define creat _creat
#define dup _dup
#define dup2 _dup2
#define eof _eof
#define filelength _filelength
#define isatty _isatty
#define lseek _lseek
#define mktemp _mktemp
#define open _open
#define read _read
#define setmode _setmode
#define sopen _sopen
#define tell _tell
#define umask _umask
#define unlink _unlink
#define write _write
#endif

#ifdef __cplusplus
 }
#endif
#endif
