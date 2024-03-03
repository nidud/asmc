include string.inc
include stdio.inc
include tchar.inc

ifdef _UNICODE
define W <'W'>
else
define W <'A'>
endif

.code

_tmain proc uses rbx argc:int_t, argv:array_t

    _tprintf(".lib%d/stdlib/argv%c:\n", size_t*8, W)

    .for ( ebx = 0 : ebx < argc : ebx++ )

	mov rcx,argv
	mov rax,[rcx+rbx*size_t]
	_tprintf( " [%d] %s\n", ebx, rax )
    .endf
    xor eax,eax
    ret

_tmain endp

    end
