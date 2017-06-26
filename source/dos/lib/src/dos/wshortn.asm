; WSHORTN.ASM--
; Copyright (C) 2015 Doszip Developers

include dos.inc
include string.inc

	.data

shortname db 14 dup(?)

	.code

wshortname PROC _CType PUBLIC path:DWORD
local wblk:S_WFBLK
	invoke	wfindfirst, path, addr wblk, 00FFh
	push	ax
	invoke	wcloseff, ax
	pop	ax
	inc	ax
	mov	ax,WORD PTR path
	mov	dx,WORD PTR path[2]
	jz	@F
	cmp	wblk.wf_shortname,0
	je	@F
	mov	shortname[12],0
	invoke	memcpy, addr shortname, addr wblk.wf_shortname, 12
@@:
	ret
wshortname ENDP

	END
