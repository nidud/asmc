include consx.inc

	.code

wcputw	PROC USES eax ecx edi b:PVOID, l, w
	mov eax,w
	mov ecx,l
	mov edi,b
	.if ah
		rep stosw
	.else
		.repeat
			stosb
			inc edi
		.untilcxz
	.endif
	ret
wcputw	ENDP

	END
