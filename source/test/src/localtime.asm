include time.inc

	.code

	assume	edx: ptr tm

main	PROC C
  local ltime
	mov	ltime,55C9D859h
	localtime(addr ltime)
	mov	edx,eax
	mov	eax,1
	.assert [edx].tm_sec   == 21
	.assert [edx].tm_min   == 11
	.assert [edx].tm_hour  == 13
	.assert [edx].tm_mday  == 11
	.assert [edx].tm_mon   == 7
	.assert [edx].tm_year  == 115
	.assert [edx].tm_wday  == 2
	.assert [edx].tm_yday  == 222
	.assert [edx].tm_isdst == 1
	xor	eax,eax
	ret
main	ENDP

	END
