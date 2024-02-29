; _TGETENVS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
ifndef __UNIX__
include winnls.inc
include winbase.inc
include tchar.inc
endif

.code

ifndef __UNIX__

_tgetenvs proc

    .new wEnv:wstring_t
    .new wTmp:wstring_t
    .new aEnv:tstring_t = NULL
    .new nSizeW:int_t

    ; obtain wide environment block

    .if ( GetEnvironmentStringsW() == NULL )
        .return
    .endif
    mov wEnv,rax

    ; look for double null that indicates end of block

    .while ( wchar_t ptr [rax] )

        add rax,wchar_t
        .if ( wchar_t ptr [rax] == 0 )
            add rax,wchar_t
        .endif
    .endw

    ; calculate total size of block, including all nulls

    add rax,wchar_t
    sub rax,wEnv
ifndef _UNICODE
    shr eax,1
endif
    mov nSizeW,eax

ifndef _UNICODE

   .new nSizeA:int_t

    ; find out how much space needed for multi-byte environment

    mov nSizeA,WideCharToMultiByte(CP_ACP, 0, wEnv, nSizeW, NULL, 0, NULL, NULL )

endif

    ; allocate space for multi-byte string

    .if ( eax )

        malloc(eax)
    .endif
    .if ( rax == NULL )

        FreeEnvironmentStringsW( wEnv )
       .return( NULL )
    .endif
    mov aEnv,rax

ifdef _UNICODE

    memcpy(rax, wEnv, nSizeW)

else

    ; do the conversion

    .if ( !WideCharToMultiByte(CP_ACP, 0, wEnv, nSizeW, aEnv, nSizeA, NULL, NULL) )

        free( aEnv )
        mov aEnv,NULL
    .endif

endif

    FreeEnvironmentStringsW( wEnv )
    mov rax,aEnv
    ret

_tgetenvs endp

endif

    end
