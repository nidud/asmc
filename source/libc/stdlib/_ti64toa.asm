; _TI64TOA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include tchar.inc

    .code

_i64tot proc val:int64_t, buffer:LPTSTR, radix:int_t

ifdef _WIN64
ifdef __UNIX__
    xor ecx,ecx
    .ifs ( edx == 10 && rdi < 0 )
        inc ecx
    .endif
    _txtoa( rdi, rsi, edx, ecx )
else
    xor r9d,r9d
    .ifs ( r8d == 10 && rcx < 0 )
        inc r9d
    .endif
    _txtoa( rcx, rdx, r8d, r9d )
endif
else
    xor eax,eax
    mov edx,dword ptr val[4]
    .ifs ( radix == 10 && edx < 0 )
        inc eax
    .endif
    _txtoa( val, buffer, radix, eax )
endif
    ret

_i64tot endp

    end
