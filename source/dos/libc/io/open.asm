; OPEN.ASM--
; Copyright (C) 2015 Doszip Developers

include io.inc
include share.inc

	.code

open	PROC _CDecl PUBLIC path:DWORD, oflag:size_t, args:VARARG
	invoke sopen,path,oflag,SH_DENYNO,addr args
	ret
open	ENDP

	END
