; _ENVIRON.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    .data
    _environ array_t 0

    .code

init_environ proc private
;    _setenvp( &_environ )
    ret
init_environ endp

.pragma init(init_environ, 5)

    end
