; RCSHADE.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include alloc.inc
include mouse.inc

	.code

_FG_DEACTIVE	equ	8

SHADE		STRUC
sh_cols		dw ?
sh_boff		dw ?
sh_soff		dw ?
sh_xcount	dw ?
sh_wcount	dw ?
SHADE		ENDS

RCInitShade PROC pascal PRIVATE rc:DWORD, wp:DWORD, rb:DWORD
	HideMouseCursor
	mov bx,WORD PTR rb
	sub ax,ax
	mov dx,ax
	mov cx,ax
	mov al,_scrcol
	add ax,ax
	mov [bx].SHADE.sh_wcount,ax
	mov ax,dx
	mov cl,rc.S_RECT.rc_row
	mov al,rc.S_RECT.rc_col
	mov [bx].SHADE.sh_xcount,ax
	mov [bx].SHADE.sh_cols,dx
	add al,rc.S_RECT.rc_x
	inc al
	cmp al,_scrcol
	ja  rcshade_init_01
	je  @F
	inc [bx].SHADE.sh_cols
      @@:
	inc [bx].SHADE.sh_cols
    rcshade_init_01:
	les di,wp
	mov al,rc.S_RECT.rc_col
	mul cl
	add ax,ax
	add di,ax
	mov [bx].SHADE.sh_boff,di
	invoke rcsprc,rc
	add ax,[bx].SHADE.sh_wcount
	add ax,[bx].SHADE.sh_xcount
	add ax,[bx].SHADE.sh_xcount
	inc ax
	mov [bx].SHADE.sh_soff,ax
	mov ds,dx
	mov dx,ax
	mov ah,_FG_DEACTIVE
	ret
RCInitShade ENDP

rcsetshade PROC _CType PUBLIC USES si di cx dx rc:DWORD, wp:DWORD
local	sh:SHADE
	push ds
	push bx
	invoke RCInitShade,rc,wp,addr sh
	.repeat
	    mov si,dx
	    add dx,sh.sh_wcount
	    .if sh.sh_cols >= 1
		mov al,[si]
		mov es:[di],al
		mov [si],ah
		.if !ZERO?
		    mov al,[si+2]
		    mov es:[di+1],al
		    mov [si+2],ah
		.endif
	    .endif
	    add di,2
	.untilcxz
	mov cx,sh.sh_xcount
	dec cx
	jz  rcsetshade_end
	dec cx
	jz  rcsetshade_end
	mov ah,_FG_DEACTIVE
	std
	sub si,2
      @@:
	movsb
	mov [si+1],ah
	dec si
	add di,2
	dec cx
	jnz @B
	cld
    rcsetshade_end:
	ShowMouseCursor
	pop bx
	pop ds
	ret
rcsetshade ENDP

rcclrshade PROC _CType PUBLIC USES si di rc:DWORD, wp:DWORD
local	sh:SHADE
	push ds
	push bx
	invoke RCInitShade,rc,wp,addr sh
    rcclrshade_00:
	mov si,dx
	add dx,sh.sh_wcount
	cmp sh.sh_cols,1
	jb  rcclrshade_01
	mov ax,es:[di]
	mov [si],al
	je  rcclrshade_01
	mov [si+2],ah
    rcclrshade_01:
	add di,2
	dec cx
	jnz rcclrshade_00
	mov cx,sh.sh_xcount
	dec cx
	jz  rcclrshade_end
	dec cx
	jz  rcclrshade_end
    rcclrshade_02:
	sub si,2
	mov al,es:[di]
	mov [si],al
	inc di
	dec cx
	jnz rcclrshade_02
    rcclrshade_end:
	ShowMouseCursor
	pop bx
	pop ds
	ret
rcclrshade ENDP

	END
