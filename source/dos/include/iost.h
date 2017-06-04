#ifndef __INC_IOST
#define __INC_IOST
#if !defined(__INC_DEFS)
 #include <defs.h>
#endif

#define SEEK_CUR	1
#define SEEK_END	2
#define SEEK_SET	0

#define ISIZE		0x8000
#define OSIZE		0x8000

#define IO_SEARCHCASE	0x0001	/* Case sensitive search	*/
#define IO_SEARCHHEX	0x0002	/* Search hex string/ascii	*/
#define IO_SEARCHSET	0x0004	/* Search entire scope		*/
#define IO_SEARCHCUR	0x0008	/* Search from cursor/set	*/
#define IO_SEARCHMASK	0x000F
#define IO_SEARCHSUB	0x0020
#define IO_STRINGB	0x0080	/* String buffer		*/
#define IO_CRYPT	0x0100	/* Crypted file			*/
#define IO_USEUPD	0x0200	/* Progress			*/
#define IO_UPDTOTAL	0x0400	/* Add Read/Write size to total */
#define IO_USECRC	0x0800	/* Update CRC on read/write	*/
#define IO_USEBITS	0x1000	/* Align bits on read/write	*/
#define IO_CLIPBOARD	0x2000	/* Flush to clipboard		*/
#define IO_MEMREAD	0x4000	/* Read from memory		*/
#define IO_ERROR	0x8000	/* Write fault			*/

#ifdef __cplusplus
 extern "C" {
#endif

typedef struct IOBS {
	unsigned char * bp;	/* buffer */
	unsigned int	i;	/* index in buffer */
	unsigned int	c;	/* byte count */
	unsigned int	bsize;	/* alloc size */
	unsigned int	flag;
	int		file;
	int		l;	/* number of bits in bit buffer */
	unsigned long	bb;	/* bit buffer | CRC value */
	unsigned long	total;	/* total bytes in/out | filesize */
	unsigned long	offs;	/* file offset | loop count */
	int (*flush)(struct IOBS *);
      } IOST;

extern	IOST _CType STDI;
extern	IOST _CType STDO;

#define OSTDI	((WORD)&STDI)
#define OSTDO	((WORD)&STDO)
/*
int _fastcall oinitst(int __offset_stream);
int _fastcall ofreest(int __offset_stream);
int _fastcall oclose(int __offset_stream);
int _fastcall oputc(int __c);
*/
int _CType openfile(char *, int __mode, int __action);
int _CType ogetouth(char *);
int _CType oopen(char *, int __mode);
int _CType ofread(void);
int _CType oflush(void);
//int _CType cputc(int);
//int _CType ogetc(void);
int _CType ogetb(void);
int _CType oputb(int __bits, int __count);
int _CType oseek(long, int);
int _CType oseekl(long, int);
int _CType oungetc(void);

char * _CType iopens(char *, int __size);
char * _CType oopens(char *, int __size);

/* Unicode */
int _CType uopen(char *, int __mode);
int _CType ugetc(void); /* -1 */
int _CType uputc(int __c); /* -1 */
int _cdecl uprintf(char *, ...);
int _CType uclose(IOST *);

#ifdef __cplusplus
 }
#endif
#endif
