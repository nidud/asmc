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

ifdef _CONIO_RETRO_COLORS
.enum CONIO_RETRO_COLORS {
    BLACK,		; 0
    BLUE,		; 1
    GREEN,		; 2
    CYAN,		; 3
    RED,		; 4
    MAGENTA,		; 5
    BROWN,		; 6
    LIGHTGRAY,		; 7
    DARKGRAY,		; 8
    LIGHTBLUE,		; 9
    LIGHTGREEN,		; 10
    LIGHTCYAN,		; 11
    LIGHTRED,		; 12
    LIGHTMAGENTA,	; 13
    YELLOW,		; 14
    WHITE		; 15
    }
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

ifndef __VT__
ifdef  __UNIX__
define __VT__
endif
endif

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
define SHIFTKEY_DOWN	( KF_EXTENDED shl 17 )
define CTRLKEY_DOWN	( KF_EXTENDED shl 18 )
define ALTKEY_DOWN	( KF_ALTDOWN  shl 16 )

define BG_MENU		3	; CYAN
define BG_ERROR		4	; RED
define BG_TITLE		15	; WHITE
define BG_INVERSE	11	; LIGHTCYAN
define BG_PUSHBUTTON	2	; GREEN
define BG_EDIT		0	; BLACK

define FG_MENU		0	; BLACK
define FG_TITLE		0	; BLACK
define FG_PUSHBUTTON	0	; BLACK
define FG_PBUTTONKEY	14	; YELLOW
define FG_TITLEKEY	14	; YELLOW
define FG_MENUKEY	15	; WHITE
define FG_EDIT		7	; GRAY

.enum VTI_COLOR { ; Virtual Terminal Color Index
    TC_BLACK,
    TC_RED,
    TC_GREEN,
    TC_BROWN,
    TC_BLUE,
    TC_MAGENTA,
    TC_CYAN,
    TC_LIGHTGRAY,
    TC_DARKGRAY,
    TC_LIGHTRED,
    TC_LIGHTGREEN,
    TC_YELLOW,
    TC_LIGHTBLUE,
    TC_LIGHTMAGENTA,
    TC_LIGHTCYAN,
    TC_WHITE
    }

_getat macro B, F
    exitm<( F or ( B shl 4 ) )>
    endm
_getattrib macro B, F
    exitm<( ( ( F or ( B shl 4 ) ) shl 16 ) or ' ' )>
    endm


.enum BOXTYPE {
    BOX_SINGLE,			; Single corners
    BOX_DOUBLE,			; Double corners
    BOX_SINGLE_VERTICAL,	; Single insert corners
    BOX_SINGLE_HORIZONTAL,
    BOX_SINGLE_ARC,		; Single rounded corners
    BOX_CLEAR
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
    W_ISOPEN		= 0x00000001,
    W_VISIBLE		= 0x00000002,
    W_MOVEABLE		= 0x00000004,
    W_SHADE		= 0x00000008,
    W_WNDPROC		= 0x00000010,
    W_CHILD		= 0x00000020,	; Item is a child
    W_CONSOLE		= 0x00000040,
    W_TRANSPARENT	= 0x00000080,

    O_RADIO		= 0x00000100,	; Active (*)
    O_CHECK		= 0x00000200,	; Active [x]
    O_LIST		= 0x00000400,	; Linked list item
    O_SELECT		= 0x00000800,	; Select text on activation
    O_CONTROL		= 0x00001000,	; Allow _CONTROL chars
    O_DEXIT		= 0x00002000,	; Close dialog and return 0: Cancel
    O_PBKEY		= 0x00004000,	; Return result if short key used
    O_DLGED		= 0x00008000,	; dialog text -- return Left/Right
    O_GLOBAL		= 0x00010000,	; Item contain global short-key table
    O_EVENT		= 0x00020000,	; Item have local event handler
    O_CHILD		= 0x00040000,	; Item have a child
    O_STATE		= 0x00080000,	; State (ON/OFF)
    O_DEACT		= O_STATE,

    O_VTERMINAL		= 0x00100000,	;
    O_MODIFIED		= 0x00200000,	; dialog text
    O_OVERWRITE		= 0x00400000,	; selected text on paste
    O_USEBEEP		= 0x00800000,
    O_CURSOR		= 0x01000000
    }

.enum CURSOR_TYPE {
    CURSOR_DEFAULT,
    CURSOR_BLOCK_BL,
    CURSOR_BLOCK,
    CURSOR_UNDERL_BL,
    CURSOR_UNDERL,
    CURSOR_BAR_BL,
    CURSOR_BAR
    }

