; DRVINIT.ASM--
; Copyright (C) 2015 Doszip Developers

include dir.inc
include dos.inc

	.data
	cp_selectdisk db 'Select disk',0
	.code

_disk_init PROC _CType PUBLIC USES di disk:size_t
	mov di,disk
	invoke _disk_test, di
	.if ax == _DISK_NOSUCHDRIVE || ax == -1
	    invoke beep,5,7
	    invoke _disk_select,addr cp_selectdisk
	    .if ax
		dec ax
		invoke _disk_init,ax
		mov di,ax
	    .endif
	.endif
	mov ax,di
	ret
_disk_init ENDP

	END
