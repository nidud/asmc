include consx.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

getxya	PROC x, y
local	lpAttribute:QWORD,
	lpNumberOfAttributesRead:QWORD
	movzx	eax,dl
	shl	eax,16
	mov	al,cl
	lea	rdx,lpAttribute
	lea	r10,lpNumberOfAttributesRead
	ReadConsoleOutputAttribute( hStdOutput, rdx, 1, eax, r10 )
	mov	rax,lpAttribute
	and	rax,00FFh
	ret
getxya	ENDP

	END
