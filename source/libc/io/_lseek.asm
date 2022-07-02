; _LSEEK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc

    .code

_lseek proc handle:SINT, offs:size_t, pos:UINT

ifdef _WIN64
    .if ( r8d == SEEK_SET )
        mov edx,edx
    .endif
    .return( _lseeki64( ecx, rdx, r8d ) )
else
    mov eax,offs
    cdq
    .if ( pos == SEEK_SET )
        xor edx,edx
    .endif
    .return( _lseeki64( handle, edx::eax, pos ) )
endif

_lseek endp

    end
