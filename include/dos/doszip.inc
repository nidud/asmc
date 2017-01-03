__DZ__		equ 1	; Doszip
__CAL__		equ 1	; Calendar
__FF__		equ 1	; File Find
__AT__		equ 1	; Edit Color
__TV__		equ 1	; Text View

include dir.inc
include fblk.inc
include wsub.inc
include filter.inc
include version.inc
include dzidd.inc
include macro.inc
include tview.inc

.xlist

externdef envseg:	word
externdef _dsstack:	word
externdef sys_ercode:	word
externdef sys_erflag:	byte
externdef sys_erdrive:	byte
tedit	proto _CType :dword, :word

; Configuration file:	DZ.CFG

_C_PANELID	equ 0001h	; config.c_lflag
_C_HORIZONTAL	equ 0002h
_C_ESCUSERSCR	equ 0004h
_C_EGALINE	equ 0008h
_C_SELECTDIR	equ 0010h
_C_INSMOVDN	equ 0020h
_C_CDCLRDONLY	equ 0040h
_C_AUTOSAVE	equ 0080h
_C_SORTDIR	equ 0100h
_C_WIDEVIEW	equ 0200h	;*
_C_DELHISTORY	equ 0400h
_C_DELTEMP	equ 0800h
_C_MENUSLINE	equ 1000h
_C_STATUSLINE	equ 2000h
_C_COMMANDLINE	equ 4000h
_C_DEFAULT	equ 70B0h

_C_CONFCOPY	equ 01h ; config.c_confirm
_C_CONFMOVE	equ 02h
_C_CONFDELETE	equ 04h
_C_CONFDELSUB	equ 08h
_C_CONFSYSTEM	equ 10h
_C_CONFRDONLY	equ 20h
_C_CONFEXIT	equ 40h

_C_ZINCSUBDIR	equ 01h ; config.c_compress

_MKL_APPEND	equ 0001h	; add to list or create new
_MKL_UNIX	equ 0002h	; convert to unix
_MKL_EXCL_CD	equ 0004h	; use local directory
_MKL_EXCL_DRV	equ 0008h	; use drive in directory
_MKL_EXCL_FILE	equ 0010h	; use file name in directory
_MKL_MASK	equ 0020h	; add mask to directory\[*.*]
_MKL_MACRO	equ 0100h	; use output macro

S_MKLST		STRUC
mkl_flag	dw ?
mkl_offspath	dw ?	; length of local directory
mkl_offset	dd ?	; search offset from findfile
mkl_handle	dw ?
mkl_count	dd ?	; total file count in list
S_MKLST		ENDS

S_CONFIG	STRUC
c_version	dw ?	; hex: 0.1.3.8 --> 0138h
c_lflag		dw ?
c_confirm	dw ?
c_console	dw ?	; -- console.inc
c_fsflag	dw ?	; -- iost.inc
c_tvflag	dw ?	; -- tview.asm
c_teflag	dw ?	; -- tedit.asm
c_tepages	dw ?	; -- tedit.asm Max EMS pages to alloc
c_telsize	dw ?	; -- tedit.asm Max line length
c_tetabsize	dw ?	; -- tedit.asm Tab Size
c_compress	dw ?	; -- inline .ZIP
c_ffflag	dw ?	; -- ff.asm
c_comprlevel	dw ?
c_panelsize	dw ?	; Alt-Up/Down
c_flaga		dw ?
c_fcb_indexa	dw ?
c_cel_indexa	dw ?
c_flagb		dw ?
c_fcb_indexb	dw ?
c_cel_indexb	dw ?
c_apath		S_PATH <?>
c_bpath		S_PATH <?>
c_filter	S_FILT <?>
c_color		db 3*16 dup(?)
c_pending_file	db 260 dup(?)
c_list		S_MKLST <?>
S_CONFIG	ENDS

