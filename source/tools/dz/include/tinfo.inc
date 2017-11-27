include consx.inc
include syserrls.inc

.xlist

TIMAXLINE	equ 8000h	; max line size
TIMAXFILE	equ 200000h	; max file size
TIMAXFILES	equ 300		; max open files
TITABCHAR	equ 0Bh		; expand tabs with this char (Vertical Tab)
TIMAXTABSIZE	equ 16		; max Tab size
STYLESIZE	equ 4000h

_T_PANELB	equ 0001h
_T_MALLOC	equ 0002h
_T_TEDIT	equ 0004h
_T_FILE		equ 0008h
_T_MODIFIED	equ 0010h	; default
_T_USEMENUS	equ 0020h	;*[x] Ctrl-M (F11)
_T_OPTIMALFILL	equ 0040h	;*[x] Ctrl-F
_T_OVERWRITE	equ 0080h	;*[x]
_T_USEINDENT	equ 0100h	;*[x] Ctrl-I
_T_USESTYLE	equ 0200h	;*[x] Ctrl-S
_T_USETABS	equ 0400h	;*[x]
_T_USEBAKFILE	equ 0800h	;*[x]
_T_USECRLF	equ 1000h	;*[x]
_T_PROMPTONREP	equ 2000h	; [x]
_T_USECONTROL	equ 4000h
_T_SHOWTABS	equ 8000h

_T_TEDEFAULT	equ 3FE0h
_T_TECFGMASK	equ 3FE0h

_T_UNREAD	equ 0x10000

_TI_CONTINUE	equ 0	; continue edit
_TI_RETEVENT	equ 1	; return current event (keystroke)
_TI_NOTEVENT	equ 2	; event not handled -- continue test
_TI_CMFAILED	equ -1	; operation fail (end of line/buffer)

S_TINFO		STRUC	; aligned S_TEDIT
ti_bp		LPSTR ? ; base pointer
ti_flag		dd ?	; config
ti_xpos		dd ?	; text window x,y
ti_ypos		dd ?
ti_cols		dd ?	; size of screen-line
ti_bcol		dd ?	; size of buffer-line
ti_clat		dd ?	; clear attrib/char
ti_xoff		dd ?	; x offset on screen
ti_boff		dd ?	; base offset - start of screen-line
ti_bcnt		dd ?	; byte count in line (expanded)
ti_clso		dd ?	; Clipboard start offset
ti_cleo		dd ?	; Clipboard end offset
;----------------------------------------------
ti_clsl		dd ?	; Clipboard start line
ti_clel		dd ?	; Clipboard end line
ti_rows		dd ?	; number of lines on screen
ti_loff		dd ?	; line offset in buffer
ti_yoff		dd ?	; y offset on screen

ti_lp		LPSTR ? ; pointer to current line
ti_flp		LPSTR ? ; pointer to current line (in file)
ti_fbcnt	dd ?	; byte count in line (in file)
ti_stat		dd ?	; style attrib/char
ti_lcnt		dd ?	; line count in file
ti_curl		dd ?	; last line accessed

ti_file		LPSTR ? ; file name
ti_time		dd ?	; file time
ti_size		SIZE_T ?; file size
ti_next		SIZE_T ?; next file
ti_prev		SIZE_T ?; prev file
ti_tabz		dd ?	; tab size
ti_style	SIZE_T ?
ti_DOBJ		S_DOBJ <?>
ti_scrc		dd ?	; screen data CRC value for minimal output
ti_blen		dd ?	; buffer size
S_TINFO		ENDS	;

S_TIOST		STRUC
ts_buffer	LPSTR ? ; &ti_lp[ti_bcol]
ts_index	dd ?
ts_file_ptr	LPSTR ?
ts_file_end	LPSTR ?
ts_line_ptr	LPSTR ?
ts_char		db ?
S_TIOST		ENDS

PTINFO		TYPEDEF PTR S_TINFO
PTIOST		TYPEDEF PTR S_TIOST

externdef	tinfo:PTINFO
externdef	tiflags:DWORD
externdef	titabsize:DWORD

