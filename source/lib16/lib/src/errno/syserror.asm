; SYSERROR.ASM--
; Copyright (C) 2015 Doszip Developers

include dos.inc
include syserrls.inc
include conio.inc
include errno.inc

extrn	IDD_SystemError:DWORD

	.data

RECT_X	equ	14
RECT_Y	equ	5
RECT_C	equ	53
RECT_R	equ	15

DOBJ	label	S_DOBJ
	dw	001Dh
	db	4,3
DOBJX	db	RECT_X
DOBJY	db	RECT_Y
	db	RECT_C
	db	RECT_R
DLWP	dd	?
	dd	_DATA:ID_IGNORE

ID_IGNORE	dw _O_PBUTT
		db 0,'C',4,6,13,1
		dd ?,?
ID_RETRY	dw _O_PBUTT
		db 0,'R',4,8,13,1
		dd ?,?
ID_TERMINATE	dw _O_PBUTT
		db 0,'T',4,10,13,1
		dd ?,?
ID_FAIL		dw _O_PBUTT
		db 0,'A',4,12,13,1
		dd ?,?

CP_ERONDEVICE	db 'Error on device:',0
CP_ERMEMORY	db 'Memory error:',0
CP_ERBLOCKDEV	db 'Block Device Error:',0
CP_ERDRIVE	db 'Error on drive A:',0
CP_ERDISKAREA	db 'Disk area of error:',0
CP_DISKAREA	db 'DOS FAT ROOTDATA'

	.code

systemerror PROC _CType PUBLIC USES dx cx bx es si di
local	WP[1680]:BYTE
	xor	di,di
	push	ss
	lea	ax,WP
	push	ax
	mov	WORD PTR DLWP,ax
	mov	WORD PTR DLWP+2,ss
	push	ds
	mov	ax,WORD PTR IDD_SystemError
	add	ax,5*8+2
	push	ax
	push	RECT_C*RECT_R
	call	wcunzip
	mov	DOBJ.dl_flag,_D_DOPEN or _D_MYBUF or _D_SHADE or _D_DMOVE
	mov	DOBJX,RECT_X
	mov	DOBJY,RECT_Y
	mov	DOBJ.dl_index,3
	push	ds
	push	offset DOBJ
	call	dlshow
	mov	al,sys_erflag
	test	al,20h
	jz	systemerror_00
	mov	ID_IGNORE,_O_PBUTT
    systemerror_00:
	test	al,10h
	jz	systemerror_01
	mov	ID_RETRY,_O_PBUTT
    systemerror_01:
       test	al,08h
	jz	systemerror_02
	mov	ID_FAIL,_O_PBUTT
    systemerror_02:
	mov	dx,ds
	test	al,80h
	jz	systemerror_04
	les	bx,sys_erdevice
	test	BYTE PTR es:[bx+5],80h
	jz	systemerror_03
	mov	di,offset CP_ERONDEVICE
	lodm	sys_erdevice
	add	ax,10
	invoke	scputs,RECT_X+21,RECT_Y+2,0,7,dx::ax
	jmp	systemerror_06
    systemerror_03:
	mov	di,offset CP_ERMEMORY
	test	BYTE PTR sys_erflag,02h
	jnz	systemerror_06
	mov	di,offset CP_ERBLOCKDEV
	jmp	systemerror_06
    systemerror_04:
	mov	di,offset CP_ERDRIVE
	mov	al,sys_erdrive
	add	al,'A'
	mov	[di+15],al
	invoke	scputs,RECT_X+4,RECT_Y+3,0,0,addr CP_ERDISKAREA
	mov	al,sys_erflag
	and	ax,6
	add	ax,ax
	add	ax,offset CP_DISKAREA
	invoke	scputs,RECT_X+24,RECT_Y+3,0,4,ds::ax
    systemerror_06:
	mov	ax,offset CP_UNKNOWN
	mov	dx,sys_ercode
	cmp	dx,20
	ja	systemerror_07
	shl	dx,4/2
	mov	bx,dx
	mov	ax,WORD PTR [bx+dos_errlist]
    systemerror_07:
	mov	dx,RECT_Y+4
	mov	bx,RECT_X+4
	mov	cx,RECT_C-8
	cmp	di,offset CP_ERDRIVE
	jne	systemerror_08
	mov	dl,RECT_Y+2
	mov	bl,RECT_X+24
	mov	cl,RECT_C-27
    systemerror_08:
	invoke	scputs,bx,dx,0,cx,ds::ax
	invoke	scputs,RECT_X+4,RECT_Y+2,0,cx,ds::di
	xor	ax,ax
	mov	sys_ercode,ax
	mov	sys_erflag,al
	mov	sys_erdrive,al
	invoke	beep,10,9
	invoke	dlmodal,addr DOBJ
	test	ax,ax
	mov	dx,3
	jz	systemerror_09
	dec	ax
	mov	dx,ax
    systemerror_09:
	mov	ax,dx
	ret
systemerror ENDP

	END
