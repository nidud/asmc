include stdio.inc
include stdlib.inc
include tchar.inc

    .code

_tmain proc argc:SINT, argv:ptr

    .for rsi=argv, edi=argc, ebx=0: edi: edi--, ebx++, rsi+=size_t

	_tprintf("[%d]: %s\n", ebx, [rsi])
    .endf
    xor eax,eax
    ret

_tmain endp

    end _tstart
