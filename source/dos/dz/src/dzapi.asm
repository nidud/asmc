; DZAPI.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include conio.inc
include errno.inc
include time.inc
include tinfo.inc
include alloc.inc
include io.inc

extrn	com_info:S_TINFO
extrn	cp_linefeed:BYTE

_DATA	segment

F0		equ 0F0h
A0		equ 03Ch
A1		equ 03Fh

Commandline_RC	dw 0200h,0010h,0000h
		db 0
Commandline_Y	db 23
Commandline_C0	db 80,1,F0
Commandline_C1	db 80,07h,F0
Commandline_C2	db 80,' '
IDD_Commandline dd DGROUP:Commandline_RC

Statusline_RC	dw 0200h,0450h,0000h
		db 0
Statusline_Y	db 24
Statusline_C0	db 80,1
		db A0,A1,A1,F0,7,A0,A1,A1,F0,6,A0,A1,A1,F0,7,A0,A1,A1,F0,7,A0
		db A1,A1,F0,7,A0,A1,A1,F0,7,A0,A1,A1,F0,8,A0,A1,A1,F0,6,A0,A1
		db A1,A1,F0
Statusline_C1	db 5,A0
		db ' F1 Help  F2 Ren  F3 View  F4 Edit  F5 Copy  F6 Move '
		db ' F7 Mkdir  F8 Del  F10 Exit',F0
Statusline_C2	db 0,' '
IDD_Statusline	dd DGROUP:Statusline_RC

Menusline_RC	dw 0200h,0050h,0000h,0000h
Menusline_C0	db 80,1
		db F0,8,A0,A1,A0,A0,A0,A1,F0,6,A0,A1,F0,6,A0,A1,F0,7,A0
		db A1,F0,7,A0,A1,F0,12,A0,A1,F0
Menusline_C1	db 4,A0,F0,20,38h
		db '  Panel-A   File   Edit   Setup   Tools   Help   Panel-B'
		db F0,24,' ',F0
Menusline_C2	db 0,' '
IDD_Menusline	dd DGROUP:Menusline_RC

dlgflags	db 5 dup(?)
dlgcursor	S_CURSOR <?>

_DATA	ENDS

_DZIP	segment

apiidle PROC _CType PRIVATE
	.if cflag & _C_MENUSLINE
	    call tupddate
	    call tupdtime
	.endif
	call trace
	xor ax,ax
	ret
apiidle ENDP

apimode PROC PRIVATE
	mov ax,3
	int 10h
	call consinit
apimode ENDP

apiega	PROC PRIVATE
	and cflag,not _C_EGALINE
	.if _scrrow > 24
	    or cflag,_C_EGALINE
	.endif
	ret
apiega	ENDP

apiopen PROC PUBLIC
	mov Statusline_C1,5
	mov Menusline_C1,4
	call consinit
	.if console & CON_IMODE
	    .if !(_scrcol == 80 && (_scrrow == 24 || _scrrow == 49))
		call apimode
	    .else
		mov al,24
		.if cflag & _C_EGALINE
		    mov al,49
		.endif
		invoke conssetl,ax
	    .endif
	.endif
	call cursory
	inc ax
	mov com_info.ti_ypos,ax
	mov al,_scrrow
	mov Statusline_Y,al
	.if cflag & _C_STATUSLINE
	    dec al
	.endif
	mov dx,com_info.ti_ypos
	.if dl < al
	    mov al,dl
	.endif
	mov Commandline_Y,al
	mov BYTE PTR com_info.ti_ypos,al
	invoke oswrite,1,addr cp_linefeed,2
	mov al,_scrcol
	mov Commandline_C0,al
	mov Commandline_C1,al
	mov Commandline_C2,al
	mov Statusline_C0,al
	mov Menusline_C0,al
	sub al,80
	add Statusline_C1,al
	mov Statusline_C2,al
	add Menusline_C1,al
	mov Menusline_C2,al
	invoke rsopen,IDD_Commandline
	stom DLG_Commandline
	invoke rsopen,IDD_Menusline
	stom DLG_Menusline
	.if cflag & _C_MENUSLINE
	    invoke dlshow,dx::ax
	    invoke tupdtime
	    invoke tupddate
	.endif
	invoke rsopen,IDD_Statusline
	stom DLG_Statusline
	.if cflag & _C_STATUSLINE
	    invoke dlshow,dx::ax
	.endif
	invoke comshow
	movp tupdate,apiidle
	call apiidle
	ret
apiopen ENDP

apiclose PROC PUBLIC
	invoke	dlclose,DLG_Menusline
	invoke	dlclose,DLG_Commandline
	invoke	dlclose,DLG_Statusline
	ret
apiclose ENDP

apiupdate PROC PUBLIC
	call	comhide
	invoke	dlhide,DLG_Menusline
	invoke	dlhide,DLG_Statusline
	call	redraw_panels
	mov	al,_scrrow
	les	bx,DLG_Statusline
	mov	es:[bx+5],al
	.if cflag & _C_STATUSLINE
	   invoke dlshow,DLG_Statusline
	.endif
	.if cflag & _C_MENUSLINE
	    invoke dlshow, DLG_Menusline
	.endif
	call comshow
	ret
apiupdate ENDP

cmegaline PROC _CType PUBLIC
	mov ax,49
	.if cflag & _C_EGALINE
	    mov al,24
	.endif
	invoke conssetl,ax
	call apiega
	call apiupdate
	ret
cmegaline ENDP

cmuserscreen PROC _CType PUBLIC
	.if _scrcol == 80
	    call consuser
	.else
	    call notsup
	.endif
	ret
cmuserscreen ENDP

_DZIP	ENDS

	END
