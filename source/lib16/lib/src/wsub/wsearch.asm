; WSEARCH.ASM--
; Copyright (C) 2015 Doszip Developers

include string.inc
include fblk.inc
include wsub.inc

	.code

wsearch PROC _CType PUBLIC USES si di bx wsub:DWORD, string:PTR BYTE
	les	bx,wsub
	mov	cx,es:[bx].S_WSUB.ws_count
	mov	si,WORD PTR es:[bx].S_WSUB.ws_fcb+2
	mov	di,WORD PTR es:[bx].S_WSUB.ws_fcb
      @@:
	mov	ax,-1
	test	cx,cx
	jz	@F
	dec	cx
	mov	es,si
	les	bx,es:[di]
	add	di,4
	invoke	stricmp,string,addr es:[bx].S_FBLK.fb_name
	jnz	@B
	mov	dx,es
	les	bx,wsub
	mov	ax,es:[bx].S_WSUB.ws_count
	sub	ax,cx
	dec	ax
      @@:
	ret
wsearch ENDP

	END
