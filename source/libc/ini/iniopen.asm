include io.inc
include alloc.inc
include ini.inc

	.code

iniclose PROC USES eax ecx
	mov	eax,cinifile
	test	eax,eax
	jz	@F
	free( eax )
	xor	eax,eax
	mov	cinifile,eax
@@:
	ret
iniclose ENDP

iniopen PROC USES esi edi ebx edx IniFile:LPSTR
	xor	esi,esi
	osopen( IniFile, _A_NORMAL, M_RDONLY, A_OPEN )
	mov	ebx,eax
	inc	eax
	jz	toend
	_filelength( ebx )
	test	eax,eax
	jz	@F
	mov	edi,eax
	add	eax,INIMAXVALUE+5
	malloc( eax )
	jz	@F
	mov	cinifile,eax
	add	eax,INIMAXVALUE+4
	mov	byte ptr [eax+edi],0
	osread( ebx, eax,  edi )
	mov	esi,cinifile
	mov	[esi+INIMAXVALUE],eax
@@:
	_close( ebx )
toend:
	mov	eax,esi
	ret
iniopen ENDP

	END
