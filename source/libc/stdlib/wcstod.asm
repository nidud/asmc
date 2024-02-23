; WCSTOD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include fltintrn.inc

    .code

wcstod proc uses rbx string:wstring_t, endptr:warray_t

   .new buffer[128]:char_t

    ldr rcx,string
    lea rdx,buffer

    .for ( ebx = 0 : ebx < 127 : ebx++, rdx++, rcx+=2 )

        mov ax,[rcx]
       .break .if ah || al > 0x7F
        mov [rdx],al
       .break .if !al
    .endf
    mov char_t ptr [rdx],0

    lea rcx,buffer
    _strtoflt( rcx )
    __cvtq_sd( rax, rax )
ifdef __SSE__
    movsd xmm0,[rax]
else
    fld real8 ptr [rax]
endif

    .if ( endptr )

        mov rdx,[rax].STRFLT.string
        lea rcx,buffer
        sub rdx,rcx
        add edx,edx
        add rdx,string
        mov rcx,endptr
        mov [rcx],rdx
    .endif
    ret

wcstod endp

    end
