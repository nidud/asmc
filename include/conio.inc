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
_cprintf	proto __Cdecl :LPSTR, :VARARG
_cputs		proto __cdecl :LPSTR
_cscanf		proto __Cdecl :LPSTR, :VARARG
_getch		proto __cdecl
_getch_nolock	proto __cdecl
_getche		proto __cdecl
_getche_nolock	proto __cdecl
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
_putch		proto __cdecl :int_t
_putch_nolock	proto __cdecl :int_t
_textbackground proto __cdecl :UINT
_textcolor	proto __cdecl :UINT
_ungetch	proto __cdecl :int_t
_wherex		proto __cdecl
_wherey		proto __cdecl

_cputws		proto __cdecl :LPWSTR
_putwch		proto __cdecl :wchar_t
_putwch_nolock	proto __cdecl :wchar_t
_getwch		proto __cdecl
_getwche	proto __cdecl
_cgetws		proto __cdecl :LPWSTR, :SIZE_T, :PVOID
_ungetwch	proto __cdecl :UINT
_cputws		proto __cdecl :LPWSTR
_cwprintf	proto __Cdecl :LPWSTR, :VARARG
_cwscanf	proto __Cdecl :LPWSTR, :VARARG
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

define MAXSCRLINE	256	; max screen size
define CURSOR_NORMAL	16	; default cursor size (0..100)

;
; https://learn.microsoft.com/en-us/windows/win32/inputdev/wm-char
;
; lParam
;
;  0-15 Virtual Key Code (Win: Repeat Count)
; 16-23 Virtual Scan Code
;    24 Extended ( KF_EXTENDED << 16 )
;    25 Shift key (Win: reserved)
;    26 Control key (Win: reserved)
; 27-28 reserved
;    29 ALT key ( KF_ALTDOWN << 16 )
;    30 previous key state ( KF_REPEAT << 16 )
;    31 transition state ( KF_UP << 16 )
;

define KEY_EXTENDED	( KF_EXTENDED shl 16 )
define KEY_SHIFT	( KF_EXTENDED shl 17 )
define KEY_CONTROL	( KF_EXTENDED shl 18 )
define KEY_ALTDOWN	( KF_ALTDOWN  shl 16 )


define at_foreground	<_conscolor.foreground>
define at_background	<_conscolor.background>

.enum COLORATTRIB : byte {
    FG_TITLE		= 0,
    FG_FRAME		= 1,
    FG_FILES		= 2,
    FG_SYSTEM		= 3,
    FG_HIDDEN		= 4,
    FG_PBSHADE		= 5,
    FG_KEYBAR		= 6,
    FG_DESKTOP		= 7,
    FG_INACTIVE		= 8,
    FG_DIALOG		= 9,
    FG_PANEL		= 10,
    FG_SUBDIR		= 11,
    FG_MENUS		= 12,
    FG_TITLEKEY		= 13,
    FG_DIALOGKEY	= 14,
    FG_MENUSKEY		= 15,
    FG_TEXTVIEW		= 16,
    FG_TEXTEDIT		= 17,
    BG_DESKTOP		= 0,
    BG_PANEL		= 1,
    BG_DIALOG		= 2,
    BG_MENUS		= 3,
    BG_ERROR		= 4,
    BG_TITLE		= 5,
    BG_INVERSE		= 6,
    BG_GRAY		= 7,
    BG_PUSHBUTTON	= 8,
    BG_INVPANEL		= 9,
    BG_INVMENUS		= 10,
    BG_TEXTVIEW		= 11,
    BG_TEXTEDIT		= 12,
    }

.enum BOXTYPE {
    BOX_SINGLE,			; Single corners
    BOX_DOUBLE,			; Double corners
    BOX_SINGLE_VERTICAL,	; Single insert corners
    BOX_SINGLE_HORIZONTAL,
    BOX_SINGLE_ARC		; Single rounded corners
    }

.enum _DLMOVE_DIRECTION {
    TW_MOVELEFT,
    TW_MOVERIGHT,
    TW_MOVEUP,
    TW_MOVEDOWN
    }

