; KBHIT.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

.code

kbhit	PROC _CType PUBLIC
	mov	ah,1
	int	16h
	jne	@F
	xor	ax,ax
      @@:
	ret
kbhit	ENDP

	END
