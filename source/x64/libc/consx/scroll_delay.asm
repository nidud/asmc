include consx.inc
include time.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

scroll_delay proc
	call	tupdate
	Sleep ( 2 )
	ret
scroll_delay endp

	end
