include errno.inc
include consx.inc

	.code

errnomsg proc etitle:LPSTR, format:LPSTR, file:LPSTR
	mov	eax,errno
	ermsg ( etitle, format, file, sys_errlist[eax*4] )
	mov	eax,-1
	ret
errnomsg endp

	END
