include stdio.inc
include limits.inc
include tchar.inc
ifdef _UNICODE
W equ <'W'>
else
W equ <'A'>
endif

.code

_tmain proc

  local i:int_t

    _tprintf(".lib%d/stdio/format%c(%%b):\n", size_t*8, W)

    .for ( i = 10 : i < 16 : i++ )

        _tprintf("%9X  %04b  %d\n", i, i, i)
    .endf
    _tprintf(" %X  %032b  %d\n", INT_MAX, INT_MAX, INT_MAX)
    _tprintf(" %X  %032b  %d\n", INT_MIN, INT_MIN, INT_MIN)
    xor eax,eax
    ret

_tmain endp

    end
