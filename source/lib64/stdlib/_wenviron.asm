include stdlib.inc
include crtl.inc

	.data
	_wenviron dq 0

	.code

Install proc private
	__wsetenvp( addr _wenviron )
	ret
Install endp

pragma_init Install, 5

	END
