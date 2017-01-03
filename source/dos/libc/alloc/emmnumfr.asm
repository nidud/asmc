; EMMNUMFR.ASM--
; Copyright (C) 2015 Doszip Developers
include alloc.inc

	.code

emmnumfreep PROC _CType PUBLIC
	push bx
	.if emmversion()
	    .if dzemm
		mov ax,1024
	    .else
		mov ah,42h	; BX = number of unallocated pages
		int 67h		; DX = total number of pages
		.if ah
		    sub ax,ax
		.else
		    mov ax,bx
		.endif
	    .endif
	.endif
	pop bx
	ret
emmnumfreep ENDP

	END
