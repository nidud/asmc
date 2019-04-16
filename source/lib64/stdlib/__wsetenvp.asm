; __WSETENVP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include string.inc
include malloc.inc
include winbase.inc

	.code

__wsetenvp PROC USES rsi rdi rbx envp:LPWSTR

	.for ( rdi = GetEnvironmentStringsW(),
	       rsi = rax, rax = 0, rbx = 0,
	       rcx = -1 : word ptr [rdi] : )

	    .if ( word ptr [rdi] != '=' )

		mov  rdx,rdi
		sub  rdx,rsi
		push rdx
		inc  rbx
	    .endif
	    repnz scasw
	.endf
	inc rbx

	sub rdi,rsi
	lea rax,[rdi+rbx*8]
	malloc(rax)
	mov rcx,envp
	mov [rcx],rax

	.if rax

	    memcpy(&[rax+rbx*8], rsi, rdi)
	    xchg rax,rsi
	    FreeEnvironmentStringsW(rax)
	    lea rdi,[rsi-8]
	    std
	    xor rax,rax
	    stosq
	    dec rbx
	    .while rbx
		pop rax
		add rax,rsi
		stosq
		dec rbx
	    .endw
	    cld
	    inc rbx
	    mov rax,envp
	    mov rax,[rax]
	.endif
	ret

__wsetenvp ENDP

	END
