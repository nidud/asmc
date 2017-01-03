; DRVSELEC.ASM--
; Copyright (C) 2015 Doszip Developers

include dir.inc
include conio.inc
include errno.inc

	.data
	PButton db '&A',0
	.code

_disk_select PROC _CType PUBLIC USES si di bx msg:DWORD
local	disk:size_t
local	dobj:S_DOBJ
local	tobj[MAXDRIVES]:S_TOBJ
	sub	ax,ax
	mov	disk,ax
	mov	ax,sys_ercode
	or	al,sys_erflag
	or	al,sys_erdrive
	jnz	@F
	call	getdrv
	mov	disk,ax
      @@:
	xor	ax,ax
	mov	si,ax
	mov	dobj.dl_index,al
	mov	dobj.dl_count,al
	lea	di,tobj
	mov	WORD PTR dobj.dl_object,di
	mov	WORD PTR dobj.dl_object+2,ss
    _disk_loop:
	invoke	_disk_type,si
	jz	_disk_next
	sub	ax,ax
	mov	al,dobj.dl_count
	inc	dobj.dl_count
	mov	[di].S_TOBJ.to_flag,_O_PBKEY
	mov	bx,ax
	cmp	si,disk
	jne	@F
	mov	al,dobj.dl_count
	dec	al
	mov	dobj.dl_index,al
      @@:
	mov	ax,si
	add	al,'A'
	mov	[di+3],al
	mov	WORD PTR [di+8],offset PButton
	mov	[di+10],ds
	mov	BYTE PTR [di+6],5
	mov	BYTE PTR [di+7],1
	mov	ax,bx
	and	ax,7
	mov	dl,al
	shl	al,3
	sub	al,dl
	add	al,4
	mov	[di+4],al
	mov	ax,bx
	shr	ax,3
	shl	ax,1
	add	ax,2
	mov	[di+5],al
	add	di,16
    _disk_next:
	inc	si
	cmp	si,MAXDRIVES
	jb	_disk_loop
	mov	dobj.dl_flag,_D_STDDLG
	mov	dobj.dl_rect.rc_x,8
	mov	dobj.dl_rect.rc_y,9
	mov	dobj.dl_rect.rc_col,63
	sub	ax,ax
	mov	al,dobj.dl_count
	dec	ax
	mov	bx,ax
	shr	ax,3
	shl	ax,1
	add	al,5
	mov	dobj.dl_rect.rc_row,al
	mov	ax,bx
	cmp	ax,7
	ja	@F
	shl	ax,3
	sub	ax,bx
	add	ax,14
	mov	dobj.dl_rect.rc_col,al
	mov	cl,80
	sub	cl,al
	shr	cl,1
	mov	dobj.dl_rect.rc_x,cl
      @@:
	xor	di,di
	mov	bl,at_foreground[F_Dialog]
	or	bl,at_background[B_Dialog]
	invoke	dlopen,addr dobj,bx,msg
	jz	_disk_fail
	lea	si,tobj
      @@:
	sub	ax,ax
	mov	al,dobj.dl_count
	cmp	di,ax
	jae	@F
	mov	al,[si+3]
	mov	PButton+1,al
	mov	al,dobj.dl_rect.rc_col
	invoke	rcbprc,DWORD PTR [si].S_TOBJ.to_rect,dobj.dl_wp,ax
	sub	cx,cx
	mov	cl,dobj.dl_rect.rc_col
	sub	bx,bx
	mov	bl,[si].S_TOBJ.to_rect.rc_col
	invoke	wcpbutt,dx::ax,cx,bx,addr PButton
	inc	di
	add	si,16
	jmp	@B
      @@:
	invoke	dlmodal,addr dobj
	mov	di,ax
    _disk_fail:
	sub	ax,ax
	test	di,di
	jz	@F
	sub	ax,ax
	mov	al,dobj.dl_index
	shl	ax,4
	lea	bx,tobj
	add	bx,ax
	sub	ax,ax
	mov	al,[bx+3]
	sub	al,'@'
      @@:
	ret
_disk_select ENDP

	END
