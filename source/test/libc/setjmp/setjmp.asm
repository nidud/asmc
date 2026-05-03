; SETJMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include setjmp.inc
include tchar.inc

    .data
    JumpBuffer _JUMP_BUFFER <>

    .code

_tmain proc

    .if !_setjmp( &JumpBuffer )

        _tprintf( "throw(): %d\n", eax )

        longjmp( &JumpBuffer, 1 )
    .else
        _tprintf( "catch(): %d\n", eax )
    .endif
    xor eax,eax
    ret

_tmain endp

    end
