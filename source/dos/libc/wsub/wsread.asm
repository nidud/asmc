; WSREAD.ASM--
; Copyright (C) 2015 Doszip Developers

include dos.inc
include string.inc
include conio.inc
include wsub.inc
include fblk.inc
include errno.inc
include dir.inc

.code

wsvolid PROC _CType PRIVATE USES bx wsub:DWORD
	local	path[WMAXPATH]:BYTE
	local	ff:S_FFBLK
	mov	bx,WORD PTR wsub
	invoke	strfcat,addr path,[bx].S_WSUB.ws_path,addr cp_stdmask
	invoke	findfirst,addr path,addr ff,_A_VOLID
	test	ax,ax
	jnz	@F
	test	ff.ff_attrib,_A_VOLID
	jz	@F
	mov	al,path
	or	al,20h
	sub	al,'a'
	mov	ah,SIZE S_DISK
	mul	ah
	mov	bx,ax
	mov	drvinfo[bx].di_name[2],' '
	invoke	strcpy,addr drvinfo[bx].di_name[3],addr ff.ff_name
      @@:
	ret
wsvolid ENDP

wsreadff PROC pascal PRIVATE USES si di wsub:DWORD, attrib:WORD
local path[WMAXPATH]:BYTE
local ff:S_FFBLK
	invoke	wsvolid,wsub
	lea	di,ff
	les	bx,wsub
	invoke	strfcat,addr path,es:[bx].S_WSUB.ws_path,addr cp_stdmask
	invoke	findfirst,dx::ax,ss::di,attrib
    wsreadff_skip:
	test	ax,ax
	jnz	wsreadff_loop
	test	BYTE PTR [di].S_FFBLK.ff_attrib,_A_VOLID
	jnz	@F
	mov	dx,WORD PTR [di].S_FFBLK.ff_name
	cmp	dx,'.'
	je	@F
	cmp	dx,'..'
	jne	wsreadff_loop
      @@:
	invoke	findnext,ss::di
	jmp	wsreadff_skip
    wsreadff_loop:
	test	ax,ax
	jnz	wsreadff_end
	test	BYTE PTR [di].S_FFBLK.ff_attrib,_A_SUBDIR
	jnz	@F
	les	bx,wsub
	invoke	cmpwarg,addr ss:[di].S_FFBLK.ff_name,es:[bx].S_WSUB.ws_mask
	jz	wsreadff_next
      @@:
if 0 ; @v2.42
	    les bx,wsub
	    les bx,es:[bx].S_WSUB.ws_flag
	    mov ax,es:[bx]
	    and ax,7F00h
	    invoke fballocff, ss::di, ax
	    .break .if !ax
endif
	invoke	fballocff,ss::di,0
	test	ax,ax
	jz	wsreadff_end
	les	bx,wsub
	mov	cx,es:[bx].S_WSUB.ws_count
	les	bx,es:[bx].S_WSUB.ws_fcb
	shl	cx,2
	add	bx,cx
	stom	es:[bx]
	les	bx,wsub
	inc	es:[bx].S_WSUB.ws_count
	mov	ax,es:[bx].S_WSUB.ws_count
	cmp	ax,es:[bx].S_WSUB.ws_maxfb
	jnb	wsreadff_end
    wsreadff_next:
	invoke	findnext,ss::di
	jmp	wsreadff_loop
    wsreadff_end:
	les	bx,wsub
	mov	ax,es:[bx]
	ret
wsreadff ENDP

wsreadwf PROC _CType PRIVATE USES bx si di wsub:DWORD, attrib:size_t
local path[WMAXPATH]:BYTE
local wf:S_WFBLK
	invoke	wsvolid,wsub
	lea	di,wf
	mov	bx,WORD PTR wsub
	invoke	strfcat,addr path,[bx].S_WSUB.ws_path,addr cp_stdmask
	invoke	wfindfirst,addr path,ss::di,attrib
	mov	si,ax
	inc	ax
	jz	wsreadwf_end
	sub	ax,ax
    wsreadwf_loop1:
	test	ax,ax
	jnz	wsreadwf_loop2
	test	BYTE PTR wf,_A_VOLID
	jnz	@F
	; @v2.42 - this failed in v2.36..2.41, subdirs A,B,.. skipped
	mov	dx,'.'
	cmp	WORD PTR wf.wf_name,dx
	je	@F
	cmp	WORD PTR wf.wf_name[1],dx
	jne	wsreadwf_loop2
      @@:
	invoke	wfindnext,ss::di,si
	jmp	wsreadwf_loop1
    wsreadwf_loop2:
	test	ax,ax
	jnz	wsreadwf_close
	test	BYTE PTR wf,_A_SUBDIR
	jnz	@F
	invoke	cmpwarg,addr wf.wf_name,[bx].S_WSUB.ws_mask
	jz	wsreadwf_next
      @@:
if 0 ; @v2.42
	mov	ax,WORD PTR [bx].S_WSUB.ws_flag
	xchg	bx,ax
	mov	bx,[bx]
	xchg	bx,ax
	and	ax,7F00h
	invoke	fballocwf,ss::di,ax
endif
	invoke	fballocwf,ss::di,0
	test	ax,ax
	jz	wsreadwf_close
	mov	cx,[bx].S_WSUB.ws_count
	shl	cx,2
	les	bx,[bx].S_WSUB.ws_fcb
	add	bx,cx
	stom	es:[bx]
	mov	bx,WORD PTR wsub
	inc	[bx].S_WSUB.ws_count
	mov	ax,[bx].S_WSUB.ws_count
	cmp	[bx].S_WSUB.ws_maxfb,ax
	jbe	wsreadwf_close
    wsreadwf_next:
	invoke	wfindnext,ss::di,si
	jmp	wsreadwf_loop2
    wsreadwf_close:
	invoke	wcloseff,si
    wsreadwf_end:
	mov	ax,[bx]
	ret
wsreadwf ENDP

wsread PROC _CType PUBLIC USES bx wsub:DWORD
	invoke	wsfree,wsub
	sub	ax,ax
ifdef __ROT__
	les	bx,wsub
	les	bx,es:[bx].S_WSUB.ws_path
	cmp	WORD PTR es:[bx][2],'\'
	jne	@F
	mov	ax,_A_ROOTDIR
      @@:
endif
	invoke	fbupdir,ax
	jz	wsreadsub_end
	les	bx,wsub
	inc	es:[bx].S_WSUB.ws_count
	les	bx,es:[bx].S_WSUB.ws_fcb
	stom	es:[bx]
	les	bx,wsub
	les	bx,es:[bx].S_WSUB.ws_mask
	mov	ax,'*'
	cmp	es:[bx],ah
	jne	@F
	mov	es:[bx]+2,ax
	mov	es:[bx],al
	mov	BYTE PTR es:[bx][1],'.'
      @@:
	les	bx,wsub
	les	bx,es:[bx].S_WSUB.ws_flag
	mov	dx,es:[bx]
	mov	ax,_A_ALLFILES
	test	dx,_W_HIDDEN
	jnz	@F
	mov	ax,_A_STDFILES
      @@:
ifdef __LFN__
	.if dx & _W_LONGNAME
	    invoke wsreadwf,wsub,ax
	.else
	    invoke wsreadff,wsub,ax
	.endif
else
	invoke wsreadff,wsub,ax
endif
    wsreadsub_end:
	les	bx,wsub
	mov	ax,es:[bx]
	ret
wsread ENDP

	END
