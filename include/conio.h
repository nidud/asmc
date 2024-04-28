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
    W_CHILD		= 0x0800,	/* is a child */
    W_CURSOR		= 0x1000,
    W_WNDPROC		= 0x2000,
    W_PARENT		= 0x4000,
    W_UNICODE		= 0x8000,
    W_RESBITS		= 0xEFEC,

    O_PBUTT		= 0x0000,
    O_RBUTT		= 0x0001,
    O_CHBOX		= 0x0002,
    O_XCELL		= 0x0003,
    O_TEDIT		= 0x0004,
    O_MENUS		= 0x0005,
    O_TBUTT		= 0x0006,
    O_USERTYPE		= 0x0007,
    O_TYPEMASK		= 0x0007,
    O_TYPEBITS		= 3,

    O_FLAGA		= 0x0008,	/* User defined */
    O_RADIO		= 0x0010,	/* Active (*) */
    O_FLAGB		= 0x0020,	/* User defined */
    O_LIST		= 0x0040,	/* Linked list item */
    O_FLAGC		= 0x0080,	/* User defined */
    O_NOFOCUS		= 0x0100,
    O_DEXIT		= 0x0200,	/* Close dialog and return */
    O_FLAGD		= 0x0400,	/* User defined */
    O_CHILD		= 0x0800,	/* is a child */
    O_FLAGE		= 0x1000,	/* User defined */
    O_WNDPROC		= 0x2000,	/* Item have local event handler */
    O_PARENT		= 0x4000,	/* Item have a child */
    O_STATE		= 0x8000,	/* Item state (ON/OFF) */
    O_RESBITS		= 0xFFFF,
    O_FLAGBITS		= 13,

    O_CHECK		= O_FLAGB,	/* O_CHBOX: Active [x] */
    O_MYBUF		= O_FLAGB,	/* O_TEDIT: static buffer (no alloc) */
    O_AUTOSELECT	= O_FLAGC,	/* O_TEDIT: Auto select text on activation */
    O_USEBEEP		= O_FLAGD,	/* O_TEDIT: Play sound on NoCanDo */
    O_CONTROL		= O_FLAGE,	/* O_TEDIT: Allow _CONTROL chars */
    };

enum TEDITFLAGS {
    TE_MODIFIED		= 0x0001,	/* text is modified */
    TE_OVERWRITE	= 0x0002,	/* selected text on paste */
    TE_DLGEDIT		= 0x0004,	/* return Left/Right */
    TE_USEBEEP		= O_USEBEEP,
    TE_MYBUF		= O_MYBUF,
    TE_CONTROL		= O_CONTROL,
    TE_AUTOSELECT	= O_AUTOSELECT,
    };

#define _D_CLEAR	0x0001		/* args to rcopen() */
#define _D_BACKG	0x0002
#define _D_FOREG	0x0004
#define _D_COLOR	(_D_BACKG|_D_FOREG)

#define _O_PBUTT	0
#define _O_RBUTT	1
#define _O_CHBOX	2
#define _O_XCELL	3
#define _O_TEDIT	4
#define _O_MENUS	5
#define _O_XHTML	6
#define _O_MOUSE	7
#define _O_LLMSU	8
#define _O_LLMSD	9
#define _O_TBUTT	10

enum CURSOR_TYPE {
    CURSOR_DEFAULT,
    CURSOR_BLOCK_BL,
    CURSOR_BLOCK,
    CURSOR_UNDERL_BL,
    CURSOR_UNDERL,
    CURSOR_BAR_BL,
    CURSOR_BAR
    };

typedef int (*DPROC)(void);

typedef unsigned int COLORREF;
typedef COLORREF *LPCOLORREF;

#pragma pack(push, 1)

typedef struct {
    short	X;
    short	Y;
} COORD;

typedef struct {
    union {
	short UnicodeChar;
	char  AsciiChar;
    } Char;
    short  Attributes;
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
    WORD	flags;
    BYTE	count;
    BYTE	index;
    TRECT	rc;
} RIDD, *PIDD;

typedef struct {		/* 8 byte object size in Resource.idd */
    WORD	flags;
    BYTE	count;
    BYTE	syskey;
    TRECT	rc;
} ROBJ, *PROBJ, *PTRES;

typedef struct {
    WORD	flags;
    BYTE	count;
    BYTE	syskey;
    TRECT	rc;
    char *	data;
    DPROC	tproc;
} TOBJ, *PTOBJ;

