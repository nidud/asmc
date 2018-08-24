include stdlib.inc
include crtl.inc

	.data
	_environ dq 0

	.code

Install proc private
	__setenvp( addr _environ )
	ret
Install endp

.pragma(init(Install, 5))

	END
