; LDIV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

.code

ldiv proc x:long_t, y:long_t

    ldr eax,x
    ldr ecx,y
    cdq
    idiv ecx
ifdef _WIN64
    shl rdx,32
    or  rax,rdx
endif
    ret

ldiv endp

    end
