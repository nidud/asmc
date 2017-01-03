; SETFTIME.ASM--
; Copyright (C) 2015 Doszip Developers

include dos.inc
include io.inc

	.code

setftime PROC _CType PUBLIC USES bx handle:size_t, ftime:PTR S_FTIME
	les bx,ftime
	.if _dos_setftime(handle,es:[bx].S_FTIME.ft_date,es:[bx].S_FTIME.ft_time)
	    mov ax,-1
	.endif
	ret
setftime ENDP

	END
