include time.inc

	.code

	assume	edx: ptr S_TM

main	PROC C
  local ltime
	mov	ltime,55C9D859h
	invoke	localtime,addr ltime
	mov	edx,eax
	mov	eax,1
	cmp	[edx].tm_sec,21
	jne	@F
	cmp	[edx].tm_min,11
	jne	@F
	cmp	[edx].tm_hour,13
	jne	@F
	cmp	[edx].tm_mday,11
	jne	@F
	cmp	[edx].tm_mon,7
	jne	@F
	cmp	[edx].tm_year,115
	jne	@F
	cmp	[edx].tm_wday,2
	jne	@F
	cmp	[edx].tm_yday,222
	jne	@F
	cmp	[edx].tm_isdst,1
	jne	@F
	xor	eax,eax
@@:
	ret
main	ENDP

	END
