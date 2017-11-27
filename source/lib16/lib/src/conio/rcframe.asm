; RCFRAME.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.data

frametypes label BYTE
	db 'ÚÄ¿³ÀÙ'
	db 'ÉÍ»ºÈ¼'
	db 'ÂÄÂ³ÁÁ'
	db 'ÃÄ´³Ã´'

	.code

rcstosw:
	.if ah
	    stosw
	.else
	    stosb
	    inc di
	.endif
	dec cl
	jnz rcstosw
	ret

rcframe PROC _CType PUBLIC USES si di bx cx dx rc:DWORD,
	wstr:DWORD, lsize:size_t, ftype:size_t
local	tmp[16]:BYTE
	cld?
	mov ax,ftype		; AL = Type [0,6,12,18]
	and ax,00FFh		; AH = Attrib
	add ax,offset frametypes
	mov si,ax		;------------------------
	lodsw			; [BP-2] UL 'Ú'
	mov [bp-2],ax		; [BP-1] HL 'Ä'
	lodsw			; [BP-4] UR '¿'
	mov [bp-4],ax		; [BP-3] VL '³'
	lodsw			; [BP-6] LL 'À'
	mov [bp-6],ax		; [BP-5] LR 'Ù'
	mov ax,lsize		;------------------------
	mov cl,al		; line size - 80 on screen
	add al,al
	mul rc.S_RECT.rc_y
	sub dx,dx
	mov dl,rc.S_RECT.rc_x
	add ax,dx
	add ax,dx
	les di,wstr
	add di,ax
	mov ah,0
	mov al,rc.S_RECT.rc_col
	sub al,2
	mov ch,al
	add ax,ax
	mov [bp-10],ax
	mov ax,ftype
	mov dl,rc.S_RECT.rc_row
	mov si,dx
	mov dl,cl
	add dx,dx
	mov bx,di
	mov cl,1
	mov al,[bp-2]	; Upper Left 'Ú'
	call rcstosw
	mov al,[bp-1]	; Horizontal Line 'Ä'
	mov cl,ch
	call rcstosw
	inc cl
	mov al,[bp-4]	; Upper Right '¿'
	call rcstosw
	.if si > 1
	    .if si != 2
		sub si,2
		.repeat
		    add bx,dx
		    mov di,bx
		    inc cl
		    mov al,[bp-3]	; Vertical Line '³'
		    call rcstosw
		    add di,[bp-10]
		    inc cl
		    call rcstosw
		    dec si
		.until !si
	    .endif
	    add bx,dx
	    mov di,bx
	    mov cl,1
	    mov al,[bp-6]	; Lower Left 'À'
	    call rcstosw
	    mov al,[bp-1]	; Horizontal Line 'Ä'
	    mov cl,ch
	    call rcstosw
	    inc cl
	    mov al,[bp-5]	; Lower Right 'Ù'
	    call rcstosw
	.endif
	ret
rcframe ENDP

	END
