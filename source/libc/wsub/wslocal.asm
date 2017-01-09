include direct.inc
include wsub.inc

	.code

wslocal PROC wsub:PTR S_WSUB
	mov	eax,wsub
	.if	_getcwd( [eax].S_WSUB.ws_path, WMAXPATH )
		wssetflag( wsub )
	.endif
	ret
wslocal ENDP

	END
