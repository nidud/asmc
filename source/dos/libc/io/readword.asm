; READWORD.ASM--
; Copyright (C) 2015 Doszip Developers

include io.inc

	.code

readword PROC _CType PUBLIC file:DWORD
local result:DWORD
	.if osopen(file,0,M_RDONLY,A_OPEN) != -1
	    push ax
	    mov cx,ax
	    invoke osread,cx,addr result,4
	    pop cx
	    push ax
	    invoke close,cx
	    pop ax
	.else
	    dec ax
	.endif
	.if ax > 1
	    lodm result
	.else
	    sub ax,ax
	    mov dx,ax
	.endif
	ret
readword ENDP

	END
