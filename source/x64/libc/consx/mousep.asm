include consx.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

mousep	PROC USES rcx rdx
	call	ReadEvevnt
	mov	eax,edx
	shr	eax,16
	and	eax,3
	ret
mousep	ENDP

	END
