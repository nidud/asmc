; DRVRETRY.ASM--
; Copyright (C) 2015 Doszip Developers

include dir.inc
include conio.inc
include errno.inc

extrn	IDD_DriveNotReady:DWORD

	.code

_disk_retry PROC _CType PUBLIC USES di disk:size_t
local	dialog:DWORD
local	ypos:size_t
local	xpos:size_t
	invoke	rsopen,IDD_DriveNotReady
	jz	@F
	stom	dialog
	mov	di,ax
	mov	es,dx
	sub	ax,ax
	mov	al,es:[di][4]
	add	al,25
	mov	xpos,ax
	mov	al,es:[di][5]
	add	al,2
	mov	ypos,ax
	invoke	dlshow,dialog
	mov	ax,disk
	add	al,'A'
	invoke	scputc,xpos,ypos,1,ax
	sub	xpos,22
	add	ypos,2
	mov	di,errno
	shl	di,2
	lodm	sys_errlist[di]
	invoke	scputs,xpos,ypos,0,29,dx::ax
	invoke	dlmodal,dialog
	test	ax,ax
      @@:
	ret
_disk_retry ENDP

	END
