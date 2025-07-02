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
ifndef __UNIX__
include winbase.inc
endif
include tchar.inc

    .code

    assume rsi:tstring_t
    assume rdi:tstring_t

_tfullpath proc uses rsi rdi rbx buf:tstring_t, path:tstring_t, maxlen:size_t

    ldr rbx,buf
    ldr rsi,path
    ldr rcx,maxlen

    .if ( !rsi || [rsi] == 0 )

        .return( _tgetcwd(rbx, ecx) )
    .endif

    .if ( !rbx )
ifdef __UNIX__
        mov eax,_MAX_PATH
else
        .ifd ( GetFullPathName(rsi, 0, NULL, NULL) == 0 )

            _dosmaperr( GetLastError() )
            .return( NULL )
        .endif
endif
        .if ( rax > maxlen )
            mov maxlen,rax
        .endif
        calloc( maxlen, tchar_t )
        .if ( rax == NULL )
            .return
        .endif
        mov rbx,rax
if defined(__UNIX__) and defined(_WIN64)
        mov rsi,path
endif
    .endif

ifdef __UNIX__

    .repeat

        mov rdi,rbx
        .if ( [rsi] == '/' )

            inc rsi

        .else

            .break .if ( !_tgetcwd( rbx, maxlen ) )
            lea rdi,[rbx+_tcslen(rbx)]
            .if ( [rdi-1] == '/' )
                dec rdi
            .endif
ifdef _WIN64
            mov rsi,path
endif
        .endif
        mov rax,maxlen
        lea rcx,[rbx+rax-1]
        mov [rdi],'/'

        .while ( [rsi] )

            mov ax,word ptr [rsi+1]
            .if ( [rsi] == '.' && al == '.' && ( !ah || ah == '/' ) )

                .repeat
                    dec rdi
                    mov al,[rdi]
                .until ( al == '/' || rdi < rbx )

                .if ( rdi < rbx )

                    _set_errno( EACCES )
                    xor eax,eax
                   .break( 1 )
                .endif

                add rsi,2
                .if ( [rsi] )
                    inc rsi
                .endif

            .elseif ( [rsi] == '.' && ( al == '/' || !al ) )

                inc rsi
                .if ( [rsi] )
                    inc rsi
                .endif

            .else

                mov rdx,rdi
                mov al,[rsi]

                .while ( al && al != '/' && rdi < rcx )

                    inc rsi
                    inc rdi
                    mov [rdi],al
                    mov al,[rsi]
                .endw

                .if ( rdi >= rcx )

                    _set_errno( ERANGE )
                    xor eax,eax
                   .break( 1 )
                .endif

                .if ( rdi == rdx )

                    _set_errno( EINVAL )
                    xor eax,eax
                   .break( 1 )
                .endif

                inc rdi
                mov [rdi],'/'
                .if ( [rsi] == '/' )
                    inc rsi
                .endif
            .endif
        .endw
        mov [rdi],0
        mov rax,rbx
    .until 1
    .if ( rax == NULL )
        .if ( rax == buf )
            free(rbx)
        .endif
        xor eax,eax
    .endif

else

    .if ( GetFullPathName(rsi, maxlen, rbx, NULL) >= maxlen )

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
endif
    ret

_tfullpath endp

    end
