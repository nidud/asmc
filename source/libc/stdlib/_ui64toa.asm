; _UI64TOA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    .code

_ui64toa proc val:uint64_t, buffer:string_t, radix:int_t

ifdef _WIN64
    .return ( _xtoa( rcx, rdx, r8d, 0 ) )
else
    .return ( _xtoa( val, buffer, radix, 0 ) )
endif

_ui64toa endp

    end
