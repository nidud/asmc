ifndef __LIBC_INC
 include libc.inc
endif

.xlist

TIMAXSCRLINE	equ 128		; max screen size

B_Desktop	equ 0
B_Panel		equ 1
B_Dialog	equ 2
B_Menus		equ 3
B_Error		equ 4
B_Title		equ 5
B_Inverse	equ 6
B_Gray		equ 7
B_PushButt	equ 8
B_InvPanel	equ 9
B_TextView	equ 12
B_TextEdit	equ 13

F_Title		equ 0
F_Frame		equ 1
F_Files		equ 2
F_System	equ 3
F_Hidden	equ 4
F_PBShade	equ 5
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

CON_UBEEP	equ 0001h	; Use Beep
CON_MOUSE	equ 0002h	; Use Mouse
CON_IOLFN	equ 0004h	; Use Long File Names
CON_CLIPB	equ 0008h	; Use System Clipboard
CON_INT2F	equ 0010h	; Use Idle Int 2Fh
CON_NTCMD	equ 0020h	; Use NT Prompt
CON_DOSIO	equ 0040h	; Use DOS2 Open/Create
CON_COLOR	equ 0080h	; Use Color
CON_UTIME	equ 0100h	; Use Time
CON_UDATE	equ 0200h	; Use Date
CON_LTIME	equ 0400h	; Use Long Time HH:MM:SS
CON_LDATE	equ 0800h	; Use Long Date YYYY-MM-DD
CON_IMODE	equ 1000h	; Init screen mode on startup
CON_REVGA	equ 2000h	; Restore VGA palette on exit

_D_DOPEN	equ 01h
_D_ONSCR	equ 02h
_D_DMOVE	equ 04h
_D_SHADE	equ 08h
_D_MYBUF	equ 10h		; do not delete on exit (static)
_D_RCNEW	equ 20h		; twclose -- delete dialog if set
_D_RESAT	equ 40h		; attrib is index in color table (rcedit)
_D_DHELP	equ 80h		; execute thelp() if set
_D_CLEAR	equ 0100h	; args on open/create
_D_BACKG	equ 0200h
_D_FOREG	equ 0400h
_D_STERR	equ 1000h	; error color (red)
_D_MENUS	equ 2000h	; menus color (gray), no title
_D_MUSER	equ 4000h

_D_COLOR	equ _D_BACKG or _D_FOREG
_D_RESRC	equ 0030h
_D_SETRC	equ 0031h
_D_STDDLG	equ (_D_DMOVE or _D_SHADE or _D_CLEAR or _D_COLOR)
_D_STDERR	equ (_D_STDDLG or _D_STERR)

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

_O_RADIO	equ 0010h	; Used in (*) Radio  (one of)
_O_FLAGB	equ 0020h	; Used in [x] switch (ON/OFF)
_O_LLIST	equ 0040h	; Linked list item
_O_DTEXT	equ 0080h	; Select text on activation
_O_CONTR	equ 0100h	; Allow _CONTROL chars
_O_DEXIT	equ 0200h	; Close dialog and return 0: Cancel
_O_PBKEY	equ 0400h	; Return result if short key used
_O_GLCMD	equ 1000h	; Object contain global short-key table
_O_EVENT	equ 2000h	; Object have local event handler
_O_CHILD	equ 4000h	; Object have a child
_O_STATE	equ 8000h	; State (ON/OFF)
_O_DEACT	equ _O_STATE

_C_NORMAL	equ 1
_C_RETURN	equ 2
_C_ESCAPE	equ 3
_C_REOPEN	equ 4

CURSOR_NORMAL	equ 0607h
CURSOR_HIDDEN	equ 0F00h

S_RECT		STRUC
rc_x		db ?
rc_y		db ?
rc_col		db ?
rc_row		db ?
S_RECT		ENDS

S_COLOR		STRUC
cl_foregr	db 16 dup(?)
cl_backgr	db 16 dup(?)
cl_palett	db 16 dup(?)
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
dl_wp		dd ?
dl_object	dd ?
S_DOBJ		ENDS

S_TOBJ		STRUC
to_flag		dw ?
to_count	db ?
to_ascii	db ?
to_rect		S_RECT <?>
to_data		dd ?
to_proc		p? ?
ifdef __c__
to_proc_seg	dw ?
endif
S_TOBJ		ENDS

