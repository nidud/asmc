; _LSEEK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc

    .code

_lseek proc handle:SINT, offs:size_t, pos:UINT

    ldr ecx,handle
    ldr rax,offs
    ldr edx,pos

ifdef _WIN64
    .if ( edx == SEEK_SET )
        mov eax,eax
    .endif
    _lseeki64( ecx, rax, edx )
else
    cmp edx,SEEK_SET
    cdq
    .ifz
        xor edx,edx
    .endif
    _lseeki64( ecx, edx::eax, pos )
endif
    ret

_lseek endp

    end
