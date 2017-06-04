include string.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

strlen	PROC string:LPSTR

	mov	eax,[esp+4]
	mov	ecx,[esp+4]
	push	edx
	and	ecx,3
	jz	L2
	sub	eax,ecx
	shl	ecx,3
	mov	edx,-1
	shl	edx,cl
	not	edx
	or	edx,[eax]
	lea	ecx,[edx-01010101h]
	not	edx
	and	ecx,edx
	and	ecx,80808080h
	jnz	L3
L1:
	add	eax,4
L2:
	mov	edx,[eax]
	lea	ecx,[edx-01010101h]
	not	edx
	and	ecx,edx
	and	ecx,80808080h
	jz	L1
L3:
	pop	edx
	bsf	ecx,ecx
	shr	ecx,3
	add	eax,ecx
	sub	eax,[esp+4]
	ret

strlen	endp

	END
