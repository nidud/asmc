; DOSZIP.INC--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT
include direct.inc
include wsub.inc
include filter.inc
include tinfo.inc
include time.inc
include dzlib.inc

	.xlist

DOSZIP_VERSION	equ 0351h
DOSZIP_MINVERS	equ 0349h
DOSZIP_VSTRING	equ <"3.51">
DOSZIP_VSTRPRE	equ <"      ">

MAXHISTORY	equ 32
MAXDOSKEYS	equ 64

DZMINROWS	equ 25
DZMINCOLS	equ 80
DZMAXROWS	equ 240
DZMAXCOLS	equ 240

DOSZIP_INIFILE	equ <"dz.ini">	; config file
DOSZIP_TXTFILE	equ <"dz.txt">	; readme file

externdef	DZTitle:DWORD
externdef	DZ_INIFILE:BYTE
externdef	DZ_TXTFILE:BYTE

HELPID_02	equ 0692h	; <> Compressed File Support
HELPID_03	equ 0815h	; <> Viewer Support
HELPID_04	equ 0A61h	; <> Editor Support
HELPID_05	equ 0BB0h	; <> Internal Editor
HELPID_06	equ 18E0h	; <> Extension and Filename Support
HELPID_07	equ 1CC8h	; <> Doszip Commander Environment Variables
HELPID_08	equ 231Ch	; <> Installing Commander under Windows
HELPID_09	equ 245Fh	; <> Creating a tools menu
HELPID_10	equ 29B3h	; <> The File Search utility
HELPID_11	equ 3022h	; <> Create List File
HELPID_12	equ 3349h	; <> Operation Filter
HELPID_13	equ 35C4h	; <> Shortcut keys
HELPID_14	equ 2C9Eh	; <> Compare Directories
HELPID_15	equ 4413h	; <> Configuration Defaults

_C_PANELID	equ 0001h	; config.c_cflag
_C_HORIZONTAL	equ 0002h
_C_ESCUSERSCR	equ 0004h
_C_EGALINE	equ 0008h
_C_SELECTDIR	equ 0010h
_C_INSMOVDN	equ 0020h
_C_CDCLRDONLY	equ 0040h
_C_AUTOSAVE	equ 0080h
_C_SORTDIR	equ 0100h
_C_WIDEVIEW	equ 0200h
_C_DELHISTORY	equ 0400h
_C_DELTEMP	equ 0800h
_C_MENUSLINE	equ 1000h
_C_STATUSLINE	equ 2000h
_C_COMMANDLINE	equ 4000h
_C_CONFCOPY	equ 00010000h
_C_CONFMOVE	equ 00020000h
_C_CONFDELETE	equ 00040000h
_C_CONFDELSUB	equ 00080000h
_C_CONFSYSTEM	equ 00100000h
_C_CONFRDONLY	equ 00200000h
_C_CONFEXIT	equ 00400000h
_C_ZINCSUBDIR	equ 00800000h
_C_VISUALUPDATE equ 01000000h
_C_PANELEDIT	equ 02000000h
_C_DEFAULT	equ 017F70A4h

_MKL_APPEND	equ 0001h	; add to list or create new
_MKL_UNIX	equ 0002h	; convert to unix
_MKL_EXCL_CD	equ 0004h	; use local directory
_MKL_EXCL_DRV	equ 0008h	; use drive in directory
_MKL_EXCL_FILE	equ 0010h	; use file name in directory
_MKL_MASK	equ 0020h	; add mask to directory\[*.*]
_MKL_MACRO	equ 0100h	; use output macro

S_MKLST		STRUC
mkl_flag	dd ?
mkl_offspath	dd ?		; length of local directory
mkl_offset	dd ?		; search offset from findfile
mkl_handle	dd ?
mkl_count	dd ?		; total file count in list
S_MKLST		ENDS

S_MSOBJ		STRUC
mo_rect		dd ?
mo_proc		dd ?
S_MSOBJ		ENDS

