; __CVTA_Q.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

__cvta_q proc number:ptr, string:string_t, endptr:ptr string_t

    _strtoflt(rdx)

    mov rcx,endptr
    .if rcx

        mov rdx,[rax].STRFLT.string
        mov [rcx],rdx
    .endif

    mov rdx,[rax].STRFLT.mantissa
    mov rcx,number
    mov qword ptr [rcx+0x00],[rdx+0x00]
    mov qword ptr [rcx+0x08],[rdx+0x08]
    mov rax,rcx
    ret

__cvta_q endp

    end
