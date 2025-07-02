; _TFOPEN_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include errno.inc
include tchar.inc

.code

_tfopen_s proc pFile:ptr LPFILE, filename:tstring_t, mode:tstring_t

    .if ( _tfopen( filename, mode ) == NULL )

        _get_errno( 0 )
    .else
        mov rcx,pFile
        mov [rcx],rax
        xor eax,eax
    .endif
    ret

_tfopen_s endp

    end
