include strlib.inc

	.code

strnzcpy PROC USES esi edi dst:LPSTR, src:LPSTR, count:SIZE_T
	mov	edi,dst
	mov	esi,src
	mov	ecx,count
	.assert ecx
@@:
	mov	al,[esi]
	mov	[edi],al
	test	al,al
	jz	@F
	inc	edi
	inc	esi
	dec	ecx
	jnz	@B
	mov	[edi],cl
@@:
	mov	eax,dst
	ret
strnzcpy ENDP

	END
