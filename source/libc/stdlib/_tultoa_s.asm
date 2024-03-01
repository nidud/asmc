; _TULTOA_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include tchar.inc

    .code

_ultot_s proc val:ulong_t, buffer:tstring_t, sizeInTChars:size_t, radix:int_t

ifdef _WIN64
 ifdef __UNIX__
    _txtoa_s( rdi, rsi, edx, ecx, 0 )
 else
    _txtoa_s( rcx, rdx, r8d, r9d, 0 )
 endif
else
    mov eax,val
    xor edx,edx
    _txtoa_s( edx::eax, buffer, sizeInTChars, radix, 0 )
endif
    ret

_ultot_s endp

    end
