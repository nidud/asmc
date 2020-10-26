include string.inc
include stdio.inc
include tchar.inc
ifdef _UNICODE
W equ <'W'>
else
W equ <'A'>
endif
.code

_tmain proc uses rsi rdi rbx argc:int_t, argv:array_t

    _tprintf(".lib%d/stdlib/argv%c:\n", size_t*8, W)

    .for ( rsi = argv, ebx = 0 : argc : ebx++, argc-- )

	mov rax,[rsi+rbx*size_t]
	_tprintf( " [%d] %s\n", ebx, rax )
    .endf
    xor eax,eax
    ret

_tmain endp

    end
