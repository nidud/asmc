; FTOLOWER.ASM--
; Copyright (C) 2015 Doszip Developers

include libc.inc
include ctype.inc

	.code

ftolower PROC _CType PUBLIC
	cmp	al,'Z'
	ja	@F
	cmp	al,'A'
	jb	@F
	add	al,'a' - 'A'
      @@:
	ret
ftolower ENDP

	END