S_SBLK		STRUC
sb_flag		dd ?
sb_size		dd ?
sb_line		dd ?
sb_offs		dd ?
sb_file		db 4 dup(?)
S_SBLK		ENDS

INFOSIZE	equ 38
BLOCKSIZE	equ SIZE S_SBLK + INFOSIZE

_XY_DRVINFO	equ 8
_XY_CONFIG	equ 7
_XY_MINISTATUS	equ 6
_XY_NEWDISK	equ 5
_XY_MOVEUP	equ 4
_XY_MOVEDOWN	equ 3
_XY_FILE	equ 2
_XY_INSIDE	equ 1
_XY_OUTSIDE	equ 0

wsmaxfba	equ <config.c_apath.ws_maxfb>
wsmaxfbb	equ <config.c_bpath.ws_maxfb>
flaga		equ <config.c_apath.ws_flag>
flagb		equ <config.c_bpath.ws_flag>

S_XCEL		STRUC
xl_flag		dw ?		; DOBJ.dl_flag
xl_cols		db ?		; number of files in one line
xl_rows		db ?		; number of lines in panel
xl_rect		S_RECT <?>	; the current position of cell
xl_bp		dd ?		; DOBJ.dl_wp
xl_cpos		S_RECT <?>	; position of first cell in panel
S_XCEL		ENDS

S_PANEL		STRUC
pn_wsub		dd ?
pn_fcb_count	dd ?
pn_cel_count	dd ?
pn_fcb_index	dd ?
pn_cel_index	dd ?
pn_xl		dd ?
pn_dialog	dd ?
pn_putfcb	dd ?
S_PANEL		ENDS

S_CONFIG	STRUC		; Configuration file:	DZ.CFG
c_version	dd ?		; hex: 0.1.3.8 --> 0138h
c_cflag		dd ?
c_console	dd ?		; -- console.inc
c_fsflag	dd ?		; -- iost.inc
c_tvflag	dd ?		; -- tview.asm
c_teflag	dd ?		; -- tedit.asm
c_titabsize	dd ?		; -- tedit.asm Tab Size
c_ffflag	dd ?		; -- ff.asm
c_comprlevel	dd ?
c_panelsize	dd ?		; Alt-Up/Down
c_fcb_indexa	dd ?
c_cel_indexa	dd ?
c_fcb_indexb	dd ?
c_cel_indexb	dd ?
c_apath		S_WSUB <?>
c_bpath		S_WSUB <?>
c_filter	S_FILT <?>
c_color		S_COLOR <?>
c_list		S_MKLST <?>
S_CONFIG	ENDS

S_DIRECTORY	STRUC
path		dd ?
flag		dd ?
fcb_index	dd ?
cel_index	dd ?
S_DIRECTORY	ENDS

S_HISTORY	STRUC
h_directory	S_DIRECTORY MAXHISTORY dup(<?>)
h_doskey	dd MAXDOSKEYS dup(?)
h_selectmask	db 32 dup(?)
S_HISTORY	ENDS

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

externdef IDD_DZCompression:	DWORD
externdef IDD_DZConfiguration:	DWORD
externdef IDD_DZConfirmations:	DWORD
externdef IDD_DZCopy:		DWORD
externdef IDD_DZDefaultColor:	DWORD
externdef IDD_DZExit:		DWORD
externdef IDD_DZFileAttributes: DWORD
externdef IDD_DZFindFile:	DWORD
externdef IDD_DZHelp:		DWORD
externdef IDD_DZHistory:	DWORD
externdef IDD_DZMemory:		DWORD
externdef IDD_DZMenuEdit:	DWORD
externdef IDD_DZMenuFile:	DWORD
externdef IDD_DZMenuHelp:	DWORD
externdef IDD_DZMenuPanel:	DWORD
externdef IDD_DZMenuSetup:	DWORD
externdef IDD_DZMenusline:	DWORD
externdef IDD_DZMenuTools:	DWORD
externdef IDD_DZMKList:		DWORD
externdef IDD_DZMove:		DWORD
externdef IDD_DZPanelFilter:	DWORD
externdef IDD_DZPanelOptions:	DWORD
externdef IDD_DZSaveSetup:	DWORD
externdef IDD_DZScreenOptions:	DWORD
externdef IDD_DZSubInfo:	DWORD
externdef IDD_DZSystemOptions:	DWORD
externdef IDD_DZZipAttributes:	DWORD
externdef IDD_ConsoleSize:	DWORD
externdef IDD_CompareOptions:	DWORD

