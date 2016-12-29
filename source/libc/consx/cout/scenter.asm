include consx.inc
include string.inc

	.code

scenter PROC USES esi ecx x, y, l, s:LPSTR
	mov	esi,s
	.if	strlen( esi ) > l
		add	esi,eax
		sub	esi,l
	.else
		mov	ecx,eax
		mov	eax,l
		sub	eax,ecx
		shr	eax,1
		add	x,eax
		sub	l,eax
	.endif
	scputs( x, y, 0, l, esi )
	ret
scenter ENDP

	END
