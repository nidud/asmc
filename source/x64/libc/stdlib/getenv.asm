include stdlib.inc
include string.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

getenv	PROC USES rsi rdi rbx rcx enval:LPSTR

	mov	rbx,rcx
	.if	strlen( rcx )

		mov	rdi,rax
		mov	rsi,_environ

		lodsq
		.while	rax
			.if	!_strnicmp( rax, rbx, rdi )

				mov	rax,[rsi-8]
				add	rax,rdi

				.if	byte ptr [rax] == '='

					inc	rax
					.break
				.endif

			.endif
			lodsq
		.endw
	.endif
	ret

getenv	ENDP

	END