S_XCELL		STRUC
xl_flag		dw ?	; DOBJ.dl_flag
xl_cols		db ?	; number of files in one line
xl_rows		db ?	; number of lines in panel
xl_rect		dd ?	; the current position of cell
xl_bp		dd ?	; DOBJ.dl_wp
xl_cpos		dd ?	; position of first cell in panel
S_XCELL		ENDS

_P_PANELID	equ 0001h
_P_VISIBLE	equ 0002h
_P_MINISTATUS	equ 0004h
_P_WIDEVIEW	equ 0008h
_P_DETAIL	equ 0010h
_P_DRVINFO	equ 0020h
_P_WHIDDEN	equ 0040h

S_PANEL		STRUC
pn_path		dw ?
pn_flag		dw ?
pn_fcb_count	dw ?
pn_cel_count	dw ?
pn_fcb_index	dw ?
pn_cel_index	dw ?
pn_xl		dd ?
pn_dialog	dd ?
pn_wsub		dd ?
pn_putfcb	dw ?
S_PANEL		ENDS

S_DZPATH	STRUC
dzp_dir		db MAXPATH dup(?)
dzp_flag	dw ?
dzp_bufid	dw ?
dzp_celid	dw ?
S_DZPATH	ENDS

S_DIRECTORY	STRUC
path		db MAXPATH dup(?)
flag		dw ?
fcb_index	dw ?
cel_index	dw ?
S_DIRECTORY	ENDS

S_OPENFILE	STRUC
of_path		db WMAXPATH dup(?)
of_loff		dw ?
of_yoff		dw ?
of_boff		dw ?
of_xoff		dw ?
S_OPENFILE	ENDS

MAXHISTORY	equ 16
MAXDOSKEY	equ 128
MAXDOSKEYS	equ 16

S_HISTORY	STRUC
h_directory	S_DIRECTORY MAXHISTORY dup(<?>)
h_doskey	db MAXDOSKEYS*MAXDOSKEY dup(?)
h_selectmask	db 32 dup(?)
S_HISTORY	ENDS

externdef config:	S_CONFIG
externdef cflag:	word
externdef flaga:	word
externdef flagb:	word
externdef fsflag:	word
externdef tvflag:	word
externdef path_a:	S_PATH
externdef path_b:	S_PATH
externdef ffflag:	word
externdef compressflag: word
externdef compresslevel:word
externdef opfilter:	S_FILT
externdef programpath:	byte	; _argv[0]/C<directory>
externdef configpath:	byte	; envconf/programpath
externdef configfile:	byte	; envconf/programpath
externdef searchstring: byte
externdef dzexe:	dword	; DZ.EXE
;externdef envconf:	dword	; %DZ%
externdef envpath:	dword	; %PATH%
externdef envtemp:	dword	; %TEMP%
externdef comspec:	dword	; %COMSPEC%

externdef cpanel:	word
externdef panela:	word
externdef panelb:	word
externdef spanela:	S_PANEL
externdef spanelb:	S_PANEL
externdef wspanela:	word
externdef prect_a:	word
externdef prect_b:	word
externdef mklist:	S_MKLST

config_read		proto
config_save		proto

historyremove		proto
historysave		proto
historymove		proto
historytocpanel		proto
doskeytocommand		proto
doskeysave		proto

prect_hide		proto
prect_close		proto
prect_open		proto pascal
prect_clear		proto pascal rect:dword, ptype:word
fblk_select		proto pascal fblk:dword
fblk_invert		proto pascal fblk:dword
pcell_select		proto
pcell_set		proto
pcell_open		proto
pcell_show		proto
pcell_update		proto
pcell_move		proto pascal
pcell_setxy		proto pascal panel:word, xpos:word, ypos:word

cpanel_state		proto
cpanel_findfirst	proto
cpanel_gettarget	proto
cpanel_setpath		proto
cpanel_deselect		proto pascal fblk:dword

