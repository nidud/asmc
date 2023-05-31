; _ENVIRON.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    .data
    _environ array_t 0

    .code
ifdef __UNIX__
    int 3
else
Install proc private
    __setenvp( &_environ )
    ret
Install endp

.pragma init(Install, 5)
endif
    end
