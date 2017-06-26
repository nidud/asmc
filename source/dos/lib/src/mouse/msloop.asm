; MSLOOP.ASM--
; Copyright (C) 2015 Doszip Developers

include mouse.inc

	.code

msloop	PROC _CType PUBLIC
  ifdef __MOUSE__
	.repeat
	    call mousep
	.until ZERO?
  else
	sub ax,ax
  endif
	ret
msloop	ENDP

	END
