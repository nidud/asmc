include string.inc

	.code

	option stackbase:esp

memmove PROC dst:LPSTR, src:LPSTR, count:SIZE_T
memmove ENDP

memcpy	proc uses esi edi dst:LPSTR, src:LPSTR, count:SIZE_T

	mov	eax,dst ; -- return value
	mov	esi,src
	mov	ecx,count

	mov	edi,eax
	cmp	eax,esi
	ja	@F
	rep	movsb
	ret
@@:
	lea	esi,[esi+ecx-1]
	lea	edi,[edi+ecx-1]
	std
	rep	movsb
	cld
	ret

memcpy	endp

	END
