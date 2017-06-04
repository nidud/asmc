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

#ifdef __cplusplus
 extern "C" {
#endif

#define _tolower(_c)	((_c)-'A'+'a')
#define _toupper(_c)	((_c)-'a'+'A')

int _fastcall ftolower(char __ch);
int _fastcall ftoupper(char __ch);

int _CType tolower(int __ch);
int _CType toupper(int __ch);

#ifdef __cplusplus
 }
#endif
#endif /* __INC_CTYPE */