externdef cp_copy:		BYTE
externdef cp_compress:		BYTE
externdef cp_decompress:	BYTE
externdef cp_deselect:		BYTE
externdef cp_compare:		BYTE
externdef cp_copyselected:	BYTE
externdef cp_delete:		BYTE
externdef cp_directory:		BYTE
externdef cp_mkdir:		BYTE
externdef cp_mkzip:		BYTE
externdef cp_move:		BYTE
externdef cp_search:		BYTE
externdef cp_select:		BYTE
externdef cp_tools:		BYTE
externdef cp_space:		BYTE
externdef cp_subdir:		BYTE
externdef cp_updir:		BYTE
externdef cp_emaxfb:		BYTE
externdef cp_ziplst:		BYTE
externdef cp_selectmask:	BYTE

externdef at_background:	BYTE
externdef at_foreground:	BYTE
externdef findfilemask:		BYTE
externdef findfilepath:		BYTE
externdef filelist_bat:		BYTE
externdef format_lst:		BYTE
externdef searchstring:		BYTE
externdef replacestring:	BYTE
externdef default_arc:		BYTE
externdef default_zip:		BYTE
externdef com_base:		BYTE
externdef findfilemask:		BYTE
externdef findfilepath:		BYTE

externdef cpanel:		DWORD
externdef panela:		DWORD
externdef panelb:		DWORD
externdef cflag:		DWORD
externdef console:		DWORD
externdef fsflag:		DWORD
externdef tvflag:		DWORD
externdef teflag:		DWORD
externdef titabsize:		DWORD
externdef ffflag:		DWORD
externdef compresslevel:	DWORD

externdef history:		DWORD
externdef envpath:		DWORD	; %PATH%
externdef envtemp:		DWORD	; %TEMP%
externdef comspec:		DWORD	; %COMSPEC%
externdef mainswitch:		DWORD
externdef dzexitcode:		DWORD
externdef numfblock:		DWORD	; number of file pointers allocated
externdef global_key:		DWORD
externdef pConfigFile:		DWORD

externdef prect_a:		S_XCEL
externdef prect_b:		S_XCEL
externdef spanela:		S_PANEL
externdef spanelb:		S_PANEL
externdef path_a:		S_WSUB
externdef path_b:		S_WSUB
externdef opfilter:		S_FILT
externdef config:		S_CONFIG
externdef mklist:		S_MKLST
externdef com_info:		S_TEDIT
externdef MOBJ_Statusline:	S_MSOBJ

externdef DLG_Commandline:	DWORD
externdef DLG_Commandline:	DWORD
externdef menus_idd:		DWORD
externdef menus_obj:		DWORD
externdef menus_iddtable:	DWORD
externdef com_wsub:		DWORD

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

ifdef __CI__
CodeInfo		PROTO
endif
ifdef __BMP__
CaptureScreen		PROTO
endif

warcread		PROTO :DWORD
warctest		PROTO :DWORD, :DWORD
warcadd			PROTO :DWORD, :DWORD, :DWORD
warccopy		PROTO :DWORD, :DWORD, :DWORD, :DWORD
warcview		PROTO :DWORD, :DWORD
warcdelete		PROTO :DWORD, :DWORD

