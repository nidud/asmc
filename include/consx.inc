include conio.inc

.xlist

B_Desktop	equ 0		; at_background
B_Panel		equ 1
B_Dialog	equ 2
B_Menus		equ 3
B_Error		equ 4
B_Title		equ 5
B_Inverse	equ 6
B_Gray		equ 7
B_PushButt	equ 8
B_InvPanel	equ 9
B_InvMenus	equ 10
B_TextView	equ 12
B_TextEdit	equ 13

F_Title		equ 0		; at_foreground
F_Frame		equ 1
F_Files		equ 2
F_System	equ 3
F_Hidden	equ 4
F_PBShade	equ 5
F_KeyBar	equ 6
F_Desktop	equ 7
F_Inactive	equ 8
F_Dialog	equ 9
F_Panel		equ 10
F_Subdir	equ 11
F_Menus		equ 12
F_TitleKey	equ 13
F_DialogKey	equ 14
F_MenusKey	equ 15
F_TextView	equ 16+14
F_TextEdit	equ 16+15

CON_UBEEP	equ 0x0001	; Use Beep
CON_MOUSE	equ 0x0002	; Use Mouse
CON_IOSFN	equ 0x0004	; Use Long File Names
CON_CLIPB	equ 0x0008	; Use System Clipboard
CON_ASCII	equ 0x0010	; Use Ascii symbol
CON_NTCMD	equ 0x0020	; Use NT Prompt
CON_CMDENV	equ 0x0040	; CMD Compatible Mode
CON_IMODE	equ 0x0080	; Init screen mode on startup
CON_UTIME	equ 0x0200	; Use Time
CON_UDATE	equ 0x0400	; Use Date
CON_LTIME	equ 0x0800	; Use Long Time HH:MM:SS
CON_LDATE	equ 0x1000	; Use Long Date YYYY-MM-DD
CON_SLEEP	equ 0x2000	; Wait if set
CON_SIMDE	equ 0x4000	; Use SSE Functions
CON_WIN95	equ 0x8000	; Windows 95 mode if set
CON_DEFAULT	equ 0x42AA
CON_SLEEP_TIME	equ 10		; Time to wait
externdef	console:DWORD

_D_DOPEN	equ 0x01
_D_ONSCR	equ 0x02
_D_DMOVE	equ 0x04
_D_SHADE	equ 0x08
_D_MYBUF	equ 0x10	; do not delete on exit (static)
_D_RCNEW	equ 0x20	; dlclose -- delete dialog if set
_D_RESAT	equ 0x40	; attrib is index in color table (rcedit)
_D_DHELP	equ 0x80	; execute thelp() if set
_D_CLEAR	equ 0x0100	; args on open/create
_D_BACKG	equ 0x0200
_D_FOREG	equ 0x0400
_D_STERR	equ 0x1000	; error color (red)
_D_MENUS	equ 0x2000	; menus color (gray), no title
_D_MUSER	equ 0x4000

_D_COLOR	equ _D_BACKG or _D_FOREG
_D_RESRC	equ _D_RCNEW or _D_MYBUF
_D_SETRC	equ _D_RCNEW or _D_MYBUF or _D_DOPEN
_D_STDDLG	equ _D_DMOVE or _D_SHADE or _D_CLEAR or _D_COLOR
_D_STDERR	equ _D_STDDLG or _D_STERR

_O_PBUTT	equ 0
_O_RBUTT	equ 1
_O_CHBOX	equ 2
_O_XCELL	equ 3
_O_TEDIT	equ 4
_O_MENUS	equ 5
_O_XHTML	equ 6
_O_MOUSE	equ 7
_O_LLMSU	equ 8
_O_LLMSD	equ 9
_O_TBUTT	equ 10

