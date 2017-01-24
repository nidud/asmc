include consx.inc
include time.inc

	.code

scroll_delay proc
	call tupdate
	Sleep( 2 )
	ret
scroll_delay endp

	end
