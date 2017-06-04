include string.inc
ifdef _SSE
include crtl.inc

	.data
	strlen_p dd _rtl_strlen
endif
	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

ifdef _SSE
strlen_386:
else
strlen	PROC string:LPSTR
endif

if 0
	mov	ecx,[esp+4]
	xor	eax,eax
@@:
	cmp	[ecx],al
	jz	exit_0
	cmp	[ecx+1],al
	jz	exit_1
	cmp	[ecx+2],al
	jz	exit_2
	cmp	[ecx+3],al
	jz	exit_3
	cmp	[ecx+4],al
	jz	exit_4
	cmp	[ecx+5],al
	jz	exit_5
	cmp	[ecx+6],al
	jz	exit_6
	cmp	[ecx+7],al
	jz	exit_7

	cmp	[ecx+8],al
	jz	exit_8
	cmp	[ecx+9],al
	jz	exit_9
	cmp	[ecx+10],al
	jz	exit_10
	cmp	[ecx+11],al
	jz	exit_11
	cmp	[ecx+12],al
	jz	exit_12
	cmp	[ecx+13],al
	jz	exit_13
	cmp	[ecx+14],al
	jz	exit_14
	cmp	[ecx+15],al
	jz	exit_15
	add	ecx,16
	jmp	@B

exit_15:
	lea	eax,[ecx+15]
	sub	eax,[esp+4]
	ret	4
exit_14:
	lea	eax,[ecx+14]
	sub	eax,[esp+4]
	ret	4
exit_13:
	lea	eax,[ecx+13]
	sub	eax,[esp+4]
	ret	4
exit_12:
	lea	eax,[ecx+12]
	sub	eax,[esp+4]
	ret	4
exit_11:
	lea	eax,[ecx+11]
	sub	eax,[esp+4]
	ret	4
exit_10:
	lea	eax,[ecx+10]
	sub	eax,[esp+4]
	ret	4
exit_9:
	lea	eax,[ecx+9]
	sub	eax,[esp+4]
	ret	4
exit_8:
	lea	eax,[ecx+8]
	sub	eax,[esp+4]
	ret	4
exit_7:
	lea	eax,[ecx+7]
	sub	eax,[esp+4]
	ret	4
exit_6:
	lea	eax,[ecx+6]
	sub	eax,[esp+4]
	ret	4
exit_5:
	lea	eax,[ecx+5]
	sub	eax,[esp+4]
	ret	4
exit_4:
	lea	eax,[ecx+4]
	sub	eax,[esp+4]
	ret	4
exit_3:
	lea	eax,[ecx+3]
	sub	eax,[esp+4]
	ret	4
exit_2:
	lea	eax,[ecx+2]
	sub	eax,[esp+4]
	ret	4
exit_1:
	lea	eax,[ecx+1]
	sub	eax,[esp+4]
	ret	4
exit_0:
	sub	ecx,[esp+4]
	add	eax,ecx
	ret	4
else
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
	ret	4
endif

ifdef _SSE
strlen	PROC string:LPSTR
	jmp	strlen_p
strlen	ENDP
	;
	; First call: set pointer and jump
	;
_rtl_strlen:
	mov	eax,strlen_386
	.if	sselevel & SSE_SSE2
		mov eax,strlen_sse
	.endif
	mov	strlen_p,eax
	jmp	eax
else
strlen	ENDP
endif
	END
