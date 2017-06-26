; SEARCHP.ASM--
; Copyright (C) 2015 Doszip Developers

include stdlib.inc
include string.inc
include dos.inc
include dir.inc

extrn	envpath: DWORD

bpPath	equ <[bp-256]>
bpFile	equ <[bp-128]>

	.code

searchp PROC _CType PUBLIC USES si di bx fname:PTR BYTE
local path[256]:BYTE
	les	bx,fname
	test	bx,bx
	jz	searchp_nul
	mov	al,es:[bx]
	test	al,al
	jz	searchp_nul
	cmp	al,'.'
	jz	searchp_nul
	cmp	al,'\'
	jne	searchp_do
    searchp_nul:
	xor	ax,ax
	mov	dx,ax
	jmp	searchp_end
    searchp_do:
	invoke	strcpy,addr bpFile,es::bx
	mov	si,ax
	invoke	strlen,dx::ax
	mov	di,si
	add	di,ax
	cmp	ax,5
	jb	searchp_02
	mov	al,'.'
	cmp	al,[di-4]
	jne	searchp_02
	mov	ax,si
	mov	dx,ss
	call	isexec
	cmp	ax,2
	jae	searchp_03
    searchp_02:
	mov	BYTE PTR [di],'.'
	inc	di
	mov	bx,di
	mov	WORD PTR [di],'OC'
	mov	WORD PTR [di+2],'M'
	call	file_exist
	je	searchp_05
	mov	WORD PTR [di],'XE'
	mov	WORD PTR [di+2],'E'
	call	file_exist
	je	searchp_05
	call	search
	jnz	searchp_end
	mov	WORD PTR [bx],'OC'
	mov	WORD PTR [bx+2],'M'
	jmp	searchp_04
    searchp_03:
	call	file_exist
	je	searchp_05
    searchp_04:
	call	search
	jmp	searchp_end
    searchp_05:
	mov	ax,bp
	sub	ax,128
	mov	dx,ss
    searchp_end:
	ret
search:
	push	bx
	invoke	fullpath,addr bpPath,0
	call	init_file
	les	di,envpath
    search_test:
	invoke	filexist,addr bpPath
	cmp	ax,1
	je	search_found
	cmp	BYTE PTR es:[di],';'
	jnz	search_nul?
	inc	di
    search_nul?:
	cmp	ah,es:[di]
	jz	search_nul
	xor	bx,bx
	lea	si,bpPath
    search_cpy:
	mov	al,es:[bx][di]
	test	al,al
	jz	search_eof
	cmp	al,';'
	je	search_eof
	mov	[bx+si],al
	inc	bx
	jmp	search_cpy
    search_found:
	mov	ax,bp
	sub	ax,256
	mov	dx,ss
	jmp	search_end
    search_nul:
	xor	ax,ax
	mov	dx,ax
    search_end:
	test	ax,ax
	pop	bx
	retn
    search_eof:
	add	di,bx
	mov	[bx+si],ah
	call	init_file
	jmp	search_test
file_exist:
	invoke	filexist,addr bpFile
	cmp	ax,1
	retn
init_file:
	push	es
	invoke	strfcat,addr bpPath,0,addr bpFile
	pop	es
	retn
searchp ENDP

	END
