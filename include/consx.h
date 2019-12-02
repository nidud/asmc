#ifndef __INC_CONSX
#define __INC_CONSX
#if !defined(__INC_DEFS)
 #include <defs.h>
#endif

#define _D_DOPEN	0x0001
#define _D_ONSCR	0x0002
#define _D_DMOVE	0x0004
#define _D_SHADE	0x0008
#define _D_MYBUF	0x0010
#define _D_RCNEW	0x0020
#define _D_RESAT	0x0040
#define _D_DHELP	0x0080
#define _D_CLEAR	0x0100
#define _D_BACKG	0x0200
#define _D_FOREG	0x0400
#define _D_COLOR	(_D_BACKG|_D_FOREG)
#define _D_STERR	0x1000
#define _D_MENUS	0x2000
#define _D_MUSER	0x4000
#define _D_RCSAVE	0x70CC

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

#define _O_RADIO	0x0010
#define _O_FLAGB	0x0020
#define _O_LLIST	0x0040
#define _O_DTEXT	0x0080
#define _O_CONTR	0x0100
#define _O_DEXIT	0x0200
#define _O_PBKEY	0x0400
#define _O_GLCMD	0x1000
#define _O_EVENT	0x2000
#define _O_CHILD	0x4000
#define _O_STATE	0x8000
#define _O_DEACT	_O_STATE

#define _C_NORMAL	1
#define _C_RETURN	2
#define _C_ESCAPE	3
#define _C_REOPEN	4

#define ESC		0x011B
#define BKSP		0x0E08
#define TAB		0x0F09
#define ENTER		0x1C0D
#define SPACE		0x3920
#define HOME		0x4700
#define UP		0x4800
#define PGUP		0x4900
#define LEFT		0x4B00
#define RIGHT		0x4D00
#define END		0x4F00
#define DOWN		0x5000
#define PGDN		0x5100
#define INS		0x5200
#define DEL		0x5300

#define F1		0x3B00
#define F2		0x3C00
#define F3		0x3D00
#define F4		0x3E00
#define F5		0x3F00
#define F6		0x4000
#define F7		0x4100
#define F8		0x4200
#define F9		0x4300
#define F10		0x4400
#define F11		0x8500
#define F12		0x8600

#define CTRLF1		0x5E00
#define CTRLF2		0x5F00
#define CTRLF3		0x6000
#define CTRLF4		0x6100
#define CTRLF5		0x6200
#define CTRLF6		0x6300
#define CTRLF7		0x6400
#define CTRLF8		0x6500
#define CTRLF9		0x6600
#define CTRLF10		0x6700
#define CTRLF11		0xA800
#define CTRLF12		0xA900

#define CTRLB		0x3002

#define ALTF1		0x6800
#define ALTF2		0x6900
#define ALTF3		0x6A00
#define ALTF4		0x6B00
#define ALTF5		0x6C00
#define ALTF6		0x6D00
#define ALTF7		0x6E00
#define ALTF8		0x6F00
#define ALTF9		0x7000
#define ALTF10		0x7100
#define ALTF11		0xB200
#define ALTF12		0xB300

#define MOUSECMD	(-1)

