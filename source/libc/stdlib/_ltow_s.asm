; _LTOW_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    .code

_ltow_s proc val:long_t, buffer:wstring_t, sizeInTChars:size_t, radix:int_t

ifdef _WIN64
 ifdef __UNIX__
    .return ( _xtow_s( rdi, rsi, edx, ecx, 0 ) )
 else
    .return ( _xtow_s( rcx, rdx, r8d, r9d, 0 ) )
 endif
else
    xor edx,edx
    mov eax,val
    .return ( _xtow_s( edx::eax, buffer, sizeInTChars, radix, 0 ) )
endif

_ltow_s endp

    end
