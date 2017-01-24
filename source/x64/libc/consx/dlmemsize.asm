include consx.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

dlmemsize PROC USES rbx dobj:PTR S_DOBJ
	mov	rbx,rcx
	movzx	ecx,[rbx].S_DOBJ.dl_count
	mov	rdx,[rbx].S_DOBJ.dl_object
	xor	eax,eax
	.while	ecx
		add	al,[rdx].S_TOBJ.to_count
		add	rdx,sizeof(S_TOBJ)
		dec	ecx
	.endw
	inc	ecx
	add	cl,[rbx].S_DOBJ.dl_count
	add	eax,ecx
	shl	eax,4
	mov	r8,rbx
	mov	rbx,rax
	rcmemsize([r8].S_DOBJ.dl_rect, [r8].S_DOBJ.dl_flag )
	add	eax,ebx
	ret
dlmemsize ENDP

	END
