; _LTOW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    .code

_ltow proc val:long_t, buffer:wstring_t, radix:int_t

ifdef _WIN64
 ifdef __UNIX__
    xor ecx,ecx
    .ifs ( edx == 10 && edi < 0 )
        inc ecx
        movsxd rdi,edi
    .endif
    .return ( _xtow( rdi, rsi, edx, ecx ) )
 else
    xor r9d,r9d
    .ifs ( r8d == 10 && ecx < 0 )
        inc r9d
        movsxd rcx,ecx
    .endif
    .return ( _xtow( rcx, rdx, r8d, r9d ) )
 endif
else
    xor ecx,ecx
    mov eax,val
    cdq
    .ifs ( radix == 10 && edx < 0 )
        inc ecx
    .endif
    .return ( _xtow( edx::eax, buffer, radix, ecx ) )
endif

_ltow endp

    end
