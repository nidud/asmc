; RSMODAL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

rsmodal proc uses rbx robj:PIDD

    ldr rbx,robj
    .if rsopen(rbx)

        xchg rbx,rax
        rsevent(rax, rbx)
        xchg rbx,rax
        dlclose(rax)
        mov eax,ebx
    .endif
    ret

rsmodal endp

    end
