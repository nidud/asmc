; _UI64TOW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    .code

_ui64tow proc val:uint64_t, buffer:wstring_t, radix:int_t

ifdef _WIN64
 ifdef __UNIX__
    .return ( _xtow( rdi, rsi, edx, 0 ) )
 else
    .return ( _xtow( rcx, rdx, r8d, 0 ) )
 endif
else
    .return ( _xtow( val, buffer, radix, 0 ) )
endif

_ui64tow endp

    end