setconfirmflag		PROTO
config_read		PROTO
config_save		PROTO
config_open		PROTO

historyread		PROTO
historywrite		PROTO
historyremove		PROTO
historysave		PROTO
historymove		PROTO
historytocpanel		PROTO
doskeytocommand		PROTO
doskeysave		PROTO

LPPANEL TYPEDEF PTR S_PANEL

fblk_select		PROTO :LPFBLK
fblk_invert		PROTO :LPFBLK
prect_hide		PROTO :LPPANEL
prect_open_ab		PROTO
pcell_show		PROTO :LPPANEL
pcell_update		PROTO :LPPANEL
pcell_setxy		PROTO :LPPANEL, :UINT, :UINT

cpanel_state		PROTO
cpanel_findfirst	PROTO
cpanel_gettarget	PROTO
cpanel_setpath		PROTO :LPSTR
cpanel_deselect		PROTO :LPFBLK

panel_state		PROTO :LPPANEL
panel_close		PROTO :LPPANEL
panel_hide		PROTO :LPPANEL
panel_show		PROTO :LPPANEL
panel_setactive		PROTO :LPPANEL
panel_curobj		PROTO :LPPANEL
panel_findnext		PROTO :LPPANEL
panel_openmsg		PROTO :LPPANEL
panel_read		PROTO :LPPANEL
panel_reread		PROTO :LPPANEL
panel_redraw		PROTO :LPPANEL
panel_toggle		PROTO :LPPANEL
panel_update		PROTO :LPPANEL
panel_xormini		PROTO :LPPANEL
panel_xorinfo		PROTO :LPPANEL
panel_setid		PROTO :LPPANEL, :UINT
panel_putitem		PROTO :LPPANEL, :UINT
panel_xycmd		PROTO :LPPANEL, :UINT, :UINT
panel_sethdd		PROTO :LPPANEL, :UINT
panel_event		PROTO :LPPANEL, :UINT
panel_stateab		PROTO
panel_open_ab		PROTO
panel_getb		PROTO
panel_toggleact		PROTO

redraw_panel		PROTO :LPPANEL
redraw_panels		PROTO
reread_panels		PROTO

mklistidd		PROTO
mklistadd		PROTO
mkziplst		PROTO
mkziplst_open		PROTO

open_idd		PROTO :DWORD, :DWORD
modal_idd		PROTO :DWORD, :DWORD, :DWORD, :DWORD
close_idd		PROTO :DWORD, :DWORD
tools_idd		PROTO :DWORD, :DWORD, :DWORD
statusline_xy		PROTO :DWORD, :DWORD, :DWORD, :DWORD

menus_getevent		PROTO
menus_event		PROTO :DWORD, :DWORD
menus_modalidd		PROTO :DWORD

cominit			PROTO :DWORD
cominitline		PROTO
comhide			PROTO
comshow			PROTO
clrcmdl			PROTO
comevent		PROTO :DWORD
comhndlevent		PROTO
command			PROTO :DWORD

FindFile		PROTO :DWORD
cmfilter_load		PROTO

cm_loadfblk		PROTO
cmfilter_load		PROTO
view_readme		PROTO
doszip_show		PROTO
doszip_hide		PROTO

apiidle			PROTO
apimode			PROTO
apiega			PROTO
apiopen			PROTO
apihide			PROTO
apishow			PROTO
apiclose		PROTO
apiupdate		PROTO

cmalong			PROTO
cmadetail		PROTO
cmahidden		PROTO
cmamini			PROTO
cmavolinfo		PROTO
cmaname			PROTO
cmatype			PROTO
cmadate			PROTO
cmasize			PROTO
cmanosort		PROTO
cmatoggle		PROTO
cmafilter		PROTO
cmasubinfo		PROTO
cmahistory		PROTO
cmaupdate		PROTO
cmachdrv		PROTO

