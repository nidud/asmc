include consx.inc

	.code

scpush	PROC lcount
	mov	eax,lcount
	mov	ah,80
	shl	eax,16
	rcopen( eax, 0, 0, 0, 0 )
	ret
scpush	ENDP

scpop	PROC wp, lc
	mov	eax,lc
	mov	ah,80
	shl	eax,16
	rcclose( eax, _D_DOPEN or _D_ONSCR, wp )
	ret
scpop	ENDP

	END
