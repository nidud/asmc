include string.inc
include alloc.inc
include wsub.inc
include direct.inc
include dzlib.inc

WSSIZE	equ WMAXPATH + _MAX_PATH*3

	.code

	ASSUME	esi: ptr S_WSUB

wsopen	PROC USES esi wsub:PTR S_WSUB
	mov	esi,wsub
	test	[esi].ws_flag,_W_MALLOC
	jnz	@F
	malloc( WSSIZE )
	jz	toend
	memset( eax, 0, WSSIZE )
	mov	[esi].ws_path,eax
	add	eax,WMAXPATH
	mov	[esi].ws_arch,eax
	add	eax,_MAX_PATH
	mov	[esi].ws_file,eax
	add	eax,_MAX_PATH
	mov	[esi].ws_mask,eax
	xor	eax,eax
	mov	[esi].ws_count,eax
	mov	[esi].ws_fcb,eax
	or	[esi].ws_flag,_W_MALLOC
@@:
	free  ( [esi].ws_fcb )
	mov	eax,[esi].ws_maxfb
	shl	eax,2
	push	eax
	malloc( eax )
	pop	ecx
	mov	[esi].ws_fcb,eax
	jz	toend
	memset( eax, 0, ecx )
	xor	eax,eax
	inc	eax
toend:
	ret
wsopen	ENDP

	END
