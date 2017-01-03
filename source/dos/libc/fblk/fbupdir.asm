; FBUPDIR.ASM--
; Copyright (C) 2015 Doszip Developers

include dos.inc
include time.inc
include fblk.inc

	.code

fbupdir PROC _CType PUBLIC flag:size_t
	call	dostime
	mov	cx,flag
	or	cx,_A_UPDIR or _A_SUBDIR
	invoke	fballoc,addr cp_dotdot,dx::ax,0,cx
	ret
fbupdir ENDP

	END
