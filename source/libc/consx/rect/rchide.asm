include consx.inc

	.code

rchide	PROC rect, fl, wp:PVOID
	mov eax,fl
	and eax,_D_DOPEN or _D_ONSCR
	.if !ZERO?
		and eax,_D_ONSCR
		.if !ZERO?
			rcxchg( rect, wp )
			jz toend
			.if fl & _D_SHADE
				rcclrshade( rect, wp )
			.endif
		.endif
		xor eax,eax
		inc eax
	.endif
toend:
	ret
rchide	ENDP

	END
