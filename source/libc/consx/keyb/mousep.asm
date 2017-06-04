include consx.inc

	.code

mousep	PROC USES ecx edx

	ReadEvevnt()
	mov eax,edx
	shr eax,16
	and eax,3
	ret

mousep	ENDP

	END
