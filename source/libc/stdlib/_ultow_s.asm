; _ULTOW_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    .code

_ultow_s proc val:ulong_t, buffer:wstring_t, sizeInTChars:size_t, radix:int_t

ifdef _WIN64
    .return ( _xtow_s( rcx, rdx, r8d, r9d, 0 ) )
else
    mov eax,val
    xor edx,edx
    .return ( _xtow_s( edx::eax, buffer, sizeInTChars, radix, 0 ) )
endif

_ultow_s endp

    end
