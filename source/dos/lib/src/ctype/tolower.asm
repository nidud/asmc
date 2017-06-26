; TOLOWER.ASM--
; Copyright (C) 2015 Doszip Developers

include libc.inc

	.code

tolower PROC _CType PUBLIC char:size_t
	sub	ax,ax
	mov	al,BYTE PTR char
	cmp	al,'Z'
	ja	@F
	cmp	al,'A'
	jb	@F
	add	al,('a' - 'A')
      @@:
	ret
tolower ENDP

	END

