; FOPEN_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include errno.inc

.code

fopen_s proc pFile:ptr ptr FILE, filename:ptr sbyte, mode:ptr sbyte

    .if ( fopen( filename, mode ) == NULL )

        _get_errno( 0 )

    .else

        mov rcx,pFile
        mov [rcx],rax
        xor eax,eax
    .endif
    ret

fopen_s endp

    end
