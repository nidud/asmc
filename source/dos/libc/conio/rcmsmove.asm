; RCMSMOVE.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include keyb.inc
include mouse.inc

	.code

ifdef __MOUSE__

rcmsmove PROC _CType PUBLIC USES di pRECT:DWORD, wp:DWORD, fl:size_t
local rc:DWORD
local xpos:size_t
local ypos:size_t
local relx:size_t
local rely:size_t
local cursor:S_CURSOR
	les di,pRECT
	movmx rc,es:[di]
	.if fl & _D_SHADE
	    invoke rcclrshade,rc,wp
	.endif
	call	mousey
	mov	ypos,ax
	mov	dx,ax
	call	mousex
	mov	xpos,ax
	mov	cx,WORD PTR rc
	sub	al,cl
	mov	relx,ax
	sub	dl,ch
	mov	rely,dx
	invoke	cursorget,addr cursor
	call	cursoroff
	.repeat
	    .if mousep() == 1	; KEY_MSLEFT
		call mousex
		cmp ax,xpos
		je @F
		ja rcmsmove_right
		cmp rc.S_RECT.rc_x,0
		jne rcmsmove_left
	      @@:
		call mousey
		cmp ax,ypos
		je @F
		ja rcmsmove_dn
		cmp rc.S_RECT.rc_y,1
		jne rcmsmove_up
	      @@:
		.continue
	      rcmsmove_up:
		mov ax,rcmoveup
		jmp rcmsmove_do
	      rcmsmove_dn:
		mov ax,rcmovedn
		jmp rcmsmove_do
	      rcmsmove_right:
		mov ax,rcmoveright
		jmp rcmsmove_do
	      rcmsmove_left:
		mov ax,rcmoveleft
	      rcmsmove_do:
		mov	cx,fl
		and	cx,not _D_SHADE
	      ifdef __CDECL__
		push	cx
		pushm	wp
		pushm	rc
	      else
		pushm	rc
		pushm	wp
		push	cx
	      endif
		pushl	cs
		call	ax
		mov	WORD PTR rc,ax
		mov	dx,ax
		mov	ax,rely
		add	al,dh
		mov	ypos,ax
		mov	ax,relx
		add	al,dl
		mov	xpos,ax
		ShowMouseCursor
	    .else
		.break
	    .endif
	.until 0
	invoke cursorset,addr cursor
	.if fl & _D_SHADE
	    invoke rcsetshade,rc,wp
	.endif
	les di,pRECT
	lodm rc
	stom es:[di]
	ret
rcmsmove ENDP
endif ; __MOUSE__

	END
