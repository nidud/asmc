; _WENVIRON.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include crtl.inc

    .data
    _wenviron dd 0

    .code

install:
    __wsetenvp(&_wenviron)
    ret

.pragma(init(install, 5))

    END
