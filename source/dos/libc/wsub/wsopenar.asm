; WSOPENAR.ASM--
; Copyright (C) 2015 Doszip Developers

include io.inc
include dir.inc
include dos.inc
include string.inc
include errno.inc
include wsub.inc

	.code

wsopenarch PROC _CType PUBLIC USES bx wsub:DWORD
local	arcname[WMAXPATH]:BYTE
	les bx,wsub
	invoke strfcat,addr arcname,es:[bx].S_WSUB.ws_path,es:[bx].S_WSUB.ws_file
	.if osopen(dx::ax,_A_ARCH,M_RDONLY,A_OPEN) == -1
	    invoke eropen,addr arcname
	.endif
	ret
wsopenarch ENDP

	END
