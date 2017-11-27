; SEARCHPA.ASM--
; Copyright (C) 2015 Doszip Developers

include stdlib.inc
include string.inc
include dos.inc
include dir.inc

.data
cp_path db 'PATH%',0

.code

file_exist:
	push	bx
	push	ss
	push	ax
	call	filexist
	cmp	ax,1
	pop	bx
	ret

init_file:
	push	es
	push	ss
	lea	ax,[bp-256]
	push	ax
	push	0
	push	0
	push	ss
	add	ax,128
	push	ax
	call	strfcat
	pop	es
	ret

searchpath PROC _CType PUBLIC fname:DWORD
local	path[256]:BYTE
local	envpath:DWORD
local	fp:WORD
	push	si
	push	di
	les	bx,fname
	test	bx,bx
	jz	searchpath_nul
	mov	al,es:[bx]
	test	al,al
	jz	searchpath_nul
	cmp	al,'.'
	jz	searchpath_nul
	cmp	al,'\'
	jne	searchpath_do
    searchpath_nul:
	xor	ax,ax
	cwd
	jmp	searchpath_end
    searchpath_do:
	push	ss
	lea	ax,[bp-128]
	mov	fp,ax
	push	ax
	push	es
	push	bx
	call	strcpy
	call	file_exist
	je	searchpath_found
	push	ss
	push	offset cp_path
	call	getenvp
	jz	searchpath_nul
	stom	envpath
	push	ss
	lea	ax,[bp-256]
	mov	fp,ax
	push	ax
	push	0
	call	fullpath
	call	init_file
	les	di,envpath
    searchpath_test:
	mov	ax,fp
	call	file_exist
	je	searchpath_found
	cmp	BYTE PTR es:[di],';'
	jnz	searchpath_nul?
	inc	di
    searchpath_nul?:
	cmp	ah,es:[di]
	jz	searchpath_nul
	xor	bx,bx
	mov	si,fp
    searchpath_cpy:
	mov	al,es:[bx+di]
	test	al,al
	jz	searchpath_eof
	cmp	al,';'
	je	searchpath_eof
	mov	[bx+si],al
	inc	bx
	jmp	searchpath_cpy
    searchpath_eof:
	add	di,bx
	mov	[bx+si],ah
	call	init_file
	jmp	searchpath_test
    searchpath_found:
	mov	ax,fp
	mov	dx,ss
    searchpath_end:
	test	ax,ax
	pop	di
	pop	si
	ret
searchpath ENDP

	END
