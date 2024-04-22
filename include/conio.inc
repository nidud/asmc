.pragma list(push, 0)

ifndef __INC_CONIO
define __INC_CONIO

define NOGDI
;define NOAPISET
include wincon.inc

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
      or  reg,C
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


define _D_CLEAR		0x0001		; args to rcopen()
define _D_BACKG		0x0002
define _D_FOREG		0x0004
define _D_COLOR		(_D_BACKG or _D_FOREG)

define _O_PBUTT		0
define _O_RBUTT		1
define _O_CHBOX		2
define _O_XCELL		3
define _O_TEDIT		4
define _O_MENUS		5
define _O_XHTML		6
define _O_MOUSE		7
define _O_LLMSU		8
define _O_LLMSD		9
define _O_TBUTT		10

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

.template GLCMD
    key		dd ?
    cmd		DPROC ?
   .ends

.template TLIST
    dlgoff	dd ?		; start index in dialog
    dcount	dd ?		; number of cells (max)
    celoff	dd ?		; cell offset
    numcel	dd ?		; number of visible cells
    count	dd ?		; total number of items in list
    index	dd ?		; index in list buffer
    list	array_t ?	; pointer to list buffer
    lproc	DPROC ?
   .ends
    LOBJ	typedef TLIST
    PLOBJ	typedef ptr TLIST
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

define MAXMSGCNT 32

.template MESSAGE
    next	ptr MESSAGE ?
    prev	ptr MESSAGE ?
    hwnd	THWND ?
    message	UINT ?
    wParam	WPARAM ?
    lParam	LPARAM ?
   .ends
    PMESSAGE	typedef ptr MESSAGE


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
    msgptr	PMESSAGE ?
    focus	int_t ?
    winpos	COORD <> ; old metrics
    consize	COORD <>
    conmax	COORD <>
    modein	int_t ?
    modeout	int_t ?
    paint	int_t ?
   .ends
    PCONSOLE	typedef ptr TCONSOLE


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
externdef	_unicode850:wchar_t

_inithelp	proto __cdecl :DPROC
_initidle	proto __cdecl :DPROC
_initupdate	proto __cdecl :DPROC

_thelp		proto __cdecl
_tidle		proto __cdecl
_tupdate	proto __cdecl

;;;

externdef	tgeteventA:DPROC
externdef	tgeteventW:DPROC

_initeventA	proto __cdecl :DPROC
_initeventW	proto __cdecl :DPROC
geteventA	proto __cdecl
geteventW	proto __cdecl
getkeyA		proto __cdecl
getkeyW		proto __cdecl
mousepA		proto __cdecl
mousepW		proto __cdecl
mouseyA		proto __cdecl
mouseyW		proto __cdecl
mousexA		proto __cdecl
mousexW		proto __cdecl
msloopA		proto __cdecl
msloopW		proto __cdecl
mousewaitA	proto __cdecl :int_t, :int_t, :int_t
mousewaitW	proto __cdecl :int_t, :int_t, :int_t

ifdef _UNICODE
define _initevent	<_initeventW>
define tgetevent	<tgeteventW>
define getevent		<geteventW>
define getkey		<getkeyW>
define mousep		<mousepW>
define mousey		<mouseyW>
define mousex		<mousexW>
define msloop		<msloopW>
define mousewait	<mousewaitW>
else
define _initevent	<_initeventA>
define tgetevent	<tgeteventA>
define getevent		<geteventA>
define getkey		<getkeyA>
define mousep		<mousepA>
define mousey		<mouseyA>
define mousex		<mousexA>
define msloop		<msloopA>
define mousewait	<mousewaitA>
endif

