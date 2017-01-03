; SETBUF.ASM--
; Copyright (C) 2015 Doszip Developers

include stdio.inc

	.code

setbuf	PROC _CType PUBLIC fp:DWORD, buf:DWORD
	invoke setvbuf,buf,fp,_IOFBF,_MINIOBUF
	ret
setbuf	ENDP

	END
