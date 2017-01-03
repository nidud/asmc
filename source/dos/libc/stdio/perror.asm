; PERROR.ASM--
; Copyright (C) 2015 Doszip Developers

include stdio.inc
include io.inc
include errno.inc
include string.inc

	.code

perror PROC _CType PUBLIC USES di string:DWORD
	lodm string
	.if ax
	    les di,string
	    mov al,es:[di]
	    .if al
		invoke strlen,string
		invoke write,2,string,ax
		write( 2,": ",2)
		mov    di,errno
		shl    di,2
		add    di,offset sys_errlist
		lodm   [di]
		push   ax
		invoke strlen,dx::ax
		mov    cx,ax
		pop    ax
		invoke write,2,dx::ax,cx
		write(2,"\n",1)
	    .endif
	.endif
	ret
perror ENDP

	END
