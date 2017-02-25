include errno.inc
include consx.inc
include wsub.inc
include winbase.inc

	.data
	cp_erinitsub db 'Error init directory',10,'%s',0

	.code

wsinit	PROC USES esi edi wsub:PTR S_WSUB
	mov	edi,wsub
	mov	esi,[edi].S_WSUB.ws_path
	.if	byte ptr [esi] == 0
		GetCurrentDirectory( WMAXPATH, esi )
	.endif
	.if	SetCurrentDirectory( esi )
		.if	GetCurrentDirectory( WMAXPATH, esi )
			movzx	eax,word ptr [esi]
			.if	ah == ':'
				.if	al <= 'z' && al >= 'a'
					sub al,'a' - 'A'
				.endif
				shl	eax,8
				mov	al,'='
				push	eax
				mov	eax,esp
				SetEnvironmentVariable( eax, esi )
				pop	eax
			.endif
		.endif
	.endif
	.if	!wssetflag( edi )
		ermsg( 0, addr cp_erinitsub, [edi].S_WSUB.ws_path )
		wslocal( edi )
	.elseif eax != 1 && eax != 3
		wslocal( edi )
	.endif
	ret
wsinit	ENDP

	END
