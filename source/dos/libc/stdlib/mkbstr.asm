; MKBSTR.ASM--
; Copyright (C) 2015 Doszip Developers

include stdlib.inc
include string.inc

	.code

mkbstring PROC _CType PUBLIC qw_buf:PTR BYTE, qw_h:DWORD, qw_l:DWORD
	invoke qwtobstr,qw_h,qw_l
	invoke strcpy,qw_buf,dx::ax
	push bx
ifdef __3__
	mov eax,qw_h
	mov edx,qw_l
	.if eax || edx
	    shl eax,22
	    shr edx,10
	    or eax,edx
	    mov edx,1
	    .repeat
		.break .if eax < 10000
		shr eax,10
		inc edx
	    .until 0
	    mov bx,dx
	    shld edx,eax,16
	    or dx,bx
	.endif
else
	mov bx,WORD PTR qw_h
	mov dx,WORD PTR qw_l
	mov ax,WORD PTR qw_h+2
	or  ax,bx
	.if ax || dx
	    shr dx,10	; cx:dx qw_l
	    mov ax,WORD PTR qw_l+2
	    mov cx,ax
	    shl ax,6
	    or	dx,ax
	    shr cx,10
	    shl bx,6	; bx::0 qw_h
	    or cx,bx
	    mov ax,dx
	    mov dx,1
	    .repeat
		.break .if !cx && ax < 10000
		mov bx,cx
		shr cx,10
		shl bx,6
		shr ax,10
		or  ax,bx
		inc dx
	    .until 0
	.endif
endif
	pop bx
	ret
mkbstring ENDP

	END
