; RCINSIDE.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

rcinside PROC _CType PUBLIC rc1:DWORD, rc2:DWORD
	mov	ax,WORD PTR rc1+2
	mov	dx,WORD PTR rc2+2
	cmp	dh,ah
	ja	rcinside_04
	cmp	dl,al
	ja	rcinside_04
	add	ax,WORD PTR rc1
	add	dx,WORD PTR rc2
	cmp	ah,dh
	jb	rcinside_00	; below
	cmp	al,dl
	jb	rcinside_03	; left
	mov	ax,WORD PTR rc1
	mov	dx,WORD PTR rc2
	cmp	ah,dh
	ja	rcinside_01	; above
	cmp	al,dl
	ja	rcinside_02	; right
	xor	ax,ax
	jmp	rcinside_05
    rcinside_00:
	mov	ax,1
	jmp	rcinside_05
    rcinside_01:
	mov	ax,2
	jmp	rcinside_05
    rcinside_02:
	mov	ax,3
	jmp	rcinside_05
    rcinside_03:
	mov	ax,4
	jmp	rcinside_05
    rcinside_04:
	mov	ax,5
    rcinside_05:
	ret
rcinside ENDP

	END
