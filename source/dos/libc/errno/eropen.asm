; EROPEN.ASM--
; Copyright (C) 2015 Doszip Developers

include errno.inc

	.data

cp_error_open	db "Error open file",0
cp_error_format db "Can't open the file:",10,"%s",10,10,"%s",0

	.code

eropen	PROC _CType PUBLIC filename:DWORD
	invoke errnomsg,addr cp_error_open,addr cp_error_format,filename
	ret
eropen	ENDP

	END
