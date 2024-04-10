.pragma list(push, 0)

ifndef __INC_CONIO
define __INC_CONIO

define NOGDI
include wincon.inc
include winuser.inc
ifdef __UNIX__
ifndef __TTY__
define __TTY__
endif
include termios.inc
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
ifdef _MSVCRT
_kbhit		proto __cdecl
else
_kbhitA		proto __cdecl
_kbhitW		proto __cdecl
ifdef _UNICODE
define _kbhit <_kbhitW>
else
define _kbhit <_kbhitA>
endif
endif
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
_putwch		proto __cdecl :int_t
_putwch_nolock	proto __cdecl :wchar_t
_getwch		proto __cdecl
_getwche	proto __cdecl
_cgetws		proto __cdecl :LPWSTR
_ungetwch	proto __cdecl :int_t
_cputws		proto __cdecl :LPWSTR
_cwprintf	proto __Cdecl :LPWSTR, :VARARG
_cwscanf	proto __Cdecl :LPWSTR, :VARARG
_vcwprintf	proto __cdecl :LPWSTR, :PVOID

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

define MAXCOLS		240	; max/min screen size
define MAXROWS		240
define MINCOLS		80
define MINROWS		25
define MAXSCRLINE	MAXCOLS

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

.enum VTI_COLOR { ; Virtual Terminal Color Index
    TC_BLACK,
    TC_BLUE,
    TC_GREEN,
    TC_CYAN,
    TC_RED,
    TC_MAGENTA,
    TC_BROWN,
    TC_LIGHTGRAY,
    TC_DARKGRAY,
    TC_LIGHTBLUE,
    TC_LIGHTGREEN,
    TC_LIGHTCYAN,
    TC_LIGHTRED,
    TC_LIGHTMAGENTA,
    TC_YELLOW,
    TC_WHITE
    }

.enum ColorBackground {
    BG_DESKTOP,
    BG_PANEL,
    BG_DIALOG,
    BG_MENU,
    BG_ERROR,
    BG_TITLE,
    BG_INVERSE,
    BG_GRAY,
    BG_PBUTTON,
    BG_INVPANEL,
    BG_INVMENU,
    BG_TVIEW,
    BG_TEDIT,
    }

.enum ColorForeground {
    FG_TITLE,
    FG_FRAME,
    FG_FILES,
    FG_SYSTEM,
    FG_HIDDEN,
    FG_PBSHADE,
    FG_KEYBAR,
    FG_DESKTOP,
    FG_INACTIVE,
    FG_DIALOG,
    FG_PANEL,
    FG_SUBDIR,
    FG_MENU,
    FG_TITLEKEY,
    FG_DIALOGKEY,
    FG_MENUKEY,
    }

externdef at_background:byte
externdef at_foreground:byte

_at macro B, F, C, reg:=<eax>
    movzx reg,at_background[B]
    or	  @Reg(reg,8),at_foreground[F]
    ifnb <C>
      shl reg,16
      mov @Reg(reg,16),C
    endif
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
    W_ISOPEN		= 0x0001,
    W_VISIBLE		= 0x0002,
    W_MOVEABLE		= 0x0004,
    W_SHADE		= 0x0008,
    W_MYBUF		= 0x0010,	; do not delete on exit (static)
    W_RCNEW		= 0x0020,	; dlclose -- delete dialog if set
    W_RESAT		= 0x0040,	; attrib is index in color table (rcedit)
    W_DHELP		= 0x0080,	; execute thelp() if set
    W_TRANSPARENT	= 0x0100,
    W_CONSOLE		= 0x0200,
    W_LIST		= 0x0400,
    W_STDLG		= 0x0800,
    W_STERR		= 0x1000,	; error color (red)
    W_MENUS		= 0x2000,	; menus color (gray), no title
    W_UTF16		= 0x8000,
    W_RESBITS		= 0xF9FC,

    O_MODIFIED		= 0x0001,	; dialog text
    O_OVERWRITE		= 0x0002,	; selected text on paste
    O_USEBEEP		= 0x0004,
    O_MYBUF		= 0x0008,	; T_EDIT -- no alloc
    O_RADIO		= 0x0010,	; Active (*)
    O_CHECK		= 0x0020,	; Active [x]
    O_LIST		= 0x0040,	; Linked list item
    O_SELECT		= 0x0080,	; Select text on activation
    O_CONTROL		= 0x0100,	; Allow _CONTROL chars
    O_DEXIT		= 0x0200,	; Close dialog and return 0: Cancel
    O_PBKEY		= 0x0400,	; Return result if short key used
    O_DLGED		= 0x0800,	; dialog text -- return Left/Right
    O_GLOBAL		= 0x1000,	; Item contain global short-key table
    O_EVENT		= 0x2000,	; Item have local event handler
    O_CHILD		= 0x4000,	; Item have a child
    O_STATE		= 0x8000,	; State (ON/OFF)
    O_RESBITS		= 0xFFF0,

    W_WNDPROC	    = 0x00010000,
    W_CHILD	    = 0x00020000,	; is a child
    O_CURSOR	    = 0x00040000,
    }