wcputw		proto __cdecl :PCHAR_INFO, :int_t, :uint_t
wcputsA		proto __cdecl :PCHAR_INFO, :int_t, :int_t, :LPSTR
wcputsW		proto __cdecl :PCHAR_INFO, :int_t, :int_t, :LPWSTR
wcputa		proto __cdecl :PCHAR_INFO, :int_t, :int_t
wcputbg		proto __cdecl :PCHAR_INFO, :int_t, :int_t
wcputfg		proto __cdecl :PCHAR_INFO, :int_t, :int_t
wcenterA	proto __cdecl :PCHAR_INFO, :int_t, :LPSTR
wcenterW	proto __cdecl :PCHAR_INFO, :int_t, :LPWSTR
wcpathA		proto __cdecl :PCHAR_INFO, :int_t, :LPSTR
wcpathW		proto __cdecl :PCHAR_INFO, :int_t, :LPWSTR
wcpbuttA	proto __cdecl :PCHAR_INFO, :int_t, :int_t, :LPSTR
wcpbuttW	proto __cdecl :PCHAR_INFO, :int_t, :int_t, :LPWSTR
wcpushstA	proto __cdecl :PCHAR_INFO, :LPSTR
wcpushstW	proto __cdecl :PCHAR_INFO, :LPWSTR
wcpopstA	proto __cdecl :PCHAR_INFO
wcpopstW	proto __cdecl :PCHAR_INFO
wctitleA	proto __cdecl :PCHAR_INFO, :int_t, :LPSTR
wctitleW	proto __cdecl :PCHAR_INFO, :int_t, :LPWSTR
wcstrcpyA	proto __cdecl :LPSTR, :PCHAR_INFO, :int_t
wcstrcpyW	proto __cdecl :LPWSTR, :PCHAR_INFO, :int_t
wcmemset	proto __cdecl :PCHAR_INFO, :CHAR_INFO, :int_t

ifdef _UNICODE
define wcputs		<wcputsW>
define wcenter		<wcenterW>
define wcpath		<wcpathW>
define wcpbutt		<wcpbuttW>
define wcpushst		<wcpushstW>
define wcpopst		<wcpopstW>
define wctitle		<wctitleW>
define wcstrcpy		<wcstrcpyW>
else
define wcputs		<wcputsA>
define wcenter		<wcenterA>
define wcpath		<wcpathA>
define wcpbutt		<wcpbuttA>
define wcpushst		<wcpushstA>
define wcpopst		<wcpopstA>
define wctitle		<wctitleA>
define wcstrcpy		<wcstrcpyA>
endif

scputsA		proto __cdecl :int_t, :int_t, :int_t, :int_t, :string_t
scputsW		proto __cdecl :int_t, :int_t, :int_t, :int_t, :wstring_t

ifdef _UNICODE
define scputs		<scputsW>
else
define scputs		<scputsA>
endif

rcopen		proto __cdecl :TRECT, :uint_t, :uint_t, :uint_t, :string_t, :ptr
rcclose		proto __cdecl :TRECT, :uint_t, :PCHAR_INFO

rcshow		proto __cdecl :TRECT, :uint_t, :PCHAR_INFO
rchide		proto __cdecl :TRECT, :uint_t, :PCHAR_INFO
rcmove		proto __cdecl :ptr TRECT, :PCHAR_INFO, :int_t, :int_t, :int_t
rcxyrow		proto __cdecl :TRECT, :int_t, :int_t
rcmsmove	proto __cdecl :ptr TRECT, :PCHAR_INFO, :uint_t

dlopen		proto __cdecl :PDOBJ, :uint_t, :LPSTR
dlclose		proto __cdecl :PDOBJ
dlhide		proto __cdecl :PDOBJ
dlshow		proto __cdecl :PDOBJ
dlinit		proto __cdecl :PDOBJ
dlmemsize	proto __cdecl :PDOBJ
dlevent		proto __cdecl :PDOBJ
dlmove		proto __cdecl :PDOBJ
dledit		proto __cdecl :LPSTR, :TRECT, :int_t, :uint_t
tosetbitflag	proto __cdecl :PTOBJ, :int_t, :uint_t, :uint_t
togetbitflag	proto __cdecl :PTOBJ, :int_t, :uint_t

rsopen		proto __cdecl :PIDD
rsevent		proto __cdecl :PIDD, :PDOBJ
rsmodal		proto __cdecl :PIDD

;;;

_coutA		proto __Cdecl :string_t, :vararg
_coutW		proto __Cdecl :wstring_t, :vararg
_readinputA	proto __cdecl :PINPUT_RECORD
_readinputW	proto __cdecl :PINPUT_RECORD
_kbflushA	proto __cdecl
_kbflushW	proto __cdecl

ifdef _UNICODE
define _cout		<_coutW>
define _readinput	<_readinputW>
define _kbflush		<_kbflushW>
else
define _cout		<_coutA>
define _readinput	<_readinputA>
define _kbflush		<_kbflushA>
endif

