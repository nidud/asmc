; EMMCOREL.ASM--
; Copyright (C) 2015 Doszip Developers
include alloc.inc

	.code

emmcoreleft PROC _CType PUBLIC
	.if emmnumfreep()
	    push dx
	    mov cx,4000h
	    mul cx
	    pop cx
	.else
	    cwd
	.endif
	ret
emmcoreleft ENDP

	END
