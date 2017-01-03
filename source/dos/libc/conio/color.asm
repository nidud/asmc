; COLOR.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	PUBLIC	at_background
	PUBLIC	at_foreground
	PUBLIC	at_palett

	.data

at_background	db 00h,10h,70h,70h,40h,30h,30h,70h
at_foreground	db 00h,0Fh,0Fh,07h,08h,05h,06h,07h
		db 08h,00h,0Ah,0Bh,00h,0Fh,0Fh,0Fh
at_palett	db 0,1,2,3,4,5,20,7
		db 56,57,58,59,60,61,62,63

	END
