include consx.inc

	.code

rsreload PROC USES ebx robj:PTR S_ROBJ, dobj:PTR S_DOBJ
	mov ebx,dobj
	mov eax,[ebx]
	and eax,_D_DOPEN
	.if !ZERO?
		dlhide( dobj )
		push eax
		movzx eax,[ebx].S_DOBJ.dl_count
		inc eax
		lea eax,[eax*8+2]
		add eax,robj
		mov ecx,eax
		mov al,[ebx].S_DOBJ.dl_rect.rc_col
		mul [ebx].S_DOBJ.dl_rect.rc_row
		.if [ebx].S_DOBJ.dl_flag & _D_RESAT
			or eax,8000h
		.endif
		xchg ecx,eax
		wcunzip( [ebx].S_DOBJ.dl_wp, eax, ecx )
		dlinit( dobj )
		pop eax
		.if eax
			dlshow( dobj )
		.endif
	.endif
	ret
rsreload ENDP

	END
