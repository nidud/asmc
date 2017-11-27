; EOF.ASM--
; Copyright (C) 2015 Doszip Developers

include io.inc

	.code

eof	PROC _CType PUBLIC USES si di handle:size_t
	invoke	lseek,handle,0,SEEK_CUR
	mov	di,dx
	mov	si,ax
	invoke	lseek,handle,0,SEEK_END
	cmp	si,-1
	jne	@F
	cmp	di,-1
	jne	@F
	mov	ax,si
	cwd
	jmp	eof_end
      @@:
	cmp	ax,si
	jne	@F
	cmp	dx,di
	jne	@F
	mov	ax,1
	jmp	eof_end
      @@:
	mov	ax,si
	mov	dx,di
	invoke	lseek,handle,dx::ax,SEEK_SET
	sub	ax,ax
	mov	dx,ax
    eof_end:
	ret
eof	ENDP

	END
