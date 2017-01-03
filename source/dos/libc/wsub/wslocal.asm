; WSLOCAL.ASM--
; Copyright (C) 2015 Doszip Developers

include dir.inc
include wsub.inc

	.code

wslocal PROC _CType PUBLIC USES bx wsub:DWORD
	les bx,wsub
	.if fullpath(es:[bx].S_WSUB.ws_path,0)
	    invoke wssetflag,wsub
	.endif
	ret
wslocal ENDP

	END