_O_RADIO	equ 0x0010 ; Used in (*) Radio	(one of)
_O_FLAGB	equ 0x0020 ; Used in [x] switch (ON/OFF)
_O_LLIST	equ 0x0040 ; Linked list item
_O_DTEXT	equ 0x0080 ; Select text on activation
_O_CONTR	equ 0x0100 ; Allow _CONTROL chars
_O_DEXIT	equ 0x0200 ; Close dialog and return 0: Cancel
_O_PBKEY	equ 0x0400 ; Return result if short key used
_O_DLGED	equ 0x0800 ; dialog text -- return Left/Right
_O_GLCMD	equ 0x1000 ; Object contain global short-key table
_O_EVENT	equ 0x2000 ; Object have local event handler
_O_CHILD	equ 0x4000 ; Object have a child
_O_STATE	equ 0x8000 ; State (ON/OFF)
_O_DEACT	equ _O_STATE

_C_NORMAL	equ 1
_C_RETURN	equ 2
_C_ESCAPE	equ 3
_C_REOPEN	equ 4

_TE_MODIFIED	equ 1
_TE_OVERWRITE	equ 2
_TE_USECONTROL	equ _O_CONTR
_TE_DLEDIT	equ _O_DLGED	; dialog text -- return Left/Right

_TE_CONTINUE	equ 0	; continue edit
_TE_RETEVENT	equ 1	; return current event (keystroke)
_TE_CMFAILED	equ -1	; operation fail (end of line/buffer)

S_TEDIT		STRUC
ti_bp		LPSTR ? ; base pointer
ti_flag		dd ?	; config
ti_xpos		dd ?	; text window x,y
ti_ypos		dd ?
ti_cols		dd ?	; size of screen-line
ti_bcol		dd ?	; size of buffer-line
ti_clat		dd ?	; clear attrib/char
ti_xoff		dd ?	; x offset on screen
ti_boff		dd ?	; base offset - start of screen-line
ti_bcnt		dd ?	; byte count in line
ti_clso		dd ?	; Clipboard start offset
ti_cleo		dd ?	; Clipboard end offset
S_TEDIT		ENDS	; 48 byte

S_RECT		STRUC
rc_x		db ?
rc_y		db ?
rc_col		db ?
rc_row		db ?
S_RECT		ENDS

S_COLOR		STRUC
foreground	db 16 dup(?)
background	db 16 dup(?)
S_COLOR		ENDS

S_ROBJ		STRUC
rs_memsize	dw ?		; Alloc size
rs_flag		dw ?		; 8 byte object size in Resource.idd
rs_count	db ?
rs_index	db ?
rs_rect		S_RECT <?>
S_ROBJ		ENDS

S_DOBJ		STRUC
dl_flag		dw ?
dl_count	db ?
dl_index	db ?
dl_rect		S_RECT <?>
dl_wp		PVOID ?
dl_object	PVOID ?
S_DOBJ		ENDS

S_TOBJ		STRUC
to_flag		dw ?
to_count	db ?
to_ascii	db ?
to_rect		S_RECT <?>
to_data		PVOID ?
to_proc		PVOID ?
S_TOBJ		ENDS

S_LOBJ		STRUC
ll_dlgoff	dd ?	; start index in dialog
ll_dcount	dd ?	; number of cells (max)
ll_celoff	dd ?	; cell offset
ll_numcel	dd ?	; number of visible cells
ll_count	dd ?	; total number of items in list
ll_index	dd ?	; index in list buffer
ll_list		PVOID ? ; pointer to list buffer
ll_proc		PVOID ?
S_LOBJ		ENDS

S_GLCMD		STRUC
gl_key		dd ?
gl_proc		PVOID ?
S_GLCMD		ENDS

S_WCHAR		STRUC
wc_ch		db ?
wc_at		db ?
S_WCHAR		ENDS

CURSOR_NORMAL	equ 16

S_CURSOR	STRUC	; CONSOLE_CURSOR_INFO
dwSize		dd ?	; .dwSize	1..100
bVisible	dd ?	; .bVisible	0..1
x		dw ?	; word x,y	COORD
y		dw ?
S_CURSOR	ENDS
PCURSOR		TYPEDEF PTR S_CURSOR