#ifdef __cplusplus
 extern "C" {
#endif

typedef struct {
	BYTE	foregr[16];
	BYTE	backgr[16];
      } COLOR;
#if 0
typedef union {
	WORD	w;
	struct {
	 BYTE	ch;
	 BYTE	at;
	};
      } WCHR;
#else
typedef struct {
	 BYTE	ch;
	 BYTE	at;
      } WCHR;
#endif
typedef struct {
	BYTE	x;
	BYTE	y;
	BYTE	col;
	BYTE	row;
      } RECT;

typedef struct {	/* CONSOLE_CURSOR_INFO */
	DWORD	size;
	DWORD	visible;
	WORD	xpos;
	WORD	ypos;
      } COBJ;

typedef struct {
	WORD	flag;
	BYTE	count;
	BYTE	ascii;
	RECT	rc;
      } FOBJ;

typedef struct { /* Note: must align 16 byte */
	WORD	flag;
	BYTE	count;
	BYTE	ascii;
	RECT	rc;
	void *	data;
	int (*	proc)(void);
      } TOBJ;

typedef struct { /* Note: must align 16 byte */
	WORD	flag;
	BYTE	count;
	BYTE	index;
	RECT	rc;
	WCHR *	wp;
	TOBJ *	object;
      } DOBJ;

typedef struct {
	WORD	flag;
	WORD	key;
	RECT	rc;
	void *	data;
	int (*	proc)(void);
      } MOBJ;


typedef struct {
	WORD	memsize;
	FOBJ	dialog;
	FOBJ	object[1];
      } ROBJ;

typedef struct {
	WORD	key;
	int (*	proc)(void);
      } GCMD;

typedef struct {
	WORD	dlgoff;
	WORD	dcount;
	WORD	celoff;
	WORD	numcel;
	WORD	count;
	WORD	index;
	void ** list;
	int  (* proc)(void);
      } LOBJ;


#define CON_UBEEP	0x0001	/* Use Beep */
#define CON_MOUSE	0x0002	/* Use Mouse */
#define CON_IOSFN	0x0004	/* Use Long File Names */
#define CON_CLIPB	0x0008	/* Use System Clipboard */
#define CON_ASCII	0x0010	/* Use Ascii symbol */
#define CON_NTCMD	0x0020	/* Use NT Prompt */
#define CON_CMDENV	0x0040	/* CMD Compatible Mode */
#define CON_IMODE	0x0080	/* Init screen mode on startup */
#define CON_UTIME	0x0200	/* Use Time */
#define CON_UDATE	0x0400	/* Use Date */
#define CON_LTIME	0x0800	/* Use Long Time HH:MM:SS */
#define CON_LDATE	0x1000	/* Use Long Date YYYY-MM-DD */
#define CON_SLEEP	0x2000	/* Wait if set */
#define CON_SIMDE	0x4000	/* Use SSE Functions */
#define CON_WIN95	0x8000	/* Windows 95 mode if set */

extern int console;
extern int _scrrow;		/* Screen rows - 1 */
extern int _scrcol;		/* Screen columns */
extern DOBJ *tdialog;
extern LOBJ *tdllist;
extern BYTE tclrascii;
extern BYTE at_background[16];
extern BYTE at_foreground[16];

typedef int (*iddfp_t)(void);

extern iddfp_t thelp;
extern iddfp_t tdidle;
extern iddfp_t tupdate;
extern iddfp_t tgetevent;

int __cdecl CursorGet(COBJ *);
int __cdecl CursorSet(COBJ *);
int __cdecl CursorOn(void);
int __cdecl CursorOff(void);

void __cdecl wcputa(void *, int, int);
void __cdecl wcputfg(void *, int, int);
void __cdecl wcputbg(void *, int, int);
void __cdecl wcputw(void *, int, unsigned);
int __cdecl wcputs(void *, int, int, char *);
int _cdecl wcputf(void *, int, int, char *, ...);
void __cdecl wcenter(void *, int, char *);
void __cdecl wctitle(void *, int, char *);
void *__cdecl wcpath(void *, int, char *);
void *__cdecl wcpbutt(void *, int, int, char *);
void __cdecl wcstrcpy(char *, void *, int);
void __cdecl wcmemset(void *, WCHR, size_t);
int __cdecl wczip(void *, void *, int, int);
int __cdecl wcunzip(void *, void *, int);
void __cdecl wcpushst(void *, char *);
void __cdecl wcpopst(void *);

char __cdecl getxya(int, int);
char __cdecl getxyc(int, int);
int __cdecl getxyw(int, int);
int __cdecl getxys(int, int, char *, int, int);
void __cdecl scputa(int, int, int, int);
void __cdecl scputc(int, int, int, int);
void __cdecl scputw(int, int, int, int);
void __cdecl scputfg(int, int, int, int);
void __cdecl scputbg(int, int, int, int);
int __cdecl scputs(int, int, int, int, char *);
int __cdecl scputsEx(int, int, int, int, char *);
int _cdecl scputf(int, int, int, int, char *, ...);
int _cdecl scputfEx(int, int, int, int, char *, ...);
int __cdecl scpath(int, int, int, char *);
int __cdecl scenter(int, int, int, char *);

void * __cdecl rcalloc(RECT, int);
void * __cdecl rcopen(RECT, int, int, char *, void *);
int __cdecl rcclose(RECT, int, void *);
int __cdecl rchide(RECT, int, void *);
int __cdecl rcshow(RECT, int, void *);
int __cdecl rcmemsize(RECT, int);
void __cdecl rcxchg(RECT, void *);
void __cdecl rcread(RECT, void *);
void __cdecl rcwrite(RECT, void *);
void __cdecl rcsetshade(RECT, void *);
void __cdecl rcclrshade(RECT, void *);
int __cdecl rcxyrow(RECT, int, int);
void * __cdecl rcbprc(RECT, void *, int);

void __cdecl rcframe(RECT, void *, int, int);
int __cdecl rcinside(RECT, RECT);
RECT __cdecl rcmove(RECT *, void *, int, int, int);
RECT __cdecl rcmsmove(RECT *, void *, int);
void __cdecl rcaddrc(RECT *, RECT, RECT);

DOBJ * __cdecl rsopen(void *);
int __cdecl rsmodal(void *);
int __cdecl rsevent(void *, DOBJ *);
int __cdecl rsreload(void *, DOBJ *);

int __cdecl dlopen(DOBJ *, char, char *);
int __cdecl dlclose(DOBJ *);
int __cdecl dlhide(DOBJ *);
int __cdecl dlshow(DOBJ *);
int __cdecl dlmove(DOBJ *);
int __cdecl dlinit(DOBJ *);
int __cdecl dlevent(DOBJ *);
int __cdecl dllevent(DOBJ *, LOBJ *);
int __cdecl dlinitobj(DOBJ *, TOBJ *);
int __cdecl dlmodal(DOBJ *);
int __cdecl dlmemsize(DOBJ *);
int __cdecl dlpbuttevent(void);
int __cdecl dlxcellevent(void);
int __cdecl dlradioevent(void);
int __cdecl dlcheckevent(void);
int __cdecl dlteditevent(void);
int __cdecl dledit(char *, RECT, int, unsigned);
int __cdecl getevent(void);
void __cdecl tupdtime(void);
void __cdecl tupddate(void);
int _cdecl ermsg(char *, char *, ...);
int _cdecl stdmsg(char *, char *, ...);
int __cdecl tgetline(const char *, char *, int, int);
void __cdecl tosetbitflag(TOBJ *, int, unsigned, unsigned);
int __cdecl togetbitflag(TOBJ *, int, unsigned);
int __cdecl thelpinit(int (*)(void));
int __cdecl thelp_set(int (*)(void));
int __cdecl thelp_pop(void);

int __cdecl PopEvent(void);
void __cdecl PushEvent(int);
int __cdecl getkey(void);
int __cdecl mousep(void);
int __cdecl mousey(void);
int __cdecl mousex(void);
int __cdecl msloop(void);
void __cdecl mousewait(int, int, int);

int __cdecl ConsoleIdle(void);
int __cdecl ConsolePush(void);
void __cdecl SetMaxConsole(void);
void __cdecl SetConsoleSize(int __cols, int __rows);
RECT __cdecl GetScreenRect(void);
int __cdecl eropen(const char *__file);

#define ENABLE_WINDOW_INPUT	8
#define ENABLE_MOUSE_INPUT	16

int WINAPI SetConsoleTitleA( const char * );
int WINAPI SetConsoleMode( int, int );

#ifdef _UNICODE
 #define SetConsoleTitle SetConsoleTitleW
#else
 #define SetConsoleTitle SetConsoleTitleA
#endif

#ifdef __cplusplus
 }
#endif
#endif
