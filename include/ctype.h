#ifndef __INC_CTYPE
#define __INC_CTYPE
#if !defined(__INC_DEFS)
 #include <defs.h>
#endif

#define _UPPER		0x01
#define _LOWER		0x02
#define _DIGIT		0x04
#define _SPACE		0x08
#define _PUNCT		0x10
#define _CONTROL	0x20
#define _BLANK		0x40
#define _HEX		0x80

extern unsigned char __ctype[]; /* Character type array */

#ifdef __cplusplus
 extern "C" {
#endif

int _CType isalnum (int __c);
int _CType isalpha (int __c);
int _CType isascii (int __c);
int _CType iscntrl (int __c);
int _CType isdigit (int __c);
int _CType isgraph (int __c);
int _CType islower (int __c);
int _CType isprint (int __c);
int _CType ispunct (int __c);
int _CType isspace (int __c);
int _CType isupper (int __c);
int _CType isxdigit(int __c);
int _CType tolower (int __c);
int _CType toupper (int __c);

#ifdef __cplusplus
 }
#endif

#define isalnum(c)  (__ctype[(unsigned char)(c) + 1] & (_DIGIT | _UPPER | _LOWER))
#define isalpha(c)  (__ctype[(unsigned char)(c) + 1] & (_UPPER | _LOWER))
#define isascii(c)  ((unsigned char)(c) < 128)
#define iscntrl(c)  (__ctype[(unsigned char)(c) + 1] & _CONTROL)
#define isdigit(c)  (__ctype[(unsigned char)(c) + 1] & _DIGIT)
#define isgraph(c)  ((unsigned char)(c) >= 0x21 && (unsigned char)(c) <= 0x7e)
#define islower(c)  (__ctype[(unsigned char)(c) + 1] & _LOWER)
#define isprint(c)  ((unsigned char)(c) >= 0x20 && (unsigned char)(c) <= 0x7e)
#define ispunct(c)  (__ctype[(unsigned char)(c) + 1] & _PUNCT)
#define isspace(c)  (__ctype[(unsigned char)(c) + 1] & _SPACE)
#define isupper(c)  (__ctype[(unsigned char)(c) + 1] & _UPPER)
#define isxdigit(c) (__ctype[(unsigned char)(c) + 1] & (_DIGIT | _HEX))

#endif /* __INC_CTYPE */