externdef	console_dl:S_DOBJ	; Init screen (user screen)
externdef	console_cu:S_CURSOR	; Init cursor (set on exit)
externdef	tdcolor:PVOID		; = &at_background
externdef	tdialog:PVOID
externdef	tdllist:PVOID
externdef	thelp:PVOID
externdef	tupdate:PVOID
externdef	tgetevent:PVOID
externdef	tdidle:PVOID

externdef	at_background:BYTE
externdef	at_foreground:BYTE
externdef	tclrascii:BYTE
externdef	clipbsize:SIZE_T

TIMAXSCRLINE	equ 256		; max screen size

rcpush		PROTO __cdecl :UINT
rcalloc		PROTO __cdecl :S_RECT, :UINT
rcclose		PROTO __cdecl :S_RECT, :UINT, :PVOID
rchide		PROTO __cdecl :DWORD, :DWORD, :PVOID
rcshow		PROTO __cdecl :DWORD, :DWORD, :PVOID
rcopen		PROTO __cdecl :DWORD, :DWORD, :DWORD, :LPSTR, :LPWSTR
rcread		PROTO __cdecl :DWORD, :PVOID
rcreadc		PROTO __cdecl :PVOID, :DWORD, :PVOID
rcwrite		PROTO __cdecl :DWORD, :PVOID
rcxchg		PROTO __cdecl :DWORD, :PVOID
rcsetshade	PROTO __cdecl :DWORD, :PVOID
rcclrshade	PROTO __cdecl :DWORD, :PVOID
rcmoveup	PROTO __cdecl :DWORD, :PVOID, :DWORD
rcmovedn	PROTO __cdecl :DWORD, :PVOID, :DWORD
rcmoveleft	PROTO __cdecl :DWORD, :PVOID, :DWORD
rcmoveright	PROTO __cdecl :DWORD, :PVOID, :DWORD
rcmove		PROTO __cdecl :PVOID, :PVOID, :DWORD, :DWORD, :DWORD
rcmsmove	PROTO __cdecl :ptr S_RECT, :PVOID, :UINT
rcaddrc		PROTO __cdecl :PVOID, :DWORD, :DWORD
rcbprc		PROTO __cdecl :DWORD, :PVOID, :DWORD
rcbprcrc	PROTO __cdecl :DWORD, :DWORD, :PVOID, :DWORD
rcframe		PROTO __cdecl :DWORD, :PVOID, :DWORD, :DWORD
rcmemsize	PROTO __cdecl :DWORD, :DWORD
rcxyrow		PROTO __cdecl :DWORD, :DWORD, :DWORD
rcinside	PROTO __cdecl :DWORD, :DWORD

dlopen		PROTO __cdecl :PTR S_DOBJ, :DWORD, :LPSTR
dlclose		PROTO __cdecl :PTR S_DOBJ
dlshow		PROTO __cdecl :PTR S_DOBJ
dlhide		PROTO __cdecl :PTR S_DOBJ
dlmove		PROTO __cdecl :PTR S_DOBJ
dlmodal		PROTO __cdecl :PTR S_DOBJ
dlevent		PROTO __cdecl :PTR S_DOBJ
dllevent	PROTO __cdecl :PTR S_DOBJ, :PTR S_LOBJ
dlinit		PROTO __cdecl :PTR S_DOBJ
dlinitobj	PROTO __cdecl :PTR S_DOBJ, :PTR S_TOBJ
dledit		PROTO __cdecl :LPSTR, :DWORD, :DWORD, :DWORD
dledite		PROTO __cdecl :PVOID, :DWORD
dlscreen	PROTO __cdecl :PTR S_DOBJ, :DWORD
dlshowall	PROTO __cdecl
dlhideall	PROTO __cdecl
dlpbuttevent	PROTO __cdecl
dlradioevent	PROTO __cdecl
dlcheckevent	PROTO __cdecl
dlxcellevent	PROTO __cdecl
dlteditevent	PROTO __cdecl
dlmenusevent	PROTO __cdecl
tosetbitflag	PROTO __cdecl :PTR S_TOBJ, :DWORD, :DWORD, :DWORD
togetbitflag	PROTO __cdecl :PTR S_TOBJ, :DWORD, :DWORD

