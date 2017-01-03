; CMMKDIR.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include conio.inc
include errno.inc
ifdef __ZIP__
 include dzzip.inc
endif

extrn	cp_mkdir:BYTE

_DZIP	segment

cmmkdir PROC _CType PUBLIC
local	path[WMAXPATH]:BYTE
  ifdef __ROT__
	mov	bx,cpanel
	mov	bx,[bx]
	test	[bx].S_PATH.wp_flag,_W_ROOTDIR
	jnz	toend
  endif
	mov	ax,cpanel
	call	panel_state
	jz	toend
	mov	path,0
	invoke	tgetline,addr cp_mkdir,addr path,0028h,0104h
	or	ax,ax
	jz	toend
	xor	ax,ax
	cmp	path,al
	je	toend
	mov	bx,cpanel
ifdef __ZIP__
	push	bx
	mov	bx,[bx]
	test	[bx].S_PATH.wp_flag,_W_ARCHZIP
	pop	bx
	jz	@F
	invoke	wzipmkdir,[bx].S_PANEL.pn_wsub,addr path
	jmp	update
    @@:
endif
	.if mkdir(addr path)
	    invoke ermkdir,addr path
	.endif
update:
	call	ret_update_AB
toend:
	ret
cmmkdir ENDP

_DZIP	ENDS

	END