.enum TTYPE {
    T_WINDOW,			; Main window
    T_PUSHBUTTON,		;  [ > Selectable text < ] + shade
    T_RADIOBUTTON,		;  (*)
    T_CHECKBOX,			;  [x]
    T_XCELL,			;  [ Selectable text ]
    T_EDIT,			;  [Text input]
    T_MENUITEM,			;  XCELL + Stausline info
    T_TEXTAREA,			;  [Selectable text]
    T_TEXTBUTTON,		;  [>Selectable text<]
    T_MOUSERECT,		;  Clickable area -- no focus
    T_SCROLLUP,			;  Clickable area for list items
    T_SCROLLDOWN,
    }

.enum TFLAGS {
    W_ISOPEN		= 0x000001,
    W_VISIBLE		= 0x000002,
    W_MOVEABLE		= 0x000004,
    W_SHADE		= 0x000008,
    W_WNDPROC		= 0x000010,
    W_CHILD		= 0x000020,	; Item is a child
    W_COLOR		= 0x000040,
    W_TRANSPARENT	= 0x000080,

    O_RADIO		= 0x000100,	; Active (*)
    O_CHECK		= 0x000200,	; Active [x]
    O_LIST		= 0x000400,	; Linked list item
    O_SELECT		= 0x000800,	; Select text on activation
    O_CONTROL		= 0x001000,	; Allow _CONTROL chars
    O_DEXIT		= 0x002000,	; Close dialog and return 0: Cancel
    O_PBKEY		= 0x004000,	; Return result if short key used
    O_DLGED		= 0x008000,	; dialog text -- return Left/Right
    O_GLOBAL		= 0x010000,	; Item contain global short-key table
    O_EVENT		= 0x020000,	; Item have local event handler
    O_CHILD		= 0x040000,	; Item have a child
    O_STATE		= 0x080000,	; State (ON/OFF)
    O_DEACT		= O_STATE,

    O_BUFFER		= 0x100000,	;
    O_MODIFIED		= 0x200000,	; dialog text
    O_OVERWRITE		= 0x400000,	; selected text on paste
    O_USEBEEP		= 0x800000
    }


.pragma pack(push, size_t)


.template COLOR
    rgb		dd 16 dup(?)
    foreground	db 18 dup(?)
    background	db 14 dup(?)
   .ends
    PCOLOR	typedef ptr COLOR


.template CURSOR	; CONSOLE_CURSOR_INFO
    csize	dd ?	; .dwSize	1..100
    visible	dd ?	; .bVisible	0..1
    x		dw ?	; COORD
    y		dw ?
   .ends
    PCURSOR	typedef ptr CURSOR


.template TRECT
    x		db ?
    y		db ?
    col		db ?
    row		db ?
   .ends


.template TLIST
    dlgoff	dd ?		; start index in dialog
    dcount	dd ?		; number of cells (max)
    celoff	dd ?		; cell offset
    numcel	dd ?		; number of visible cells
    count	dd ?		; total number of items in list
    index	dd ?		; index in list buffer
    list	array_t ?	; pointer to list buffer
   .ends


.template TOBJ
    flags	dd ?
    ttype	db ?
    syskey	db ?
    count	db ?		; item: extra buffer size in para
    index	db ?
    rc		TRECT <>
   .ends
    PTOBJ	typedef ptr TOBJ
    THWND	typedef ptr TCLASS


.template TEDIT
    base	LPTSTR ?	; base pointer
    flags	uint_t ?	; config
    xpos	uint_t ?	; window x
    ypos	uint_t ?	; window y
    scols	uint_t ?	; size of screen-line
    bcols	uint_t ?	; size of buffer-line
    xoffs	uint_t ?	; x offset on screen
    boffs	uint_t ?	; base offset - start of screen-line
    bcount	uint_t ?	; byte count in line (expanded)
    clrattrib	CHAR_INFO <>	; clear attrib/char
    clip_so	uint_t ?	; Clipboard start offset
    clip_eo	uint_t ?	; Clipboard end offset
   .ends
    PTEDIT	typedef ptr TEDIT


.template TCONTEXT
    union
     struct
      state	db ?
      flags	db ?
      x		db ?
      y		db ?
      rc	TRECT <>
     ends
     object	ptr_t ?
    ends
    buffer	ptr_t ?
   .ends