rsopen		PROTO __cdecl :PTR S_ROBJ
rsevent		PROTO __cdecl :PTR S_ROBJ, :PTR S_DOBJ
rsmodal		PROTO __cdecl :PTR S_ROBJ
rsreload	PROTO __cdecl :PTR S_ROBJ, :PTR S_DOBJ

wcputf		PROTO _CDecl :PVOID, :DWORD, :DWORD, :LPSTR, :VARARG
wcputs		PROTO __cdecl :PVOID, :DWORD, :DWORD, :LPSTR
__wcpath	PROTO __cdecl :PVOID, :DWORD, :LPSTR
wcpath		PROTO __cdecl :PVOID, :DWORD, :PVOID
wcputa		PROTO __cdecl :PVOID, :DWORD, :DWORD
wcputw		PROTO __cdecl :PVOID, :DWORD, :DWORD
wcputfg		PROTO __cdecl :PVOID, :DWORD, :DWORD
wcputbg		PROTO __cdecl :PVOID, :DWORD, :DWORD
wcenter		PROTO __cdecl :PVOID, :DWORD, :LPSTR
wctitle		PROTO __cdecl :PVOID, :DWORD, :LPSTR
wcpbutt		PROTO __cdecl :PVOID, :DWORD, :DWORD, :LPSTR
wcpushst	PROTO __cdecl :PVOID, :LPSTR
wcpopst		PROTO __cdecl :PVOID
wcunzip		PROTO __cdecl :PVOID, :PVOID, :DWORD
wcstrcpy	PROTO __cdecl :LPSTR, :PVOID, :DWORD
wcmemset	PROTO __cdecl :PVOID, :DWORD, :DWORD

getevent	PROTO __cdecl
ermsg		PROTO _CDecl :LPSTR, :LPSTR, :VARARG
stdmsg		PROTO _CDecl :LPSTR, :LPSTR, :VARARG
msgbox		PROTO __cdecl :LPSTR, :DWORD, :LPSTR

__wputs		PROTO __cdecl

putxys		PROTO __cdecl :DWORD,:DWORD,:DWORD,:DWORD
putxysl		PROTO __cdecl :DWORD,:DWORD,:DWORD,:DWORD

getxya		PROTO __cdecl :DWORD, :DWORD
getxyc		PROTO __cdecl :DWORD, :DWORD
getxyw		PROTO __cdecl :DWORD, :DWORD
scgetws		PROTO __cdecl :DWORD, :DWORD, :DWORD
scputws		PROTO __cdecl :DWORD, :DWORD, :DWORD, :PVOID
scgetword	PROTO __cdecl :LPSTR
scputa		PROTO __cdecl :DWORD, :DWORD, :DWORD, :DWORD
scputal		PROTO __cdecl :DWORD, :DWORD, :DWORD, :PVOID
scputfg		PROTO __cdecl :DWORD, :DWORD, :DWORD, :DWORD
scputbg		PROTO __cdecl :DWORD, :DWORD, :DWORD, :DWORD
scputc		PROTO __cdecl :DWORD, :DWORD, :DWORD, :DWORD
scputw		PROTO __cdecl :DWORD, :DWORD, :DWORD, :DWORD
scputs		PROTO __cdecl :DWORD, :DWORD, :DWORD, :DWORD, :LPSTR
scputsEx	PROTO __cdecl :DWORD, :DWORD, :DWORD, :DWORD, :LPSTR
scpath		PROTO __cdecl :DWORD, :DWORD, :DWORD, :LPSTR
scpathl		PROTO __cdecl :DWORD, :DWORD, :DWORD, :LPSTR
scenter		PROTO __cdecl :DWORD, :DWORD, :DWORD, :LPSTR
scputf		PROTO _CDecl :DWORD, :DWORD, :DWORD, :DWORD, :LPSTR, :VARARG
scputfEx	PROTO _CDecl :DWORD, :DWORD, :DWORD, :DWORD, :LPSTR, :VARARG
getxys		PROTO __cdecl :DWORD, :DWORD, :LPSTR, :DWORD, :DWORD
tgetline	PROTO __cdecl :LPSTR, :LPSTR, :DWORD, :DWORD
notsup		PROTO __cdecl
scroll_delay	PROTO __cdecl

