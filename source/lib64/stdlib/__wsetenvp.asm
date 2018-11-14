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

	mov rdi,GetEnvironmentStringsW()
	mov rsi,rax			; save start of block in ESI
	xor rax,rax
	xor rbx,rbx
	mov rcx,-1
	.while	WORD PTR [rdi]		; size up the environment
	    .if WORD PTR [rdi] != '='
		mov  rdx,rdi		; save offset of string
		sub  rdx,rsi
		push rdx
		inc  rbx		; increase count
	    .endif
	    repnz scasw			; next string..
	.endw
	inc rbx				; count strings plus NULL
	sub rdi,rsi			; EDI to size
	lea rax,[rdi+rbx*8]		; pointers plus size of environment
	malloc(rax)
	mov rcx,envp			; return result
	mov [rcx],rax
	.if rax
	    lea rax,[rax+rbx*8]		; new adderss of block
	    memcpy(rax,rsi,rdi)
	    xchg rax,rsi		; ESI to block
	    FreeEnvironmentStringsW(rax)
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

__wsetenvp ENDP

	END