_scgetp		proto __cdecl :uchar_t, :uchar_t, :uchar_t
_scgeta		proto __cdecl :uchar_t, :uchar_t
_scgetc		proto __cdecl :uchar_t, :uchar_t
_scgetw		proto __cdecl :uchar_t, :uchar_t
_scputa		proto __cdecl :uchar_t, :uchar_t, :uchar_t, :ushort_t
_scputfg	proto __cdecl :uchar_t, :uchar_t, :uchar_t, :uchar_t
_scputbg	proto __cdecl :uchar_t, :uchar_t, :uchar_t, :uchar_t
_scputc		proto __cdecl :uchar_t, :uchar_t, :uchar_t, :int_t
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

ifdef _UNICODE
define _scputs		<_scputsW>
define _scnputs		<_scnputsW>
define _scputf		<_scputfW>
define _scpath		<_scpathW>
define _sccenter	<_sccenterW>
else
define _scputs		<_scputsA>
define _scnputs		<_scnputsA>
define _scputf		<_scputfA>
define _scpath		<_scpathA>
define _sccenter	<_sccenterA>
endif

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
_rcmemsize	proto __cdecl :TRECT, :uint_t
_rcalloc	proto __cdecl :TRECT, :uint_t
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
_rcaddrc	proto __cdecl :TRECT, :TRECT
_rcinside	proto __cdecl :TRECT, :TRECT

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

ifdef _UNICODE
define _rccenter	<_rccenterW>
define _rcputs		<_rcputsW>
define _rcputf		<_rcputfW>
else
define _rccenter	<_rccenterA>
define _rcputs		<_rcputsA>
define _rcputf		<_rcputfA>
endif

_clipsetA	proto __cdecl :string_t, :uint_t
_clipsetW	proto __cdecl :wstring_t, :uint_t
_clipgetA	proto __cdecl
_clipgetW	proto __cdecl

ifdef _UNICODE
define _clipget		<_clipgetW>
define _clipset		<_clipsetW>
else
define _clipget		<_clipgetA>
define _clipset		<_clipsetA>
endif

ifndef _WINUSER_

define IDOK		1
define IDCANCEL		2
define IDABORT		3
define IDRETRY		4
define IDIGNORE		5
define IDYES		6
define IDNO		7
define IDCLOSE		8
define IDHELP		9
define IDTRYAGAIN	10
define IDCONTINUE	11

define MB_OK			0x00000000
define MB_OKCANCEL		0x00000001
define MB_ABORTRETRYIGNORE	0x00000002
define MB_YESNOCANCEL		0x00000003
define MB_YESNO			0x00000004
define MB_RETRYCANCEL		0x00000005
define MB_CANCELTRYCONTINUE	0x00000006
define MB_ICONHAND		0x00000010
define MB_ICONQUESTION		0x00000020
define MB_ICONEXCLAMATION	0x00000030
define MB_ICONASTERISK		0x00000040
define MB_USERICON		0x00000080
define MB_ICONWARNING		MB_ICONEXCLAMATION
define MB_ICONERROR		MB_ICONHAND

define MB_DEFBUTTON1		0x00000000
define MB_DEFBUTTON2		0x00000100
define MB_DEFBUTTON3		0x00000200
define MB_DEFBUTTON4		0x00000300

endif

_vmsgboxA	proto __cdecl :uint_t, :string_t, :string_t
_vmsgboxW	proto __cdecl :uint_t, :wstring_t, :wstring_t
_msgboxA	proto __Cdecl :uint_t, :string_t, :string_t, :vararg
_msgboxW	proto __Cdecl :uint_t, :wstring_t, :wstring_t, :vararg
_stdmsgA	proto __Cdecl :string_t, :string_t, :vararg
_stdmsgW	proto __Cdecl :wstring_t, :wstring_t, :vararg
_errmsgA	proto __Cdecl :string_t, :string_t, :vararg
_errmsgW	proto __Cdecl :wstring_t, :wstring_t, :vararg
_syserrA	proto __Cdecl :string_t, :string_t, :vararg
_syserrW	proto __Cdecl :wstring_t, :wstring_t, :vararg
_eropenA	proto __cdecl :string_t
_eropenW	proto __cdecl :wstring_t

