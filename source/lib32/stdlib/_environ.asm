include stdlib.inc
include crtl.inc

	.data
	_environ dd 0

	.code

install:
	__setenvp( addr _environ )
	ret

.pragma(init(install, 5))

	END
