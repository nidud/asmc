; _SHR32.ASM--
; Copyright (C) 2015 Doszip Developers

include libc.inc

PUBLIC	_shr32	; DX:AX >> CX

.code

_shr32:
	.while dx && cx
	    shr ax,1
	    shr dx,1
	    jnc @F
	    or ah,80h
	  @@:
	    dec cx
	.endw
	.if cx
	    shr ax,cl
	.endif
	ret

	END
