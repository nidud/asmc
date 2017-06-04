include consx.inc

	.code

wcputxg PROC USES ecx
	inc ebx
	.repeat
		and [ebx],ah
		or  [ebx],al
		add ebx,2
	.untilcxz
	ret
wcputxg ENDP

	END
