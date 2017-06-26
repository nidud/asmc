; QWTOBSTR.ASM--
; Copyright (C) 2015 Doszip Developers

include stdlib.inc
include string.inc

	.code

qwtobstr PROC _CType PUBLIC USES si di odx:DWORD, oax:DWORD
local	result[128]:BYTE
	invoke	qwtostr,odx,oax
	invoke	strrev,dx::ax
	mov	si,ax
	lea	di,result
	sub	dx,dx
      @@:
	lodsb
	stosb
	test	al,al
	jz	@F
	inc	dl
	cmp	dl,3
	jne	@B
	mov	al,' '
	stosb
	sub	dl,dl
	jmp	@B
      @@:
	cmp	BYTE PTR [di-2],' '
	jne	@F
	mov	[di-2],dh
      @@:
	invoke	strrev,addr result
	ret
qwtobstr ENDP

	END
