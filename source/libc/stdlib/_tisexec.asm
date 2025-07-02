; _TISEXEC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Test if <ext> == bat | cmd | com | exe
;
include stdlib.inc
include string.inc
include tchar.inc

    .code

_tisexec proc uses rbx path:tstring_t

    .if _tcsext( ldr(path) )

        lea rbx,[rax+tchar_t]
        .if ( _tcsicmp(rbx, "cmd") == 0 )
            .return( _EXEC_CMD )
        .endif
        .if ( _tcsicmp(rbx, "exe") == 0 )
            .return( _EXEC_EXE )
        .endif
        .if ( _tcsicmp(rbx, "com") == 0 )
            .return( _EXEC_COM )
        .endif
        .if ( _tcsicmp(rbx, "bat") == 0 )
            .return( _EXEC_BAT )
        .endif
        xor eax,eax
    .endif
    ret

_tisexec endp

    end
