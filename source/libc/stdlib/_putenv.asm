; _PUTENV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include string.inc
include errno.inc
include processenv.inc

.code

_putenv proc uses rbx string:string_t

    xor ebx,ebx
    .if ( strchr(string, '=') != NULL )

        mov char_t ptr [rax],0
        lea rbx,[rax+1]
    .endif
ifdef __UNIX__
    xor eax,eax
else
    SetEnvironmentVariableA(string, rbx)
endif
    .if ( rbx )
        mov char_t ptr [rbx-1],'='
    .endif
    .if ( !eax )

        dec rax
       .return
    .endif
ifndef __UNIX__
    mov rbx,_environ
    .if ( __setenvp( &_environ ) )

        free(rbx)
        xor eax,eax
    .else
        mov _environ,rbx
        dec rax
    .endif
endif
    ret

_putenv endp

    end