.enum RESOURCE_FLAGS {

    _D_DOPEN		= 0x0001,
    _D_ONSCR		= 0x0002,
    _D_DMOVE		= 0x0004,
    _D_SHADE		= 0x0008,
    _D_MYBUF		= 0x0010,	; do not delete on exit (static)
    _D_RCNEW		= 0x0020,	; dlclose -- delete dialog if set
    _D_RESAT		= 0x0040,	; attrib is index in color table (rcedit)
    _D_DHELP		= 0x0080,	; execute thelp() if set
    _D_CLEAR		= 0x0100,	; args on open/create
    _D_BACKG		= 0x0200,
    _D_FOREG		= 0x0400,
    _D_STDLG		= 0x0800,
    _D_STERR		= 0x1000,	; error color (red)
    _D_MENUS		= 0x2000,	; menus color (gray), no title
    _D_MUSER		= 0x4000,
    _D_UTF16		= 0x8000,

    _O_PBUTT		= 0x0000,
    _O_RBUTT		= 0x0001,
    _O_CHBOX		= 0x0002,
    _O_XCELL		= 0x0003,
    _O_TEDIT		= 0x0004,
    _O_MENUS		= 0x0005,
    _O_XHTML		= 0x0006,
    _O_MOUSE		= 0x0007,
    _O_LLMSU		= 0x0008,
    _O_LLMSD		= 0x0009,
    _O_TBUTT		= 0x000A,

    _O_RADIO		= 0x0010,
    _O_FLAGB		= 0x0020,
    _O_LLIST		= 0x0040,
    _O_DTEXT		= 0x0080,
    _O_CONTR		= 0x0100,
    _O_DEXIT		= 0x0200,
    _O_PBKEY		= 0x0400,
    _O_DLGED		= 0x0800,
    _O_GLCMD		= 0x1000,
    _O_EVENT		= 0x2000,
    _O_CHILD		= 0x4000,
    _O_STATE		= 0x8000,
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

CALLBACKC(DPROC)

.pragma pack(push, 1)

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

.template RIDD
   size		dw ?
   flag		dw ?
   count	db ?
   index	db ?
   rc		TRECT <>
  .ends
   PIDD		typedef ptr RIDD

.template ROBJ
    flag	dw ?		; 8 byte object size in Resource.idd
    count	db ?
    index	db ?
    rc		TRECT <>
   .ends
    PROBJ	typedef ptr ROBJ
    PTRES	typedef ptr ROBJ

.template TOBJ
    flag	dw ?
    count	db ?
    ascii	db ?
    rc		TRECT <>
    data	PVOID ?
    tproc	DPROC ?
   .ends
    PTOBJ	typedef ptr TOBJ

.template DOBJ
    flag	dw ?
    count	db ?
    index	db ?
    rc		TRECT <>
    wp		PCHAR_INFO ?
    object	PTOBJ ?
   .ends
    PDOBJ	typedef ptr DOBJ

.template TLIST
    dlgoff	dd ?		; start index in dialog
    dcount	dd ?		; number of cells (max)
    celoff	dd ?		; cell offset
    numcel	dd ?		; number of visible cells
    count	dd ?		; total number of items in list
    index	dd ?		; index in list buffer
    list	array_t ?	; pointer to list buffer
   .ends
    PTLIST	typedef ptr TLIST

.template TDLG
    flags	dd ?
    type	db ?
    syskey	db ?
    count	db ?		; item: extra buffer size in para
    index	db ?
    rc		TRECT <>
   .ends
    PTDLG	typedef ptr TDLG
    THWND	typedef ptr TCLASS

.pragma pack(pop)

.pragma pack(push, size_t)

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
    clip_so	uint_t ?	; Clipboard start offset
    clip_eo	uint_t ?	; Clipboard end offset
    clrattrib	CHAR_INFO <>	; clear attrib/char
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
     tedit	PTEDIT ?
    ends
    llist	PTLIST ?
   .ends


CALLBACKC(TPROC, :THWND, :UINT, :WPARAM, :LPARAM)

.template TCLASS : public TDLG
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

.template MESSAGE
    next	ptr MESSAGE ?
    hwnd	THWND ?
    message	UINT ?
    wParam	WPARAM ?
    lParam	LPARAM ?
   .ends
    PMESSAGE	typedef ptr MESSAGE

.template CINPUT
    union
     q	    intptr_t ?
     b	    db 8 dup(?)
    ends
    count   dd ?
   .ends

.pragma pack(pop)

ifdef __UNIX__
define CONIN	<"/dev/tty">
define CONOUT	<"/dev/tty">
else
define CONIN	<"CONIN$">
define CONOUT	<"CONOUT$">
externdef	_confh:HANDLE
externdef	_coninpfh:HANDLE
endif

externdef	_confd:int_t
externdef	_coninpfd:int_t
externdef	_console:PCONSOLE
externdef	_rgbcolortable:COLORREF
externdef	_terminalcolorid:byte

_inithelp	proto __cdecl :DPROC
_initidle	proto __cdecl :DPROC
_initupdate	proto __cdecl :DPROC

_thelp		proto __cdecl
_tidle		proto __cdecl
_tupdate	proto __cdecl

;;;

externdef	tgetevent:DPROC

getevent	proto __cdecl
getkey		proto __cdecl
mousep		proto __cdecl
mousey		proto __cdecl
mousex		proto __cdecl
msloop		proto __cdecl
mousewait	proto __cdecl :int_t, :int_t, :int_t

getxyc		proto __cdecl :int_t, :int_t
getxya		proto __cdecl :int_t, :int_t
scputc		proto __cdecl :int_t, :int_t, :int_t, :int_t
scputa		proto __cdecl :int_t, :int_t, :int_t, :int_t
scputbg		proto __cdecl :int_t, :int_t, :int_t, :int_t
scputfg		proto __cdecl :int_t, :int_t, :int_t, :int_t


wcputw		proto __cdecl :PCHAR_INFO, :int_t, :uint_t
wcputs		proto __cdecl :PCHAR_INFO, :int_t, :int_t, :LPSTR
wcputa		proto __cdecl :PCHAR_INFO, :int_t, :int_t
wcputbg		proto __cdecl :PCHAR_INFO, :int_t, :int_t
wcputfg		proto __cdecl :PCHAR_INFO, :int_t, :int_t
wcenter		proto __cdecl :PCHAR_INFO, :int_t, :LPSTR
wcpath		proto __cdecl :PCHAR_INFO, :int_t, :LPSTR
wcpbutt		proto __cdecl :PCHAR_INFO, :int_t, :int_t, :LPSTR
wcpushst	proto __cdecl :PCHAR_INFO, :LPSTR
wcpopst		proto __cdecl :PCHAR_INFO
wctitle		proto __cdecl :PCHAR_INFO, :int_t, :LPSTR
wcstrcpy	proto __cdecl :LPSTR, :PCHAR_INFO, :int_t

rcread		proto __cdecl :TRECT, :PCHAR_INFO
rcwrite		proto __cdecl :TRECT, :PCHAR_INFO
rcxchg		proto __cdecl :TRECT, :PCHAR_INFO

;;;

_coutA		proto __Cdecl :string_t, :vararg
_coutW		proto __Cdecl :wstring_t, :vararg
_readinputA	proto __cdecl :PINPUT_RECORD
_readinputW	proto __cdecl :PINPUT_RECORD
_kbflushA	proto __cdecl
_kbflushW	proto __cdecl

_scgetp		proto __cdecl :uchar_t, :uchar_t, :uchar_t
_scgeta		proto __cdecl :uchar_t, :uchar_t
_scgetc		proto __cdecl :uchar_t, :uchar_t
_scgetw		proto __cdecl :uchar_t, :uchar_t
_scputa		proto __cdecl :uchar_t, :uchar_t, :uchar_t, :ushort_t
_scputfg	proto __cdecl :uchar_t, :uchar_t, :uchar_t, :uchar_t
_scputbg	proto __cdecl :uchar_t, :uchar_t, :uchar_t, :uchar_t
_scputc		proto __cdecl :uchar_t, :uchar_t, :uchar_t, :wchar_t
_scputw		proto __cdecl :uchar_t, :uchar_t, :uchar_t, :CHAR_INFO
_scgetl		proto __cdecl :int_t, :int_t, :int_t
_scputl		proto __cdecl :int_t, :int_t, :int_t, :PCHAR_INFO
_scputsA	proto __cdecl :uchar_t, :uchar_t, :string_t
_scputsW	proto __cdecl :uchar_t, :uchar_t, :wstring_t
_scnputsA	proto __cdecl :uchar_t, :uchar_t, :uchar_t, :string_t
_scnputsW	proto __cdecl :uchar_t, :uchar_t, :uchar_t, :wstring_t
_scputfA	proto __Cdecl :uchar_t, :uchar_t, :string_t, :vararg
_scputfW	proto __Cdecl :uchar_t, :uchar_t, :wstring_t, :vararg
_scpathA	proto __cdecl :uchar_t, :uchar_t, :uchar_t, :string_t
_scpathW	proto __cdecl :uchar_t, :uchar_t, :uchar_t, :wstring_t
_sccenterA	proto __cdecl :uchar_t, :uchar_t, :uchar_t, :string_t
_sccenterW	proto __cdecl :uchar_t, :uchar_t, :uchar_t, :wstring_t
_scframe	proto __cdecl :TRECT, :int_t, :ushort_t

_getcursor	proto __cdecl :PCURSOR
_setcursor	proto __cdecl :PCURSOR
_cursoron	proto __cdecl
_cursoroff	proto __cdecl
_cursortype	proto __cdecl :int_t
_cursorxy	proto __cdecl ; COORD
_gotoxy		proto __cdecl :uint_t, :uint_t
ifdef __TTY__
externdef	_cursor:CURSOR
endif
_rcframe	proto __cdecl :TRECT, :TRECT, :PCHAR_INFO, :int_t, :uchar_t
_rcmemsize	proto __cdecl :TRECT, :int_t
_rcalloc	proto __cdecl :TRECT, :int_t
_rcread		proto __cdecl :TRECT, :PCHAR_INFO
_rcwrite	proto __cdecl :TRECT, :PCHAR_INFO
_rcxchg		proto __cdecl :TRECT, :PCHAR_INFO
_rcmovel	proto __cdecl :TRECT, :PCHAR_INFO
_rcmover	proto __cdecl :TRECT, :PCHAR_INFO
_rcmoveu	proto __cdecl :TRECT, :PCHAR_INFO
_rcmoved	proto __cdecl :TRECT, :PCHAR_INFO
_rczip		proto __cdecl :TRECT, :ptr, :PCHAR_INFO, :uint_t
_rcunzip	proto __cdecl :TRECT, :PCHAR_INFO, :ptr, :uint_t
_rcunzipat	proto __cdecl :TRECT, :PCHAR_INFO
_rcbprc		proto __cdecl :TRECT, :TRECT, :PCHAR_INFO
_rcgetw		proto __cdecl :TRECT, :PCHAR_INFO, :uchar_t, :uchar_t
_rcputc		proto __cdecl :TRECT, :TRECT, :PCHAR_INFO, :wchar_t
_rcputa		proto __cdecl :TRECT, :TRECT, :PCHAR_INFO, :ushort_t
_rcputfg	proto __cdecl :TRECT, :TRECT, :PCHAR_INFO, :uchar_t
_rcputbg	proto __cdecl :TRECT, :TRECT, :PCHAR_INFO, :uchar_t
_rcshade	proto __cdecl :TRECT, :PCHAR_INFO, :int_t
_rcclear	proto __cdecl :TRECT, :PCHAR_INFO, :CHAR_INFO
_rccenterA	proto __cdecl :TRECT, :PCHAR_INFO, :TRECT, :ushort_t, :string_t
_rccenterW	proto __cdecl :TRECT, :PCHAR_INFO, :TRECT, :ushort_t, :wstring_t
_rcputsA	proto __cdecl :TRECT, :PCHAR_INFO, :uchar_t, :uchar_t, :ushort_t, :string_t
_rcputsW	proto __cdecl :TRECT, :PCHAR_INFO, :uchar_t, :uchar_t, :ushort_t, :wstring_t
_rcputfA	proto __Cdecl :TRECT, :PCHAR_INFO, :uchar_t, :uchar_t, :ushort_t, :string_t, :vararg
_rcputfW	proto __Cdecl :TRECT, :PCHAR_INFO, :uchar_t, :uchar_t, :ushort_t, :wstring_t, :vararg

_clipsetA	proto __cdecl :string_t, :uint_t
_clipsetW	proto __cdecl :wstring_t, :uint_t
_clipgetA	proto __cdecl
_clipgetW	proto __cdecl

_vmsgboxA	proto __cdecl :uint_t, :string_t, :string_t
_vmsgboxW	proto __cdecl :uint_t, :wstring_t, :wstring_t
_msgboxA	proto __Cdecl :uint_t, :string_t, :string_t, :vararg
_msgboxW	proto __Cdecl :uint_t, :wstring_t, :wstring_t, :vararg
_stdmsgA	proto __Cdecl :string_t, :string_t, :vararg
_stdmsgW	proto __Cdecl :wstring_t, :wstring_t, :vararg
_errmsgA	proto __Cdecl :string_t, :string_t, :vararg
_errmsgW	proto __Cdecl :wstring_t, :wstring_t, :vararg
_syserrA	proto __cdecl :uint_t, :string_t
_syserrW	proto __cdecl :uint_t, :wstring_t

_dlopen		proto __cdecl :TRECT, :uint_t, :uint_t, :uint_t
_dlinitA	proto __cdecl :THWND, :string_t
_dlinitW	proto __cdecl :THWND, :wstring_t
_dlclose	proto __cdecl :THWND
_dlmodal	proto __cdecl :THWND, :TPROC
_dlhide		proto __cdecl :THWND
_dlshow		proto __cdecl :THWND
_dlsetfocus	proto __cdecl :THWND, :uchar_t
_dlgetfocus	proto __cdecl :THWND
_dlmove		proto __cdecl :THWND, :int_t
_dltitleA	proto __cdecl :THWND, :string_t
_dltitleW	proto __cdecl :THWND, :wstring_t

_tcontrolA	proto __cdecl :THWND, :uint_t, :ushort_t, :string_t
_tcontrolW	proto __cdecl :THWND, :uint_t, :ushort_t, :wstring_t
_tiputsA	proto __cdecl :PTEDIT
_tiputsW	proto __cdecl :PTEDIT
_tiprocA	proto __cdecl :THWND, :uint_t, :WPARAM, :LPARAM
_tiprocW	proto __cdecl :THWND, :uint_t, :WPARAM, :LPARAM

_conslink	proto __cdecl :THWND
_consunlink	proto __cdecl :THWND
_conpaint	proto __cdecl
_cbeginpaint	proto __cdecl
_cendpaint	proto __cdecl

_sendmessage	proto __cdecl :THWND, :uint_t, :WPARAM, :LPARAM
_postmessage	proto __cdecl :THWND, :uint_t, :WPARAM, :LPARAM
_getmessage	proto __cdecl :PMESSAGE, :THWND
_dispatchmsg	proto __cdecl :PMESSAGE
_translatemsg	proto __cdecl :PMESSAGE
_postquitmsg	proto __cdecl :THWND, :uint_t
_defwinproc	proto __cdecl :THWND, :uint_t, :WPARAM, :LPARAM

_rsopenA	proto __cdecl :PTRES
_rsopenW	proto __cdecl :PTRES
_rssave		proto __cdecl :THWND, :string_t

_getkey		proto __cdecl


define KEY_ESC		VK_ESCAPE
define KEY_SPACE	VK_SPACE
define KEY_PGUP		(VK_PRIOR  shl 8)
define KEY_PGDN		(VK_NEXT   shl 8)
define KEY_END		(VK_END	   shl 8)
define KEY_HOME		(VK_HOME   shl 8)
define KEY_LEFT		(VK_LEFT   shl 8)
define KEY_UP		(VK_UP	   shl 8)
define KEY_RIGHT	(VK_RIGHT  shl 8)
define KEY_DOWN		(VK_DOWN   shl 8)
define KEY_INSERT	(VK_INSERT shl 8)
define KEY_DELETE	(VK_DELETE shl 8)

define KEY_F1		(VK_F1	   shl 8)
define KEY_F2		(VK_F2	   shl 8)
define KEY_F3		(VK_F3	   shl 8)
define KEY_F4		(VK_F4	   shl 8)
define KEY_F5		(VK_F5	   shl 8)
define KEY_F6		(VK_F6	   shl 8)
define KEY_F7		(VK_F7	   shl 8)
define KEY_F8		(VK_F8	   shl 8)
define KEY_F9		(VK_F9	   shl 8)
define KEY_F10		(VK_F10	   shl 8)
define KEY_F11		(VK_F11	   shl 8)
define KEY_F12		(VK_F12	   shl 8)


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

ifdef _UNICODE
define _cout		<_coutW>
define _scputs		<_scputsW>
define _scnputs		<_scnputsW>
define _scputf		<_scputfW>
define _scpath		<_scpathW>
define _sccenter	<_sccenterW>
define _rccenter	<_rccenterW>
define _rcputs		<_rcputsW>
define _rcputf		<_rcputfW>
define _dlinit		<_dlinitW>
define _dltitle		<_dltitleW>
define _rsopen		<_rsopenW>
define _tcontrol	<_tcontrolW>
define _tiputs		<_tiputsW>
define _tiproc		<_tiprocW>
define _msgbox		<_msgboxW>
define _vmsgbox		<_vmsgboxW>
define _stdmsg		<_stdmsgW>
define _errmsg		<_errmsgW>
define _syserr		<_syserrW>
define _clipget		<_clipgetW>
define _clipset		<_clipsetW>
define _readinput	<_readinputW>
define _kbflush		<_kbflushW>
else
define _cout		<_coutA>
define _scputs		<_scputsA>
define _scnputs		<_scnputsA>
define _scputf		<_scputfA>
define _scpath		<_scpathA>
define _sccenter	<_sccenterA>
define _rccenter	<_rccenterA>
define _rcputs		<_rcputsA>
define _rcputf		<_rcputfA>
define _dlinit		<_dlinitA>
define _dltitle		<_dltitleA>
define _rsopen		<_rsopenA>
define _tcontrol	<_tcontrolA>
define _tiputs		<_tiputsA>
define _tiproc		<_tiprocA>
define _msgbox		<_msgboxA>
define _vmsgbox		<_vmsgboxA>
define _stdmsg		<_stdmsgA>
define _errmsg		<_errmsgA>
define _syserr		<_syserrA>
define _clipget		<_clipgetA>
define _clipset		<_clipsetA>
define _readinput	<_readinputA>
define _kbflush		<_kbflushA>
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

define U_UPPER_HALF_BLOCK		0x2580	; Push Button shade
define U_LOWER_HALF_BLOCK		0x2584

define U_BLACK_POINTER_RIGHT		0x25BA	; > small
define U_BLACK_POINTER_LEFT		0x25C4	; <

define U_BLACK_TRIANGLE_RIGHT		0x25B6	; > big
define U_BLACK_TRIANGLE_LEFT		0x25C0	; <
define U_BLACK_TRIANGLE_UP		0x25B2	;
define U_BLACK_TRIANGLE_DOWN		0x25BC	;

define U_FULL_BLOCK			0x2588
define U_LIGHT_SHADE			0x2591
define U_MEDIOM_SHADE			0x2592
define U_DARK_SHADE			0x2593

define U_MIDDLE_DOT			0x00B7	; Text input
define U_BULLET_OPERATOR		0x2219	; (*) Radio

endif

endif
.pragma list(pop)
