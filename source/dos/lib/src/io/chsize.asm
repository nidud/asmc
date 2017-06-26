; CHSIZE.ASM--
; Copyright (C) 2015 Doszip Developers

include io.inc
include errno.inc

	.code

chsize	PROC _CType PUBLIC USES di si handle:size_t, new_size:DWORD
local	zbuf[512]:BYTE
local	offs:DWORD
local	count:DWORD
	mov ax,4201h		; save current offset
	mov bx,handle
	xor cx,cx
	mov dx,cx
	int 21h
	.if !CARRY?
	    mov WORD PTR offs,ax
	    mov WORD PTR offs+2,dx
	    mov ax,4202h	; seek to end of file
	    sub cx,cx
	    mov dx,cx
	    int 21h
	.endif
	.if !CARRY?
	    mov si,WORD PTR new_size+2
	    mov di,WORD PTR new_size
	    mov cx,si
	    .if dx > cx || dx == cx && ax > di
		mov ax,4200h	; Seek to new_size
		mov dx,di
		int 21h
		jc @F
		mov ah,40h
		sub cx,cx	; Write zero byte at current file position
		int 21h
		jc @F
	    .elseif dx < cx || dx == cx && ax < di
		push ax
		push ss
		pop es
		lea di,zbuf
		xor ax,ax
		mov cx,512/2
		cld?
		rep stosw
		pop ax
		mov di,WORD PTR new_size
		sub di,ax
		sbb si,dx
		mov WORD PTR count+2,0
		.repeat
		    mov WORD PTR count,512
		    .if si < WORD PTR count+2 || si == WORD PTR count+2 && di < 512
			mov WORD PTR count,di
			mov WORD PTR count+2,si
			.break .if !di
		    .endif
		    mov cx,WORD PTR count
		    sub di,cx
		    sbb si,WORD PTR count+2
		    lea dx,zbuf
		    mov ah,40h	; WRITE TO FILE OR DEVICE
		    int 21h
		    jc @F
		    .continue .if ax == cx
		    mov ax,ER_DISK_FULL
		    jmp @F
		.until 0
	    .endif
	    mov dx,WORD PTR offs
	    mov cx,WORD PTR offs+2
	    mov ax,4200h
	    int 21h
	    jc @F
	    sub ax,ax
	.else
	@@:
	    call osmaperr
	.endif
    chsize_end:
	ret
chsize	ENDP

	END