CursorOn	PROTO __cdecl
CursorOff	PROTO __cdecl
CursorGet	PROTO __cdecl :PCURSOR
CursorSet	PROTO __cdecl :PCURSOR

externdef	ASCII_DOT:	BYTE
externdef	ASCII_RIGHT:	BYTE
externdef	ASCII_LEFT:	BYTE
externdef	ASCII_UP:	BYTE
externdef	ASCII_DOWN:	BYTE
externdef	ASCII_ARROWD:	BYTE
externdef	ASCII_RADIO:	BYTE

externdef	_scrrow:	DWORD	; Screen rows - 1
externdef	_scrcol:	DWORD	; Screen columns
externdef	_scrmax:	DWORD	; Max screen columns,rows

externdef	hCurrentWindow: HANDLE

setasymbol	PROTO __cdecl
SetMaxConsole	PROTO __cdecl ; (80..255, 16..255)
SetConsoleSize	PROTO __cdecl cols:DWORD, rows:DWORD
ConsoleIdle	PROTO __cdecl
GetScreenRect	PROTO __cdecl
ConsolePush	PROTO __cdecl

;;;;;;;;;;;;;;; keyb

SHIFT_RIGHT		equ 0x01
SHIFT_LEFT		equ 0x02
SHIFT_CTRL		equ 0x04
SHIFT_ALT		equ 0x08
SHIFT_SCROLL		equ 0x10
SHIFT_NUMLOCK		equ 0x20
SHIFT_CAPSLOCK		equ 0x40
SHIFT_INSERTSTATE	equ 0x80
SHIFT_CTRLLEFT		equ 0x0100
SHIFT_ALTLEFT		equ 0x0200
SHIFT_ENHANCED		equ 0x0400
SHIFT_CONTROLEKEY	equ 0x0800
SHIFT_SCROLLKEY		equ 0x1000
SHIFT_NUMLOCKKEY	equ 0x2000
SHIFT_CAPSLOCKKEY	equ 0x4000
SHIFT_INSERTKEY		equ 0x8000
SHIFT_KEYSPRESSED	equ 0x01000000
SHIFT_MOUSEKEYLEFT	equ 0x00010000
SHIFT_MOUSEKEYRIGTH	equ 0x00020000
SHIFT_MOUSEKEYLEFT2	equ 0x00040000
SHIFT_MOUSEKEYLEFT3	equ 0x00080000
SHIFT_MOUSEKEYLEFT4	equ 0x00100000
SHIFT_MOUSEWHEEL	equ 0x00200000
SHIFT_MOUSEDOUBLECLICK	equ 0x00400000
SHIFT_MOUSEMOVED	equ 0x00800000
SHIFT_MOUSEFLAGS	equ 0x00FF0000
SHIFT_RELEASEKEY	equ 0x80000000

KEY_ALT		equ 0x08
KEY_CTRL	equ 0x04
KEY_SHIFT	equ 0x03

KEY_ESC		equ 0x011B
KEY_BKSP	equ 0x0E08
KEY_TAB		equ 0x0F09
KEY_ENTER	equ 0x1C0D
KEY_SPACE	equ 0x3920
KEY_HOME	equ 0x4700
KEY_UP		equ 0x4800
KEY_PGUP	equ 0x4900
KEY_LEFT	equ 0x4B00
KEY_RIGHT	equ 0x4D00
KEY_END		equ 0x4F00
KEY_DOWN	equ 0x5000
KEY_PGDN	equ 0x5100
KEY_INS		equ 0x5200
KEY_DEL		equ 0x5300

