ifndef __LIBC_INC
 include libc.inc
endif
ifndef _WINCON_
 include wincon.inc
endif
ifndef _WINUSER_
 include winuser.inc
endif
.xlist

ifndef __INC_CONIO
__INC_CONIO	EQU 1

ifdef __PE__
option	dllimport:<msvcrt>
endif

ifdef _CONIO_RETRO_COLORS
BLACK		equ 0
BLUE		equ 1
GREEN		equ 2
CYAN		equ 3
RED		equ 4
MAGENTA		equ 5
BROWN		equ 6
LIGHTGRAY	equ 7
DARKGRAY	equ 8
LIGHTBLUE	equ 9
LIGHTGREEN	equ 10
LIGHTCYAN	equ 11
LIGHTRED	equ 12
LIGHTMAGENTA	equ 13
YELLOW		equ 14
WHITE		equ 15
endif
MAXINPUTRECORDS equ 100

_cgets		proto :LPSTR
_clreol		proto
_clrscr		proto
_cprintf	proto _CDecl :LPSTR, :VARARG
_cputs		proto :LPSTR
_cscanf		proto _CDecl :LPSTR, :VARARG
_getch		proto
_getche		proto
_gotoxy		proto :UINT, :UINT
_inp		proto :UINT
_inpw		proto :UINT
_inpd		proto :UINT
_kbhit		proto
_outp		proto :UINT, :UINT
_outpw		proto :UINT, :UINT
_outpd		proto :UINT, :ULONG
_putch		proto :UINT
_textbackground proto :UINT
_textcolor	proto :UINT
_ungetch	proto :UINT
_wherex		proto
_wherey		proto

_cputws		proto :LPWSTR
_putwch		proto :UINT ; WCHAR_T
_getwch		proto
_getwche	proto
_cgetws		proto :LPWSTR, :SIZE_T, :PVOID
_ungetwch	proto :UINT
_cputws		proto :LPWSTR
_cwprintf	proto _CDecl :LPWSTR, :VARARG
_cwscanf	proto _CDecl :LPWSTR, :VARARG
_vcwprintf	proto :LPWSTR, :PVOID

;;;;;;;;;;;;;;; crtl
ifndef __PE__
externdef hStdInput:  HANDLE
externdef hStdOutput: HANDLE
externdef hStdError:  HANDLE
endif
endif	; __INC_CONIO

.list
