; ISCNTRL.ASM--
; Copyright (C) 2015 Doszip Developers

include libc.inc
include ctype.inc

	.code

iscntrl PROC PUBLIC USES ax
	call getctype
	test ah,_CONTROL
	ret
iscntrl ENDP

	END

