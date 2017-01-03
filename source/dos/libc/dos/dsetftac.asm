; DSETFTAC.ASM--
; Copyright (C) 2015 Doszip Developers
;
; int _dos_setftime_access(int __handle, int __date, int __time);
;
; Win32 - return OS error code on error
;
include dos.inc
include io.inc

	.code

_dos_setftime_access PROC _CType PUBLIC h:size_t, d:size_t, t:size_t
	ret
_dos_setftime_access ENDP

	END
