; _TFULLPATH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; char * _fullpath(char *, const char *, size_t);
; wchar_t * _wfullpath(wchar_t *, const wchar_t *, size_t);
;

include direct.inc
include malloc.inc
include string.inc
include stdlib.inc
include errno.inc
include winbase.inc
include tchar.inc

.code

_tfullpath proc uses rsi rdi rbx buf:tstring_t, path:tstring_t, maxlen:size_t

    ldr rbx,buf
    ldr rdi,path
    ldr rcx,maxlen

    .if ( !rdi || tchar_t ptr [rdi] == 0 )
        .return( _tgetcwd(rbx, ecx) )
    .endif
    .if ( !rbx )
        .ifd ( GetFullPathName(rdi, 0, NULL, NULL) == 0 )
            _dosmaperr( GetLastError() )
            .return( NULL )
        .endif
        .if ( rax > maxlen )
            mov maxlen,rax
        .endif
        calloc( maxlen, tchar_t )
        .if ( rax == NULL )
            .return
        .endif
        mov rbx,rax
if defined(__UNIX__) and defined(_WIN64)
        mov rdi,path
endif
    .endif
    .if ( GetFullPathName(rdi, maxlen, rbx, NULL) >= maxlen )
        .if ( !buf )
            free(rbx)
        .endif
        _set_errno( ERANGE )
        xor ebx,ebx
    .elseif ( eax == 0 )
        .if ( !buf )
            free(rbx)
        .endif
        _dosmaperr( GetLastError() )
        xor ebx,ebx
    .endif
    mov rax,rbx
    ret
    endp

    end
