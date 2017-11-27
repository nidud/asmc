; FPUTS.ASM--
; Copyright (C) 2015 Doszip Developers

include stdio.inc
include string.inc

	.code

fputs	PROC _CType PUBLIC string:DWORD, fp:DWORD
	invoke	_stbuf,fp
	push	ax
	invoke	strlen,string
	invoke	fwrite,string,1,ax,fp
	pop	dx
	push	ax
	invoke	_ftbuf,dx,fp
	invoke	strlen,string
	pop	dx
	cmp	ax,dx
	mov	ax,0
	je	@F
	dec	ax
      @@:
	ret
fputs	ENDP

	END
