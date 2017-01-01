include stdlib.inc
include crtl.inc

	.data
	_environ dq 0

	.code

Install proc
	__setenvp( addr _environ )
	ret
Install endp

pragma_init Install, 5

	END
