; ERDELETE.ASM--
; Copyright (C) 2015 Doszip Developers

include errno.inc

.data
cp_error_delete db "Error delete",0
cp_error_format db "Can't delete the file:",10,"%s",10,10,"%s",0

.code

erdelete PROC _CType PUBLIC filename:DWORD	; return -1
	invoke errnomsg,addr cp_error_delete,addr cp_error_format,filename
	ret
erdelete ENDP

	END
