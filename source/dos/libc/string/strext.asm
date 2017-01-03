; STREXT.ASM--
; Copyright (C) 2015 Doszip Developers

include string.inc

	.code

strext	PROC _CType PUBLIC string:PTR BYTE
	invoke	strfn,string
	push	ax
	invoke	strrchr,dx::ax,'.'
	pop	cx
	jz	@F
	cmp	ax,cx
	jne	@F
	sub	ax,ax
      @@:
	ret
strext	ENDP

	END
