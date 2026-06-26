	.386
	.model flat, stdcall
	.code

	OPTION	CSTACK: ON

cstack	PROC USES esi edi ebx arg
	sub	esp,arg
	ret
cstack	ENDP

	OPTION	CSTACK: OFF

astack	PROC USES esi edi ebx arg
	sub	esp,arg
	ret
astack	ENDP

	END
