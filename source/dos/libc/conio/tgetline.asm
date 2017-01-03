; TGETLINE.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include keyb.inc
include mouse.inc

	.code

tgetline PROC _CType PUBLIC USES si di ttl:DWORD, buf:DWORD, lsize:size_t, bsize:size_t
local dobj:S_DOBJ
local rc:S_RECT
	mov	dobj.dl_flag,_D_STDDLG
	mov	dobj.dl_rect.rc_row,5
	mov	dobj.dl_rect.rc_y,5
	mov	al,BYTE PTR lsize
	mov	rc.rc_col,al
	add	al,8
	mov	dobj.dl_rect.rc_col,al
	shr	al,1
	mov	ah,40
	sub	ah,al
	mov	dobj.dl_rect.rc_x,ah
	mov	rc.rc_row,1
	mov	rc.rc_x,4
	mov	rc.rc_y,2
	mov	dl,at_background[B_Dialog]
	or	dl,at_foreground[F_Dialog]
	invoke	dlopen,addr dobj,dx,ttl
	test	ax,ax
	jz	tgetline_end
	les	bx,dobj.dl_wp
	sub	cx,cx
	mov	cl,rc.rc_col
	mov	ax,cx
	add	ax,8
	shl	ax,2
	add	ax,8
	add	bx,ax
	mov	al,07h
	invoke	wcputa,es::bx,cx,ax
	invoke	dlshow,addr dobj
      ifdef __MOUSE__
	call	msloop
      else
	sub	ax,ax
      endif
	mov	si,ax
	mov	di,ax
	jmp	tgetline_04
    tgetline_01:
	lodm	rc
	add	ax,WORD PTR dobj.dl_rect
	mov	cx,bsize
	sub	bx,bx
	test	ch,80h
	jz	tgetline_td
	mov	bx,_O_DTEXT
	and	cx,7FFFh
    tgetline_td:
	invoke	dledit,buf,dx::ax,cx,bx
	mov	si,ax
	cmp	si,KEY_ENTER
	je	tgetline_02
	cmp	si,KEY_KPENTER
	jne	tgetline_03
    tgetline_02:
	inc	di
	jmp	tgetline_05
    tgetline_03:
  ifdef __MOUSE__
	cmp	si,MOUSECMD
	jne	tgetline_04
	call	mousex
	mov	dx,ax
	call	mousey
	invoke	rcxyrow,DWORD PTR dobj.dl_rect,dx,ax
	jz	tgetline_05
	invoke	dlmove,addr dobj
  endif
    tgetline_04:
	cmp	si,KEY_ESC
	jne	tgetline_01
    tgetline_05:
	invoke	dlclose,addr dobj
    tgetline_end:
	mov	ax,di
	ret
tgetline ENDP

	END
