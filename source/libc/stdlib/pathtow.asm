; _PATHTOW.ASM--
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

_pathtow proc path:string_t, outPath:ptr wstring_t

ifdef __UNIX__
    int 3
    ret
else
   .new len:int_t
   .new codePage:UINT = CP_ACP

    ldr rcx,path
    ldr rdx,outPath
    .if ( rcx == NULL || rdx == NULL )

        _set_errno( EINVAL )
        .return( FALSE )
    .endif

    xor eax,eax
    mov [rdx],rax

    mov len,MultiByteToWideChar( codePage, 0, path, -1, 0, 0 )

    .if  ( len == 0 )

        _dosmaperr( GetLastError() )
        .return( FALSE )
    .endif

    imul ecx,len,wchar_t
    .if ( malloc( rcx ) == NULL )

        .return( FALSE )
    .endif
    mov rcx,rax
    mov rax,outPath
    mov [rax],rcx

    .if ( MultiByteToWideChar( codePage, 0, path, -1, rcx, len ) == 0 )

        _dosmaperr( GetLastError() )

        mov rdx,outPath
        mov rcx,[rdx]
        mov [rdx],rax
        free(rcx)
       .return( FALSE )
    .endif
    .return( TRUE )
endif

_pathtow endp

    end
