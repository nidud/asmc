#ifndef __INC_STDIO
#define __INC_STDIO
#if !defined(__INC_DEFS)
 #include <defs.h>
#endif

#include <_nfile.h>

#ifdef __cplusplus
 extern "C" {
#endif

typedef void *	va_list;
#define __size(x)	((sizeof(x) + sizeof(int) - 1) & ~(sizeof(int) - 1))
#define va_start(ap,p)	((void)((ap) = (va_list)((char *)(&p) + __size(p))))
#define va_arg(ap,t)	(*(t *)(((*(char **)&(ap))+=__size(t))-(__size(t))))
#define va_end(ap)	((void)0)

#define _NSTREAM_	10

#define SEEK_CUR	1
#define SEEK_END	2
#define SEEK_SET	0

#define _MAXIOBUF	0x4000
#define _INTIOBUF	0x1000
#define _MINIOBUF	0x0200

#define _IOFBF		0x0000
#define _IOREAD		0x0001
#define _IOWRT		0x0002
#define _IONBF		0x0004
#define _IOMYBUF	0x0008
#define _IOEOF		0x0010
#define _IOERR		0x0020
#define _IOSTRG		0x0040
#define _IOLBF		0x0040
#define _IORW		0x0080
#define _IOYOURBUF	0x0100
#define _IOSETVBUF	0x0400
#define _IOFEOF		0x0800
#define _IOFLRTN	0x1000
#define _IOCTRLZ	0x2000
#define _IOCOMMIT	0x4000

#define _IOSTDIN	(_IOREAD | _IOYOURBUF)
#define _IOSTDOUT	(_IOWRT)
#define _IOSTDERR	(_IOWRT)
#define _IOSTDAUX	(_IORW)
#define _IOSTDPRN	(_IOWRT)

#define EOF		(-1)

typedef struct {
	unsigned char * bp;
	int		cnt;
	unsigned char * base;
	unsigned	flag;
	int		file;
	int		bufsize;
	int		charbuf;
      } FILE;
extern	FILE _iob[];

#define stdin	(&_iob[0])
#define stdout	(&_iob[1])
#define stderr	(&_iob[2])
#define stdaux	(&_iob[3])
#define stdpnr	(&_iob[4])

extern	char _bufin[];

FILE *	_CType fopen(char *, char *);
FILE *	_CType fsopen(char *, char *, int);
int	_CType fclose(FILE *);
int	_CType fgetc(FILE *);
int	_CType fputc(int, FILE *);
int	_CType fflush(FILE *);
int	_CType fseek(FILE *, long, int);
long	_CType ftell(FILE *);
size_t	_CType fread(void *, size_t, size_t, FILE *);
size_t	_CType fwrite(void *, size_t, size_t, FILE *);
void	_CType perror(char *);
int	_CType puts(char *);
int	_cdecl printf(char *, ...);
int	_cdecl fprintf(FILE *, char *, ...);
int	_cdecl fprinth(int, char *, ...);
char *	_CType fgets(char *, int, FILE *);
int	_CType fputs(char *, FILE *);
int	_cdecl sprintf(char *, char *, ...);
int	_CType vsprintf(char *, char *, va_list);
void	_CType setbuf(FILE *, char *__buf);
int	_CType setvbuf(FILE *, char *__buf, int __type, size_t __size);
int	_CType feof(FILE *);
int	_CType ferror(FILE *);

int	_CType remove(char *__filename);
int	_CType rename(char *, char *);
int	_CType osrename(char *, char *);

void	_CType _freebuf(FILE *);
void	_CType _getbuf(FILE *);
int	_CType _filebuf(FILE *);
int	_CType _output(FILE *, char *, va_list);
int	_CType _stbuf(FILE *);
void	_CType _ftbuf(int __flag, FILE *);
int	_CType _flsbuf(int, FILE *);
int	_CType _flushall(void);
int	_CType _fcloseall(void);
FILE *	_CType _getst(void);
void	_CType _exitbuf(void); /* Free buffer for stdout and stderr */

#define _getc_lk(s) (--(s)->cnt >= 0 ? 0xFF & *(s)->bp++ : _filebuf(s))
#define _putc_lk(c,s)\
    (--(s)->cnt >= 0 ? (*(s)->bp++ = (char)(c)) : _flsbuf((c),(s)))
#define _ungetc_lc(s)\
    (++(s)->cnt < (s)->bufsize ? (s)->bp-- : (s)->cnt--)

#define inuse(s)	((s)->flag & (_IOREAD|_IOWRT|_IORW))
#define mbuf(s)		((s)->flag & _IOMYBUF)
#define nbuf(s)		((s)->flag & _IONBF)
#define ybuf(s)		((s)->flag & _IOYOURBUF)
#define bigbuf(s)	((s)->flag & (_IOMYBUF|_IOYOURBUF))
#define anybuf(s)	((s)->flag & (_IOMYBUF|_IONBF|_IOYOURBUF))

#define _fileno(s)	((s)->file)
#define _lastiob	&_iob[_NSTREAM_ - 1]

#ifdef __cplusplus
 }
#endif
#endif
