; _TENVIRON.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include tchar.inc

    .data
    _tenviron tarray_t 0

    .code

ifndef __UNIX__

init_environ proc private
    _tsetenvp( &_tenviron )
    ret
init_environ endp

.pragma init(init_environ, 5)

endif

    end
