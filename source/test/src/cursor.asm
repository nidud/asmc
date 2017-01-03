include consx.inc

	.data
	cu S_CURSOR <>
	co S_CURSOR <>
	.code

main	proc c
	GetCursor(addr co)
	CursorOn()
	_gotoxy(0,24)
test_	macro x,y
	.assert _wherex() == x
	.assert _wherey() == y
	endm
	test_	0,24
	lea	edi,cu
	lea	esi,co
	mov	ecx,SIZE S_CURSOR
	rep	movsb
	mov	cu.x,20
	mov	cu.y,2
	SetCursor(addr cu)
	test_	20,2
	movzx	esi,co.y
	movzx	edi,co.x
	SetCursor(addr co)
	test_	edi,esi
	sub	eax,eax
	ret
main	endp

	end
