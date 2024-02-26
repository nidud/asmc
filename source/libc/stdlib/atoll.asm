; ATOLL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    .code

atoll proc string:string_t

    ldr rcx,string
    _atoi64(rcx)
    ret

atoll endp

    end
