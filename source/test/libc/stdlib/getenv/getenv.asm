include stdio.inc
include stdlib.inc
include tchar.inc

ifdef _UNICODE
W equ <'W'>
else
W equ <'A'>
endif

.code

_tmain proc

    _tprintf(".lib%d/stdlib/getenv%c:\n", size_t*8, W)

    _tprintf("ASMCDIR:      %s\n", _tgetenv("ASMCDIR"))
    _tprintf("INCLUDE:      %s\n", _tgetenv("INCLUDE"))
    _tprintf("LIBRARY_PATH: %s\n", _tgetenv("LIBRARY_PATH"))
    _tprintf("SYSTEMROOT:   %s\n", _tgetenv("SYSTEMROOT"))
    _tprintf("COMSPEC:      %s\n", _tgetenv("COMSPEC"))
    _tprintf("TEMP:         %s\n", _tgetenv("TEMP"))

    xor eax,eax
    ret

_tmain endp

    end
