; _SHL32.ASM--
; Copyright (C) 2015 Doszip Developers

include libc.inc

PUBLIC	_shl32	; DX:AX << CL

.code

_shl32:
	shl	dx,1
	shl	ax,1
	adc	dl,0
	dec	cl
	jnz	_shl32
	ret

	END
