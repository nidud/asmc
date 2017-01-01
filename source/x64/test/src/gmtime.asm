include time.inc

	.code

main	PROC
	local	ltime
	mov	ltime,55C9D859h
	gmtime(addr ltime)
	.assert [rax].S_TM.tm_sec  == 21
	.assert [rax].S_TM.tm_min  == 11
	.assert [rax].S_TM.tm_hour == 11
	.assert [rax].S_TM.tm_mday == 11
	.assert [rax].S_TM.tm_mon  == 7
	.assert [rax].S_TM.tm_year == 115
	.assert [rax].S_TM.tm_wday == 2
	.assert [rax].S_TM.tm_yday == 222
	.assert [rax].S_TM.tm_isdst == 0
	xor	eax,eax
	ret
main	ENDP

	END
