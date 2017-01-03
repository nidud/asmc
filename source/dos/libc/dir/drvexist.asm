; DRVEXIST.ASM--
; Copyright (C) 2015 Doszip Developers

include dir.inc
include dos.inc

extrn	cp_stdpath:BYTE ; 'C:\*.*'

	.code

_disk_exist PROC _CType PUBLIC disk:size_t
	mov ax,disk
	add al,'A'
	mov cp_stdpath,al
	mov ax,4E00h
	mov dx,offset cp_stdpath
	mov cx,07Fh
	int 21h ; hard error if not exist..
	.if CARRY?
	    call osmaperr
	    xor ax,ax
	.else
	    mov ax,1
	.endif
	ret
_disk_exist ENDP

	END
