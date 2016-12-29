include consx.inc

	.code

GetShiftState PROC

	mov eax,keyshift
	mov eax,[eax]
	and eax,SHIFT_KEYSPRESSED or SHIFT_LEFT or SHIFT_RIGHT
	ret

GetShiftState ENDP

	END
