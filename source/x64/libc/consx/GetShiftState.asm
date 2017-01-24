include consx.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

GetShiftState PROC
	mov	rax,keyshift
	mov	eax,[rax]
	and	eax,SHIFT_KEYSPRESSED or SHIFT_LEFT or SHIFT_RIGHT
	ret
GetShiftState ENDP

	END
