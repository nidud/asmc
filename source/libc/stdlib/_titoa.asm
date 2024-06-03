; _TITOA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include tchar.inc

    .code

_itot proc val:int_t, buffer:LPTSTR, radix:int_t

ifdef _WIN64
 ifdef __UNIX__
    xor ecx,ecx
    .ifs ( edx == 10 && edi < 0 )
        inc ecx
        movsxd rdi,edi
    .endif
    _txtoa( rdi, rsi, edx, ecx )
 else
    xor r9d,r9d
    .ifs ( r8d == 10 && ecx < 0 )
        inc r9d
        movsxd rcx,ecx
    .endif
    _txtoa( rcx, rdx, r8d, r9d )
 endif
else
    xor ecx,ecx
    mov eax,val
    cdq
    .ifs ( radix == 10 && edx < 0 )
        inc ecx
    .endif
    _txtoa( edx::eax, buffer, radix, ecx )
endif
    ret

_itot endp

    end
