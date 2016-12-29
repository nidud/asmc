include consx.inc

	.code

rsmodal PROC robj:PTR S_ROBJ
	rsopen( robj )
	jz	@F
	push	eax
	rsevent( robj, eax )
	call	dlclose
	mov	eax,edx
	test	eax,eax
@@:
	ret
rsmodal ENDP

	END
