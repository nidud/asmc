include stdio.inc

	.code

	OPTION	WIN64:3, STACKBASE:rsp

vfprintf PROC USES rsi file:LPFILE, format:LPSTR, args:PVOID
	_stbuf( rcx )
	mov	rsi,rax
	_output( file, format, args )
	mov	rcx,rsi
	mov	rsi,rax
	_ftbuf( ecx, file )
	mov	rax,rsi
	ret
vfprintf ENDP

	END