KEY_F1		equ 0x3B00
KEY_F2		equ 0x3C00
KEY_F3		equ 0x3D00
KEY_F4		equ 0x3E00
KEY_F5		equ 0x3F00
KEY_F6		equ 0x4000
KEY_F7		equ 0x4100
KEY_F8		equ 0x4200
KEY_F9		equ 0x4300
KEY_F10		equ 0x4400
KEY_F11		equ 0x8500
KEY_F12		equ 0x8600

KEY_KPSTAR	equ 0x372A
KEY_KPPLUS	equ 0x4E2B
KEY_KPMIN	equ 0x4A2D
KEY_KPENTER	equ 0xE00D

KEY_CTRLF1	equ 0x5E00
KEY_CTRLF2	equ 0x5F00
KEY_CTRLF3	equ 0x6000
KEY_CTRLF4	equ 0x6100
KEY_CTRLF5	equ 0x6200
KEY_CTRLF6	equ 0x6300
KEY_CTRLF7	equ 0x6400
KEY_CTRLF8	equ 0x6500
KEY_CTRLF9	equ 0x6600
KEY_CTRLF10	equ 0x6700
KEY_CTRLF11	equ 0xA800
KEY_CTRLF12	equ 0xA900

KEY_CTRL1	equ 0x0200
KEY_CTRL2	equ 0x0300
KEY_CTRL3	equ 0x0400
KEY_CTRL4	equ 0x0500
KEY_CTRL5	equ 0x0600
KEY_CTRL6	equ 0x0700
KEY_CTRL7	equ 0x0800
KEY_CTRL8	equ 0x0900
KEY_CTRL9	equ 0x0A00
KEY_CTRL0	equ 0x0B00

KEY_CTRLA	equ 0x1E01
KEY_CTRLB	equ 0x3002
KEY_CTRLC	equ 0x2E03
KEY_CTRLD	equ 0x2004
KEY_CTRLE	equ 0x1205
KEY_CTRLF	equ 0x2106
KEY_CTRLG	equ 0x2207
KEY_CTRLH	equ 0x2308
KEY_CTRLI	equ 0x1709
KEY_CTRLJ	equ 0x240A
KEY_CTRLK	equ 0x250B
KEY_CTRLL	equ 0x260C
KEY_CTRLM	equ 0x320D
KEY_CTRLN	equ 0x310E
KEY_CTRLO	equ 0x180F
KEY_CTRLP	equ 0x1910
KEY_CTRLQ	equ 0x1011
KEY_CTRLR	equ 0x1312
KEY_CTRLS	equ 0x1F13
KEY_CTRLT	equ 0x1414
KEY_CTRLU	equ 0x1615
KEY_CTRLV	equ 0x2F16
KEY_CTRLW	equ 0x1117
KEY_CTRLX	equ 0x2D18
KEY_CTRLY	equ 0x1519
KEY_CTRLZ	equ 0x2C1A

KEY_CTRLP1	equ 0x1A1B
KEY_CTRLP2	equ 0x1B1D

KEY_CTRLINS	equ 0x9200
KEY_CTRLDEL	equ 0x9300
KEY_CTRLLEFT	equ 0x7300
KEY_CTRLRIGHT	equ 0x7400
KEY_CTRLUP	equ 0x8D00
KEY_CTRLDN	equ 0x9100
KEY_CTRLEND	equ 0x7500
KEY_CTRLHOME	equ 0x7700
KEY_CTRLPGUP	equ 0x8400
KEY_CTRLPGDN	equ 0x7600
KEY_CTRLTAB	equ 0x9400
KEY_CTRLENTER	equ 0x1C0A
KEY_CTRLBKSP	equ 0x0E7F

