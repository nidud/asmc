; REMTEMP.ASM--
; Copyright (C) 2015 Doszip Developers

include dos.inc
include dir.inc
include string.inc

extrn	envtemp:DWORD

	.code

removetemp PROC _CType PUBLIC path:DWORD
local nbuf[WMAXPATH]:BYTE
	invoke strfcat,addr nbuf,envtemp,path
	invoke removefile,dx::ax
	ret
removetemp ENDP

	END
