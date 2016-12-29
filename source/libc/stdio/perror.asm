include stdio.inc
include io.inc
include errno.inc
include string.inc

	.code

perror	PROC USES edi string:LPSTR
	mov	eax,string
	.if	eax
		mov	edi,eax
		mov	al,[edi]
		.if	al
			_write( 2, string, strlen( string ) )
			_write( 2, ": ", 2 )
			mov    edi,errno
			shl    edi,2
			add    edi,offset sys_errlist
			mov    eax,[edi]
			push   eax
			strlen( eax )
			mov    ecx,eax
			pop    eax
			_write( 2, eax, ecx )
			_write( 2, "\n", 1 )
		.endif
	.endif
	ret
perror	ENDP

	END
