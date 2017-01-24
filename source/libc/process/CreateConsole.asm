include stdlib.inc
include process.inc
include string.inc
include direct.inc
include consx.inc
include cfini.inc

externdef	cp_quote:byte

	.code

CreateConsole PROC USES esi edi string:LPSTR, flag

  local cmd[1024]:byte

	mov	esi,console
	and	esi,CON_NTCMD
	CFGetComspec( esi )
	mov	ecx,eax

	lea	edi,cmd
	strcat( strcpy( edi, ecx ), " " )
	mov	ecx,__pCommandArg
	.if	ecx
		strcat( strcat( edi, ecx ), " " )
	.endif
	.if	esi
		strcat( edi, addr cp_quote )
	.endif
	strlen( edi )
	lea	edx,[edi+eax]
	strcat( edi, string )
	.if	strchr( edi, 10 )
		CreateBatch( edx, 0, 0 )
	.endif
	.if	esi
		strcat( edi, addr cp_quote )
	.endif
	mov	eax,flag
	.if	eax == _P_NOWAIT
		or eax,DETACHED_PROCESS
	.endif
	process( 0, edi, eax )
	SetKeyState()
	ret

CreateConsole ENDP

	END
