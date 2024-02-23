; _WPUTENV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include string.inc
include errno.inc
include processenv.inc

.code

_wputenv proc uses rbx string:wstring_t

    xor ebx,ebx
    .if ( wcschr(string, '=') != NULL )

        mov wchar_t ptr [rax],0
        lea rbx,[rax+2]
    .endif
ifdef __UNIX__
    xor eax,eax
else
    SetEnvironmentVariableW(string, rbx)
endif
    .if ( rbx )
        mov wchar_t ptr [rbx-2],'='
    .endif
    .if ( !eax )

        dec rax
       .return
    .endif
ifndef __UNIX__
    mov rbx,_wenviron
    .if ( __wsetenvp( &_wenviron ) )

        free(rbx)
        xor eax,eax
    .else
        mov _wenviron,rbx
        dec rax
    .endif
endif
    ret

_wputenv endp

    end
