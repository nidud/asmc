include io.inc
include string.inc
include stdlib.inc

.code

main	proc c

	system( "echo system()" )
	xor	eax,eax
	ret

main	endp

	end
