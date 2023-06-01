include string.inc
include stdio.inc
include tchar.inc
ifdef _UNICODE
W equ <'W'>
else
W equ <'A'>
endif
.code

_tmain proc argc:int_t, argv:array_t

    _tprintf(".lib%d/stdlib/argv%c:\n", size_t*8, W)

    .for ( ebx = 0 : ebx < argc : ebx++ )

	mov rcx,argv
	mov rax,[rcx+rbx*string_t]
	_tprintf( " [%d] %s\n", ebx, rax )
    .endf
    .return( 0 )

_tmain endp

    end
