; _I64TOA_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    .code

_i64toa_s proc val:int64_t, buffer:string_t, sizeInTChars:size_t, radix:int_t

ifdef _WIN64
    xor eax,eax
    .ifs ( r9d == 10 && rcx < 0 )
        inc eax
    .endif
    .return ( _xtoa_s( rcx, rdx, r8d, r9d, eax ) )
else
    xor ecx,ecx
    mov eax,dword ptr val[0]
    mov edx,dword ptr val[4]
    .ifs ( radix == 10 && edx < 0 )
        inc ecx
    .endif
    .return ( _xtoa_s( edx::eax, buffer, sizeInTChars, radix, ecx ) )
endif

_i64toa_s endp

    end
