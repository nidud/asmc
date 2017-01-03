; CMHELP.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include string.inc
include conio.inc
include dir.inc
include helpid.inc

_DATA	segment

CP_COPYING db 'LICENSE.TXT',0
CP_DZTXT   db 'DOSZIP.TXT',0
Offset_README label WORD
	dw 0		; DZ.TXT
	dw HELPID_01	; Memory
	dw HELPID_02	; Compress
	dw HELPID_03	; View
	dw HELPID_06	; Extension
	dw HELPID_07	; Environ
	dw HELPID_08	; Windows
	dw HELPID_08	; Install
	dw HELPID_09	; Tools
	dw HELPID_10	; FF
	dw HELPID_11	; List
	dw HELPID_12	; Filter
	dw HELPID_13	; Shortkey

M_WZIP	macro val, count
	db 0F0h or ((count and 0FF00h) shr 8)
	db count and 00FFh
	db val
	endm

S_OOBJ		STRUC
ro_flag		dw ?
ro_mem		db ?
ro_key		db ?
ro_rcx		db ?
ro_rcy		db ?
ro_rcc		db ?
ro_rcr		db ?
S_OOBJ		ENDS

;******** Resource begin DZABOUT *
;	{ 0x005C,   2,	 0, {15, 7,50,10} },
;	{ 0x0000,   0, 'O', {20, 8, 8, 1} },
;	{ 0x400A,   0, 'L', {17, 5,28, 1} },
;******** Resource data	 *******************
DZABOUT_RC label WORD
	dw	1116		; Alloc size
	S_OOBJ	<005Ch,2,0,15,7,50,10>
	S_OOBJ	<_O_PBUTT,0,'O',20,8,8,1>
	S_OOBJ	<_O_TBUTT or _O_CHILD,0,'L',17,5,28,1>
	M_WZIP	5Ch,50
	M_WZIP	29h,50*7+20
	M_WZIP	50h,3
	db	5Dh
	M_WZIP	50h,4
	M_WZIP	20h,50*2+20
	M_WZIP	' About',22
	M_WZIP	' The Doszip Commander Version ',78
	db	VERSSTR
	db	' Dos16'
	M_WZIP	' Copyright (C) 97-2016 Doszip Developers',11
	M_WZIP	' ',11
	M_WZIP	'Ä',39
	M_WZIP	' License:     GNU General Public License',11
%	M_WZIP	' Build Date:  &@Date  Time: &@Time',11
	M_WZIP	' OK   ',79
	db	'Ü'
	M_WZIP	' ',42
	M_WZIP	'ß',8
	M_WZIP	' ',21
;******** Resource end	 DZABOUT *

_DATA	ENDS

_DZIP	segment

view_doszip PROC pascal PRIVATE f:DWORD, o:DWORD
local path[WMAXPATH]:BYTE
	invoke strfcat,addr path,addr configpath,f
  ifdef __TV__
    ifdef __MEMVIEW__
	invoke tview,dx::ax,o,0,0
    else
	invoke tview,dx::ax,o
    endif
  else
	invoke load_tview,dx::ax,0
  endif
	ret
view_doszip ENDP

view_readme PROC _CType PUBLIC
	sub dx,dx
	invoke view_doszip,addr CP_DZTXT,dx::ax
	ret
view_readme ENDP

view_license PROC _CType PRIVATE
	invoke view_doszip,addr CP_COPYING,16090
	ret
view_license ENDP

cmabout PROC _CType PUBLIC
	invoke rsopen,addr DZABOUT_RC
	.if ax
	    movp es:[bx].S_TOBJ.to_proc[32],view_license
	    invoke dlmodal,dx::ax
	.endif
	ret
cmabout ENDP

cmhelp	PROC _CType PUBLIC USES si di
	.if rsopen(IDD_DZHelp)
	    mov si,dx
	    mov di,ax
	    mov ax,offset cmabout
	    movp es:[di].S_TOBJ.to_proc[15*16],cmabout
	    pushl cs
	    push ax
	    call thelp_set
	    .repeat
		invoke rsevent,IDD_DZHelp,si::di
		.break .if ax <= 0
		dec ax
		add ax,ax
		mov bx,ax
		mov ax,[bx+Offset_README]
		call view_readme
	    .until 0
	    invoke dlclose,si::di
	    call thelp_pop
	    mov ax,1
	.endif
	ret
cmhelp	ENDP

_DZIP	ENDS

	END
