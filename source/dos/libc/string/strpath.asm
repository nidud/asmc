; STRPATH.ASM--
; Copyright (C) 2015 Doszip Developers

include string.inc

	.code

strpath PROC _CType PUBLIC USES di s1:PTR BYTE
	invoke	strfn,s1
	mov	di,ax
	lodm	s1
	cmp	ax,di
	je	@F
	dec	di
      @@:
	mov	BYTE PTR es:[di],0
	ret
strpath ENDP

	END
