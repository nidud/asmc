; COLOR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

PUBLIC	at_background
PUBLIC	at_foreground

	.data

at_foreground	db 00h,0Fh,0Fh,07h,08h,00h,00h,07h
		db 08h,00h,0Ah,0Bh,00h,0Fh,0Fh,0Fh
at_background	db 00h,10h,70h,70h,40h,30h,30h,70h
		db 30h,30h,30h,00h,00h,00h,07h,07h

	END
