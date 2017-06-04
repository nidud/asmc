#ifndef __INC_CONIO
#define __INC_CONIO

#include <keyb.h>
#include <mouse.h>

#define USE_CLIPBOARD

#define CON_UBEEP 0x0001	/* Use Beep			*/
#define CON_MOUSE 0x0002	/* Use Mouse			*/
#define CON_IOLFN 0x0004	/* Use Long File Names		*/
#define CON_CLIPB 0x0008	/* Use System Clipboard		*/
#define CON_INT28 0x0010	/* Use DOS Idle Int 2Fh		*/
#define CON_COLOR 0x0080	/* Use Color			*/
#define CON_UTIME 0x0100	/* Use Time			*/
#define CON_UDATE 0x0200	/* Use Date			*/
#define CON_IMODE 0x1000	/* Init screen mode on startup	*/
#define CON_REVGA 0x2000	/* Restore VGA palette on exit	*/

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

#define _D_STDDLG	(_D_DMOVE|_D_SHADE|_D_CLEAR|_D_COLOR)
#define _D_STDERR	(_D_STDDLG|_D_STERR)

#define O_type(o)	(o->flag & 0x000F)
#define O_clrtype(o)	(o->flag &= 0xFFF0)
#define O_settype(o,t)	(o->flag |= t)

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

#ifdef	__f__
#define CURSOR_NORMAL	1
#define CURSOR_HIDDEN	0
#define CURSOR_SIZE	20
#else
#define CURSOR_NORMAL	0x0607
#define CURSOR_HIDDEN	0x0F00
#endif

