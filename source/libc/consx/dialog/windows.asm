include consx.inc

MAXWINDOWS	equ 20

	.data
	windows	 dd MAXWINDOWS dup(0)
	winflag	 dw MAXWINDOWS dup(0)
	winlevel dd 0

	.code

__dlpush PROC USES eax
	mov eax,winlevel
	cmp eax,MAXWINDOWS
	jnb toend
	inc winlevel
	mov windows[eax*4],edi
  toend:
	ret
__dlpush ENDP

__dlpop PROC USES eax
	sub eax,eax
     @@:
	cmp eax,winlevel
	je  toend
	cmp windows[eax*4],edi
	je  found
	inc eax
	jmp @B
  found:
	mov ecx,windows[eax*4+4]
	mov windows[eax*4],ecx
	inc eax
	cmp eax,winlevel
	jne found
	dec winlevel
  toend:
	ret
__dlpop ENDP

dlhideall PROC USES esi
	mov esi,winlevel
	.while	esi
		dec esi
		mov edx,windows[esi*4]
		mov ax,[edx].S_DOBJ.dl_flag
		mov winflag[esi*2],ax
		and [edx].S_DOBJ.dl_flag,not _D_ONSCR
		rchide( [edx].S_DOBJ.dl_rect, eax, [edx].S_DOBJ.dl_wp )
	.endw
	ret
dlhideall ENDP

dlshowall PROC USES esi ecx edx eax
	xor esi,esi
	.while	esi != winlevel
		mov dx,winflag[esi*2]
		.if dx & _D_ONSCR
			mov eax,windows[esi*4]
			mov [eax].S_DOBJ.dl_flag,dx
			xor dx,_D_ONSCR
			rcshow( [eax].S_DOBJ.dl_rect, edx, [eax].S_DOBJ.dl_wp )
		.endif
		inc esi
	.endw
	ret
dlshowall ENDP

	END
