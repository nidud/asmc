include string.inc
include ctype.inc

	.code

tistripend PROC USES esi string:LPSTR
	mov	esi,string
	mov	ecx,strlen( esi )
	.if	eax
		add	esi,eax
		xor	eax,eax
		.repeat
			dec	esi
			mov	al,[esi]
			mov	al,byte ptr _ctype[eax*2+2]
			.break .if !( al & _SPACE )
			mov	[esi],ah
		.untilcxz
		mov	eax,ecx
		test	eax,eax
	.endif
	ret
tistripend ENDP

	END
