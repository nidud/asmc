; BEEP.ASM--
; Copyright (C) 2015 Doszip Developers

include dos.inc
include conio.inc

	.code

beep	PROC _CType PUBLIC __hz:WORD, __time:WORD
	mov	ax,WORD PTR console
	and	ax,CON_UBEEP
	jz	@F
	mov	bx,__hz
	mov	dx,__time
	mov	ax,00B6h
	out	43h,al
	mov	ax,0
	out	42h,al
	mov	ax,bx
	out	42h,al
	mov	al,4Fh
	out	61h,al
	invoke	delay,dx
	mov	al,4Dh
	out	61h,al
      @@:
	ret
beep	ENDP

	END
