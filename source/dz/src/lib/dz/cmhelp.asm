; CMHELP.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include string.inc
include tview.inc
include stdlib.inc

    .data

DZ_TXTFILE	db DOSZIP_TXTFILE,0
Offset_README	dd 0	    ; DZ_TXTFILE
		dd HELPID_02	; Compress
		dd HELPID_03	; View
		dd HELPID_06	; Extension
		dd HELPID_07	; Environ
		dd HELPID_08	; Install
		dd HELPID_09	; Tools
		dd HELPID_10	; FF
		dd HELPID_11	; List
		dd HELPID_12	; Filter
		dd HELPID_13	; Shortkey

M_WZIP	macro val, count
    db 0F0h or ((count and 0FF00h) shr 8)
    db count and 00FFh
    db val
    endm

S_OOBJ	STRUC
ro_flag dw ?
ro_mem	db ?
ro_key	db ?
ro_rcx	db ?
ro_rcy	db ?
ro_rcc	db ?
ro_rcr	db ?
S_OOBJ	ENDS

;******** Resource begin DZABOUT *
;	{ 0x005C,   2,	 0, {15, 7,50,10} },
;	{ 0x0000,   0, 'O', {20, 8, 8, 1} },
;	{ 0x400A,   0, 'L', {17, 5,28, 1} },
;******** Resource data	 *******************

DZABOUT_RC label word
    dw	1600	    ; Alloc size
    S_OOBJ  <005Ch,1,0,15,7,50,12>
    S_OOBJ  <_O_PBUTT,0,'O',20,10,8,1>
    M_WZIP  50h,50
    M_WZIP  29h,50*9+20
    M_WZIP  80h,3
    db	8Dh
    M_WZIP  80h,4
    M_WZIP  25h,50*2+20
    M_WZIP  ' About',22
    M_WZIP  ' The Doszip Commander Version ',78
    db	DOSZIP_VSTRING
    db	DOSZIP_VSTRPRE
    M_WZIP  ' Copyright (C) 2016 Doszip Developers',11
    M_WZIP  ' ',14
    M_WZIP  196,39
    M_WZIP  ' Source code is available under the GNU',11
    M_WZIP  ' General Public License version 2.0',12
    M_WZIP  ' ',52
    M_WZIP  ' Build Date: ',14
%   db	"&@Date"
    M_WZIP  ' OK   ',50+46
    db	'Ü'
    M_WZIP  ' ',42
    M_WZIP  'ß',8
    M_WZIP  ' ',21
;******** Resource end	 DZABOUT *

    .code

view_doszip proc private f, o
    local   path[_MAX_PATH]:byte
    lea ecx,path
    tview (strfcat(ecx, _pgmpath, f), o)
    ret
view_doszip endp

view_readme proc
    view_doszip(addr DZ_TXTFILE, eax)
    ret
view_readme endp

cmabout proc
    rsmodal(addr DZABOUT_RC)
    ret
cmabout endp

cmhelp proc uses esi edi
    .if rsopen(IDD_DZHelp)
	mov edi,eax
	mov [edi].S_TOBJ.to_proc[13*16],cmabout
	mov esi,thelp
	mov thelp,cmabout
	.while rsevent(IDD_DZHelp, edi)
	    dec eax
	    mov eax,Offset_README[eax*4]
	    view_readme()
	.endw
	dlclose(edi)
	mov thelp,esi
	mov eax,1
    .endif
    ret
cmhelp endp

    END
