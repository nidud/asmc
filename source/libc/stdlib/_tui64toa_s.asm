; _TUI64TOA_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include tchar.inc

    .code

_ui64tot_s proc val:uint64_t, buffer:tstring_t, sizeInTChars:size_t, radix:int_t

    _txtoa_s( ldr(val), ldr(buffer), ldr(sizeInTChars), ldr(radix), 0 )
    ret

_ui64tot_s endp

    end
