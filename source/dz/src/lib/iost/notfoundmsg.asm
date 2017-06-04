include string.inc
include consx.inc

	.data

externdef	searchstring:BYTE
cp_search	db 'Search',0
cp_notfoundmsg	db "Search string not found: '%s'",0

	.code

notfoundmsg PROC
	mov cp_notfoundmsg[24],' '
	.if strlen( addr searchstring ) > 28
		mov cp_notfoundmsg[24],10
	.endif
	stdmsg( addr cp_search, addr cp_notfoundmsg, addr searchstring )
	xor	eax,eax
	ret
notfoundmsg ENDP

	END
