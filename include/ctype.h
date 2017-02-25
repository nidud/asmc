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

_CRTIMP int _CType isalnum (int __c);
_CRTIMP int _CType isalpha (int __c);
_CRTIMP int _CType isascii (int __c);
_CRTIMP int _CType iscntrl (int __c);
_CRTIMP int _CType isdigit (int __c);
_CRTIMP int _CType isgraph (int __c);
_CRTIMP int _CType islower (int __c);
_CRTIMP int _CType isprint (int __c);
_CRTIMP int _CType ispunct (int __c);
_CRTIMP int _CType isspace (int __c);
_CRTIMP int _CType isupper (int __c);
_CRTIMP int _CType isxdigit(int __c);
_CRTIMP int _CType tolower (int __c);
_CRTIMP int _CType toupper (int __c);

_CRTIMP int _CType _isctype(int, int);
_CRTIMP int _CType _tolower(int);
_CRTIMP int _CType _toupper(int);
_CRTIMP int _CType __isascii(int);
_CRTIMP int _CType __toascii(int);
_CRTIMP int _CType __iscsymf(int);
_CRTIMP int _CType __iscsym(int);
#define _CTYPE_DEFINED
#endif

#ifndef _WCTYPE_DEFINED

_CRTIMP int _CType iswalpha(wint_t);
_CRTIMP int _CType iswupper(wint_t);
_CRTIMP int _CType iswlower(wint_t);
_CRTIMP int _CType iswdigit(wint_t);
_CRTIMP int _CType iswxdigit(wint_t);
_CRTIMP int _CType iswspace(wint_t);
_CRTIMP int _CType iswpunct(wint_t);
_CRTIMP int _CType iswalnum(wint_t);
_CRTIMP int _CType iswprint(wint_t);
_CRTIMP int _CType iswgraph(wint_t);
_CRTIMP int _CType iswcntrl(wint_t);
_CRTIMP int _CType iswascii(wint_t);
_CRTIMP int _CType isleadbyte(int);
_CRTIMP wchar_t _CType towupper(wchar_t);
_CRTIMP wchar_t _CType towlower(wchar_t);
_CRTIMP int _CType iswctype(wint_t, wctype_t);

#define _WCTYPE_DEFINED
#endif

#ifdef __cplusplus
 }
#endif

#define isalnum(c)  ((unsigned char)_ctype[(unsigned char)(c) + 1] & (_DIGIT | _UPPER | _LOWER))
#define isalpha(c)  ((unsigned char)_ctype[(unsigned char)(c) + 1] & (_UPPER | _LOWER))
#define isascii(c)  ((unsigned char)(c) < 128)
#define iscntrl(c)  ((unsigned char)_ctype[(unsigned char)(c) + 1] & _CONTROL)
#define isdigit(c)  ((unsigned char)_ctype[(unsigned char)(c) + 1] & _DIGIT)
#define isgraph(c)  ((unsigned char)(c) >= 0x21 && (unsigned char)(c) <= 0x7e)
#define islower(c)  ((unsigned char)_ctype[(unsigned char)(c) + 1] & _LOWER)
#define isprint(c)  ((unsigned char)(c) >= 0x20 && (unsigned char)(c) <= 0x7e)
#define ispunct(c)  ((unsigned char)_ctype[(unsigned char)(c) + 1] & _PUNCT)
#define isspace(c)  ((unsigned char)_ctype[(unsigned char)(c) + 1] & _SPACE)
#define isupper(c)  ((unsigned char)_ctype[(unsigned char)(c) + 1] & _UPPER)
#define isxdigit(c) ((unsigned char)_ctype[(unsigned char)(c) + 1] & (_DIGIT | _HEX))

#define _tolower(_c)	( (_c)-'A'+'a' )
#define _toupper(_c)	( (_c)-'a'+'A' )

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