typedef struct {
    WORD	flags;
    BYTE	count;
    BYTE	index;
    TRECT	rc;
    PCHAR_INFO	wp;
    PTOBJ	object;
} DOBJ, * PDOBJ;

typedef struct {
    int		dlgoff;		/* start index in dialog */
    int		dcount;		/* number of cells (max) */
    int		celoff;		/* cell offset */
    int		numcel;		/* number of visible cells */
    int		count;		/* total number of items in list */
    int		index;		/* index in list buffer */
    void **	list;		/* pointer to list buffer */
    int (*lproc)(void);
} TLIST, LOBJ, *PTLIST;

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
    void *	next;
    void *	prev;
    THWND	hwnd;
    int		message;
    WPARAM	wParam;
    LPARAM	lParam;
} MESSAGE, *PMESSAGE;

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
    PMESSAGE	msgptr;
    int		focus;
    COORD	winpos;		/* old metrics */
    COORD	consize;
    COORD	conmax;
    int		modein;
    int		modeout;
    int		paint;
} TCONSOLE, *PCONSOLE;

typedef void *PINPUT_RECORD;
typedef void *HANDLE;

extern int	_confd;
extern int	_coninpfd;
extern HANDLE	_confh;
extern HANDLE	_coninpfh;

extern PCONSOLE _console;
extern COLORREF _rgbcolortable[16];
extern unsigned char _terminalcolorid[16];
extern unsigned short _unicode850[256];

#define CON_UBEEP	0x0001	/* Use Beep */
#define CON_MOUSE	0x0002	/* Use Mouse */
#define CON_CLIPB	0x0008	/* Use System Clipboard */
#define CON_UTIME	0x0200	/* Use Time */
#define CON_SLEEP	0x2000	/* Wait if set */

extern int console;
extern int _scrrow;		/* Screen rows - 1 */
extern int _scrcol;		/* Screen columns */
extern DOBJ *tdialog;
extern int tclrascii;

extern DPROC	tgeteventA;
extern DPROC	tgeteventW;

DPROC __cdecl _inithelp(DPROC);
DPROC __cdecl _initidle(DPROC);
DPROC __cdecl _initupdate(DPROC);
int __cdecl _thelp(void);
int __cdecl _tidle(void);
int __cdecl _tupdate(void);

DPROC __cdecl _initeventA(DPROC);
DPROC __cdecl _initeventW(DPROC);
int __cdecl geteventA(void);
int __cdecl geteventW(void);
int __cdecl getkeyA(void);
int __cdecl getkeyW(void);
int __cdecl mousepA(void);
int __cdecl mousepW(void);
int __cdecl mouseyA(void);
int __cdecl mouseyW(void);
int __cdecl mousexA(void);
int __cdecl mousexW(void);
void __cdecl msloopA(void);
void __cdecl msloopW(void);
void __cdecl mousewaitA(int, int, int);
void __cdecl mousewaitW(int, int, int);
#ifdef _UNICODE
#define _initevent	_initeventW
#define tgetevent	tgeteventW
#define getevent	geteventW
#define getkey		getkeyW
#define mousep		mousepW
#define mousex		mousexW
#define mousey		mouseyW
#define msloop		msloopW
#define mousewait	mousewaitW
#else
#define _initevent	_initeventA
#define tgetevent	tgeteventA
#define getevent	geteventA
#define getkey		getkeyA
#define mousep		mousepA
#define mousex		mousexA
#define mousey		mouseyA
#define msloop		msloopA
#define mousewait	mousewaitA
#endif

void __cdecl wcputw(PCHAR_INFO, int, int);
int __cdecl wcputsA(PCHAR_INFO, int, int, char *);
int __cdecl wcputsW(PCHAR_INFO, int, int, wchar_t *);
void __cdecl wcputa(PCHAR_INFO, int, int);
void __cdecl wcputbg(PCHAR_INFO, int, int);
void __cdecl wcputfg(PCHAR_INFO, int, int);
void __cdecl wcenterA(PCHAR_INFO, int, char *);
void __cdecl wcenterW(PCHAR_INFO, int, wchar_t *);
void __cdecl wcpathA(PCHAR_INFO, int, char *);
void __cdecl wcpathW(PCHAR_INFO, int, wchar_t *);
void __cdecl wcpbuttA(PCHAR_INFO, int, int, char *);
void __cdecl wcpbuttW(PCHAR_INFO, int, int, wchar_t *);
void __cdecl wcpushstA(PCHAR_INFO, char *);
void __cdecl wcpushstW(PCHAR_INFO, wchar_t *);
void __cdecl wcpopstA(PCHAR_INFO);
void __cdecl wcpopstW(PCHAR_INFO);
void __cdecl wctitleA(PCHAR_INFO, int, char *);
void __cdecl wctitleW(PCHAR_INFO, int, wchar_t *);
void __cdecl wcstrcpyA(char *, PCHAR_INFO, int);
void __cdecl wcstrcpyW(wchar_t *, PCHAR_INFO, int);
void __cdecl wcmemset(PCHAR_INFO, CHAR_INFO, int);

