; DGETFTIM.ASM--
; Copyright (C) 2015 Doszip Developers
;
; unsigned _dos_getftime(int handle, unsigned *datep, unsigned *timep);
;
; Return 0 on success, else DOS error code
;
include dos.inc

	.code

_dos_getftime PROC _CType PUBLIC handle:size_t, datep:DWORD, timep:DWORD
	local ft:S_FTIME
	.if getftime(handle,addr ft) != -1
		push bx
		les bx,datep
		mov ax,ft.ft_date
		mov es:[bx],ax
		les bx,timep
		mov ax,ft.ft_time
		mov es:[bx],ax
		pop bx
		sub ax,ax
	.else
	    mov ax,doserrno
	.endif
	ret
_dos_getftime ENDP

	END
