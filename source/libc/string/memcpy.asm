include string.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

memmove PROC dst:LPSTR, src:LPSTR, count:SIZE_T
memmove ENDP

memcpy	proc dst:LPSTR, src:LPSTR, count:SIZE_T
	push	esi
	push	edi
	mov	eax,8[esp+4]	; dst -- return value
	mov	esi,8[esp+8]	; src
	mov	ecx,8[esp+12]	; count

	mov	edi,eax
	cmp	eax,esi
	ja	@F
	rep	movsb
	pop	edi
	pop	esi
	ret
@@:
	lea	esi,[esi+ecx-1]
	lea	edi,[edi+ecx-1]
	std
	rep	movsb
	cld
	pop	edi
	pop	esi
	ret
memcpy	endp

	END
