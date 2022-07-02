; _ITOA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    .code

_itoa proc val:long_t, buffer:string_t, radix:int_t

ifdef _WIN64
    xor r9d,r9d
    .ifs ( r8d == 10 && ecx < 0 )
        inc r9d
        movsxd rcx,ecx
    .endif
    .return ( _xtoa( rcx, rdx, r8d, r9d ) )
else
    xor ecx,ecx
    mov eax,val
    cdq
    .ifs ( radix == 10 && edx < 0 )
        inc ecx
    .endif
    .return ( _xtoa( edx::eax, buffer, radix, ecx ) )
endif

_itoa endp

    end
