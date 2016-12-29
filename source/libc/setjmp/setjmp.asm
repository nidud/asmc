include setjmp.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

	ASSUME	eax: PTR S_JMPBUF

setjmp	PROC C JMPBUF:PTR S_JMPBUF
	mov	eax,[esp+4]
	mov	[eax].J_EBP,ebp
	mov	[eax].J_EBX,ebx
	mov	[eax].J_EDI,edi
	mov	[eax].J_ESI,esi
	mov	[eax].J_ESP,esp
	mov	[eax].J_EDX,edx
	mov	[eax].J_ECX,ecx
	mov	ecx,[esp]
	mov	[eax].J_EIP,ecx
	mov	ecx,[eax].J_ECX
	xor	eax,eax
	ret
setjmp	ENDP

	ASSUME	edx: PTR S_JMPBUF

longjmp PROC C JMPBUF:PTR S_JMPBUF, retval:DWORD
	mov	edx,[esp+4]
	mov	eax,[esp+8]
	mov	ecx,[edx].J_ECX
	mov	ebp,[edx].J_EBP
	mov	ebx,[edx].J_EBX
	mov	edi,[edx].J_EDI
	mov	esi,[edx].J_ESI
	mov	esp,[edx].J_ESP
	push	[edx].J_EIP
	mov	edx,[edx].J_EDX
	ret	4
longjmp ENDP

	END
