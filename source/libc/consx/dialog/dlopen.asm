include consx.inc

	.code
	ASSUME ebx: PTR S_DOBJ

dlopen	PROC USES ebx dobj:PTR S_DOBJ, at, ttl:LPSTR
	mov ebx,dobj
	rcopen( [ebx].dl_rect, [ebx].dl_flag, at, ttl, [ebx].dl_wp )
	mov [ebx].dl_wp,eax
	.if eax
		or  [ebx].dl_flag,_D_DOPEN
		mov eax,1
	.endif
	ret
dlopen	ENDP

	END