KEY_ALTF1	equ 0x6800
KEY_ALTF2	equ 0x6900
KEY_ALTF3	equ 0x6A00
KEY_ALTF4	equ 0x6B00
KEY_ALTF5	equ 0x6C00
KEY_ALTF6	equ 0x6D00
KEY_ALTF7	equ 0x6E00
KEY_ALTF8	equ 0x6F00
KEY_ALTF9	equ 0x7000
KEY_ALTF10	equ 0x7100
KEY_ALTF11	equ 0xB200
KEY_ALTF12	equ 0xB300

KEY_ALT1	equ 0x7800
KEY_ALT2	equ 0x7900
KEY_ALT3	equ 0x7A00
KEY_ALT4	equ 0x7B00
KEY_ALT5	equ 0x7C00
KEY_ALT6	equ 0x7D00
KEY_ALT7	equ 0x7E00
KEY_ALT8	equ 0x7F00
KEY_ALT9	equ 0x8000
KEY_ALT0	equ 0x8100

KEY_ALTUP	equ 0x9800
KEY_ALTDN	equ 0xA000
KEY_ALTLEFT	equ 0x9B00
KEY_ALTRIGHT	equ 0x9D00
KEY_ALTC	equ 0x2E00
KEY_ALTL	equ 0x2600
KEY_ALTM	equ 0x3200
KEY_ALTP	equ 0x1900
KEY_ALTQ	equ 0x1000
KEY_ALTS	equ 0x1F00
KEY_ALTW	equ 0x1100
KEY_ALTX	equ 0x2D00
KEY_ALTZ	equ 0x2C00

KEY_SHIFTF1	equ 0x5400
KEY_SHIFTF2	equ 0x5500
KEY_SHIFTF3	equ 0x5600
KEY_SHIFTF4	equ 0x5700
KEY_SHIFTF5	equ 0x5800
KEY_SHIFTF6	equ 0x5900
KEY_SHIFTF7	equ 0x5A00
KEY_SHIFTF8	equ 0x5B00
KEY_SHIFTF9	equ 0x5C00
KEY_SHIFTF10	equ 0x5D00
KEY_SHIFTF11	equ 0x9E00
KEY_SHIFTF12	equ 0x9F00

MOUSECMD	equ -1
KEY_MSLEFT	equ 1
KEY_MSRIGTH	equ 2
KEY_MOUSEPRESS	equ KEY_MSLEFT or KEY_MSRIGTH
KEY_MOUSEUP	equ 0x00010000
KEY_MOUSEDN	equ 0x00020000
MAXKEYSTACK	equ 32

externdef	keyshift:SIZE_T
externdef	keybchar:BYTE
externdef	keybscan:BYTE
externdef	keybcode:BYTE
externdef	keybstate:BYTE
externdef	keybstack:DWORD
externdef	keybcount:DWORD
externdef	keybmouse_x:DWORD
externdef	keybmouse_y:DWORD

PopEvent	PROTO __cdecl
PushEvent	PROTO __cdecl Event:DWORD

getkey		PROTO __cdecl
mousep		PROTO __cdecl
mousey		PROTO __cdecl
mousex		PROTO __cdecl
msloop		PROTO __cdecl
mousewait	PROTO __cdecl x:UINT, y:UINT, l:UINT

ReadEvevnt	PROTO __cdecl
SetKeyState	PROTO __cdecl
UpdateKeyEvent	PROTO __cdecl :PTR INPUT_RECORD
UpdateMouseEvent PROTO __cdecl :PTR INPUT_RECORD
GetShiftState	PROTO __cdecl

strshr		PROTO __cdecl :LPSTR, :UINT
strtrim		PROTO __cdecl :LPSTR

MAXCLIPSIZE	equ 0x100000
CF_TEXT		equ 1

externdef	clipboard: SIZE_T
externdef	clipbsize: SIZE_T

ClipboardCopy	PROTO __cdecl :LPSTR, :SIZE_T
ClipboardPaste	PROTO __cdecl
ClipboardFree	PROTO __cdecl

cliprintf	PROTO _CDecl :LPSTR, :VARARG

.list
