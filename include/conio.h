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
enum CONIO_RETRO_COLORS {
    BLACK,		// 0
    BLUE,		// 1
    GREEN,		// 2
    CYAN,		// 3
    RED,		// 4
    MAGENTA,		// 5
    BROWN,		// 6
    LIGHTGRAY,		// 7
    DARKGRAY,		// 8
    LIGHTBLUE,		// 9
    LIGHTGREEN,		// 10
    LIGHTCYAN,		// 11
    LIGHTRED,		// 12
    LIGHTMAGENTA,	// 13
    YELLOW,		// 14
    WHITE		// 15
    };
#endif


_CRTIMP char * __cdecl _cgets(char *);
_CRTIMP void __cdecl _clreol(void);
_CRTIMP void __cdecl _clrscr(void);
_CRTIMP int __cdecl _cputs(const char *);
_CRTIMP int __cdecl _getch(void);
_CRTIMP int __cdecl _getche(void);
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


enum VTI_COLOR { /* Virtual Terminal Color Index */
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
    };

enum ColorBackground {
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
    };

enum ColorForeground {
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
    };

extern unsigned char at_background[16];
extern unsigned char at_foreground[16];

enum BOXTYPE {
    BOX_SINGLE,			/* Single corners */
    BOX_DOUBLE,			/* Double corners */
    BOX_SINGLE_VERTICAL,	/* Single insert corners */
    BOX_SINGLE_HORIZONTAL,
    BOX_SINGLE_ARC,		/* Single rounded corners */
    BOX_CLEAR
    };

enum _DLMOVE_DIRECTION {
    TW_MOVELEFT,
    TW_MOVERIGHT,
    TW_MOVEUP,
    TW_MOVEDOWN
    };

enum TTYPE {
    T_WINDOW,			/* Main window */
    T_PUSHBUTTON,		/*  [ > Selectable text < ] + shade */
    T_RADIOBUTTON,		/*  (*) */
    T_CHECKBOX,			/*  [x] */
    T_XCELL,			/*  [ Selectable text ] */
    T_EDIT,			/*  [Text input] */
    T_MENUITEM,			/*  XCELL + Stausline info */
    T_TEXTAREA,			/*  [Selectable text] */
    T_TEXTBUTTON,		/*  [>Selectable text<] */
    T_MOUSERECT,		/*  Clickable area -- no focus */
    T_SCROLLUP,			/*  Clickable area for list items */
    T_SCROLLDOWN,
    };

enum TFLAGS {
    W_ISOPEN		= 0x0001,
    W_VISIBLE		= 0x0002,
    W_MOVEABLE		= 0x0004,
    W_SHADE		= 0x0008,
    W_MYBUF		= 0x0010,	/* do not delete on exit (static) */
    W_RCNEW		= 0x0020,	/* dlclose -- delete dialog if set */
    W_RESAT		= 0x0040,	/* attrib is index in color table (rcedit) */
    W_DHELP		= 0x0080,	/* execute thelp() if set */
    W_TRANSPARENT	= 0x0100,
    W_CONSOLE		= 0x0200,
    W_LIST		= 0x0400,
    W_STDLG		= 0x0800,
    W_STERR		= 0x1000,	/* error color (red) */
    W_MENUS		= 0x2000,	/* menus color (gray), no title */
    W_UTF16		= 0x8000,
    W_RESBITS		= 0xF9FC,

    O_MODIFIED		= 0x0001,	/* dialog text */
    O_OVERWRITE		= 0x0002,	/* selected text on paste */
    O_USEBEEP		= 0x0004,
    O_MYBUF		= 0x0008,	/* T_EDIT -- no alloc */
    O_RADIO		= 0x0010,	/* Active (*) */
    O_CHECK		= 0x0020,	/* Active [x] */
    O_LIST		= 0x0040,	/* Linked list item */
    O_SELECT		= 0x0080,	/* Select text on activation */
    O_CONTROL		= 0x0100,	/* Allow _CONTROL chars */
    O_DEXIT		= 0x0200,	/* Close dialog and return 0: Cancel */
    O_PBKEY		= 0x0400,	/* Return result if short key used */
    O_DLGED		= 0x0800,	/* dialog text -- return Left/Right */
    O_GLOBAL		= 0x1000,	/* Item contain global short-key table */
    O_EVENT		= 0x2000,	/* Item have local event handler */
    O_CHILD		= 0x4000,	/* Item have a child */
    O_STATE		= 0x8000,	/* State (ON/OFF) */
    O_RESBITS		= 0xFFF0,

