include stdlib.inc

	.code

main	proc c

	.assert xtol("1") == 1
	.assert xtol("8") == 8
	.assert xtol("A") == 10
	.assert xtol("f") == 15
	.assert xtol("ffff") == 0xffff
	.assert xtol("89abcdef") == 0x89abcdef

	.assert _xtoi64("1") == 1
	.assert _xtoi64("8") == 8
	.assert _xtoi64("A") == 10
	.assert _xtoi64("f") == 15
	.assert _xtoi64("ffff") == 0xffff
	.assert _xtoi64("89abcdef") == 0x89abcdef
	_xtoi64("0x0123456789abcdef")
	.assert eax == 0x89abcdef
	.assert edx == 0x01234567

	xor	eax,eax
	ret
main	endp

	end
