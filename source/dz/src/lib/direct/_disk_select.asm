include direct.inc
include consx.inc
include errno.inc
include dzlib.inc

	.data
	push_button db "&A",0

	.code

_disk_select PROC USES esi edi ebx msg:LPSTR
local	dobj:S_DOBJ
local	tobj[MAXDRIVES]:S_TOBJ
	call	_getdrive
	mov	ebx,eax
	call	_disk_read
	mov	DWORD PTR dobj.dl_flag,_D_STDDLG
	mov	dobj.dl_rect,003F0908h
	lea	edi,tobj
	mov	dobj.dl_object,edi
	mov	esi,1
loop_drv:
	_disk_exist( esi )
	test	eax,eax
	jz	next_drv
	movzx	eax,dobj.dl_count
	inc	dobj.dl_count
	mov	[edi].S_TOBJ.to_flag,_O_PBKEY
	mov	ecx,eax
	cmp	esi,ebx
	jne	@F
	mov	al,dobj.dl_count
	dec	al
	mov	dobj.dl_index,al
@@:
	mov	eax,esi
	add	al,'@'
	mov	[edi].S_TOBJ.to_ascii,al
	mov	eax,01050000h
	mov	al,cl
	shr	al,3
	shl	al,1
	add	al,2
	mov	ah,al
	and	cl,7
	mov	al,cl
	shl	al,3
	sub	al,cl
	add	al,4
	mov	[edi].S_TOBJ.to_rect,eax
	add	edi,16
next_drv:
	inc	esi
	cmp	esi,MAXDRIVES
	jna	loop_drv
	movzx	eax,dobj.dl_count
	dec	eax
	mov	ebx,eax
	shr	eax,3
	shl	eax,1
	add	al,5
	mov	dobj.dl_rect.rc_row,al
	mov	eax,ebx
	cmp	eax,7
	ja	@F
	shl	eax,3
	sub	eax,ebx
	add	eax,14
	mov	dobj.dl_rect.rc_col,al
	mov	cl,BYTE PTR _scrcol
	sub	cl,al
	shr	cl,1
	mov	dobj.dl_rect.rc_x,cl
@@:
	xor	edi,edi
	mov	bl,at_foreground[F_Dialog]
	or	bl,at_background[B_Dialog]
	dlopen( addr dobj, ebx, msg )
	jz	done
	lea	esi,tobj
	mov	bl,[esi].S_TOBJ.to_rect.rc_col
@@:
	movzx	eax,dobj.dl_count
	cmp	edi,eax
	jae	@F
	mov	al,[esi].S_TOBJ.to_ascii
	mov	push_button[1],al
	mov	al,dobj.dl_rect.rc_col
	rcbprc( [esi].S_TOBJ.to_rect, dobj.dl_wp, eax )
	movzx	ecx,dobj.dl_rect.rc_col
	wcpbutt( eax, ecx, ebx, addr push_button )
	inc	edi
	add	esi,sizeof(S_TOBJ)
	jmp	@B
@@:
	dlmodal( addr dobj )
	mov	edi,eax
done:
	xor	eax,eax
	test	edi,edi
	jz	toend
	or	al,dobj.dl_index
	shl	eax,4
	add	eax,dobj.dl_object
	movzx	eax,[eax].S_TOBJ.to_ascii
	sub	al,'@'
toend:
	ret
_disk_select ENDP

	END