tiselected	PROTO :PTINFO
ticopyselection PROTO :PTINFO
ticlipset	PROTO :PTINFO
ticlipdel	PROTO :PTINFO
ticlipcut	PROTO :PTINFO, :UINT
ticliptostart	PROTO :PTINFO
ticlippaste	PROTO :PTINFO
tiselectall	PROTO :PTINFO

__st_open	PROTO :PTINFO, :PTIOST, :UINT
__st_putc	PROTO :PTIOST, :UINT
__st_trim	PROTO :PTIOST
__st_copy	PROTO :PTINFO, :PTIOST
__st_copy2	PROTO :PTINFO, :PTIOST
__st_tail	PROTO :PTINFO, :PTIOST, :LPSTR
__st_flush	PROTO :PTINFO, :PTIOST

tirealloc	PROTO :PTINFO
tialloc		PROTO :PTINFO
tifree		PROTO :PTINFO

ticontinue	PROTO
tiretevent	PROTO
ticmdfailed	PROTO
tiisword	PROTO
tinocando	PROTO

tistate		PROTO :PTINFO
ticurlp		PROTO :PTINFO
ticurcp		PROTO :PTINFO
tiseto		PROTO :PTINFO
tigeto		PROTO :PTINFO, :UINT, :UINT
tiexpandline	PROTO :PTINFO, :LPSTR
tidecx		PROTO :PTINFO
tiincx		PROTO :PTINFO
tiincy		PROTO :PTINFO
tialignx	PROTO :PTINFO, :UINT
tialigny	PROTO :PTINFO, :UINT
tihome		PROTO :PTINFO
titoend		PROTO :PTINFO
tileft		PROTO :PTINFO
tiup		PROTO :PTINFO
tiputc		PROTO :PTINFO, :UINT
tibacksp	PROTO :PTINFO
tidelete	PROTO :PTINFO
timemzero	PROTO :PTINFO
tigetline	PROTO :PTINFO, :UINT
tigetnextl	PROTO :PTINFO
tiputs		PROTO :PTINFO
tioptimalfill	PROTO :PTINFO, :LPSTR
tistripend	PROTO :LPSTR
tistyle		PROTO :PTINFO, :DWORD, :LPSTR, :DWORD, :PTR WORD
tireadstyle	PROTO :PTINFO
tishow		PROTO :PTINFO
tihide		PROTO :PTINFO
tihideall	PROTO :PTINFO
timenus		PROTO :PTINFO
titogglemenus	PROTO :PTINFO
tiftime		PROTO :PTINFO
tigetfile	PROTO :PTINFO
tiopen		PROTO :PTINFO, :UINT, :UINT
ticlose		PROTO :PTINFO
tievent		PROTO :PTINFO, :UINT
tilseek		PROTO :PTINFO
tiread		PROTO :PTINFO
tireload	PROTO :PTINFO
tiflush		PROTO :PTINFO
tiflushl	PROTO :PTINFO, :UINT, :UINT, :UINT, :UINT
tigetfilename	PROTO :PTINFO
tisearch	PROTO :PTINFO
tisearchxy	PROTO :PTINFO
ticontsearch	PROTO :PTINFO
tireplace	PROTO :PTINFO
tioption	PROTO :PTINFO
titogglefile	PROTO :PTINFO, :PTINFO
tisaveas	PROTO :PTINFO

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

SaveChanges	PROTO :LPSTR
tdlgopen	PROTO
tihandler	PROTO
toption		PROTO
topen		PROTO :LPSTR, :UINT
tclose		PROTO
tcloseall	PROTO
tclosefile	PROTO
tmodal		PROTO
tevent		PROTO
tedit		PROTO :LPSTR, :DWORD
TIOpenSession	PROTO __ini:DWORD, __section:LPSTR
TISaveSession	PROTO __ini:DWORD, __section:LPSTR
topensession	PROTO
topenedi	PROTO :LPSTR
tloadfiles	PROTO
tsavefiles	PROTO
tnewfile	PROTO
tnextfile	PROTO
TIShiftFx	PROTO :UINT
TIAltFx		PROTO :UINT
tinexterror	PROTO
tipreviouserror PROTO
titransfer	PROTO
twindows	PROTO
twindowsize	PROTO
tgetrect	PROTO
tsetrect	proto :PTINFO, :S_RECT

.list
