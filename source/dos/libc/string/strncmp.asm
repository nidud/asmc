; STRNCMP.ASM--
; Copyright (C) 2015 Doszip Developers

include string.inc

	.code

strncmp PROC _CType PUBLIC USES si di s1:PTR BYTE, s2:PTR BYTE, count:size_t
	push	ds
	mov	cx,count
	test	cx,cx
	jz	strncmp_end
	mov	dx,cx
	les	di,s1
	mov	si,di
	sub	ax,ax
	repne	scasb
	neg	cx
	add	cx,dx
	mov	di,si
	lds	si,s2
	repe	cmpsb
	mov	al,[si-1]
	xor	cx,cx
	cmp	al,es:[di][-1]
	ja	@F
	je	strncmp_end
	sub	cx,2
      @@:
	not	cx
    strncmp_end:
	mov	ax,cx
	pop	ds
	ret
strncmp ENDP

	END
