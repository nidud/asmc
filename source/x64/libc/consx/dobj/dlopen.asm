include consx.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp
	ASSUME	rbx:PTR S_DOBJ

dlopen	PROC USES rbx dobj:PTR S_DOBJ, at:DWORD, ttl:LPSTR

	mov	rbx,rcx ; dobj
	mov	r9,r8	; title
	mov	r8d,edx ; attrib

	rcopen( [rbx].dl_rect, [rbx].dl_flag, r8d, r9, [rbx].dl_wp )
	mov	[rbx].dl_wp,rax
	.if	eax
		or  [rbx].dl_flag,_D_DOPEN
		mov eax,1
	.endif
	ret
dlopen	ENDP

	END
