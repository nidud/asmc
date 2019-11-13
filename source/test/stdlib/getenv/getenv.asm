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

    _tprintf("Temp:       %s\n", _tgetenv("Temp"))
    _tprintf("SystemRoot: %s\n", _tgetenv("SystemRoot"))
    _tprintf("ComSpec:    %s\n", _tgetenv("ComSpec"))
    _tprintf("AsmcDir:    %s\n", _tgetenv("AsmcDir"))
    xor eax,eax
    ret

_tmain endp

    end