    W_WNDPROC	    = 0x00010000,
    W_CHILD	    = 0x00020000,	/* is a child */
    O_CURSOR	    = 0x00020000,
    };

enum RESOURCE_FLAGS {

    _D_DOPEN		= 0x0001,
    _D_ONSCR		= 0x0002,
    _D_DMOVE		= 0x0004,
    _D_SHADE		= 0x0008,
    _D_MYBUF		= 0x0010,	/* do not delete on exit (static) */
    _D_RCNEW		= 0x0020,	/* dlclose -- delete dialog if set */
    _D_RESAT		= 0x0040,	/* attrib is index in color table (rcedit) */
    _D_DHELP		= 0x0080,	/* execute thelp() if set */
    _D_CLEAR		= 0x0100,	/* args on open/create */
    _D_BACKG		= 0x0200,
    _D_FOREG		= 0x0400,
    _D_STDLG		= 0x0800,
    _D_STERR		= 0x1000,	/* error color (red) */
    _D_MENUS		= 0x2000,	/* menus color (gray), no title */
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
    };

enum CURSOR_TYPE {
    CURSOR_DEFAULT,
    CURSOR_BLOCK_BL,
    CURSOR_BLOCK,
    CURSOR_UNDERL_BL,
    CURSOR_UNDERL,
    CURSOR_BAR_BL,
    CURSOR_BAR
    };

typedef int __cdecl (*DPROC)(void);

typedef unsigned int COLORREF;
typedef COLORREF *LPCOLORREF;

#pragma pack(push, 1)

typedef struct {
    short X;
    short Y;
} COORD;

typedef struct {
    union {
	wchar_t UnicodeChar;
	char	AsciiChar;
    } Char;
    wchar_t Attributes;
} CHAR_INFO, *PCHAR_INFO;

typedef struct {
    BYTE	x;
    BYTE	y;
    BYTE	type;
    BYTE	visible;
} CURSOR, *PCURSOR;

typedef struct {
    BYTE	x;
    BYTE	y;
    BYTE	col;
    BYTE	row;
} TRECT, *PTRECT;

typedef struct {
    WORD	size;
    WORD	flag;
    BYTE	count;
    BYTE	index;
    TRECT	rc;
} RIDD, *PIDD;

typedef struct {		/* 8 byte object size in Resource.idd */
    WORD	flag;
    BYTE	count;
    BYTE	index;
    TRECT	rc;
} ROBJ, *PROBJ, *PTRES;

typedef struct {
    WORD	flag;
    BYTE	count;
    BYTE	index;
    TRECT	rc;
    void *	data;
    DPROC	tproc;
} TOBJ, *PTOBJ;

typedef struct {
    WORD	flag;
    BYTE	count;
    BYTE	index;
    TRECT	rc;
    PCHAR_INFO	wp;
    PTOBJ	object;
} DOBJ, *PDOBJ;

typedef struct {
    int		dlgoff;		/* start index in dialog */
    int		dcount;		/* number of cells (max) */
    int		celoff;		/* cell offset */
    int		numcel;		/* number of visible cells */
    int		count;		/* total number of items in list */
    int		index;		/* index in list buffer */
    char *	list[];		/* pointer to list buffer */
} TLIST, *PTLIST;

typedef struct {
    int		flags;
    BYTE	type;
    BYTE	syskey;
    BYTE	count;		/* item: extra buffer size in para */
    BYTE	index;
    TRECT	rc;
} TDLG, *PTDLG, *THWND;

#pragma pack(pop)

typedef int (*TPROC)(THWND, int, WPARAM, LPARAM);

