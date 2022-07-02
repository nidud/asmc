; CRT0DAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include direct.inc
include malloc.inc
include errno.inc
include winnls.inc
include awint.inc

    .code

__copy_path_to_wide_string proc path:ptr char_t, outPath:ptr ptr wchar_t

    .new len:int_t
    .new codePage:UINT = CP_ACP

    ; validation section
    .if ( path == NULL || outPath == NULL )
        _set_errno( EINVAL )
        .return( FALSE )
    .endif

ifndef _CORESYS
    .if ( !__crtIsPackagedApp() )
        .if ( !AreFileApisANSI() )
            mov codePage,CP_OEMCP
        .endif
    .endif
endif

    xor eax,eax
    mov rcx,outPath
    mov [rcx],rax

    ; get the buffer size needed for conversion
    mov len,MultiByteToWideChar( codePage, 0, path, -1, 0, 0 )

    .if  ( len == 0 )

        _dosmaperr( GetLastError() )
        .return( FALSE )
    .endif

    ; allocate enough space for path wide char
    imul ecx,len,wchar_t
    .if ( malloc( rcx ) == NULL )

        ; malloc should set the errno
        .return( FALSE )
    .endif
    mov rcx,rax
    mov rax,outPath
    mov [rax],rcx

    ; now do the conversion
    .if ( MultiByteToWideChar( codePage, 0, path, -1, rcx, len ) == 0 )

        _dosmaperr( GetLastError() )

        mov rdx,outPath
        mov rcx,[rdx]
        mov [rdx],rax
        free(rcx)
       .return( FALSE )
    .endif
    .return( TRUE )

__copy_path_to_wide_string endp

    end