ifdef _UNICODE
define _msgbox		<_msgboxW>
define _vmsgbox		<_vmsgboxW>
define _stdmsg		<_stdmsgW>
define _errmsg		<_errmsgW>
define _syserr		<_syserrW>
define _eropen		<_eropenW>
else
define _msgbox		<_msgboxA>
define _vmsgbox		<_vmsgboxA>
define _stdmsg		<_stdmsgA>
define _errmsg		<_errmsgA>
define _syserr		<_syserrA>
define _eropen		<_eropenA>
endif

_dlopen		proto __cdecl :TRECT, :uint_t, :uint_t, :uint_t
_dlinitA	proto __cdecl :THWND, :string_t
_dlinitW	proto __cdecl :THWND, :wstring_t
_dlclose	proto __cdecl :THWND
_dlmodalA	proto __cdecl :THWND, :TPROC
_dlmodalW	proto __cdecl :THWND, :TPROC
_dlhide		proto __cdecl :THWND
_dlshow		proto __cdecl :THWND
_dlsetfocus	proto __cdecl :THWND, :uchar_t
_dlgetfocus	proto __cdecl :THWND
_dlmove		proto __cdecl :THWND, :int_t
_dltitleA	proto __cdecl :THWND, :string_t
_dltitleW	proto __cdecl :THWND, :wstring_t

ifdef _UNICODE
define _dlinit		<_dlinitW>
define _dlmodal		<_dlmodalW>
define _dltitle		<_dltitleW>
else
define _dlinit		<_dlinitA>
define _dlmodal		<_dlmodalA>
define _dltitle		<_dltitleA>
endif

_tcontrolA	proto __cdecl :THWND, :uint_t, :ushort_t, :string_t
_tcontrolW	proto __cdecl :THWND, :uint_t, :ushort_t, :wstring_t
_tiputsA	proto __cdecl :PTEDIT
_tiputsW	proto __cdecl :PTEDIT
_tiprocA	proto __cdecl :THWND, :uint_t, :WPARAM, :LPARAM
_tiprocW	proto __cdecl :THWND, :uint_t, :WPARAM, :LPARAM
_tgetlineA	proto __cdecl :string_t, :string_t, :int_t, :int_t
_tgetlineW	proto __cdecl :wstring_t, :wstring_t, :int_t, :int_t

ifdef _UNICODE
define _tcontrol	<_tcontrolW>
define _tiputs		<_tiputsW>
define _tiproc		<_tiprocW>
define _tgetline	<_tgetlineW>
else
define _tcontrol	<_tcontrolA>
define _tiputs		<_tiputsA>
define _tiproc		<_tiprocA>
define _tgetline	<_tgetlineA>
endif

_conslink	proto __cdecl :THWND
_consunlink	proto __cdecl :THWND
_conpaint	proto __cdecl
_cbeginpaint	proto __cdecl
_cendpaint	proto __cdecl

_sendmessage	proto __cdecl :THWND, :uint_t, :WPARAM, :LPARAM
_postmessage	proto __cdecl :THWND, :uint_t, :WPARAM, :LPARAM
_getmessageA	proto __cdecl :PMESSAGE, :THWND, :int_t
_getmessageW	proto __cdecl :PMESSAGE, :THWND, :int_t
_dispatchmsg	proto __cdecl :PMESSAGE
_translatemsg	proto __cdecl :PMESSAGE
_postquitmsg	proto __cdecl :THWND, :uint_t
_defwinproc	proto __cdecl :THWND, :uint_t, :WPARAM, :LPARAM

ifdef _UNICODE
define _getmessage	<_getmessageW>
else
define _getmessage	<_getmessageA>
endif

_rsopenA	proto __cdecl :PTRES
_rsopenW	proto __cdecl :PTRES
_rssave		proto __cdecl :THWND, :string_t

ifdef _UNICODE
define _rsopen		<_rsopenW>
else
define _rsopen		<_rsopenA>
endif

_getkey		proto __cdecl

ifndef _WINUSER_

define VK_BACK		0x08
define VK_TAB		0x09
define VK_CLEAR		0x0C
ifdef __UNIX__
define VK_RETURN	0x0A
else
define VK_RETURN	0x0D
endif

define VK_SHIFT		0x10
define VK_CONTROL	0x11
define VK_MENU		0x12
define VK_PAUSE		0x13
define VK_CAPITAL	0x14

define VK_ESCAPE	0x1B

