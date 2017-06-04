include string.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

strcpy	PROC dst:LPSTR, src:LPSTR
	push	edi
	push	edx
	mov	ecx,8[esp+8]
	mov	edi,8[esp+4]
	jmp	start
dword_loop:
	mov	[edi],eax
	add	edi,4
start:
	mov	eax,[ecx]
	add	ecx,4
	lea	edx,[eax-01010101h]
	not	eax
	and	edx,eax
	not	eax
	and	edx,80808080h
	jz	dword_loop
	mov	[edi],al
	test	al,al
	jz	toend
	mov	[edi+1],ah
	test	ah,ah
	jz	toend
	shr	eax,16
	mov	[edi+2],al
	test	al,al
	jz	toend
	mov	[edi+3],ah
toend:
	pop	edx
	pop	edi
	mov	eax,[esp+4]
	ret
strcpy	ENDP

	END
