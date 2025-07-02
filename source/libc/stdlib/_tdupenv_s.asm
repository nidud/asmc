; _TDUPENV_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include errno.inc
include tchar.inc

.code

_tdupenv_s proc uses rbx pBuffer:tarray_t, pBufferSizeInTChars:ptr size_t, varname:tstring_t

   .new string:tstring_t
   .new size:size_t

    ldr rbx,pBuffer
    ldr rcx,varname
    ldr rdx,pBufferSizeInTChars

    .if ( rbx == NULL || rcx == NULL )

        _set_errno(EINVAL)
        .return( EINVAL )
    .endif

    xor eax,eax
    mov [rbx],rax
    .if ( rdx != NULL )
        mov [rdx],rax
    .endif

    .if ( _tgetenv(rcx) == NULL )

        .return( 0 )
    .endif
    mov string,rax

    mov size,&[_tcslen(rax)+1]
    mov [rbx],calloc(rax, tchar_t)

    .if ( rax == NULL )

        _set_errno(ENOMEM)
        .return( ENOMEM )
    .endif

    .ifd ( _tcscpy_s( rax, size, string ) == 0 )

        mov rcx,pBufferSizeInTChars
        .if ( rcx != NULL )

            mov rdx,size
            mov [rcx],rdx
        .endif
    .endif
    ret

_tdupenv_s endp

    end
