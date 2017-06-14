include stdio.inc

	.code

	OPTION	WIN64:3, STACKBASE:rsp

printf	PROC USES rbx format:LPSTR, argptr:VARARG
	_stbuf( addr stdout )
	mov	rbx,rax
	_output( addr stdout, format, addr argptr )
	xchg	rax,rbx
	_ftbuf( eax, addr stdout )
	ret
printf	ENDP

	END
