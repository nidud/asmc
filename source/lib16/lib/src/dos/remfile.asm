; REMFILE.ASM--
; Copyright (C) 2015 Doszip Developers

include dos.inc

	.code

removefile PROC _CType PUBLIC file:DWORD
	invoke _dos_setfileattr,file,0
	invoke remove,file
	ret
removefile ENDP

	END
