include string.inc
include direct.inc

	.data
buf	dw 4096 dup(0)
cp_A	dw 'A'
cp_X	dw "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
cp_B	dw 'B'
cp_9	dw 9
	dw 0
	.code

main	proc c

	lea edi,buf
	lea esi,buf[4]

	.assert wcslen	(edi) == 0
	.assert ZERO?
	.assert wcslen	("1") == 1
	.assert wcscpy	(edi, "abc") == edi
	.assert wcslen	(edi) == 3
	.assert wcscmp	(edi, "abc") == 0
	.assert wcscmp	(edi, "abc ") == -1
	.assert wcspbrk (edi, "a") == edi
	.assert wcspbrk (edi, "c") == esi
	.assert wcsncmp (edi, "abc", 4) == 0
	.assert wcsncmp (edi, "abc ", 4) == -1
	.assert wcscat	(edi, "\\abc") == edi
	lea esi,[edi+40]
	.assert wcscpy	(edi, "01234567890123456789strstr") == edi
	.assert wcsstr	(edi, "strstr") == esi
	.assert wcsstr	(edi, "strstrx") == 0
	lea esi,[edi+18]
	.assert wcschr	(edi, '9') == esi
	.assert wcschr	(addr cp_X, 'B') == offset cp_B
	.assert wcschr	(addr cp_X, 9) == offset cp_9
	xor	eax,eax
	ret

main	endp

	end