.pragma pack(push, size_t)


.template CURSOR
    x		db ?
    y		db ?
    type	db ?
    visible	db ?
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
    type	db ?
    syskey	db ?
    count	db ?		; item: extra buffer size in para
    index	db ?
    rc		TRECT <>
   .ends
    PTOBJ	typedef ptr TOBJ
    THWND	typedef ptr TCLASS
    PTRES	typedef ptr TOBJ


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
   .ends


CALLBACKC(TPROC, :THWND, :UINT, :WPARAM, :LPARAM)

.template TCLASS : public TOBJ
    cursor	CURSOR <>
    window	PCHAR_INFO ?
    next	THWND ?
    prev	THWND ?
    object	THWND ?
    winproc	TPROC ?
    context	TCONTEXT <>
    buffer	ptr_t ?
   .ends

.template TCONSOLE : public TCLASS
    color	LPCOLORREF ?
    winpos	COORD <> ; old metrics
    consize	COORD <>
    conmax	COORD <>
    modein	int_t ?
    modeout	int_t ?
    paint	int_t ?
   .ends
    PCONSOLE	typedef ptr TCONSOLE

.pragma pack(pop)

ifdef __UNIX__
externdef	_confh:int_t
externdef	_coninpfh:int_t
else
externdef	_confh:intptr_t
externdef	_coninpfh:intptr_t
endif
externdef	_console:PCONSOLE
externdef	_terminalcolorid:byte

__initconin	proto __cdecl
__termconin	proto __cdecl
__initconout	proto __cdecl
__termconout	proto __cdecl

_coutA		proto __Cdecl :LPSTR, :vararg
_coutW		proto __Cdecl :LPWSTR, :vararg

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
_scframe	proto __cdecl :TRECT, :SINT, :WORD

_getcursor	proto __cdecl :PCURSOR
_setcursor	proto __cdecl :PCURSOR
_cursoron	proto __cdecl
_cursoroff	proto __cdecl
_cursortype	proto __cdecl :int_t
_cursorxy	proto __cdecl ; COORD
_gotoxy		proto __cdecl :uint_t, :uint_t

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
_rcputsA	proto __cdecl :TRECT, :PCHAR_INFO, :BYTE, :BYTE, :WORD, :LPSTR
_rcputsW	proto __cdecl :TRECT, :PCHAR_INFO, :BYTE, :BYTE, :WORD, :LPWSTR
_rcputfA	proto __Cdecl :TRECT, :PCHAR_INFO, :BYTE, :BYTE, :WORD, :LPSTR, :vararg
_rcputfW	proto __Cdecl :TRECT, :PCHAR_INFO, :BYTE, :BYTE, :WORD, :LPWSTR, :vararg

_clipsetA	proto __cdecl :LPSTR, :UINT
_clipsetW	proto __cdecl :LPWSTR, :UINT
_clipgetA	proto __cdecl
_clipgetW	proto __cdecl

_msgboxA	proto __Cdecl :UINT, :LPSTR, :LPSTR, :vararg
_msgboxW	proto __Cdecl :UINT, :LPWSTR, :LPWSTR, :vararg

_dlopen		proto __cdecl :TRECT, :UINT, :UINT, :UINT
_dlinitA	proto __cdecl :THWND, :UINT, :TRECT, :UINT, :BYTE, :BYTE, :LPSTR
_dlinitW	proto __cdecl :THWND, :UINT, :TRECT, :UINT, :BYTE, :BYTE, :LPWSTR
_dlclose	proto __cdecl :THWND
_dlmodal	proto __cdecl :THWND, :TPROC
_dlhide		proto __cdecl :THWND
_dlshow		proto __cdecl :THWND
_dlsetfocus	proto __cdecl :THWND, :BYTE
_dlgetfocus	proto __cdecl :THWND
_dlgetid	proto __cdecl :THWND, :UINT
_dlmove		proto __cdecl :THWND, :SINT
_dltitleA	proto __cdecl :THWND, :LPSTR
_dltitleW	proto __cdecl :THWND, :LPWSTR

_tcontrolA	proto __cdecl :THWND, :UINT, :WORD, :LPSTR
_tcontrolW	proto __cdecl :THWND, :UINT, :WORD, :LPWSTR
_conslink	proto __cdecl :THWND
_consunlink	proto __cdecl :THWND
_cbeginpaint	proto __cdecl
_cendpaint	proto __cdecl

