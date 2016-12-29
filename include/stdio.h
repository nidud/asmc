#ifndef __INC_STDIO
#define __INC_STDIO
#if !defined(__INC_DEFS)
 #include <defs.h>
#endif

#include <_nfile.h>

#ifdef __cplusplus
 extern "C" {
#endif

#define _NSTREAM_	10
#define FILENAME_MAX	260

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

#ifndef _FILE_DEFINED
struct _iobuf {
	char *_ptr;
	int   _cnt;
	char *_base;
	int   _flag;
	int   _file;
	int   _charbuf;
	int   _bufsiz;
	char *_tmpfname;
	};
typedef struct _iobuf FILE;
#define _FILE_DEFINED
#endif

extern	FILE _iob[];
#define __iob _iob
#define stdin	(&_iob[0])
#define stdout	(&_iob[1])
#define stderr	(&_iob[2])

extern	char _bufin[];

#ifndef _STDIO_DEFINED

_CRTIMP int _CType _filbuf(FILE *);
_CRTIMP int _CType _flsbuf(int, FILE *);
_CRTIMP int _CType feof(FILE *);
_CRTIMP int _CType fflush(FILE *);
_CRTIMP int _CType fgetc(FILE *);
_CRTIMP char * _CType fgets(char *, int, FILE *);
_CRTIMP FILE * _CType fopen(const char *, const char *);
_CRTIMP int _CDecl fprintf(FILE *, const char *, ...);
_CRTIMP int _CType fputc(int, FILE *);
_CRTIMP int _CType fputs(char *, FILE *);
_CRTIMP size_t _CType fread(void *, size_t, size_t, FILE *);
_CRTIMP int _CType fseek(FILE *, long, int);
_CRTIMP int _CType ftell(FILE *);
_CRTIMP size_t _CType fwrite(const void *, size_t, size_t, FILE *);
_CRTIMP void _CType perror(char *);
_CRTIMP int _CDecl printf(const char *, ...);
_CRTIMP int _CType puts(char *);
_CRTIMP int _CType remove(const char *);
_CRTIMP int _CType rename(const char *, const char *);
_CRTIMP void _CType rewind(FILE *);
_CRTIMP void _CType setbuf(FILE *, char *);
_CRTIMP int _CType setvbuf(FILE *, char *, int, size_t);
_CRTIMP int _CDecl sprintf(char *, const char *, ...);
_CRTIMP int _CType vfprintf(FILE *, const char *, va_list);
_CRTIMP int _CType vsprintf(char *, const char *, va_list);
_CRTIMP int _CType fclose(FILE *);
_CRTIMP int _CType _output(FILE *, char *, va_list);
_CRTIMP int _CType _stbuf(FILE *);
_CRTIMP void _CType _ftbuf(int __flag, FILE *);

#endif	/* _STDIO_DEFINED */

FILE * _CType _getst(void);
int _CDecl _print(const char *, ...);
int _CDecl ftobufin(const char *, ...);

#define feof(s)		((s)->_flag & _IOEOF)
#define ferror(s)	((s)->_flag & _IOERR)
#define _fileno(s)	((s)->_file)
#define _lastiob	&_iob[_NSTREAM_ - 1]

#define getc(s)		(--(s)->_cnt >= 0 ? 0xFF & *(s)->_ptr++ : _filbuf(s))
#define putc(c,s)	(--(s)->_cnt >= 0 ? 0xFF & (*(s)->_ptr++ = (char)(c)) : _flsbuf((c),(s)))
#define getchar()	getc(stdin)
#define putchar(c)	putc((c),stdout)

#ifdef	_MT
#undef	getc
#undef	putc
#undef	getchar
#undef	putchar
#endif

#define inuse(s)	((s)->_flag & (_IOREAD|_IOWRT|_IORW))
#define mbuf(s)		((s)->_flag & _IOMYBUF)
#define nbuf(s)		((s)->_flag & _IONBF)
#define ybuf(s)		((s)->_flag & _IOYOURBUF)
#define bigbuf(s)	((s)->_flag & (_IOMYBUF|_IOYOURBUF))
#define anybuf(s)	((s)->_flag & (_IOMYBUF|_IONBF|_IOYOURBUF))

#ifdef __cplusplus
 }
#endif
#endif
