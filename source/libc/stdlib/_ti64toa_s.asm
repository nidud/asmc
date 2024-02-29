; _TI64TOA_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include tchar.inc

    .code

_i64tot_s proc val:int64_t, buffer:LPTSTR, sizeInTChars:size_t, radix:int_t

ifdef _WIN64
    xor eax,eax
ifdef __UNIX__
    .ifs ( ecx == 10 && rdi < 0 )
        inc eax
    .endif
    _txtoa_s( rdi, rsi, edx, ecx, eax )
else
    .ifs ( r9d == 10 && rcx < 0 )
        inc eax
    .endif
    _txtoa_s( rcx, rdx, r8d, r9d, eax )
endif
else
    xor ecx,ecx
    mov eax,dword ptr val[0]
    mov edx,dword ptr val[4]
    .ifs ( radix == 10 && edx < 0 )
        inc ecx
    .endif
    _txtoa_s( edx::eax, buffer, sizeInTChars, radix, ecx )
endif
    ret

_i64tot_s endp

    end
