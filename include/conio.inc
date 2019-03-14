.pragma list(push, 0)
ifndef __INC_CONIO
__INC_CONIO equ <>
ifndef __LIBC_INC
 include libc.inc
endif
ifndef _WINCON_
 include wincon.inc
endif
ifndef _WINUSER_
 include winuser.inc
endif
ifdef __PE__
option	dllimport:<msvcrt>
else
includelib libc.lib
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

;;;;;;;;;;;;;;; crtl

ifndef _INTPTR_T_DEFINED
_INTPTR_T_DEFINED equ <>
ifdef _WIN64
intptr_t typedef sqword
else
intptr_t typedef sdword
endif
endif

ifndef __PE__
externdef hStdInput:  HANDLE
externdef hStdOutput: HANDLE
externdef hStdError:  HANDLE

__initconout proto
__termconout proto
externdef _confh:intptr_t

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

endif

endif
.pragma list(pop)
