; _SWAB.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include stdlib.inc
include errno.inc

.code

_swab proc uses rbx src:string_t, dest:string_t, n:int_t

    ldr rcx,src
    ldr rdx,dest
    ldr ebx,n

    .ifs ( !rcx || !rdx || ebx < 0 )

        _set_errno(EINVAL)
    .else
        .while ( ebx > 1 )

            mov ax,[rcx]
            mov [rdx],ah
            mov [rdx+1],al
            add rcx,2
            add rdx,2
            add ebx,2
        .endw
    .endif
    ret

_swab endp

    end
