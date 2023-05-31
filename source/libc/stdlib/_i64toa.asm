; _I64TOA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    .code

_i64toa proc val:int64_t, buffer:string_t, radix:int_t

ifdef _WIN64
ifdef __UNIX__
    xor ecx,ecx
    .ifs ( edx == 10 && rdi < 0 )
        inc ecx
    .endif
    .return ( _xtoa( rdi, rsi, edx, ecx ) )
else
    xor r9d,r9d
    .ifs ( r8d == 10 && rcx < 0 )
        inc r9d
    .endif
    .return ( _xtoa( rcx, rdx, r8d, r9d ) )
endif
else
    xor eax,eax
    mov edx,dword ptr val[4]
    .ifs ( radix == 10 && edx < 0 )
        inc eax
    .endif
    .return ( _xtoa( val, buffer, radix, eax ) )
endif

_i64toa endp

    end