#ifdef _UNICODE
#define wcputs		wcputsW
#define wcenter		wcenterW
#define wcpath		wcpathW
#define wcpbutt		wcpbuttW
#define wcpushst	wcpushstW
#define wcpopst		wcpopstW
#define wctitle		wctitleW
#define wcstrcpy	wcstrcpyW
#else
#define wcputs		wcputsA
#define wcenter		wcenterA
#define wcpath		wcpathA
#define wcpbutt		wcpbuttA
#define wcpushst	wcpushstA
#define wcpopst		wcpopstA
#define wctitle		wctitleA
#define wcstrcpy	wcstrcpyA
#endif

int __cdecl scputsA(int, int, int, int, char *);
int __cdecl scputsW(int, int, int, int, wchar_t *);

#ifdef _UNICODE
#define scputs		scputsW
#else
#define scputs		scputsA
#endif

int __cdecl rcshow(TRECT, int, PCHAR_INFO);
int __cdecl rchide(TRECT, int, PCHAR_INFO);
TRECT __cdecl rcmove(TRECT *, PCHAR_INFO, int, int, int);
int __cdecl rcxyrow(TRECT, int, int);
void * __cdecl rcopen(TRECT, int, int, int, char *, void *);
int __cdecl rcclose(TRECT, int, void *);
TRECT __cdecl rcmsmove(TRECT *, void *, int);

int __cdecl dlmemsize(DOBJ *);
int __cdecl dlhide(DOBJ *);
int __cdecl dlshow(DOBJ *);
int __cdecl dlopen(DOBJ *);
int __cdecl dlinit(DOBJ *);
int __cdecl dlclose(DOBJ *);
int __cdecl dlmove(DOBJ *);
int __cdecl dlevent(DOBJ *);
int __cdecl dllevent(DOBJ *, LOBJ *);
int __cdecl dlmodal(DOBJ *);
int __cdecl dledit(char *, TRECT, int, unsigned);
void __cdecl tosetbitflag(TOBJ *, int, unsigned, unsigned);
int __cdecl togetbitflag(TOBJ *, int, unsigned);

#define _C_NORMAL	1
#define _C_RETURN	2
#define _C_ESCAPE	3
#define _C_REOPEN	4

DOBJ * __cdecl rsopen(void *);
int __cdecl rsmodal(void *);
int __cdecl rsevent(void *, DOBJ *);

int __cdecl _coutA(char *, ...);
int __cdecl _coutW(wchar_t *, ...);
int __cdecl _readinputA(PINPUT_RECORD);
int __cdecl _readinputW(PINPUT_RECORD);
int __cdecl _kbflushA(void);
int __cdecl _kbflushW(void);

#ifdef _UNICODE
#define _cout		_coutW
#define _readinput	_readinputW
#define _kbflush	_kbflushW
#else
#define _cout		_coutA
#define _readinput	_readinputA
#define _kbflush	_kbflushA
#endif

PCHAR_INFO __cdecl _scgetp(int, int, int);
int __cdecl _scgeta(int, int);
int __cdecl _scgetc(int, int);
int __cdecl _scgetw(int, int);
int __cdecl _scputa(int, int, int, int);
int __cdecl _scputfg(int, int, int, int);
int __cdecl _scputbg(int, int, int, int);
int __cdecl _scputc(int, int, int, int);
int __cdecl _scputw(int, int, int, int);
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

#ifdef _UNICODE
#define _scputs		_scputsW
#define _scnputs	_scnputsW
#define _scputf		_scputfW
#define _scpath		_scpathW
#define _sccenter	_sccenterW
#else
#define _scputs		_scputsA
#define _scnputs	_scnputsA
#define _scputf		_scputfA
#define _scpath		_scpathA
#define _sccenter	_sccenterA
#endif

