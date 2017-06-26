; RCSHOW.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

rcshow	PROC _CType PUBLIC rect:DWORD, flag:size_t, wp:DWORD
	mov	ax,flag
	and	ax,_D_DOPEN
	jz	rcshow_end
	test	BYTE PTR flag,_D_ONSCR
	jnz	@F
	invoke	rcxchg,rect,wp
	test	BYTE PTR flag,_D_SHADE
	jz	@F
	invoke	rcsetshade,rect,wp
      @@:
	mov	ax,1
    rcshow_end:
	ret
rcshow	ENDP

	END
