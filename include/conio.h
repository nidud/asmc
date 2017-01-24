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

_CRTIMP char *	_CType _cgets(char *);
_CRTIMP void	_CType _clreol(void);
_CRTIMP void	_CType _clrscr(void);
_CRTIMP int	_CType _cputs(const char *);
_CRTIMP int	_CType _getch(void);
_CRTIMP int	_CType _getche(void);
_CRTIMP void	_CType _gotoxy(int, int);
_CRTIMP int	_CType _inp(unsigned short);
_CRTIMP WORD	_CType _inpw(unsigned short);
_CRTIMP DWORD	_CType _inpd(unsigned short);
_CRTIMP int	_CType _kbhit(void);
_CRTIMP int	_CType _outp(unsigned short, int);
_CRTIMP WORD	_CType _outpw(unsigned short, unsigned short);
_CRTIMP DWORD	_CType _outpd(unsigned short, unsigned long);
_CRTIMP int	_CType _putch(int);
_CRTIMP wint_t	_CType _putwch(wchar_t);
_CRTIMP void	_CType _textbackground(int);
_CRTIMP void	_CType _textcolor(int);
_CRTIMP int	_CType _ungetch(int);
_CRTIMP int	_CType _wherex(void);
_CRTIMP int	_CType _wherey(void);

#ifdef __cplusplus
 }
#endif
#endif
