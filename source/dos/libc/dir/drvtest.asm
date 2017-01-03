; DRVTEST.ASM--
; Copyright (C) 2015 Doszip Developers

include dir.inc
include errno.inc

	.code

_disk_test PROC _CType PUBLIC disk:size_t
	invoke _disk_type,disk
	.if ax != _DISK_NOSUCHDRIVE
	    invoke _disk_ready,disk
	    .if ax
		mov ax,1
	    .elseif errno != ENOENT
		mov ax,-1
	    .else
		.while 1
		    invoke _disk_retry,disk
		    .if ax
			invoke _disk_ready,disk
			.break .if ax
		    .else
			mov ax,-1
			.break
		    .endif
		.endw
	    .endif
	.endif
	ret
_disk_test ENDP

	END