S_LOBJ		STRUC
ll_dlgoff	dw ?	; start index in dialog
ll_dcount	dw ?	; number of cells (max)
ll_celoff	dw ?	; cell offset
ll_numcel	dw ?	; number of visible cells
ll_count	dw ?	; total number of items in list
ll_index	dw ?	; index in list buffer
ll_list		dd ?	; pointer to list buffer
ll_proc		p? ?
S_LOBJ		ENDS

S_GLCMD		STRUC
gl_key		dw ?
gl_proc		p? ?
S_GLCMD		ENDS

S_WCHAR		STRUC
wc_ch		db ?
wc_at		db ?
S_WCHAR		ENDS

S_CURSOR	STRUC	; CONSOLE_CURSOR_INFO
cr_xy		dw ?	; byte x,y
cr_type		dw ?	;
S_CURSOR	ENDS

GCMD	macro	key, name	; GlobalCommand: <ShortKey>, <cmdProc>
	dw	key
	p?	name
	endm

externdef	_scrseg:WORD	; Screen segment (B800 or B000)
externdef	console:WORD	; BEEP/MOUSE/LFN/CLIPB/2F/COLOR/TIME/DATE
externdef	console_dl:S_DOBJ	; Init screen (user screen)
;externdef	console_cu:S_CURSOR	; Init cursor (set on exit)
externdef	_scrrow:BYTE	; Screen rows - 1
externdef	_scrcol:BYTE	; Screen columns
externdef	tdialog:DWORD
externdef	tdllist:DWORD
externdef	thelp:size_p
externdef	tupdate:size_p
externdef	tgetevent:size_p
externdef	at_palett:BYTE
externdef	at_background:BYTE
externdef	at_foreground:BYTE

rcpush		PROTO _CType :WORD
rcalloc		PROTO _CType :DWORD, :WORD
rcclose		PROTO _CType :DWORD, :WORD, :DWORD
rchide		PROTO _CType :DWORD, :WORD, :DWORD
rcshow		PROTO _CType :DWORD, :WORD, :DWORD
rcopen		PROTO _CType :DWORD, :WORD, :WORD, :DWORD, :DWORD
rcread		PROTO _CType :DWORD, :DWORD
rcwrite		PROTO _CType :DWORD, :DWORD
rcxchg		PROTO _CType :DWORD, :DWORD
rcsetshade	PROTO _CType :DWORD, :DWORD
rcclrshade	PROTO _CType :DWORD, :DWORD
rcmoveup	PROTO _CType :DWORD, :DWORD, :WORD
rcmovedn	PROTO _CType :DWORD, :DWORD, :WORD
rcmoveleft	PROTO _CType :DWORD, :DWORD, :WORD
rcmoveright	PROTO _CType :DWORD, :DWORD, :WORD
rcmove		PROTO _CType :DWORD, :DWORD, :WORD, :WORD, :WORD
rcmsmove	PROTO _CType :DWORD, :DWORD, :WORD
rcaddrc		PROTO _CType :DWORD, :DWORD, :DWORD
rcsprc		PROTO _CType :DWORD
rcbprc		PROTO _CType :DWORD, :DWORD, :WORD
rcbprcrc	PROTO _CType :DWORD, :DWORD, :DWORD, :WORD
rcframe		PROTO _CType :DWORD, :DWORD, :WORD, :WORD
rcmemsize	PROTO _CType :DWORD, :WORD
rcxyrow		PROTO _CType :DWORD, :WORD, :WORD
rcinside	PROTO _CType :DWORD, :DWORD

dlopen		PROTO _CType :DWORD, :WORD, :DWORD
dlclose		PROTO _CType :DWORD
dlshow		PROTO _CType :DWORD
dlhide		PROTO _CType :DWORD
dlmove		PROTO _CType :DWORD
dlmodal		PROTO _CType :DWORD
dlevent		PROTO _CType :DWORD
dllevent	PROTO _CType :DWORD, :DWORD
dlinit		PROTO _CType :DWORD
dlinitobj	PROTO _CType :DWORD, :DWORD
dledit		PROTO _CType :DWORD, :DWORD, :WORD, :WORD
dlscreen	PROTO _CType :DWORD, :WORD

