; _WENVIRON.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    .data
    _wenviron warray_t 0

    .code

ifndef __UNIX__

Install proc private
    __wsetenvp( &_wenviron )
    ret
Install endp

.pragma init(Install, 5)
endif
    end
