; SETFT_CR.ASM--
; Copyright (C) 2015 Doszip Developers
;
; int setftime_create(int handle, struct ftime *ftimep);
;
include dos.inc
include io.inc

	.code

setftime_create PROC _CType PUBLIC USES bx handle:size_t, ftime:PTR S_FTIME
	les bx,ftime
	.if _dos_setftime_create(handle,es:[bx].S_FTIME.ft_date,es:[bx].S_FTIME.ft_time)
	    mov ax,-1
	.endif
	ret
setftime_create ENDP

	END
