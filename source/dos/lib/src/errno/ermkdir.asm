; ERMKDIR.ASM--
; Copyright (C) 2015 Doszip Developers

include errno.inc

PUBLIC	cp_mkdir

.data
cp_mkdir  db "Make directory",0
cp_format db "Can't create the directory:",10,"%s",10,10,"%s",0

.code

ermkdir PROC _CType PUBLIC directory:DWORD
	invoke errnomsg,addr cp_mkdir,addr cp_format,directory
	ret
ermkdir ENDP

	END
