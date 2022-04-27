; CVTA_Q.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

cvta_q proc uses rbx _str:string_t, endptr:ptr string_t

    mov rbx,endptr
    _strtoflt(_str)
    .if rbx
        mov rdx,[rax].STRFLT.string
        mov [rbx],rdx
    .endif
    ret

cvta_q endp

    end
