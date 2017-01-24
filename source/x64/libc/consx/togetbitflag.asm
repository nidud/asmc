include consx.inc

	.code

	OPTION	WIN64:0, STACKBASE:rsp

togetbitflag PROC tobj:PTR S_TOBJ, count, flag
	mov	r9d,edx;count
	dec	r9
	imul	r9,r9,sizeof(S_TOBJ)
	add	rcx,r9;tobj
	xor	eax,eax
	.while	edx
		.if	r8w & [rcx]
			or al,1
		.endif
		shl	eax,1
		sub	rcx,SIZE S_TOBJ
		dec	edx
	.endw
	shr	eax,1
	ret
togetbitflag ENDP

	END
