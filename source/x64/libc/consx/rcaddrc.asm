include consx.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

rcaddrc PROC result:PVOID, r1, r2
	add	r8w,dx
	mov	[rcx],r8d
	ret
rcaddrc ENDP

	END