#ifdef __cplusplus
 extern "C" {
#endif

enum ColorBackground {
	B_Desktop,
	B_Panel,
	B_Dialog,
	B_Menus,
	B_Error,
	B_Title,
	B_Reverse,
	B_Gray
};

enum ColorForeground {
	F_Title,
	F_Frame,
	F_Files,
	F_System,
	F_Hidden,
	F_5,
	F_6,
	F_Desktop,
	F_Inactive,
	F_Dialog,
	F_Panel,
	F_Subdir,
	F_Menus,
	F_TitleKey,
	F_DialogKey,
	F_MenusKey,
};

#define bg_Desktop	at_background[B_Desktop]
#define bg_Dialog	at_background[B_Dialog]
#define bg_Menus	at_background[B_Menus]
#define bg_Error	at_background[B_Error]
#define bg_Title	at_background[B_Title]
#define bg_Reverse	at_background[B_Reverse]

#define fg_Title	at_background[F_Title]
#define fg_Frame	at_foreground[F_Frame]
#define fg_Files	at_foreground[F_Files]
#define fg_System	at_foreground[F_System]
#define fg_Hidden	at_foreground[F_Hidden]
#define fg_Desktop	at_foreground[F_Desktop]
#define fg_Inactive	at_foreground[F_Inactive]
#define fg_Dialog	at_foreground[F_Dialog]
#define fg_Panel	at_foreground[F_Panel]
#define fg_Subdir	at_foreground[F_Subdir]
#define fg_Menus	at_foreground[F_Menus]
#define fg_TitleKey	at_foreground[F_TitleKey]
#define fg_DialogKey	at_foreground[F_DialogKey]
#define fg_MenusKey	at_foreground[F_MenusKey]


#define MKAT(b,f)	(at_background[b] | at_foreground[f])

#define at_Menus	MKAT(B_Menus,	F_Menus)
#define at_Dialog	MKAT(B_Dialog,	F_Dialog)
#define at_Desktop	MKAT(B_Desktop, F_Desktop)
#define at_MenusKey	MKAT(B_Menus,	F_MenusKey)
#define at_DialogKey	MKAT(B_Dialog,	F_DialogKey)

#define at_Panel	MKAT(B_Panel,	F_Panel)
#define at_Frame	MKAT(B_Panel,	F_Frame)
#define at_Subdir	MKAT(B_Panel,	F_Subdir)
#define at_Files	MKAT(B_Panel,	F_Files)
#define at_System	MKAT(B_Panel,	F_System)
#define at_Hidden	MKAT(B_Panel,	F_Hidden)
#define at_Selected	MKAT(B_Panel,	F_Panel)

#define at_Msdos	MKAT(B_Desktop, F_Desktop)
#define at_Reverse	MKAT(B_Reverse, F_Desktop)
#define at_Error	MKAT(B_Error,	F_Desktop)
#define at_Title	MKAT(B_Title,	F_Title)
#define at_TitleKey	MKAT(B_Title,	F_TitleKey)

#define LoadColor(c)	memcpy(at_background, c, 40)

typedef struct {
	BYTE	backgr[8];
	BYTE	foregr[16];
	BYTE	palett[16];
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
#ifdef __f__
	DWORD	size;
	DWORD	type;
	WORD	xpos;
	WORD	ypos;
#else
	BYTE	xpos;
	BYTE	ypos;
	WORD	type;
#endif
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
#ifndef __f__
#if (LPROG == 0)
	int	p_align16;
#endif
#endif
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
#ifndef __f__
#if (LPROG == 0)
	int	p_align16;
#endif
#endif
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
	int (*	proc)(void);
      } LOBJ;

extern WORD console;
extern DOBJ *tdialog;
extern LOBJ *tdllist;
extern BYTE tmaxascii;
extern BYTE tminascii;
extern BYTE tclrascii;
extern BYTE at_background[8];
extern BYTE at_foreground[16];
extern BYTE at_palett[16];
extern int (*thelp)(void);
extern int (*tupdate)(void);
extern int (*tgetevent)(void);
extern char _FAR *__egaline;

int	_CType getch(void);
int	_CType kbhit(void);
#ifndef __f__
void	_CType beep(int __hz, int __time);
#else
void	Beep(int __hz, int __time);
#define beep Beep
#endif
void	_CType gotoxy(int __x, int __y);
int	_CType cursorget(COBJ *);
int	_CType cursorset(COBJ *);
int	_CType cursorx(void);
int	_CType cursory(void);
int	_CType cursoron(void);
int	_CType cursoroff(void);

void	_CType setpal(int __0_255, int __0_15);
void	_CType resetpal(void);
void	_CType loadpal(unsigned char *__16);

void	_CType wcputa(void _FAR *, int __count, int __at);
void	_CType wcputfg(void _FAR *, int __count, int __at);
void	_CType wcputbg(void _FAR *, int __count, int __at);
void	_CType wcputc(void _FAR *, int __count, int __ch);
void	_CType wcputw(void _FAR *, int __count, WORD);
int	_CType wcputs(void _FAR *, int __lsize, int __count, char *__str);
int	_cdecl wcputf(void _FAR *, int __lsize, int __count, char *__frm, ...);
int	_CType wcenter(WCHR _FAR *, int __lsize, char *__str);
void	_CType wctitle(void _FAR *, int __lsize, char *__title);
int	_CType wcpath(void _FAR *, int __lsize, char *);
void *	_CType wcpbutt(void _FAR *__bp, int __bp_col, int __rc_col, char *);
char *	_CType wcstrmov(char *, WCHR _FAR *, int __lsize);
char *	_CType wcstrcpy(char *, WCHR _FAR *, int __lsize);
void *	_CType wcmemset(void *, WCHR, size_t);
int	_CType wczip(void _FAR *, void *, int __wcount);
/* [0x8000 | wcount] if use color */
int	_CType wcunzip(void *__dest, void *__resource, int __wcount);
void	_CType wcpushst(WCHR _FAR *, char *__statusline);
void	_CType wcpopst(WCHR _FAR *);

#define wc_puts(p, lsize, at, count, cp) \
	wcputs(p, MKW(at, lsize), count, cp)
#define _getxya(x,y)	((char)getxyw(x,y) >> 8)
#define _getxyc(x,y)	(char)getxyw(x,y)

char	_CType getxya(int __x, int __y);
char	_CType getxyc(int __x, int __y);
WORD	_CType getxyw(int __x, int __y);
#ifndef __f__
void *	_CType getxyp(int __x, int __y);
#endif
int	_CType getxys(int, int, char *, int __lsize, WORD __bsize);
void	_CType scputa(int, int, int __count, int __at);
void	_CType scputc(int, int, int __count, int __ch);
void	_CType scputw(int, int, int __count, WORD __sw);
void	_CType scputfg(int __x, int __y, int __count, int __attrib);
void	_CType scputbg(int __x, int __y, int __count, int __attrib);
int	_CType scputs(int, int, int __at, int __max, char *);
int	_cdecl scputf(int, int, int __at, int __max, char *, ...);
void	_CType scclr(int, int, int __col, int __row, int __at);
int	_CType scpath(int, int, int __max, char *);
int	_CType scenter(int, int, int __max, char *);
#define mscputc(x,y,a,c,ch) scputw(x,y,c,MKW(a,ch))

#define _FRAMESINGLE	0
#define _FRAMEDOUBLE	6
#define _INSFRAMEVER	12
#define _INSFRAMEHOR	18

void	_CType scbox(int, int, int __col, int __row, int __type, int __at);
void *	_CType scpush(int __lcount);
void	_CType scpop(void *__scbuf, int __lcount);
void	_CType scpushst(char *__statusline);
void	_CType scpopst(void);
int	_cdecl printfs(char *, ...);

void *	_CType rcalloc(RECT, int);
WCHR *	_CType rcopen(RECT, int, char, char *, WCHR *);
int	_CType rcclose(RECT, int, void *);
int	_CType rchide(RECT, int, void *);
int	_CType rcshow(RECT, int, void *);
int	_CType rcmemsize(RECT, int);
void	_CType rcxchg(RECT, void *);
void	_CType rcread(RECT, void *);
void	_CType rcwrite(RECT, void *);
void	_CType rcsetshade(RECT, void *);
void	_CType rcclrshade(RECT, void *);
int	_CType rcxyrow(RECT, int, int);
#ifndef __f__
WCHR *	_CType rcsprc(RECT);
WCHR *	_CType rcsprcrc(RECT, RECT);
#endif
WCHR *	_CType rcbprc(RECT, void *, int __dlcols);
WCHR *	_CType rcbprcrc(RECT, RECT, void *, int __dlcols);

/* Frame Type 0,6,12,18 */
void	_CType rcframe(RECT, void _FAR *__bp, int __lsize, int __type_color);
int	_CType rcinside(RECT __dlg, RECT __obj);
int	_CType rcmove(RECT *, void *, int, int, int);
int	_CType rcmsmove(RECT *, void *, int);
void	_CType rcaddrc(RECT *, RECT, RECT);

DOBJ *	_CType rsopen(void *);
int	_CType rsmodal(void *);
int	_CType rsevent(void *, DOBJ *);
int	_CType rsreload(void *, DOBJ *);

int	_CType dlopen(DOBJ *, char __at, char *);
int	_CType dlclose(DOBJ *);
int	_CType dlhide(DOBJ *);
int	_CType dlshow(DOBJ *);
int	_CType dlmove(DOBJ *);
int	_CType dlinit(DOBJ *);
int	_CType dlevent(DOBJ *);
int	_CType dllevent(DOBJ *, LOBJ *);
int	_CType dlinitobj(DOBJ *, TOBJ *);
int	_CType dlmodal(DOBJ *);
int	_CType dlmemsize(DOBJ *);
int	_CType dlpbuttevent(void);
int	_CType dlxcellevent(void);
int	_CType dlradioevent(void);
int	_CType dlcheckevent(void);
int	_CType dlteditevent(void);
int	_CType dledit(char *__bp, RECT __sc, int __bsize, int __o_flag);

int	_CType getevent(void);
int	_CType tupdtime(void);
int	_CType tupddate(void);

int	_CType tview(char *, long);
int	_CType tedit(char *, int);

int	_cdecl ermsg(char *, char *, ...);
int	_cdecl stdmsg(char *, char *, ...);
int	_CType tgetline(char *__title, char *__buf, int __lsize, int __bsize);
int	_CType getxys(int, int, char *, int __lsize, WORD __bsize);

void	_CType tosetbitflag(TOBJ *, int __count, int __flag, long __bitflag);
long	_CType togetbitflag(TOBJ *, int __count, int __flag);

int	_CType thelpinit(int (*)(void));
int	_CType thelp_set(int (*)(void));
int	_CType thelp_pop(void);

int	_CType editpal(void);
int	_CType editattrib(void);
int	_CType editcolor(void);

#ifdef __cplusplus
 }
#endif
#endif