panel_state		proto
panel_close		proto
panel_hide		proto
panel_show		proto
panel_setactive		proto
panel_curobj		proto
panel_findnext		proto
panel_openmsg		proto
panel_putinfo		proto pascal
panel_putmini		proto pascal
panel_read		proto
panel_reread		proto
panel_redraw		proto
panel_toggle		proto
panel_update		proto
panel_xormini		proto
panel_xorinfo		proto
panel_setid		proto	; panel:AX, index:DX
panel_putitem		proto pascal panel:word, index:word
panel_xycmd		proto pascal panel:word, xpos:word, ypos:word
panel_sethdd		proto pascal panel:word, hdd:word
panel_event		proto pascal panel:word, event:word
panel_stateab		proto
redraw_panels		proto

cmalong		proto _CType
cmadetail	proto _CType
cmahidden	proto _CType
cmamini		proto _CType
cmavolinfo	proto _CType
cmaname		proto _CType
cmatype		proto _CType
cmadate		proto _CType
cmasize		proto _CType
cmanosort	proto _CType
cmatoggle	proto _CType
cmafilter	proto _CType
cmasubinfo	proto _CType
cmaupdate	proto _CType
cmachdrv	proto _CType

cmrename	proto _CType
cmview		proto _CType
cmedit		proto _CType
cmtmodal	proto _CType
cmcopy		proto _CType
cmmove		proto _CType
cmmkdir		proto _CType
cmdelete	proto _CType
cmattrib	proto _CType
cmcompress	proto _Ctype
cmdecompress	proto _Ctype

ifdef __FF__
  cmsearch	proto _CType
endif
cmhistory	proto _CType
cmexit		proto _CType

cmselect	proto _CType
cmdeselect	proto _CType
cminvert	proto _CType
cmquicksearch	proto _CType	; Ctrl-Q
cmcompare	proto _CType

cmtoggleon	proto _CType
cmtogglehz	proto _CType
cmtogglesz	proto _CType
cmegaline	proto _CType
cmswap		proto _CType
cmconfirm	proto _CType
cmpanel		proto _CType
cmcompression	proto _CType
ifdef __TE__
teoption	proto _CType
endif
cmscreen	proto _CType
cmsystem	proto _CType
cmoptions	proto _CType

cmhelp		proto _CType
cmabout		proto _CType

cmblong		proto _CType
cmbdetail	proto _CType
cmbhidden	proto _CType
cmbmini		proto _CType
cmbvolinfo	proto _CType
cmbname		proto _CType
cmbtype		proto _CType
cmbdate		proto _CType
cmbsize		proto _CType
cmbnosort	proto _CType
cmbtoggle	proto _CType
cmbfilter	proto _CType
cmbsubinfo	proto _CType
cmbupdate	proto _CType
cmbchdrv	proto _CType

cmawideview	proto _CType
cmbwideview	proto _CType
cmcwideview	proto _CType

cmcopycell	proto _CType
cmlastmenu	proto _CType
cmtool0		proto _CType
cmtool1		proto _CType
cmtool2		proto _CType
cmtool3		proto _CType
cmtool4		proto _CType
cmtool5		proto _CType
cmtool6		proto _CType
cmtool7		proto _CType
cmtool8		proto _CType
cmtool9		proto _CType
cmpath0		proto _CType
cmpath1		proto _CType
cmpath2		proto _CType
cmpath3		proto _CType
cmpath4		proto _CType
cmpath5		proto _CType
cmpath6		proto _CType
cmpath7		proto _CType
cmcname		proto _CType
cmctype		proto _CType
cmcdate		proto _CType
cmcsize		proto _CType
cmuserscreen	proto _CType
cmchidden	proto _CType
cmclong		proto _CType
cmcmini		proto _CType
cmcupdate	proto _CType
cmcdetail	proto _CType
cmcnosort	proto _CType
cmvolinfo	proto _CType
cmxormenubar	proto _CType
cmxorkeybar	proto _CType
cmxorcmdline	proto _CType
cmupdir		proto _CType
cmsubdir	proto _CType
cmcfblktocmd	proto _CType
cmpathatocmd	proto _CType
cmpathbtocmd	proto _CType
cmclrcmdl	proto _CType
cmpsizeup	proto _CType
cmpsizedn	proto _CType
cmpathleft	proto _CType	  ; Alt-Left  - Previous Directory
cmpathright	proto _CType	; Alt-Right - Next Directory
cmdoskey_up	proto _CType	; Alt-Up    - Previous Command
cmdoskey_dn	proto _CType	; Alt-Down  - Next Command
cmsavesetup	proto _CType	; Shift-F10
cmsubsize	proto _CType	; F3
cmsubinfo	proto _CType	; Menus
cmquit		proto _CType		; Alt-X
clrcmdl		proto _CType		; Esc
cmfilter	proto _CType
cmmklist	proto _CType	; Alt-L
cmloadpath	proto _CType	; Alt-P
ifdef __CAL__
 cmcalendar	proto _CType	; Ctrl-G
