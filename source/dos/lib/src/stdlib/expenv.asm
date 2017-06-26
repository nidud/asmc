; EXPENV.ASM--
; Copyright (C) 2015 Doszip Developers
;
; Change history:
; 11/15/2011 - limit size of %environ% to 128 -- crash: echo %path%
;
include stdlib.inc
include string.inc

	.code ; expand '%TEMP%' to 'C:\TEMP'

expenviron PROC _CType PUBLIC USES si di bx string:PTR BYTE ; [128]
local envl:WORD
local environ[132]:BYTE
local expanded[132]:BYTE
	mov di,WORD PTR string
	.repeat
	    mov ax,WORD PTR string+2
	    .break .if !strchr(ax::di,'%'); get start of [%]environ%
	    mov si,ax
	    inc ax
	    .break .if !strchr(dx::ax,'%'); get end of %environ[%]
	    mov di,ax
	    sub ax,si
	    inc ax	; = length of %environ%
	    mov envl,ax
	    .if ax < 128
		lea bx,environ
		invoke strnzcpy,ss::bx,dx::si,ax ; copy %environ% to stack
		inc ax
		.if getenvp(dx::ax)
		    lea bx,expanded
		    invoke strnzcpy,ss::bx,dx::ax,128
		    invoke strlen,dx::ax
		    mov bx,ax
		    invoke strlen,string
		    add ax,bx
		    sub ax,envl
		    .if ax < 128
			mov cx,di
			sub cx,si
			inc cx ; xchg %environ% with value
			invoke strxchg,string,addr environ,addr expanded,cx
			invoke strlen,addr expanded
			add ax,si
			dec ax
			mov di,ax ; move to end of %environ%
		    .endif
		.endif
	    .endif
	    inc di
	.until 0
	ret
expenviron ENDP

	END
