include stdlib.inc
include string.inc
include malloc.inc
include winbase.inc

	.code

__setenvp PROC USES rsi rdi rbx envp:LPSTR

	mov rdi,GetEnvironmentStringsA()
	mov rsi,rax			; save start of block in ESI
	xor rax,rax
	xor rbx,rbx
	mov rcx,-1
	.while	BYTE PTR [rdi]		; size up the environment
	    .if BYTE PTR [rdi] != '='
		mov  rdx,rdi		; save offset of string
		sub  rdx,rsi
		push rdx
		inc  rbx		; increase count
	    .endif
	    repnz scasb			; next string..
	.endw
	inc rbx				; count strings plus NULL
	sub rdi,rsi			; EDI to size
	lea rax,[rdi+rbx*8]		; pointers plus size of environment
	malloc(rax)
	mov rcx,envp			; return result
	mov [rcx],rax
	.if rax
	    lea rax,[rax+rbx*8]		; new adderss of block
	    memcpy(rax, rsi, rdi)
	    xchg rax,rsi		; ESI to block
	    FreeEnvironmentStringsA(rax)
	    lea rdi,[rsi-8]		; EDI to end of pointers array
	    std				; move backwards
	    xor rax,rax			; set last pointer to NULL
	    stosq
	    dec rbx
	    .while rbx
		pop rax			; pop offset in reverse
		add rax,rsi		; add address of block
		stosq
		dec rbx
	    .endw
	    cld
	    inc rbx			; remove ZERO flag
	    mov rax,envp		; return address of new _environ
	    mov rax,[rax]
	.endif
	ret
__setenvp ENDP

	END
