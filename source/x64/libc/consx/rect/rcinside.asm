include consx.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

rcinside PROC rc1, rc2
	xor	eax,eax
	mov	r8w,cx
	mov	r9w,dx
	shr	ecx,16
	shr	edx,16
	.if	dh > ch || dl > cl
		mov eax,5
	.else
		add	cx,r8w
		add	dx,r9w
		.if	ch < dh
			inc eax
		.elseif cl < dl
			mov eax,4
		.else
			mov	cx,r8w
			mov	dx,r9w
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
