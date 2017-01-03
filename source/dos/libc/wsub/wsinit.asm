; WSINIT.ASM--
; Copyright (C) 2015 Doszip Developers

include wsub.inc
include dir.inc
include dir.inc
include conio.inc

	.data
	cp_erinitsub db 'Error init directory',10,'%s',0

	.code

wsinit	PROC _CType PUBLIC USES di si bx wsub:DWORD
	les	di,wsub
	mov	ax,':'
	les	bx,es:[di].S_WSUB.ws_path
	cmp	es:[bx],ah
	jz	wsinit_get
	cmp	es:[bx]+1,al
	je	wsinit_str
    wsinit_get:
	call	getdrv
	jmp	wsinit_init
    wsinit_str:
	mov	al,es:[bx]
	sub	ax,'A'
    wsinit_init:
	invoke	_disk_init,ax
	invoke	chdrv,ax
	mov	ax,':'
	les	di,wsub
	les	bx,es:[di].S_WSUB.ws_path
	cmp	es:[bx],ah
	jz	wsinit_path
	cmp	es:[bx][1],al
	jnz	wsinit_flag
	invoke	chdir,es::bx
	test	ax,ax
	jz	wsinit_flag
    wsinit_path:
	les	di,wsub
	invoke	fullpath,es:[di].S_WSUB.ws_path,0
    wsinit_flag:
	invoke	wssetflag,wsub
	mov	dx,ax
	test	ax,ax
	jnz	wsinit_05
	les	di,wsub
	invoke	ermsg,0,addr cp_erinitsub,es:[di].S_WSUB.ws_path
	jmp	wsinit_loc
    wsinit_05:
	cmp	ax,1
	je	wsinit_end
	cmp	ax,3		; network
	mov	ax,1
	je	wsinit_end
    wsinit_loc:
	invoke	wslocal,wsub
    wsinit_end:
	ret
wsinit	ENDP

	END
