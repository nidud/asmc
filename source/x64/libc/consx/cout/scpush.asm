include consx.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

scpush	PROC lcount
	mov	ch,80
	shl	ecx,16
	rcopen( ecx, 0, 0, 0, 0 )
	ret
scpush	ENDP

scpop	PROC wp:PVOID, lc
	mov	r8,rcx
	mov	ecx,edx
	mov	ch,80
	shl	ecx,16
	rcclose( ecx, _D_DOPEN or _D_ONSCR, r8 )
	ret
scpop	ENDP

	END
