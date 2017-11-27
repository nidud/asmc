; DRVREADY.ASM--
; Copyright (C) 2015 Doszip Developers

include dir.inc
include string.inc
include errno.inc

	.code

_disk_ready PROC _CType PUBLIC disk:size_t
	push WORD PTR sys_erproc
	mov WORD PTR sys_erproc,0
	invoke _disk_exist,disk
	pop dx
	mov WORD PTR sys_erproc,dx
	.if !ax && !(sys_erflag & __ISDEVICE) && errno == 2
	    mov sys_erflag,al
	    mov sys_erdrive,al
	    mov sys_ercode,ax
	.endif
	ret
_disk_ready ENDP

	END