_sendmessage	proto __cdecl :THWND, :UINT, :WPARAM, :LPARAM
_postmessage	proto __cdecl :THWND, :UINT, :WPARAM, :LPARAM
_postquitmsg	proto fastcall :THWND, :UINT
_defwinproc	proto __cdecl :THWND, :UINT, :WPARAM, :LPARAM

_rsopen		proto __cdecl :PTRES
_rssave		proto __cdecl :THWND, :LPWSTR

ifdef __VT__

.template CINPUT
    union
     q	    dq ?
     b	    db 8 dup(?)
    ends
    count   dd ?
   .ends

_kbflush	proto __cdecl

define ESC <"\e">
define CSI <"\e[">

define SET_X10_MOUSE		   <CSI "?9h">
define SET_VT200_MOUSE		   <CSI "?1001h">
define SET_VT200_HIGHLIGHT_MOUSE   <CSI "?1001h">
define SET_BTN_EVENT_MOUSE	   <CSI "?1002h">
define SET_ANY_EVENT_MOUSE	   <CSI "?1003h">
define SET_FOCUS_EVENT_MOUSE	   <CSI "?1004h">
define SET_ALTERNATE_SCROLL	   <CSI "?1007h">
define SET_EXT_MODE_MOUSE	   <CSI "?1005h">
define SET_SGR_EXT_MODE_MOUSE	   <CSI "?1006h">
define SET_URXVT_EXT_MODE_MOUSE	   <CSI "?1015h">
define SET_PIXEL_POSITION_MOUSE	   <CSI "?1016h">

define RST_X10_MOUSE		   <CSI "?9l">
define RST_VT200_MOUSE		   <CSI "?1001l">
define RST_VT200_HIGHLIGHT_MOUSE   <CSI "?1001l">
define RST_BTN_EVENT_MOUSE	   <CSI "?1002l">
define RST_ANY_EVENT_MOUSE	   <CSI "?1003l">
define RST_FOCUS_EVENT_MOUSE	   <CSI "?1004l">
define RST_ALTERNATE_SCROLL	   <CSI "?1007l">
define RST_EXT_MODE_MOUSE	   <CSI "?1005l">
define RST_SGR_EXT_MODE_MOUSE	   <CSI "?1006l">
define RST_URXVT_EXT_MODE_MOUSE	   <CSI "?1015l">
define RST_PIXEL_POSITION_MOUSE	   <CSI "?1016l">

endif

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

; Unicode box charcters -- https://www.compart.com/en/unicode/U+2500

define U_LIGHT_HORIZONTAL		0x2500	; -
define U_LIGHT_VERTICAL			0x2502	; |
define U_LIGHT_DOWN_AND_RIGHT		0x250C	; Single corners
define U_LIGHT_DOWN_AND_LEFT		0x2510	;
define U_LIGHT_UP_AND_RIGHT		0x2514	;
define U_LIGHT_UP_AND_LEFT		0x2518	;

define U_LIGHT_VERTICAL_AND_RIGHT	0x251C	; Insert single corners
define U_LIGHT_VERTICAL_AND_LEFT	0x2524	;
define U_LIGHT_DOWN_AND_HORIZONTAL	0x252C	;
define U_LIGHT_UP_AND_HORIZONTAL	0x2534	;

define U_DOUBLE_HORIZONTAL		0x2550	; =
define U_DOUBLE_VERTICAL		0x2551	; ||
define U_DOUBLE_DOWN_AND_RIGHT		0x2554	; Double corners
define U_DOUBLE_DOWN_AND_LEFT		0x2557	;
define U_DOUBLE_UP_AND_RIGHT		0x255A	;
define U_DOUBLE_UP_AND_LEFT		0x255D	;

define U_LIGHT_ARC_DOWN_AND_RIGHT	0x256D	; Single rounded corners
define U_LIGHT_ARC_DOWN_AND_LEFT	0x256E	;
define U_LIGHT_ARC_UP_AND_LEFT		0x256F	;
define U_LIGHT_ARC_UP_AND_RIGHT		0x2570	;

define U_UPPER_HALF_BLOCK		0x2580	; Push Button
define U_LOWER_HALF_BLOCK		0x2584
define U_BLACK_RIGHT_POINTER		0x25BA	; >
define U_BLACK_LEFT_POINTER		0x25C4	; <

define U_FULL_BLOCK			0x2588
define U_LIGHT_SHADE			0x2591
define U_FULL_BLOCK			0x2588

define U_MIDDLE_DOT			0x00B7	; Text input
define U_BULLET_OPERATOR		0x2219	; (*) Radio

endif

endif
.pragma list(pop)
