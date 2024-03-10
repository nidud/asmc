; CONSOLE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include tchar.inc

.code

_tmain proc argc:int_t, argv:tarray_t

    ldr rdx,argv
    mov rax,[rdx]

    .for ( rcx = rax : TCHAR ptr [rax] : rax += TCHAR )

        .if ( TCHAR ptr [rax] == '\' )

            lea rcx,[rax+TCHAR]
        .endif
    .endf

    _tprintf("%s:\tWin32 console application\n", rcx)
    .return( 0 )

_tmain endp

    end
