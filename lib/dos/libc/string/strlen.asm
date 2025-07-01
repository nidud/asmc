; STRLEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.

include string.inc

    .code

strlen proc uses di string:string_t

    xor     ax,ax
    lesl    di,string
    mov     cx,-1
    repne   scasb
    mov     ax,cx
    not     ax
    dec     ax
    ret

strlen endp

    end
