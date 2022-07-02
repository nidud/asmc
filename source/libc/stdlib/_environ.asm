; _ENVIRON.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include crtl.inc

    .data
    _environ array_t 0

    .code

Install proc private
    __setenvp( addr _environ )
    ret
Install endp

.pragma(init(Install, 5))

    end
