include consx.inc

	.code

wcmemset PROC USES edi string:PVOID, val, count
	mov ecx,count
	mov edi,string
	mov eax,val
	rep stosw
	ret
wcmemset ENDP

	END
