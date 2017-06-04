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

#define _LEADBYTE	0x8000
#define _ALPHA		(0x0100|_UPPER|_LOWER)

extern unsigned short _ctype[]; /* Character type array */

#ifdef __cplusplus
 extern "C" {
#endif

#ifndef _CTYPE_DEFINED

_CRTIMP int __cdecl isalnum (int __c);
_CRTIMP int __cdecl isalpha (int __c);
_CRTIMP int __cdecl isascii (int __c);
_CRTIMP int __cdecl iscntrl (int __c);
_CRTIMP int __cdecl isdigit (int __c);
_CRTIMP int __cdecl isgraph (int __c);
_CRTIMP int __cdecl islower (int __c);
_CRTIMP int __cdecl isprint (int __c);
_CRTIMP int __cdecl ispunct (int __c);
_CRTIMP int __cdecl isspace (int __c);
_CRTIMP int __cdecl isupper (int __c);
_CRTIMP int __cdecl isxdigit(int __c);
_CRTIMP int __cdecl tolower (int __c);
_CRTIMP int __cdecl toupper (int __c);

_CRTIMP int __cdecl _isctype(int, int);
_CRTIMP int __cdecl _tolower(int);
_CRTIMP int __cdecl _toupper(int);
_CRTIMP int __cdecl __isascii(int);
_CRTIMP int __cdecl __toascii(int);
_CRTIMP int __cdecl __iscsymf(int);
_CRTIMP int __cdecl __iscsym(int);
#define _CTYPE_DEFINED
#endif

#ifndef _WCTYPE_DEFINED

_CRTIMP int __cdecl iswalpha(wint_t);
_CRTIMP int __cdecl iswupper(wint_t);
_CRTIMP int __cdecl iswlower(wint_t);
_CRTIMP int __cdecl iswdigit(wint_t);
_CRTIMP int __cdecl iswxdigit(wint_t);
_CRTIMP int __cdecl iswspace(wint_t);
_CRTIMP int __cdecl iswpunct(wint_t);
_CRTIMP int __cdecl iswalnum(wint_t);
_CRTIMP int __cdecl iswprint(wint_t);
_CRTIMP int __cdecl iswgraph(wint_t);
_CRTIMP int __cdecl iswcntrl(wint_t);
_CRTIMP int __cdecl iswascii(wint_t);
_CRTIMP int __cdecl isleadbyte(int);
_CRTIMP wchar_t __cdecl towupper(wchar_t);
_CRTIMP wchar_t __cdecl towlower(wchar_t);
_CRTIMP int __cdecl iswctype(wint_t, wctype_t);

#define _WCTYPE_DEFINED
#endif

#ifdef __cplusplus
 }
#endif

#define isalnum(c)  (_ctype[(unsigned char)(c) + 1] & (_DIGIT | _UPPER | _LOWER))
#define isalpha(c)  (_ctype[(unsigned char)(c) + 1] & (_UPPER | _LOWER))
#define isascii(c)  ((unsigned char)(c) < 128)
#define iscntrl(c)  (_ctype[(unsigned char)(c) + 1] & _CONTROL)
#define isdigit(c)  (_ctype[(unsigned char)(c) + 1] & _DIGIT)
#define isgraph(c)  ((unsigned char)(c) >= 0x21 && (unsigned char)(c) <= 0x7e)
#define islower(c)  (_ctype[(unsigned char)(c) + 1] & _LOWER)
#define isprint(c)  ((unsigned char)(c) >= 0x20 && (unsigned char)(c) <= 0x7e)
#define ispunct(c)  (_ctype[(unsigned char)(c) + 1] & _PUNCT)
#define isspace(c)  (_ctype[(unsigned char)(c) + 1] & _SPACE)
#define isupper(c)  (_ctype[(unsigned char)(c) + 1] & _UPPER)
#define isxdigit(c) (_ctype[(unsigned char)(c) + 1] & _HEX)

#define _tolower(_c)	((_c)-'A'+'a')
#define _toupper(_c)	((_c)-'a'+'A')

#define __isascii(_c)	( (unsigned)(_c) < 0x80 )
#define __toascii(_c)	( (_c) & 0x7f )

#ifndef _WCTYPE_INLINE_DEFINED
#ifndef __cplusplus
#define iswalpha(_c)	( iswctype(_c,_ALPHA) )
#define iswupper(_c)	( iswctype(_c,_UPPER) )
#define iswlower(_c)	( iswctype(_c,_LOWER) )
#define iswdigit(_c)	( iswctype(_c,_DIGIT) )
#define iswxdigit(_c)	( iswctype(_c,_HEX) )
#define iswspace(_c)	( iswctype(_c,_SPACE) )
#define iswpunct(_c)	( iswctype(_c,_PUNCT) )
#define iswalnum(_c)	( iswctype(_c,_ALPHA|_DIGIT) )
#define iswprint(_c)	( iswctype(_c,_BLANK|_PUNCT|_ALPHA|_DIGIT) )
#define iswgraph(_c)	( iswctype(_c,_PUNCT|_ALPHA|_DIGIT) )
#define iswcntrl(_c)	( iswctype(_c,_CONTROL) )
#define iswascii(_c)	( (unsigned)(_c) < 0x80 )
#define isleadbyte(_c)	(_pctype[(unsigned char)(_c)] & _LEADBYTE)
#endif	/* __cplusplus */
#define _WCTYPE_INLINE_DEFINED
#endif	/* _WCTYPE_INLINE_DEFINED */
#endif /* __INC_CTYPE */
