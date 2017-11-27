; LSEEK.ASM--
; Copyright (C) 2015 Doszip Developers

include io.inc
include errno.inc

	.code

lseek	PROC _CType PUBLIC handle:size_t, offs:DWORD, pos:size_t
	mov ax,4200h
	add ax,pos
	mov bx,handle
	mov cx,WORD PTR offs+2
	mov dx,WORD PTR offs
	int 21h
	.if CARRY?
	  @@:
	    call osmaperr
	    cwd
	.elseif ax == -1 && dx == -1
	    xor cx,cx
	    mov dx,cx
	    mov ax,4200h
	    int 21h
	    mov ax,ER_NEGATIVE_SEEK
	    jmp @B
	.endif
	ret
lseek	ENDP

	END
