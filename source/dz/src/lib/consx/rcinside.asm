include consx.inc

	.code

rcinside PROC rc1, rc2
	xor	eax,eax
	mov	cx,WORD PTR rc1+2
	mov	dx,WORD PTR rc2+2
	.if	dh > ch || dl > cl
		mov eax,5
	.else
		add	cx,WORD PTR rc1
		add	dx,WORD PTR rc2
		.if	ch < dh
			inc eax
		.elseif cl < dl
			mov eax,4
		.else
			mov	cx,WORD PTR rc1
			mov	dx,WORD PTR rc2
			.if	ch > dh
				mov eax,2
			.elseif cl > dl
				mov eax,3
			.endif
		.endif
	.endif
	ret
rcinside ENDP

	END