typedef struct {
    char	base;		/* base pointer */
    int		flags;		/* config */
    int		xpos;		/* window x */
    int		ypos;		/* window y */
    int		scols;		/* size of screen-line */
    int		bcols;		/* size of buffer-line */
    int		xoffs;		/* x offset on screen */
    int		boffs;		/* base offset - start of screen-line */
    int		bcount;		/* byte count in line (expanded) */
    int		clip_so;	/* Clipboard start offset */
    int		clip_eo;	/* Clipboard end offset */
    CHAR_INFO	clrattrib;	/* clear attrib/char */
} TEDIT, *PTEDIT;


typedef struct {
    union {
     struct {
      BYTE	state;
      BYTE	flags;
      BYTE	x;
      BYTE	y;
      TRECT	rc;
     };
     PTEDIT	tedit;
    };
    PTLIST	llist;
} TCONTEXT;

typedef struct {
    int		flags;
    BYTE	type;
    BYTE	syskey;
    BYTE	count;		/* item: extra buffer size in para */
    BYTE	index;
    TRECT	rc;
    CURSOR	cursor;
    PCHAR_INFO	window;
    THWND	next;
    THWND	prev;
    THWND	object;
    TPROC	winproc;
    TCONTEXT	context;
    char *	buffer;
} TCLASS, *PTCLASS;


typedef struct {
    int		flags;
    BYTE	type;
    BYTE	syskey;
    BYTE	count;		/* item: extra buffer size in para */
    BYTE	index;
    TRECT	rc;
    CURSOR	cursor;
    PCHAR_INFO	window;
    THWND	next;
    THWND	prev;
    THWND	object;
    TPROC	winproc;
    TCONTEXT	context;
    char *	buffer;
    LPCOLORREF	color;
    COORD	winpos;		/* old metrics */
    COORD	consize;
    COORD	conmax;
    int		modein;
    int		modeout;
    int		paint;
} TCONSOLE, *PCONSOLE;

typedef struct {
    void *	next;
    THWND	hwnd;
    int		message;
    WPARAM	wParam;
    LPARAM	lParam;
} MESSAGE, *PMESSAGE;

typedef void *PINPUT_RECORD;

DPROC __cdecl _inithelp(DPROC);
DPROC __cdecl _initidle(DPROC);
DPROC __cdecl _initupdate(DPROC);

int __cdecl _thelp(void);
int __cdecl _tidle(void);
int __cdecl _tupdate(void);

int __cdecl _coutA(char *, ...);
int __cdecl _coutW(wchar_t *, ...);
int __cdecl _readinputA(PINPUT_RECORD);
int __cdecl _readinputW(PINPUT_RECORD);
int __cdecl _kbflushA(void);
int __cdecl _kbflushW(void);

int __cdecl _scgetp(int, int, int);
int __cdecl _scgeta(int, int);
int __cdecl _scgetc(int, int);
int __cdecl _scgetw(int, int);
int __cdecl _scputa(int, int, int, int);
int __cdecl _scputfg(int, int, int, int);
int __cdecl _scputbg(int, int, int, int);
int __cdecl _scputc(int, int, int, int);
int __cdecl _scputw(int, int, int, CHAR_INFO);
int __cdecl _scgetl(int, int, int);
int __cdecl _scputl(int, int, int, PCHAR_INFO);
int __cdecl _scputsA(int, int, char *);
int __cdecl _scputsW(int, int, wchar_t *);
int __cdecl _scnputsA(int, int, int, char *);
int __cdecl _scnputsW(int, int, int, wchar_t *);
int __cdecl _scputfA(int, int, char *, ...);
int __cdecl _scputfW(int, int, wchar_t *, ...);
int __cdecl _scpathA(int, int, int, char *);
int __cdecl _scpathW(int, int, int, wchar_t *);
int __cdecl _sccenterA(int, int, int, char *);
int __cdecl _sccenterW(int, int, int, wchar_t *);
int __cdecl _scframe(TRECT, int, int);

