; __CVTA_Q.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

__cvta_q proc number:ptr, strptr:string_t, endptr:ptr string_t

    push rdi
    push rdx
    _strtoflt(rsi)
    pop rcx
    .if rcx
        mov rdx,[rax].STRFLT.string
        mov [rcx],rdx
    .endif
    pop rax
    ret

__cvta_q endp

    end
