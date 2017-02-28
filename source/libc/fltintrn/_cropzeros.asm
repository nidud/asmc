include string.inc
include fltintrn.inc

	.code

_cropzeros proc uses ebx buffer:LPSTR

	mov	ebx,buffer
	add	ebx,strlen(ebx)
	mov	eax,'0'
	.while	[ebx-1] == al

		mov [ebx-1],ah
		dec ebx
	.endw

	.if byte ptr [ebx-1] == '.'

		mov [ebx-1],ah
	.endif
	ret

_cropzeros endp

	END
