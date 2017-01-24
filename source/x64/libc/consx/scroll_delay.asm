include consx.inc
include time.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

scroll_delay proc
	call	tupdate
	delay ( 2 )
	ret
scroll_delay endp

	end