int __cdecl _getcursor(PCURSOR);
int __cdecl _setcursor(PCURSOR);
int __cdecl _cursoron(void);
int __cdecl _cursoroff(void);
int __cdecl _cursortype(int);
int __cdecl _cursorxy(void);
int __cdecl _gotoxy(int, int);
#ifdef __TTY__
extern CURSOR _cursor;
#endif

int __cdecl _rcframe(TRECT, TRECT, PCHAR_INFO, int, int);
int __cdecl _rcmemsize(TRECT, int);
void * __cdecl _rcalloc(TRECT, int);
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
PCHAR_INFO __cdecl _rcbprc(TRECT, TRECT, PCHAR_INFO);
TRECT __cdecl _rcaddrc(TRECT, TRECT);
int __cdecl _rcinside(TRECT, TRECT);

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

#ifdef _UNICODE
#define _rccenter	_rccenterW
#define _rcputs		_rcputsW
#define _rcputf		_rcputfW
#else
#define _rccenter	_rccenterA
#define _rcputs		_rcputsA
#define _rcputf		_rcputfA
#endif

int __cdecl _clipsetA(char *, int);
int __cdecl _clipsetW(wchar_t *, int);
int __cdecl _clipgetA(void);
int __cdecl _clipgetW(void);

#ifdef _UNICODE
#define _clipget	_clipgetW
#define _clipset	_clipsetW
#else
#define _clipget	_clipgetA
#define _clipset	_clipsetA
#endif

int __cdecl _msgboxA(int, char *, char *, ...);
int __cdecl _msgboxW(int, wchar_t *, wchar_t *, ...);
int __cdecl _vmsgboxW(int, wchar_t *, wchar_t *);
int __cdecl _vmsgboxA(int, char *, char *);
int __cdecl _stdmsgA(char *, char *, ...);
int __cdecl _stdmsgW(wchar_t *, wchar_t *, ...);
int __cdecl _errmsgA(char *, char *, ...);
int __cdecl _errmsgW(wchar_t *, wchar_t *, ...);
int __cdecl _syserrA(char *, char *, char *);
int __cdecl _syserrW(wchar_t *, wchar_t *, wchar_t *);
int __cdecl _eropenA(char *);
int __cdecl _eropenW(wchar_t *);

#ifdef _UNICODE
#define _msgbox		_msgboxW
#define _vmsgbox	_vmsgboxW
#define _stdmsg		_stdmsgW
#define _errmsg		_errmsgW
#define _syserr		_syserrW
#define _eropen		_eropenW
#else
#define _msgbox		_msgboxA
#define _vmsgbox	_vmsgboxA
#define _stdmsg		_stdmsgA
#define _errmsg		_errmsgA
#define _syserr		_syserrA
#define _eropen		_eropenA
#endif

int __cdecl _dlopen(TRECT, int, int, int);
int __cdecl _dlinitA(THWND, char *);
int __cdecl _dlinitW(THWND, wchar_t *);
int __cdecl _dlclose(THWND);
int __cdecl _dlmodalA(THWND, TPROC);
int __cdecl _dlmodalW(THWND, TPROC);
int __cdecl _dlhide(THWND);
int __cdecl _dlshow(THWND);
int __cdecl _dlsetfocus(THWND, int);
int __cdecl _dlgetfocus(THWND);
int __cdecl _dlmove(THWND, int);
int __cdecl _dltitleA(THWND, char *);
int __cdecl _dltitleW(THWND, wchar_t *);

#ifdef _UNICODE
#define _dlinit		_dlinitW
#define _dlmodal	_dlmodalW
#define _dltitle	_dltitleW
#else
#define _dlinit		_dlinitA
#define _dlmodal	_dlmodalA
#define _dltitle	_dltitleA
#endif

int __cdecl _tcontrolA(THWND, int, int, char *);
int __cdecl _tcontrolW(THWND, int, int, wchar_t *);
int __cdecl _tiputsA(PTEDIT);
int __cdecl _tiputsW(PTEDIT);
int __cdecl _tiprocA(THWND, int, WPARAM, LPARAM);
int __cdecl _tiprocW(THWND, int, WPARAM, LPARAM);
int __cdecl _tgetlineA(char *, char *, int, int);
int __cdecl _tgetlineW(wchar_t *, wchar_t *, int, int);

