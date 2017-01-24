include consx.inc

	.code

	OPTION	WIN64:0, STACKBASE:rsp

wcputxg PROC
	inc	rbx
	.repeat
		and	[rbx],ah
		or	[rbx],al
		add	rbx,2
	.untilcxz
	ret
wcputxg ENDP

	END
