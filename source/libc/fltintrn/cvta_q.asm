; CVTA_Q.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include fltintrn.inc

    .code

__cvta_q proc __ccall number:ptr qfloat_t, strptr:string_t, endptr:ptr string_t

    _strtoflt( strptr )
    mov rcx,endptr
    .if rcx
        mov rdx,[rax].STRFLT.string
        mov [rcx],rdx
    .endif
    mov rcx,number
    mov rdx,rax
    mov [rcx],[rdx].U128.u128
    mov rax,rcx
    ret

__cvta_q endp

    end
