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

typedef struct {
	BYTE	ch;
	BYTE	at;
      } WCHR;

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

extern int (*thelp)(void);
extern int (*tdidle)(void);
extern int (*tupdate)(void);
extern int (*tgetevent)(void);

int _CType GetCursor(COBJ *);
int _CType SetCursor(COBJ *);
int _CType CursorOn(void);
int _CType CursorOff(void);

void _CType wcputa(void *, int, int);
void _CType wcputfg(void *, int, int);
void _CType wcputbg(void *, int, int);
void _CType wcputw(void *, int, unsigned);
int _CType wcputs(void *, int, int, char *);
int _cdecl wcputf(void *, int, int, char *, ...);
void _CType wcenter(void *, int, char *);
void _CType wctitle(void *, int, char *);
void *_CType wcpath(void *, int, char *);
void *_CType wcpbutt(void *, int, int, char *);
void _CType wcstrcpy(char *, void *, int);
void _CType wcmemset(void *, WCHR, size_t);
int _CType wczip(void *, void *, int, int);
int _CType wcunzip(void *, void *, int);
void _CType wcpushst(void *, char *);
void _CType wcpopst(void *);

char _CType getxya(int, int);
char _CType getxyc(int, int);
int _CType getxyw(int, int);
int _CType getxys(int, int, char *, int, int);
void _CType scputa(int, int, int, int);
void _CType scputc(int, int, int, int);
void _CType scputw(int, int, int, int);
void _CType scputfg(int, int, int, int);
void _CType scputbg(int, int, int, int);
int _CType scputs(int, int, int, int, char *);
int _CType scputsEx(int, int, int, int, char *);
int _cdecl scputf(int, int, int, int, char *, ...);
int _cdecl scputfEx(int, int, int, int, char *, ...);
int _CType scpath(int, int, int, char *);
int _CType scenter(int, int, int, char *);

void * _CType rcalloc(RECT, int);
void * _CType rcopen(RECT, int, int, char *, void *);
int _CType rcclose(RECT, int, void *);
int _CType rchide(RECT, int, void *);
int _CType rcshow(RECT, int, void *);
int _CType rcmemsize(RECT, int);
void _CType rcxchg(RECT, void *);
void _CType rcread(RECT, void *);
void _CType rcwrite(RECT, void *);
void _CType rcsetshade(RECT, void *);
void _CType rcclrshade(RECT, void *);
int _CType rcxyrow(RECT, int, int);
void * _CType rcbprc(RECT, void *, int);

void _CType rcframe(RECT, void *, int, int);
int _CType rcinside(RECT, RECT);
RECT _CType rcmove(RECT *, void *, int, int, int);
RECT _CType rcmsmove(RECT *, void *, int);
void _CType rcaddrc(RECT *, RECT, RECT);

DOBJ * _CType rsopen(void *);
int _CType rsmodal(void *);
int _CType rsevent(void *, DOBJ *);
int _CType rsreload(void *, DOBJ *);

int _CType dlopen(DOBJ *, char, char *);
int _CType dlclose(DOBJ *);
int _CType dlhide(DOBJ *);
int _CType dlshow(DOBJ *);
int _CType dlmove(DOBJ *);
int _CType dlinit(DOBJ *);
int _CType dlevent(DOBJ *);
int _CType dllevent(DOBJ *, LOBJ *);
int _CType dlinitobj(DOBJ *, TOBJ *);
int _CType dlmodal(DOBJ *);
int _CType dlmemsize(DOBJ *);
int _CType dlpbuttevent(void);
int _CType dlxcellevent(void);
int _CType dlradioevent(void);
int _CType dlcheckevent(void);
int _CType dlteditevent(void);
int _CType dledit(char *, RECT, int, unsigned);
int _CType getevent(void);
void _CType tupdtime(void);
void _CType tupddate(void);
int _cdecl ermsg(char *, char *, ...);
int _cdecl stdmsg(char *, char *, ...);
int _CType tgetline(const char *, char *, int, int);
void _CType tosetbitflag(TOBJ *, int, unsigned, unsigned);
int _CType togetbitflag(TOBJ *, int, unsigned);
int _CType thelpinit(int (*)(void));
int _CType thelp_set(int (*)(void));
int _CType thelp_pop(void);

int _CType PopEvent(void);
void _CType PushEvent(int);
int _CType getkey(void);
int _CType mousep(void);
int _CType mousey(void);
int _CType mousex(void);
int _CType msloop(void);
void _CType mousewait(int, int, int);

int _CType ConsoleIdle(void);
int _CType ConsolePush(void);
void _CType SetMaxConsole(void);
void _CType SetConsoleSize(int __cols, int __rows);
RECT _CType GetScreenRect(void);

#define ENABLE_WINDOW_INPUT	8
#define ENABLE_MOUSE_INPUT	16

int _CType SetConsoleTitleA( const char * );
int _CType SetConsoleMode( int, int );

#ifdef _UNICODE
 #define SetConsoleTitle SetConsoleTitleW
#else
 #define SetConsoleTitle SetConsoleTitleA
#endif

#ifdef __cplusplus
 }
#endif
#endif
