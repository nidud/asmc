include consx.inc
include string.inc

	.code

wcpath	PROC USES esi edi b:PVOID, l:DWORD, p:PVOID
	__wcpath( b, l, p )
	.if	ecx
		mov	esi,edx
		mov	edi,eax
		.repeat
			movsb
			inc edi
		.untilcxz
	.endif
	ret
wcpath	ENDP

	END
