; MSWAIT.ASM--
; Copyright (C) 2015 Doszip Developers

include mouse.inc

	.code

mousewait PROC _CType PUBLIC USES si x:size_t, y:size_t, l:size_t
	mov	si,x
	jmp	mousewait_01
    mousewait_00:
	call	mousex
	cmp	ax,si
	jl	mousewait_end
	mov	dx,si
	add	dx,l
	cmp	ax,dx
	jg	mousewait_end
	call	mousey
	cmp	ax,y
	jne	mousewait_end
    mousewait_01:
	call	mousep
	jnz	mousewait_00
    mousewait_end:
	ret
mousewait ENDP

	END
