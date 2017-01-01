include signal.inc

	.data
	sig_table dq NSIG dup(0)

	.code

	option	win64:0
	option	stackbase:rsp

signal	PROC index:DWORD, func:PVOID
	lea	r8,sig_table
	mov	rax,[r8+rcx*8]
	mov	[r8+rcx*8],rdx
	ret
signal	ENDP

	option	win64:2

raise	PROC index:DWORD
	lea	r8,sig_table
	mov	rax,[r8+rcx*8]
	.if	rax
		call rax
	.endif
	ret
raise	ENDP

	END
