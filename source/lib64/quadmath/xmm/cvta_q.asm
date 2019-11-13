; CVTA_Q.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

cvta_q proc vectorcall string:string_t, endptr:ptr string_t

    _strtoflt(rcx)

    mov rcx,endptr
    .if rcx

        mov rdx,[rax].STRFLT.string
        mov [rcx],rdx
    .endif
    mov rax,[rax].STRFLT.mantissa
    movups xmm0,[rax]
    ret

cvta_q endp

    end
