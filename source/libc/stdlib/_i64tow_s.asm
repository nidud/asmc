; _I64TOW_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    .code

_i64tow_s proc val:int64_t, buffer:wstring_t, sizeInTChars:size_t, radix:int_t

ifdef _WIN64
    xor eax,eax
 ifdef __UNIX__
    .ifs ( ecx == 10 && rdi < 0 )
        inc eax
    .endif
    .return ( _xtow_s( rdi, rsi, edx, ecx, eax ) )
 else
    .ifs ( r9d == 10 && rcx < 0 )
        inc eax
    .endif
    .return ( _xtow_s( rcx, rdx, r8d, r9d, eax ) )
 endif
else
    xor ecx,ecx
    mov eax,dword ptr val[0]
    mov edx,dword ptr val[4]
    .ifs ( radix == 10 && edx < 0 )
        inc ecx
    .endif
    .return ( _xtow_s( edx::eax, buffer, sizeInTChars, radix, ecx ) )
endif

_i64tow_s endp

    end
