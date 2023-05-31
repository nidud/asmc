; STREXT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

strext proc uses rbx string:string_t

    ldr rcx,string
    mov rbx,strfn( rcx )
    .if strrchr( rbx, '.' )
        .if ( rax == rbx )
            xor eax,eax
        .endif
    .endif
    ret

strext endp

    end
