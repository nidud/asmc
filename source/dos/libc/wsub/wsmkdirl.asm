; WSMKDIRL.ASM--
; Copyright (C) 2015 Doszip Developers

include wsub.inc
include dir.inc
include errno.inc

	.code

wsmkdirlocal PROC _CType PUBLIC path:PTR BYTE
	.if mkdir(path)
	    invoke ermkdir,path
	.else
	    inc ax
	.endif
	ret
wsmkdirlocal ENDP

	END
