include time.inc

	.code

	assume	rax: ptr tm

main	PROC
	local	ltime
	mov	ltime,55C9D859h
	localtime(addr ltime)
	.assert [rax].tm_sec  == 21
	.assert [rax].tm_min  == 11
	.assert [rax].tm_hour == 13
	.assert [rax].tm_mday == 11
	.assert [rax].tm_mon  == 7
	.assert [rax].tm_year == 115
	.assert [rax].tm_wday == 2
	.assert [rax].tm_yday == 222
	.assert [rax].tm_isdst == 1
	xor	eax,eax
	ret
main	ENDP

	END