endif
ifdef __ZIP__
  cmmkzip	proto _CType	; Shift-F7
endif
ifdef DEBUG
  cmdebug	proto _CType	; Shift-F1
endif
cmmemory	proto _CType	; Alt-M
cmhomedir	proto _CType
ifdef __TE__
cmwindowlist	proto _CType
endif

setconfirmflag		proto

externdef mainswitch:	word
externdef dzexitcode:	word
externdef global_key:	word
externdef com_base:	byte
externdef com_wsub:	word

cominit		proto pascal :dword
comshow		proto
comhide		proto
comevent	proto pascal :word

externdef convbuf:	byte
externdef cp_dzcmd:	byte

command		proto pascal :dword
dzexpenviron	proto _Ctype :dword
fbinitype	proto pascal :dword, :dword
;inicommand	proto _CType :dword, :dword, :dword

load_tedit	proto pascal :dword, :word
load_tview	proto pascal :dword, :word
loadiniproc	proto pascal :dword, :dword, :word
cm_loadfblk	proto

externdef cp_copy:	byte
externdef cp_space:	byte
externdef DLG_Commandline:dword
externdef DLG_Statusline:dword
externdef DLG_Menusline:dword
externdef cp_tools:	byte

open_idd		proto
modal_idd		proto
close_idd		proto
tools_idd		proto pascal :word, :dword, :dword
statusline_xy		proto
prect_open_ab		proto
panel_open_ab		proto
apiopen			proto
apiclose		proto
apiupdate		proto

externdef cp_search:	byte

notsup		proto _CType
cmfilter_load	proto _CType
view_readme	proto _CType

externdef cp_compare:	byte
externdef cp_copyselected:byte
externdef cp_delete:	byte
externdef cp_ziplst:	byte

ret_update_AB	proto
mkziplst	proto _CType
mkziplst_open	proto _CType

externdef cp_directory: byte

_COPY_SELECTED	equ 01h ; copy selected files
_COPY_IARCHIVE	equ 02h ; source is archive
_COPY_OARCHIVE	equ 04h ; target is archive
_COPY_IEXTFILE	equ 08h ; source is .DLL archive - %doszip%/dll/.dll
_COPY_IZIPFILE	equ 10h ; source is .ZIP archive
_COPY_OZIPFILE	equ 20h ; target is .ZIP archive
_COPY_OEXTFILE	equ 40h ; target is .DLL archive
_COPY_RECURSIV	equ 80h ; recursive error

externdef cp_move:	byte
externdef copy_jump:	word
externdef copy_flag:	byte

fp_copydirectory	proto _CType :dword
fp_copyfile		proto _CType :dword, :dword
copyfile		proto pascal :dword, :word, :word, :word

externdef cp_select:	byte
externdef cp_deselect:	byte

removetemp proto _CType :dword
getpanelb proto

ifdef __l__
_DZIP	SEGMENT WORD USE16 public 'CODE'
_DZIP	ENDS
	ASSUME CS:_DZIP, DS:DGROUP
else
_DZIP	equ <_TEXT>
endif

.list
