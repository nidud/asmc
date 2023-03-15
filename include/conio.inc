.pragma list(push, 0)
ifndef __INC_CONIO
define __INC_CONIO
ifndef __LIBC_INC
 include libc.inc
endif
ifndef _WINCON_
 include wincon.inc
endif
ifndef _WINUSER_
 include winuser.inc
endif
.pragma comment(lib, libc, msvcrt)

if defined(_CONIO_RETRO_COLORS) or defined(__TWINDOW_INC)
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

_cgets		proto __cdecl :LPSTR
_clreol		proto __cdecl
_clrscr		proto __cdecl
_cprintf	proto _CDecl :LPSTR, :VARARG
_cputs		proto __cdecl :LPSTR
_cscanf		proto _CDecl :LPSTR, :VARARG
_getch		proto __cdecl
_getche		proto __cdecl
_gotoxy		proto __cdecl :UINT, :UINT
ifdef _M_IX86
_inp		proto __cdecl :UINT
_inpw		proto __cdecl :UINT
_inpd		proto __cdecl :UINT
endif
_kbhit		proto __cdecl
ifdef _M_IX86
_outp		proto __cdecl :UINT, :UINT
_outpw		proto __cdecl :UINT, :UINT
_outpd		proto __cdecl :UINT, :ULONG
endif
_putch		proto __cdecl :UINT
_putch_nolock	proto __cdecl :UINT
_textbackground proto __cdecl :UINT
_textcolor	proto __cdecl :UINT
_ungetch	proto __cdecl :UINT
_wherex		proto __cdecl
_wherey		proto __cdecl

_cputws		proto __cdecl :LPWSTR
_putwch		proto __cdecl :UINT ; WCHAR_T
_putwch_nolock	proto __cdecl :UINT
_getwch		proto __cdecl
_getwche	proto __cdecl
_cgetws		proto __cdecl :LPWSTR, :SIZE_T, :PVOID
_ungetwch	proto __cdecl :UINT
_cputws		proto __cdecl :LPWSTR
_cwprintf	proto _CDecl :LPWSTR, :VARARG
_cwscanf	proto _CDecl :LPWSTR, :VARARG
_vcwprintf	proto __cdecl :LPWSTR, :PVOID

ifdef _UNICODE
_tcgets		equ <_cgetws>
_tcprintf	equ <_cwprintf>
_tcputs		equ <_cputws>
_tcscanf	equ <_cwscanf>
_tgetch		equ <_getwch>
_tgetche	equ <_getwche>
_tputch		equ <_putwch>
else
_tcgets		equ <_cgets>
_tcprintf	equ <_cprintf>
_tcputs		equ <_cputs>
_tcscanf	equ <_cscanf>
_tgetch		equ <_getch>
_tgetche	equ <_getche>
_tputch		equ <_putch>
endif

;;;;;;;;;;;;;;; crtl

ifndef _INTPTR_T_DEFINED
define _INTPTR_T_DEFINED
ifdef _WIN64
intptr_t typedef sqword
else
intptr_t typedef sdword
endif
endif

if not defined(_MSVCRT) or defined(_CRTBLD)

__initconin  proto __cdecl
__termconin  proto __cdecl
__initconout proto __cdecl
__termconout proto __cdecl

externdef _confh:intptr_t
externdef _coninpfh:intptr_t

ifndef TRECT

MAXSCRLINE  equ 256 ; max screen size

TRECT	    STRUC
x	    db ?
y	    db ?
col	    db ?
row	    db ?
TRECT	    ENDS

MTRECT macro x, y, col, row
    exitm<(x or (y shl 8) or (col shl 16) or (row shl 24 ))>
    endm

endif

_getxya	  proto __cdecl :int_t, :int_t
_getxyc	  proto __cdecl :int_t, :int_t
_getxyw	  proto __cdecl :int_t, :int_t
_scputa	  proto __cdecl :int_t, :int_t, :int_t, :uchar_t
_scputfg  proto __cdecl :int_t, :int_t, :int_t, :uchar_t
_scputbg  proto __cdecl :int_t, :int_t, :int_t, :uchar_t
_scputc	  proto __cdecl :int_t, :int_t, :int_t, :char_t
_scputw	  proto __cdecl :int_t, :int_t, :int_t, :ushort_t
_scputs	  proto __cdecl :int_t, :int_t, :string_t
_scputf	  proto _CDecl	:int_t, :int_t, :string_t, :vararg
_scpath	  proto __cdecl :int_t, :int_t, :int_t, :string_t
_scenter  proto __cdecl :int_t, :int_t, :int_t, :string_t

_scread	  proto __cdecl :TRECT, :PCHAR_INFO
_scwrite  proto __cdecl :TRECT, :PCHAR_INFO
_scxchg	  proto __cdecl :TRECT, :PCHAR_INFO
_screadl  proto __cdecl :int_t, :int_t, :int_t
_scwritel proto __cdecl :int_t, :int_t, :int_t, :PCHAR_INFO
_scmovel  proto __cdecl :TRECT, :PCHAR_INFO
_scmover  proto __cdecl :TRECT, :PCHAR_INFO
_scmoveu  proto __cdecl :TRECT, :PCHAR_INFO
_scmoved  proto __cdecl :TRECT, :PCHAR_INFO

endif

endif
.pragma list(pop)