CALLBACKC(TPROC, :THWND, :UINT, :WPARAM, :LPARAM)

.template TCLASS : public TOBJ
    window	PCHAR_INFO ?
    next	THWND ?
    prev	THWND ?
    object	THWND ?
    winproc	TPROC ?
    cursor	CURSOR <>
    context	TCONTEXT <>
   .ends

.pragma pack(pop)

externdef	_confh:intptr_t
externdef	_coninpfh:intptr_t
externdef	_console:THWND
externdef	_consize:COORD
externdef	_consmax:COORD
externdef	_conscolor:COLOR

_getattrib proto fastcall :abs, :abs {
    movzx	eax,at_foreground[_1]
    or		al, at_background[_2]
    shl		eax,16
    mov		al,' '
    }

__initconin	proto __cdecl
__termconin	proto __cdecl
__initconout	proto __cdecl
__termconout	proto __cdecl

_coutA		proto __cdecl :LPSTR, :vararg
_coutW		proto __cdecl :LPWSTR, :vararg

_scgeta		proto __cdecl :BYTE, :BYTE
_scgetc		proto __cdecl :BYTE, :BYTE
_scgetw		proto __cdecl :BYTE, :BYTE
_scputa		proto __cdecl :BYTE, :BYTE, :BYTE, :WORD
_scputfg	proto __cdecl :BYTE, :BYTE, :BYTE, :BYTE
_scputbg	proto __cdecl :BYTE, :BYTE, :BYTE, :BYTE
_scputc		proto __cdecl :BYTE, :BYTE, :BYTE, :wchar_t
_scputw		proto __cdecl :BYTE, :BYTE, :BYTE, :CHAR_INFO
_scgetl		proto __cdecl :SINT, :SINT, :SINT
_scputl		proto __cdecl :SINT, :SINT, :SINT, :PCHAR_INFO
_scputsA	proto __cdecl :BYTE, :BYTE, :LPSTR
_scputsW	proto __cdecl :BYTE, :BYTE, :LPWSTR
_scputfA	proto __Cdecl :BYTE, :BYTE, :LPSTR, :vararg
_scputfW	proto __Cdecl :BYTE, :BYTE, :LPWSTR, :vararg
_scpathA	proto __cdecl :BYTE, :BYTE, :BYTE, :LPSTR
_scpathW	proto __cdecl :BYTE, :BYTE, :BYTE, :LPWSTR
_sccenterA	proto __cdecl :BYTE, :BYTE, :BYTE, :LPSTR
_sccenterW	proto __cdecl :BYTE, :BYTE, :BYTE, :LPWSTR

_getcursor	proto __cdecl :PCURSOR
_setcursor	proto __cdecl :PCURSOR
_cursoron	proto __cdecl
_cursoroff	proto __cdecl
_cursorsize	proto __cdecl :uint_t
_gotoxy		proto __cdecl :BYTE, :BYTE

_rcframe	proto __cdecl :TRECT, :TRECT, :PCHAR_INFO, :SINT, :BYTE
_rcmemsize	proto __cdecl :TRECT, :SINT
_rcalloc	proto __cdecl :TRECT, :SINT
_rcread		proto __cdecl :TRECT, :PCHAR_INFO
_rcwrite	proto __cdecl :TRECT, :PCHAR_INFO
_rcxchg		proto __cdecl :TRECT, :PCHAR_INFO
_rcmovel	proto __cdecl :TRECT, :PCHAR_INFO
_rcmover	proto __cdecl :TRECT, :PCHAR_INFO
_rcmoveu	proto __cdecl :TRECT, :PCHAR_INFO
_rcmoved	proto __cdecl :TRECT, :PCHAR_INFO
_rczip		proto __cdecl :TRECT, :ptr, :PCHAR_INFO
_rcunzip	proto __cdecl :TRECT, :PCHAR_INFO, :ptr
_rcbprc		proto __cdecl :TRECT, :TRECT, :PCHAR_INFO
_rcgetw		proto __cdecl :TRECT, :PCHAR_INFO, :BYTE, :BYTE
_rcputc		proto __cdecl :TRECT, :TRECT, :PCHAR_INFO, :wchar_t
_rcputa		proto __cdecl :TRECT, :TRECT, :PCHAR_INFO, :WORD
_rcputfg	proto __cdecl :TRECT, :TRECT, :PCHAR_INFO, :BYTE
_rcputbg	proto __cdecl :TRECT, :TRECT, :PCHAR_INFO, :BYTE
_rcshade	proto __cdecl :TRECT, :PCHAR_INFO, :SINT
_rcclear	proto __cdecl :TRECT, :PCHAR_INFO, :CHAR_INFO
_rccenterA	proto __cdecl :TRECT, :PCHAR_INFO, :TRECT, :WORD, :LPSTR
_rccenterW	proto __cdecl :TRECT, :PCHAR_INFO, :TRECT, :WORD, :LPWSTR
_rcputsA	proto __cdecl :TRECT, :PCHAR_INFO, :SINT, :SINT, :WORD, :LPSTR
_rcputsW	proto __cdecl :TRECT, :PCHAR_INFO, :SINT, :SINT, :WORD, :LPWSTR
_rcputfA	proto __Cdecl :TRECT, :PCHAR_INFO, :SINT, :SINT, :WORD, :LPSTR, :vararg
_rcputfW	proto __Cdecl :TRECT, :PCHAR_INFO, :SINT, :SINT, :WORD, :LPWSTR, :vararg

