include io.inc
include winbase.inc

	.code

	option win64:rsp nosave

rename	PROC Oldname:LPSTR, Newname:LPSTR
	.if MoveFile(rcx, rdx)
	    xor rax,rax
	.else
	    osmaperr()
	.endif
	ret
rename	ENDP

	END
