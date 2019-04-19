include libc.inc
include asmc.inc

	.code

	ASSUME	ecx:PTR asmtok
B	equ <SBYTE PTR>

DelayExpand PROC FASTCALL tokenarray

	xor	eax,eax
	test	[tokenarray].hll_flags,T_HLL_DELAY
	jz	toend
	cmp	ModuleInfo.strict_masm_compat,1
	je	toend
	cmp	Parse_Pass,PASS_1
	jne	toend
	cmp	eax,NoLineStore
	jne	toend

	push	ebx
	xor	edx,edx

find_macro:
	cmp	eax,ModuleInfo.token_count
	jge	delayed
	test	[tokenarray][edx].hll_flags,T_HLL_MACRO
	lea	edx,[edx+16]
	lea	eax,[eax+1]
	jz	find_macro
	cmp	[tokenarray][edx].token,T_OP_BRACKET
	jne	find_macro

	mov	ebx,1	; one open bracket found

macro_loop:

	lea	edx,[edx+16]
	lea	eax,[eax+1]
	cmp	eax,ModuleInfo.token_count
	jge	delayed

	.switch [tokenarray][edx].token
	  .case T_OP_BRACKET
		add	ebx,1
		jmp	macro_loop
	  .case T_CL_BRACKET
		sub	ebx,1
		jz	find_macro
		jmp	macro_loop
	  .case T_STRING
		mov eax,[tokenarray][edx].string_ptr
		.if B[eax] != '<'
			mov eax,[tokenarray][edx].tokpos
			.if B[eax] == '<'
				asmerr( 7008, eax )
				jmp nodelay
			.endif
		.endif
		mov	eax,edx
		shr	eax,4
		jmp	macro_loop
	.endsw
	jmp	macro_loop

delayed:
	pop	ebx
	or	[tokenarray].hll_flags,T_HLL_DELAYED
	mov	eax,1
	ret
nodelay:
	pop	ebx
	xor	eax,eax
toend:
	ret
DelayExpand ENDP

	END
