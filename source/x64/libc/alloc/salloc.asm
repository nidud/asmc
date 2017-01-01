include alloc.inc
include string.inc

	.code

	OPTION WIN64:2, STACKBASE:rsp

salloc	PROC USES rbx string:LPSTR
	mov	rbx,rcx

	.if	strlen( rcx )

		inc	rax
		.if	malloc(rax)

			strcpy( rax, rbx )
			test	rax,rax
		.endif
	.endif

	ret

salloc	ENDP

	END
