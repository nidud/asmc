.xlist

_T_MALLOC	equ 0001h
_T_EMMBUF	equ 0002h
_T_LINEBUF	equ 0003h
_T_FILE		equ 0004h
_T_MODIFIED	equ 0008h
_T_USECONTROL	equ 0010h	; default
_T_USEMENUS	equ 0020h	;*[x] Ctrl-M (F11)
_T_OPTIMALFILL	equ 0040h	;*[x] Ctrl-F
_T_OVERWRITE	equ 0080h	;*[x]
_T_USEINDENT	equ 0100h	;*[x] Ctrl-I
_T_USESTYLE	equ 0200h	;*[x] Ctrl-S
_T_USETABS	equ 0400h	;*[x]
_T_USEBAKFILE	equ 0800h	;*[x]
_T_USECRLF	equ 1000h	;*[x]
_T_PROMPTONREP	equ 2000h	; [x]
_T_SHOWTABS	equ 4000h
_T_TEDEFAULT	equ 3FE0h
_T_TECFGMASK	equ 3FE0h

_TI_CONTINUE	equ 0	; continue edit
_TI_RETEVENT	equ 1	; return current event (keystroke)
_TI_CMFAILED	equ 2	; operation fail (end of line/buffer)

S_TINFO		STRUC
ti_bp		dd ?	; base pointer
ti_flag		dw ?	; config
ti_xpos		dw ?	; text window x,y
ti_ypos		dw ?
ti_cols		dw ?	; size of screen-line
ti_bcol		dw ?	; size of buffer-line
ti_xoff		dw ?	; x offset on screen
ti_boff		dw ?	; base offset - start of screen-line
ti_clat		db ?	; clear attrib
ti_clch		db ?	; clear char
ti_cursor	S_CURSOR <?>
ti_bcnt		dw ?	; byte count in line
ti_clso		dw ?	; Clipboard start offset
ti_cleo		dw ?	; Clipboard end offset
ti_clsl		dw ?	; Clipboard start line
ti_clel		dw ?	; Clipboard end line
ti_brow		dw ?	; number of lines in buffer
ti_rows		dw ?	; number of lines on screen
ti_loff		dw ?	; line offset in buffer
ti_yoff		dw ?	; y offset on screen
S_TINFO		ENDS	; 42 byte

externdef	tinfo: WORD	; offset SS/DS

TITABCHAR	equ 0Bh ; expand/trunc tabs with this char (Vertical Tab)
TIMAXSCRLINE	equ 128
TIMAXTABSIZE	equ 64

ifdef __TE__

TIMAXFILES	equ 100
TIMINLINE	equ 128
TIMAXLINE	equ 1024
STYLESIZE	equ 4096
EMSMINPAGES	equ 4
WMAXPATH	equ 260

S_TEDIT		STRUC
te_info		S_TINFO <?>
ti_stat		db ?	; style attrib
ti_stch		db ?	; style char
ti_lcnt		dw ?	; line count in file
ti_emmh		dw ?	; EMM handle
ti_emmp		dw ?	; EMM page
ti_file		dd ?	; file name
ti_time		dw ?	; file time
ti_date		dw ?	; file date
ti_size		dd ?	; file size
ti_next		dw ?	; next file
ti_prev		dw ?	; prev file
ti_style	dd ?
ti_DOBJ		S_DOBJ <?>
S_TEDIT		ENDS	; 86 byte

externdef	teflag:WORD
externdef	tepages:WORD
externdef	telsize:WORD
externdef	tetabsize:WORD
externdef	fsflag:WORD
externdef	searchstring:BYTE
externdef	replacestring:BYTE

tistate		PROTO _CType	; AX tinfo
tigetfile	PROTO _CType
topen		PROTO _CType :DWORD
tclose		PROTO _CType
tcloseall	PROTO _CType
tmodal		PROTO _CType
tdlgopen	PROTO _CType
teoption	PROTO _CType

endif

.list
