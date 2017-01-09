include crtl.inc

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

	.code

memxchg PROC dst:LPSTR, src:LPSTR, count:SIZE_T

	push	esi
	push	edi
	push	edx

	mov	edi,12[esp+4]
	mov	esi,12[esp+8]
	mov	ecx,12[esp+12]
tail:
	test	ecx,ecx
	jz	toend
	test	ecx,3
	jz	tail_4

	sub	ecx,1
	mov	al,[esi+ecx]
	mov	dl,[edi+ecx]
	mov	[esi+ecx],dl
	mov	[edi+ecx],al
	jmp	tail

	ALIGN	4
tail_4:
	sub	ecx,4
	mov	eax,[esi+ecx]
	mov	edx,[edi+ecx]
	mov	[esi+ecx],edx
	mov	[edi+ecx],eax
	jnz	tail_4
toend:
	mov	eax,edi
	pop	edx
	pop	edi
	pop	esi
	ret	12

memxchg ENDP

	END
