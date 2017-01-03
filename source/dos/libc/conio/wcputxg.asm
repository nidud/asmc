; WCPUTXG.ASM--
; Copyright (C) 2015 Doszip Developers
include conio.inc

	.code

wcputxg PROC PUBLIC
	push	cx
	inc	bx
      @@:
	and	es:[bx],ah
	or	es:[bx],al
	add	bx,2
	dec	cx
	jnz	@B
	pop	cx
	ret
wcputxg ENDP

	END
