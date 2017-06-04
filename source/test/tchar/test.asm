include stdio.inc
include stdlib.inc
include tchar.inc
ifdef _WIN64
    option win64:3
endif
    .code

_tmain proc argc:SINT, argv:ptr

    .for RSI = argv, edi = argc, ebx = 0: edi: edi--, ebx++, RSI += size_t

	_tprintf("[%d]: %s\n", ebx, [RSI])
    .endf
    xor eax,eax
    ret

_tmain endp

    end _tstart
