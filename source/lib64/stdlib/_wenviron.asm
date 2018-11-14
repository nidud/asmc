; _WENVIRON.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include crtl.inc

	.data
	_wenviron dq 0

	.code

Install proc private
	__wsetenvp( addr _wenviron )
	ret
Install endp

.pragma(init(Install, 5))

	END