cmrename		PROTO
cmview			PROTO
cmedit			PROTO
cmtmodal		PROTO
cmcopy			PROTO
cmmove			PROTO
cmmkdir			PROTO
cmdelete		PROTO
cmattrib		PROTO
cmcompress		PROTO
cmdecompress		PROTO
cmsearch		PROTO
cmcompsub		PROTO
cmhistory		PROTO
cmexit			PROTO

cmselect		PROTO
cmdeselect		PROTO
cminvert		PROTO
cmquicksearch		PROTO	; Ctrl-Q
cmcompare		PROTO

cmtoggleon		PROTO
cmtogglehz		PROTO
cmtogglesz		PROTO
cmegaline		PROTO
cmswap			PROTO
cmconfirm		PROTO
cmpanel			PROTO
cmcompression		PROTO
teoption		PROTO
cmscreen		PROTO
cmsystem		PROTO
cmoptions		PROTO

cmhelp			PROTO
cmabout			PROTO

cmblong			PROTO
cmbdetail		PROTO
cmbhidden		PROTO
cmbmini			PROTO
cmbvolinfo		PROTO
cmbname			PROTO
cmbtype			PROTO
cmbdate			PROTO
cmbsize			PROTO
cmbnosort		PROTO
cmbtoggle		PROTO
cmbfilter		PROTO
cmbsubinfo		PROTO
cmbhistory		PROTO
cmbupdate		PROTO
cmbchdrv		PROTO

cmawideview		PROTO
cmbwideview		PROTO
cmcwideview		PROTO

cmcopycell		PROTO
cmlastmenu		PROTO
cmtool0			PROTO
cmtool1			PROTO
cmtool2			PROTO
cmtool3			PROTO
cmtool4			PROTO
cmtool5			PROTO
cmtool6			PROTO
cmtool7			PROTO
cmtool8			PROTO
cmtool9			PROTO
cmpath0			PROTO
cmpath1			PROTO
cmpath2			PROTO
cmpath3			PROTO
cmpath4			PROTO
cmpath5			PROTO
cmpath6			PROTO
cmpath7			PROTO
cmcname			PROTO
cmctype			PROTO
cmcdate			PROTO
cmcsize			PROTO
cmuserscreen		PROTO
cmchidden		PROTO
cmclong			PROTO
cmcmini			PROTO
cmcupdate		PROTO
cmcdetail		PROTO
cmcnosort		PROTO
cmvolinfo		PROTO
cmxormenubar		PROTO
cmxorkeybar		PROTO
cmxorcmdline		PROTO
cmupdir			PROTO
cmsubdir		PROTO
cmcfblktocmd		PROTO
cmpathatocmd		PROTO
cmpathbtocmd		PROTO
cmclrcmdl		PROTO
cmpsizeup		PROTO
cmpsizedn		PROTO
cmpathleft		PROTO	; Alt-Left  - Previous Directory
cmpathright		PROTO	; Alt-Right - Next Directory
cmdoskeyup		PROTO	; Alt-Up    - Previous Command
cmdoskeydown		PROTO	; Alt-Down  - Next Command
cmsavesetup		PROTO	; Shift-F10
cmsubsize		PROTO	; F3
cmsubinfo		PROTO	; Menus
cmquit			PROTO	; Alt-X
clrcmdl			PROTO	; Esc
cmfilter		PROTO
cmmklist		PROTO	; Alt-L
cmloadpath		PROTO	; Alt-P
cmcalendar		PROTO	; Ctrl-G
cmmkzip			PROTO	; Shift-F7
IFDEF DEBUG
cmdebug			PROTO	; Shift-F1
ENDIF
cmsysteminfo		PROTO	; Alt-M
cmhomedir		PROTO
cmwindowlist		PROTO
cmenviron		PROTO	; Shift-F6
cmscreensize		PROTO

conssetl		PROTO :DWORD
consuser		PROTO
editattrib		PROTO

.list