dlpbuttevent	PROTO _CType
dlradioevent	PROTO _CType
dlcheckevent	PROTO _CType
dlxcellevent	PROTO _CType
dlteditevent	PROTO _CType
dlmenusevent	PROTO _CType
tosetbitflag	PROTO _CType :DWORD, :WORD, :WORD, :DWORD
togetbitflag	PROTO _CType :DWORD, :WORD, :WORD

thelpinit	PROTO _CType :size_p
thelp_set	PROTO _CType :size_p
thelp_pop	PROTO _CType

rsopen		PROTO _CType :DWORD
rsevent		PROTO _CType :DWORD, :DWORD
rsmodal		PROTO _CType :DWORD
rsreload	PROTO _CType :DWORD, :DWORD

setpal		PROTO _CType :WORD, :WORD
resetpal	PROTO _CType
loadpal		PROTO _CType :PTR BYTE
editpal		PROTO _CType
editattrib	PROTO _CType

consinit	PROTO _CType
consrect	PROTO _CType
conssetl	PROTO _CType :WORD
consuser	PROTO _CType

cursorget	PROTO _CType :DWORD
cursorset	PROTO _CType :DWORD
cursoron	PROTO _CType
cursoroff	PROTO _CType
cursorx		PROTO _CType
cursory		PROTO _CType
gotoxy		PROTO _CType :WORD, :WORD

wcputf		PROTO _CDecl :DWORD, :WORD, :WORD, :DWORD, :VARARG
wcputs		PROTO _CType :DWORD, :WORD, :WORD, :DWORD
wcpath		PROTO _CType :DWORD, :WORD, :DWORD
wcputa		PROTO _CType :DWORD, :WORD, :WORD
wcputw		PROTO _CType :DWORD, :WORD, :WORD
wcputfg		PROTO _CType :DWORD, :WORD, :WORD
wcputbg		PROTO _CType :DWORD, :WORD, :WORD
wcenter		PROTO _CType :DWORD, :WORD, :DWORD
wctitle		PROTO _CType :DWORD, :WORD, :DWORD
wcpbutt		PROTO _CType :DWORD, :WORD, :WORD, :DWORD
wcpushst	PROTO _CType :DWORD, :DWORD
wcpopst		PROTO _CType :DWORD
wcunzip		PROTO _CType :DWORD, :DWORD, :WORD
wcstrcpy	PROTO _CType :DWORD, :DWORD, :WORD

getch		PROTO _CType
kbhit		PROTO _CType

getevent	PROTO _CType
ermsg		PROTO _CDecl :DWORD, :DWORD, :VARARG
stdmsg		PROTO _CDecl :DWORD, :DWORD, :VARARG
;msgbox		proto _CType :dword, :word, :dword

externdef	_scrcol:BYTE
externdef	_scrrow:BYTE
externdef	tupdate:size_p
externdef	tgetevent:size_p
externdef	tclrascii:BYTE
externdef	_scrseg:WORD
__getxyp	PROTO
__getxypm	PROTO
__wputs		PROTO

getxyp		PROTO _CType :WORD, :WORD
getxya		PROTO _CType :WORD, :WORD
getxyc		PROTO _CType :WORD, :WORD
getxyw		PROTO _CType :WORD, :WORD
scputa		PROTO _CType :WORD, :WORD, :WORD, :WORD
scputfg		PROTO _CType :WORD, :WORD, :WORD, :WORD
scputbg		PROTO _CType :WORD, :WORD, :WORD, :WORD
scputc		PROTO _CType :WORD, :WORD, :WORD, :WORD
scputw		PROTO _CType :WORD, :WORD, :WORD, :WORD
scputs		PROTO _CType :WORD, :WORD, :WORD, :WORD, :DWORD
scpath		PROTO _CType :WORD, :WORD, :WORD, :DWORD
scenter		PROTO _CType :WORD, :WORD, :WORD, :DWORD
scputf		PROTO _CDecl :WORD, :WORD, :WORD, :WORD, :DWORD, :VARARG
getxys		PROTO _CType :WORD, :WORD, :DWORD, :WORD, :WORD
tgetline	PROTO _CType :DWORD, :DWORD, :WORD, :WORD

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

.list
