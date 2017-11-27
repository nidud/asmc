include stdlib.inc
include crtl.inc

    .data
    _wenviron dd 0

    .code

install:
    __wsetenvp(&_wenviron)
    ret

pragma_init install, 5

    END