int __cdecl _getcursor(PCURSOR);
int __cdecl _setcursor(PCURSOR);
int __cdecl _cursoron(void);
int __cdecl _cursoroff(void);
int __cdecl _cursortype(int);
int __cdecl _cursorxy(void);
int __cdecl _gotoxy(int, int);
#ifdef __TTY__
extern	CURSOR _cursor;
#endif
int __cdecl _rcframe(TRECT, TRECT, PCHAR_INFO, int, int);
int __cdecl _rcmemsize(TRECT, int);
int __cdecl _rcalloc(TRECT, int);
int __cdecl _rcread(TRECT, PCHAR_INFO);
int __cdecl _rcwrite(TRECT, PCHAR_INFO);
int __cdecl _rcxchg(TRECT, PCHAR_INFO);
int __cdecl _rcmovel(TRECT, PCHAR_INFO);
int __cdecl _rcmover(TRECT, PCHAR_INFO);
int __cdecl _rcmoveu(TRECT, PCHAR_INFO);
int __cdecl _rcmoved(TRECT, PCHAR_INFO);
int __cdecl _rczip(TRECT, void *, PCHAR_INFO, int);
int __cdecl _rcunzip(TRECT, PCHAR_INFO, void *, int);
int __cdecl _rcunzipat(TRECT, PCHAR_INFO);
int __cdecl _rcbprc(TRECT, TRECT, PCHAR_INFO);
int __cdecl _rcgetw(TRECT, PCHAR_INFO, int, int);
int __cdecl _rcputc(TRECT, TRECT, PCHAR_INFO, int);
int __cdecl _rcputa(TRECT, TRECT, PCHAR_INFO, int);
int __cdecl _rcputfg(TRECT, TRECT, PCHAR_INFO, int);
int __cdecl _rcputbg(TRECT, TRECT, PCHAR_INFO, int);
int __cdecl _rcshade(TRECT, PCHAR_INFO, int);
int __cdecl _rcclear(TRECT, PCHAR_INFO, CHAR_INFO);
int __cdecl _rccenterA(TRECT, PCHAR_INFO, TRECT, int, char *);
int __cdecl _rccenterW(TRECT, PCHAR_INFO, TRECT, int, wchar_t *);
int __cdecl _rcputsA(TRECT, PCHAR_INFO, int, int, int, char *);
int __cdecl _rcputsW(TRECT, PCHAR_INFO, int, int, int, wchar_t *);
int __cdecl _rcputfA(TRECT, PCHAR_INFO, int, int, int, char *, ...);
int __cdecl _rcputfW(TRECT, PCHAR_INFO, int, int, int, wchar_t *, ...);

int __cdecl _clipsetA(char *, int);
int __cdecl _clipsetW(wchar_t *, int);
int __cdecl _clipgetA(void);
int __cdecl _clipgetW(void);

int __cdecl _msgboxA(int, char *, char *, ...);
int __cdecl _msgboxW(int, wchar_t *, wchar_t *, ...);
int __cdecl _vmsgboxW(int, wchar_t *, wchar_t *);
int __cdecl _vmsgboxA(int, char *, char *);
int __cdecl _stdmsgA(char *, char *, ...);
int __cdecl _stdmsgW(wchar_t *, wchar_t *, ...);
int __cdecl _errmsgA(char *, char *, ...);
int __cdecl _errmsgW(wchar_t *, wchar_t *, ...);
int __cdecl _syserrA(int, char *);
int __cdecl _syserrW(int, wchar_t *);

int __cdecl _dlopen(TRECT, int, int, int);
int __cdecl _dlinitA(THWND, char *);
int __cdecl _dlinitW(THWND, wchar_t *);
int __cdecl _dlclose(THWND);
int __cdecl _dlmodal(THWND, TPROC);
int __cdecl _dlhide(THWND);
int __cdecl _dlshow(THWND);
int __cdecl _dlsetfocus(THWND, int);
int __cdecl _dlgetfocus(THWND);
int __cdecl _dlmove(THWND, int);
int __cdecl _dltitleA(THWND, char *);
int __cdecl _dltitleW(THWND, wchar_t *);

