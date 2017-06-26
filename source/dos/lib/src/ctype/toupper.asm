; TOUPPER.ASM--
; Copyright (C) 2015 Doszip Developers

include libc.inc

	.code

toupper PROC _CType PUBLIC char:size_t
	sub	ax,ax
	mov	al,BYTE PTR char
	cmp	al,'z'
	ja	@F
	cmp	al,'a'
	jb	@F
	sub	al,('a' - 'A')
      @@:
	ret
toupper ENDP

	END

