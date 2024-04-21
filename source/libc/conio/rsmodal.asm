; RSMODAL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

rsmodal proc uses rbx robj:PIDD

    ldr rcx,robj
    .if rsopen(rcx)

        mov rbx,rax
        rsevent(robj, rax)
        xchg rbx,rax
        dlclose(rax)
        mov eax,ebx
    .endif
    ret

rsmodal endp

    end