int __cdecl _tcontrolA(THWND, int, int, char *);
int __cdecl _tcontrolW(THWND, int, int, wchar_t *);
int __cdecl _tiputsA(PTEDIT);
int __cdecl _tiputsW(PTEDIT);
int __cdecl _tiprocA(THWND, int, WPARAM, LPARAM);
int __cdecl _tiprocW(THWND, int, WPARAM, LPARAM);

int __cdecl _conslink(THWND);
int __cdecl _consunlink(THWND);
int __cdecl _conpaint(void);
int __cdecl _cbeginpaint(void);
int __cdecl _cendpaint(void);

int __cdecl _sendmessage(THWND, int, WPARAM, LPARAM);
int __cdecl _postmessage(THWND, int, WPARAM, LPARAM);
int __cdecl _getmessage(PMESSAGE, THWND);
int __cdecl _dispatchmsg(PMESSAGE);
int __cdecl _translatemsg(PMESSAGE);
int __cdecl _postquitmsg(THWND, int);
int __cdecl _defwinproc(THWND, int, WPARAM, LPARAM);

int __cdecl _rsopenA(PTRES);
int __cdecl _rsopenW(PTRES);
int __cdecl _rssave(THWND, char *);

int __cdecl _getkey(void);

#ifdef _UNICODE
#define _cout		_coutW
#define _scputs		_scputsW
#define _scnputs	_scnputsW
#define _scputf		_scputfW
#define _scpath		_scpathW
#define _sccenter	_sccenterW
#define _rccenter	_rccenterW
#define _rcputs		_rcputsW
#define _rcputf		_rcputfW
#define _dlinit		_dlinitW
#define _dltitle	_dltitleW
#define _rsopen		_rsopenW
#define _tcontrol	_tcontrolW
#define _tiputs		_tiputsW
#define _tiproc		_tiprocW
#define _msgbox		_msgboxW
#define _vmsgbox	_vmsgboxW
#define _stdmsg		_stdmsgW
#define _errmsg		_errmsgW
#define _syserr		_syserrW
#define _clipget	_clipgetW
#define _clipset	_clipsetW
#define _readinput	_readinputW
#define _kbflush	_kbflushW
#else
#define _cout		_coutA
#define _scputs		_scputsA
#define _scnputs	_scnputsA
#define _scputf		_scputfA
#define _scpath		_scpathA
#define _sccenter	_sccenterA
#define _rccenter	_rccenterA
#define _rcputs		_rcputsA
#define _rcputf		_rcputfA
#define _dlinit		_dlinitA
#define _dltitle	_dltitleA
#define _rsopen		_rsopenA
#define _tcontrol	_tcontrolA
#define _tiputs		_tiputsA
#define _tiproc		_tiprocA
#define _msgbox		_msgboxA
#define _vmsgbox	_vmsgboxA
#define _stdmsg		_stdmsgA
#define _errmsg		_errmsgA
#define _syserr		_syserrA
#define _clipget	_clipgetA
#define _clipset	_clipsetA
#define _readinput	_readinputA
#define _kbflush	_kbflushA
#endif

#define KEY_ESC		0x1B
#define KEY_SPACE	0x20
#define KEY_PGUP	0x2100
#define KEY_PGDN	0x2200
#define KEY_END		0x2300
#define KEY_HOME	0x2400
#define KEY_LEFT	0x2500
#define KEY_UP		0x2600
#define KEY_RIGHT	0x2700
#define KEY_DOWN	0x2800
#define KEY_INSERT	0x2D00
#define KEY_DELETE	0x2E00

#define KEY_F1		0x7000
#define KEY_F2		0x7100
#define KEY_F3		0x7200
#define KEY_F4		0x7300
#define KEY_F5		0x7400
#define KEY_F6		0x7500
#define KEY_F7		0x7600
#define KEY_F8		0x7700
#define KEY_F9		0x7800
#define KEY_F10		0x7900
#define KEY_F11		0x7A00
#define KEY_F12		0x7B00

#ifdef __cplusplus
 }
#endif
#endif
