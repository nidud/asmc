#ifndef __INC_CONIO
#define __INC_CONIO
#if !defined(__INC_DEFS)
 #include <defs.h>
#endif

#ifdef __cplusplus
 extern "C" {
#endif

#ifndef _WCHAR_T_DEFINED
#define _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#endif

#ifndef _WINT_T_DEFINED
#define _WINT_T_DEFINED
typedef unsigned short wint_t;
#endif

#ifdef _CONIO_RETRO_COLORS
#define BLACK  0
#define BLUE  1
#define GREEN  2
#define CYAN  3
#define RED  4
#define MAGENTA	 5
#define BROWN  6
#define LIGHTGRAY  7
#define DARKGRAY  8
#define LIGHTBLUE  9
#define LIGHTGREEN  10
#define LIGHTCYAN  11
#define LIGHTRED  12
#define LIGHTMAGENTA  13
#define YELLOW	14
#define WHITE  15
#endif

_CRTIMP char * __cdecl _cgets(char *);
_CRTIMP void __cdecl _clreol(void);
_CRTIMP void __cdecl _clrscr(void);
_CRTIMP int __cdecl _cputs(const char *);
_CRTIMP int __cdecl _getch(void);
_CRTIMP int __cdecl _getche(void);
_CRTIMP void __cdecl _gotoxy(int, int);
_CRTIMP int __cdecl _inp(unsigned short);
_CRTIMP unsigned short __cdecl _inpw(unsigned short);
_CRTIMP unsigned long __cdecl _inpd(unsigned short);
_CRTIMP int __cdecl _kbhit(void);
_CRTIMP int __cdecl _outp(unsigned short, int);
_CRTIMP unsigned short	__cdecl _outpw(unsigned short, unsigned short);
_CRTIMP unsigned long __cdecl _outpd(unsigned short, unsigned long);
_CRTIMP int __cdecl _putch(int);
_CRTIMP wint_t __cdecl _putwch(wchar_t);
_CRTIMP void __cdecl _textbackground(int);
_CRTIMP void __cdecl _textcolor(int);
_CRTIMP int __cdecl _ungetch(int);
_CRTIMP int __cdecl _wherex(void);
_CRTIMP int __cdecl _wherey(void);

#ifdef __cplusplus
 }
#endif
#endif
