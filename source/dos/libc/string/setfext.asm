; SETFEXT.ASM--
; Copyright (C) 2015 Doszip Developers

include string.inc

	.code

setfext PROC _CType PUBLIC path:PTR BYTE, ext:PTR BYTE
	.if strext(path)
	    xchg ax,bx
	    mov BYTE PTR es:[bx],0
	    mov bx,ax
	.endif
	invoke strcat,path,ext
	ret
setfext ENDP

	END
