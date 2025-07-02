; _TGETENV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include string.inc
include tchar.inc

    .code

_tgetenv proc uses rbx enval:tstring_t

   .new len:int_t

    .ifd ( _tcsclen( ldr(enval) ) == 0 )
        .return
    .endif

    mov len,eax
    mov rbx,_tenviron
    mov rax,[rbx]

    .while ( rax )

        .ifd ( !_tcsncicmp( rax, enval, len ) )

            mov eax,len
ifdef _UNICODE
            add eax,eax
endif
            add rax,[rbx]

            .if ( tchar_t ptr [rax] == '=' )
                .return( &[rax+tchar_t] )
            .endif
        .endif
        add rbx,tstring_t
        mov rax,[rbx]
    .endw
    ret

_tgetenv endp

    end