#ifdef _UNICODE
#define _tcontrol	_tcontrolW
#define _tiputs		_tiputsW
#define _tiproc		_tiprocW
#define _tgetline	_tgetlineW
#else
#define _tcontrol	_tcontrolA
#define _tiputs		_tiputsA
#define _tiproc		_tiprocA
#define _tgetline	_tgetlineA
#endif

int __cdecl _conslink(THWND);
int __cdecl _consunlink(THWND);
int __cdecl _conpaint(void);
int __cdecl _cbeginpaint(void);
int __cdecl _cendpaint(void);


int __cdecl _sendmessage(THWND, int, WPARAM, LPARAM);
int __cdecl _postmessage(THWND, int, WPARAM, LPARAM);
int __cdecl _getmessageA(PMESSAGE, THWND);
int __cdecl _getmessageW(PMESSAGE, THWND);
int __cdecl _dispatchmsg(PMESSAGE);
int __cdecl _translatemsg(PMESSAGE);
int __cdecl _postquitmsg(THWND, int);
int __cdecl _defwinproc(THWND, int, WPARAM, LPARAM);

#ifdef _UNICODE
#define _getmessage	_getmessageW
#else
#define _getmessage	_getmessageA
#endif

int __cdecl _rsopenA(PTRES);
int __cdecl _rsopenW(PTRES);
int __cdecl _rssave(THWND, char *);

#ifdef _UNICODE
#define _rsopen		<_rsopenW>
#else
#define _rsopen		<_rsopenA>
#endif

int __cdecl _getkey(void);

#define MOUSECMD	(-2)

#define KEY_ALT		0x10000
#define KEY_CTRL	0x20000
#define KEY_SHIFT	0x40000

#define KEY_TAB		0x09
#define KEY_RETURN	0x0D
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

/* Unicode box charcters -- https://www.compart.com/en/unicode/U+2500 */

#define U_LIGHT_HORIZONTAL		0x2500	/* - */
#define U_LIGHT_VERTICAL		0x2502	/* | */
#define U_LIGHT_DOWN_AND_RIGHT		0x250C	/* Single corners */
#define U_LIGHT_DOWN_AND_LEFT		0x2510
#define U_LIGHT_UP_AND_RIGHT		0x2514
#define U_LIGHT_UP_AND_LEFT		0x2518

#define U_LIGHT_VERTICAL_AND_RIGHT	0x251C	/* Insert single corners */
#define U_LIGHT_VERTICAL_AND_LEFT	0x2524
#define U_LIGHT_DOWN_AND_HORIZONTAL	0x252C
#define U_LIGHT_UP_AND_HORIZONTAL	0x2534

#define U_DOUBLE_HORIZONTAL		0x2550	/* = */
#define U_DOUBLE_VERTICAL		0x2551	/* || */
#define U_DOUBLE_DOWN_AND_RIGHT		0x2554	/* Double corners */
#define U_DOUBLE_DOWN_AND_LEFT		0x2557
#define U_DOUBLE_UP_AND_RIGHT		0x255A
#define U_DOUBLE_UP_AND_LEFT		0x255D

#define U_LIGHT_ARC_DOWN_AND_RIGHT	0x256D	/* Single rounded corners */
#define U_LIGHT_ARC_DOWN_AND_LEFT	0x256E
#define U_LIGHT_ARC_UP_AND_LEFT		0x256F
#define U_LIGHT_ARC_UP_AND_RIGHT	0x2570

#define U_UPPER_HALF_BLOCK		0x2580	/* Push Button shade */
#define U_LOWER_HALF_BLOCK		0x2584

#define U_BLACK_POINTER_RIGHT		0x25BA	/* > small */
#define U_BLACK_POINTER_LEFT		0x25C4	/* < */

#define U_BLACK_TRIANGLE_RIGHT		0x25B6	/* > big */
#define U_BLACK_TRIANGLE_LEFT		0x25C0	/* < */
#define U_BLACK_TRIANGLE_UP		0x25B2
#define U_BLACK_TRIANGLE_DOWN		0x25BC

#define U_FULL_BLOCK			0x2588
#define U_LIGHT_SHADE			0x2591
#define U_MEDIOM_SHADE			0x2592
#define U_DARK_SHADE			0x2593

#define U_MIDDLE_DOT			0x00B7	/* Text input */
#define U_BULLET_OPERATOR		0x2219	/* (*) Radio */

#ifdef __cplusplus
 }
#endif
#endif