define VK_SPACE		0x20
define VK_PRIOR		0x21
define VK_NEXT		0x22
define VK_END		0x23
define VK_HOME		0x24
define VK_LEFT		0x25
define VK_UP		0x26
define VK_RIGHT		0x27
define VK_DOWN		0x28
define VK_SELECT	0x29
define VK_PRINT		0x2A
define VK_EXECUTE	0x2B
define VK_SNAPSHOT	0x2C
define VK_INSERT	0x2D
define VK_DELETE	0x2E
define VK_HELP		0x2F

define VK_LWIN		0x5B
define VK_RWIN		0x5C
define VK_APPS		0x5D

define VK_NUMPAD0	0x60
define VK_NUMPAD1	0x61
define VK_NUMPAD2	0x62
define VK_NUMPAD3	0x63
define VK_NUMPAD4	0x64
define VK_NUMPAD5	0x65
define VK_NUMPAD6	0x66
define VK_NUMPAD7	0x67
define VK_NUMPAD8	0x68
define VK_NUMPAD9	0x69
define VK_MULTIPLY	0x6A
define VK_ADD		0x6B
define VK_SEPARATOR	0x6C
define VK_SUBTRACT	0x6D
define VK_DECIMAL	0x6E
define VK_DIVIDE	0x6F
define VK_F1		0x70
define VK_F2		0x71
define VK_F3		0x72
define VK_F4		0x73
define VK_F5		0x74
define VK_F6		0x75
define VK_F7		0x76
define VK_F8		0x77
define VK_F9		0x78
define VK_F10		0x79
define VK_F11		0x7A
define VK_F12		0x7B
define VK_F13		0x7C
define VK_F14		0x7D
define VK_F15		0x7E
define VK_F16		0x7F
define VK_F17		0x80
define VK_F18		0x81
define VK_F19		0x82
define VK_F20		0x83
define VK_F21		0x84
define VK_F22		0x85
define VK_F23		0x86
define VK_F24		0x87

define VK_NUMLOCK	0x90
define VK_SCROLL	0x91

define MK_LBUTTON	0x0001
define MK_RBUTTON	0x0002
define MK_SHIFT		0x0004
define MK_CONTROL	0x0008
define MK_MBUTTON	0x0010

define WM_NULL		0x0000
define WM_CREATE	0x0001
define WM_SIZE		0x0005
define WM_SETFOCUS	0x0007
define WM_KILLFOCUS	0x0008
define WM_CLOSE		0x0010
define WM_QUIT		0x0012
define WM_KEYDOWN	0x0100
define WM_KEYUP		0x0101
define WM_CHAR		0x0102
define WM_SYSCHAR	0x0106
define WM_COMMAND	0x0111
define WM_ENTERIDLE	0x0121

define WM_MOUSEMOVE	0x0200
define WM_LBUTTONDOWN	0x0201
define WM_LBUTTONUP	0x0202
define WM_LBUTTONDBLCLK 0x0203
define WM_RBUTTONDOWN	0x0204
define WM_RBUTTONUP	0x0205
define WM_RBUTTONDBLCLK 0x0206
define WM_MBUTTONDOWN	0x0207
define WM_MBUTTONUP	0x0208
define WM_MBUTTONDBLCLK 0x0209
define WM_MOUSEHWHEEL	0x020E
define WM_MOUSEWHEEL	0x020A
define WM_XBUTTONDBLCLK 0x020D

endif

define _C_NORMAL	1
define _C_RETURN	2
define _C_ESCAPE	3
define _C_REOPEN	4

define MOUSECMD		(-2)	; tgetkey()
define KEY_MOUSEUP	(-3)
define KEY_MOUSEDN	(-4)

define KEY_WMCHAR	0x10000 ;

define KEY_ALT		0x10000 ;
define KEY_CTRL		0x20000 ;
define KEY_SHIFT	0x40000 ;


define KEY_BKSP		VK_BACK
define KEY_TAB		VK_TAB
define KEY_SPACE	VK_SPACE
define KEY_ESC		VK_ESCAPE
define KEY_RETURN	VK_RETURN

define KEY_KPRETURN	(VK_RETURN shl 8)

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

define KEY_CTRLINS	(KEY_CTRL or KEY_INSERT)
define KEY_CTRLDEL	(KEY_CTRL or KEY_DELETE)

define KEY_CTRLC	(KEY_CTRL or ('C' shl 8))
define KEY_CTRLV	(KEY_CTRL or ('V' shl 8))

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
