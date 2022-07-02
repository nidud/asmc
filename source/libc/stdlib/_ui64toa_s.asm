; _UI64TOA_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    .code

_ui64toa_s proc val:uint64_t, buffer:string_t, sizeInTChars:size_t, radix:int_t

ifdef _WIN64
    .return ( _xtoa_s( rcx, rdx, r8d, r9d, 0 ) )
else
    .return ( _xtoa_s( val, buffer, sizeInTChars, radix, 0 ) )
endif

_ui64toa_s endp

    end
