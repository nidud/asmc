; _TLTOA_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include tchar.inc

    .code

_ltot_s proc val:int_t, buffer:LPTSTR, sizeInTChars:size_t, radix:int_t

ifdef _WIN64
    xor eax,eax
 ifdef __UNIX__
    .ifs ( ecx == 10 && edi < 0 )
        inc eax
        movsxd rdi,edi
    .endif
    _txtoa_s( rdi, rsi, edx, ecx, eax )
 else
    .ifs ( r9d == 10 && ecx < 0 )
        inc eax
        movsxd rcx,ecx
    .endif
    _txtoa_s( rcx, rdx, r8d, r9d, eax )
 endif
else
    xor ecx,ecx
    mov eax,val
    cdq
    .ifs ( radix == 10 && edx < 0 )
        inc ecx
    .endif
    _txtoa_s( edx::eax, buffer, sizeInTChars, radix, ecx )
endif
    ret

_ltot_s endp

    end
