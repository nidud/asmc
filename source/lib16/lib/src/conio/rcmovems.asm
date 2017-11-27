; RCMOVEMS.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include mouse.inc

rcm	STRUC
scp	dd ?
xcn	dw ?
ycn	dw ?
wcn	dw ?
scn	dw ?
base	dd ?	; (R|E)BP -- sizeof(locals)
ifdef __64__
	dd ?
endif
ifndef __c__
	dw ?
endif
ifdef __CDECL__
rect	dd ?
wchr	dd ?
shade	dw ?
else
shade	dw ?
wchr	dd ?
rect	dd ?
endif
rcm	ENDS

A_rc	equ <[bp+rcm.rect-rcm.base]>
A_wp	equ <[bp+rcm.wchr-rcm.base]>
A_sh	equ <[bp+rcm.shade-rcm.base]>
L_scp	equ <[bp+rcm.scp-rcm.base]>
L_xcn	equ <WORD PTR [bp+rcm.xcn-rcm.base]>
L_ycn	equ <WORD PTR [bp+rcm.ycn-rcm.base]>
L_wcn	equ <WORD PTR [bp+rcm.wcn-rcm.base]>
L_scn	equ <WORD PTR [bp+rcm.scn-rcm.base]>

	.code

InitRCMove:
	pop	ax
	push	si
	push	di
	push	bx
	push	ds
	push	ax
	mov	ah,0
	mov	al,dh
	mov	L_ycn,ax
	mov	al,dl
	mov	L_xcn,ax
	add	ax,ax
	mov	L_wcn,ax
	mov	al,_scrcol
	add	ax,ax
	mov	L_scn,ax
	invoke	rcsprc,A_rc
	stom	L_scp
	.if A_sh & _D_SHADE
	    invoke rcclrshade,A_rc,A_wp
	.endif
	HideMouseCursor
	cld?
	ret
ExitRCMove:
	pop	ax
	pop	ds
	pop	bx
	pop	di
	pop	si
	push	ax
	ShowMouseCursor
	.if A_sh & _D_SHADE
	    invoke rcsetshade,A_rc,A_wp
	.endif
	lodm A_rc
	ret

rcmoveup PROC _CType PUBLIC rc:DWORD, wp:DWORD, flag:size_t
local rci[rcm.base]:BYTE
	lodm rc
	.if ah > 1
	    call InitRCMove
	    mov ax,L_scn
	    sub WORD PTR L_scp,ax
	    dec rc.S_RECT.rc_y
	    lds si,wp
	    mov ax,L_xcn
	    mov dx,L_ycn
	    mul dl
	    add ax,ax
	    add ax,si
	    sub ax,L_wcn
	    mov si,ax
	    les di,L_scp
	    mov ax,L_ycn
	    mov dx,L_scn
	    mul dx
	    add di,ax
	    xor bx,bx
	    mov cx,L_xcn
	    .repeat
		push cx
		push si
		push di
		mov cx,L_ycn
		mov dx,[bx+si]
		cmp cx,1
		je @F
		.repeat
		    push bx
		    sub bx,L_wcn
		    mov ax,[bx+si]
		    pop bx
		    mov [bx+si],ax
		  @@:
		    mov ax,es:[bx+di]
		    mov es:[bx+di],dx
		    mov dx,ax
		    sub di,L_scn
		    sub si,L_wcn
		.untilcxz
		mov ax,es:[bx+di]
		mov es:[bx+di],dx
		add si,L_wcn
		mov [bx+si],ax
		add bx,2
		pop di
		pop si
		pop cx
	    .untilcxz
	    call ExitRCMove
	.endif
	ret
rcmoveup ENDP

rcmovedn PROC _CType PUBLIC rc:DWORD, wp:DWORD, flag:size_t
local rci[rcm.base]:BYTE
	lodm rc
	.if _scrrow > ah
	    call InitRCMove
	    inc rc.S_RECT.rc_y
	    mov ax,L_scn
	    add WORD PTR L_scp,ax
	    mov ax,WORD PTR L_scp+2
	    mov es,ax
	    mov di,WORD PTR L_scp
	    xor bx,bx
	    mov cx,L_xcn
	    .repeat
		push cx
		lds si,wp
		mov di,WORD PTR L_scp
		sub di,L_scn
		mov cx,L_ycn
		mov dx,[bx+si]
		.repeat
		    mov ax,es:[bx+di]
		    mov es:[bx+di],dx
		    push ax
		    mov dx,bx
		    add bx,L_wcn
		    mov ax,[bx+si]
		    mov bx,dx
		    mov [bx+si],ax
		    add di,L_scn
		    add si,L_wcn
		    pop dx
		.untilcxz
		mov ax,es:[bx+di]
		mov es:[bx+di],dx
		sub si,L_wcn
		mov [bx+si],ax
		add bx,2
		pop cx
	    .untilcxz
	    call ExitRCMove
	.endif
	ret
rcmovedn ENDP

rcmoveright PROC _CType PUBLIC rc:DWORD, wp:DWORD, flag:size_t
local rci[rcm.base]:BYTE
	lodm rc
	.if _scrcol > al
	    call InitRCMove
	    inc rc.S_RECT.rc_x
	    add WORD PTR L_scp,2
	    les di,wp
	    mov ax,WORD PTR L_scp+2
	    mov ds,ax
	    mov dx,WORD PTR L_scp
	    mov cx,L_ycn
	    .repeat
		mov si,dx
		add dx,L_scn
		push cx
		mov cx,L_xcn
		mov bx,es:[di]
		.repeat
		    mov ax,[si-2]
		    mov [si-2],bx
		    mov bx,ax
		    mov ax,[si]
		    add si,2
		    mov ax,es:[di+2]
		    mov es:[di],ax
		    add di,2
		.untilcxz
		mov ax,[si-2]
		mov [si-2],bx
		mov es:[di-2],ax
		pop cx
	    .untilcxz
	    call ExitRCMove
	.endif
	ret
rcmoveright ENDP

rcmoveleft PROC _CType PUBLIC rc:DWORD, wp:DWORD, flag:size_t
local rci[rcm.base]:BYTE
	lodm rc
	.if al
	    call InitRCMove
	    dec rc.S_RECT.rc_x
	    sub WORD PTR L_scp,2
	    les di,wp
	    lds dx,L_scp
	    mov cx,L_ycn
	    .repeat
		mov si,dx
		add dx,L_scn
		mov ax,[si]
		add si,2
		mov bx,es:[di]
		mov es:[di],ax
		add di,2
		push cx
		mov cx,L_xcn
		dec cx
		.if !cx
		    mov ax,[si]
		    mov [si],bx
		    mov [si-2],ax
		.else
		    .repeat
			mov ax,[si]
			mov [si-2],ax
			add si,2
			mov ax,bx
			mov bx,es:[di]
			mov es:[di],ax
			add di,2
		    .untilcxz
		    mov ax,[si]
		    mov [si-2],ax
		    mov [si],bx
		    add si,2
		.endif
		pop cx
	    .untilcxz
	    call ExitRCMove
	.endif
	ret
rcmoveleft ENDP

	END
