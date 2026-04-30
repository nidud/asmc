
	.code

	repeat	10
	push	rbp
	mov	rbp,rsp
	mov	rsp,rbp
	pop	rbp
	endm
	ret

	END