_clipsetA	proto __cdecl :LPSTR, :UINT
_clipsetW	proto __cdecl :LPWSTR, :UINT
_clipgetA	proto __cdecl
_clipgetW	proto __cdecl

_msgboxA	proto __cdecl :UINT, :LPSTR, :LPSTR, :vararg
_msgboxW	proto __cdecl :UINT, :LPWSTR, :LPWSTR, :vararg

_dlopen		proto __cdecl :TRECT, :UINT, :UINT, :UINT
_dlinitA	proto __cdecl :THWND, :UINT, :TRECT, :UINT, :BYTE, :BYTE, :LPSTR
_dlinitW	proto __cdecl :THWND, :UINT, :TRECT, :UINT, :BYTE, :BYTE, :LPWSTR
_dlclose	proto __cdecl :THWND
_dlmodal	proto __cdecl :THWND, :TPROC
_dlhide		proto __cdecl :THWND
_dlshow		proto __cdecl :THWND
_dlsetfocus	proto __cdecl :THWND, :BYTE
_dlmove		proto __cdecl :THWND, :SINT
_dltitleA	proto __cdecl :THWND, :LPSTR
_dltitleW	proto __cdecl :THWND, :LPWSTR

_tcontrolA	proto __cdecl :THWND, :UINT, :LPSTR
_tcontrolW	proto __cdecl :THWND, :UINT, :LPWSTR
_conslink	proto __cdecl :THWND
_consunlink	proto __cdecl :THWND

_sendmessage	proto __cdecl :THWND, :UINT, :WPARAM, :LPARAM
_postmessage	proto __cdecl :THWND, :UINT, :WPARAM, :LPARAM
_postquitmsg	proto fastcall :THWND, :UINT
_defwinproc	proto __cdecl :THWND, :UINT, :WPARAM, :LPARAM

ifdef _UNICODE
define _cout		<_coutW>
define _scputs		<_scputsW>
define _scputf		<_scputfW>
define _scpath		<_scpathW>
define _sccenter	<_sccenterW>
define _rccenter	<_rccenterW>
define _rcputs		<_rcputsW>
define _rcputf		<_rcputfW>
define _dlinit		<_dlinitW>
define _dltitle		<_dltitleW>
define _tcontrol	<_tcontrolW>
define _msgbox		<_msgboxW>
define _clipget		<_clipgetW>
define _clipset		<_clipsetW>
else
define _cout		<_coutA>
define _scputs		<_scputsA>
define _scputf		<_scputfA>
define _scpath		<_scpathA>
define _sccenter	<_sccenterA>
define _rccenter	<_rccenterA>
define _rcputs		<_rcputsA>
define _rcputf		<_rcputfA>
define _dlinit		<_dlinitA>
define _dltitle		<_dltitleA>
define _tcontrol	<_tcontrolA>
define _msgbox		<_msgboxA>
define _clipget		<_clipgetA>
define _clipset		<_clipsetA>
endif

endif

endif
.pragma list(pop)
