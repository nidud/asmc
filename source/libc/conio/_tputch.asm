; _TPUTCH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include io.inc
include conio.inc
include stdlib.inc
include tchar.inc

    .code

_puttch proc character:int_t

    .new n:int_t
    .new c:int_t

    .if ( _confd == -1 )

        .return( -1 )
    .endif

    ldr ecx,character
    mov c,ecx
if defined(_UNICODE) and defined(__UNIX__)
    mov n,_wtoutf(cx)
    _write( _confd, &n, ecx )
elseifndef _UNICODE
    _write( _confd, &c, 1 )
else
    WriteConsole( _confh, &c, 1, &n, NULL )
endif
    .if ( eax )
        mov eax,c
    .else
        dec rax
    .endif
    ret

_puttch endp

    end
