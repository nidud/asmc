include consx.inc

	.code

dlscreen PROC dobj:PTR S_DOBJ, attrib
	mov	edx,dobj
	xor	eax,eax
	mov	[edx],eax
	mov	eax,_scrcol	; adapt to current screen
	mov	ah,BYTE PTR _scrrow
	inc	ah
	shl	eax,16
	mov	[edx].S_DOBJ.dl_rect,eax
	rcopen( eax, _D_CLEAR or _D_BACKG, attrib, 0, 0 )
	.if	!ZERO?
		mov edx,dobj
		mov [edx].S_DOBJ.dl_wp,eax
		mov [edx].S_DOBJ.dl_flag,_D_DOPEN
		mov eax,edx
	.endif
	ret
dlscreen ENDP

	END
