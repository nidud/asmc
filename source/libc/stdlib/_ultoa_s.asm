; _ULTOA_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    .code

_ultoa_s proc val:ulong_t, buffer:string_t, sizeInTChars:size_t, radix:int_t

ifdef _WIN64
    .return ( _xtoa_s( rcx, rdx, r8d, r9d, 0 ) )
else
    mov eax,val
    xor edx,edx
    .return ( _xtoa_s( edx::eax, buffer, sizeInTChars, radix, 0 ) )
endif

_ultoa_s endp

    end
