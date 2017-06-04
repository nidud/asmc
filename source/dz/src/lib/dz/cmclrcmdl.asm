; CMCLRCMDL.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc

	.code

cmclrcmdl PROC
	.if	cflag & _C_ESCUSERSCR
		call cmtoggleon
	.endif
	call	clrcmdl
	ret
cmclrcmdl ENDP

	END
