; WSETFLAG.ASM--
; Copyright (C) 2015 Doszip Developers

include dos.inc
include wsub.inc
include dir.inc

	.code

ifdef __LFN__

wscdroom PROC _CType PRIVATE wsub:DWORD
local	vol[32]:BYTE
	xor	ax,ax
	cmp	al,_ifsmgr
	jz	wscdroom_end
	les	bx,wsub
	invoke	wvolinfo,es:[bx].S_WSUB.ws_path,addr vol
	test	ax,ax
	jnz	wscdroom_end
	cmp	vol,al
	je	wscdroom_cdroom
	cmp	WORD PTR vol,'DC'
	jne	wscdroom_end
	cmp	WORD PTR vol+2,'SF'
	jne	wscdroom_end
    wscdroom_cdroom:
	or	di,_W_CDROOM
    wscdroom_end:
	ret
wscdroom ENDP

endif

wssetflag PROC _CType PUBLIC USES di bx wsub:DWORD
	les	bx,wsub
	les	bx,es:[bx].S_WSUB.ws_flag
	mov	di,es:[bx]
	and	di,not _W_NETWORK
	mov	es:[bx],di
	add	bx,S_PATH.wp_path
	mov	ax,es:[bx]
	cmp	ah,':'
	jne	wssetflag_net?
	mov	ah,0
	sub	al,'A'
	invoke	_disk_type,ax
	les	bx,wsub
	cmp	ax,_DISK_FLOPPY
	jne	wssetflag_net
	or	di,_W_FLOPPY
	jmp	wssetflag_set
    wssetflag_net:
	cmp	ax,_DISK_NETWORK
	jne	wssetflag_sub
	or	di,_W_NETWORK
	mov	ax,3
	jmp	wssetflag_cd
    wssetflag_sub:
	cmp	ax,_DISK_SUBST
	jne	wssetflag_loc
	mov	ax,2
    wssetflag_cd:
  ifdef __LFN__
	push	ax
	invoke	wscdroom,wsub
	pop	ax
  endif
	jmp	wssetflag_set
    wssetflag_loc:
	and	ax,1
	jmp	wssetflag_end
    wssetflag_net?:
	mov	al,0
	cmp	ah,'\'
	jne	wssetflag_loc
	mov	ax,3
	or	di,_W_NETWORK
    wssetflag_set:
	les	bx,wsub ; @v2.18
	les	bx,es:[bx].S_WSUB.ws_flag
	mov	es:[bx],di
    wssetflag_end:
	ret
wssetflag ENDP

	END
