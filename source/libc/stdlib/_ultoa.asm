; _UITOA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    .code

_ultoa proc val:ulong_t, buffer:string_t, radix:int_t

ifdef _WIN64
    .return ( _xtoa( rcx, rdx, r8d, 0 ) )
else
    mov eax,val
    xor edx,edx
    .return ( _xtoa( edx::eax, buffer, radix, 0 ) )
endif

_ultoa endp

    end
