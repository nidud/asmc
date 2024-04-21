; DLMODAL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

dlmodal proc uses rbx dobj:PDOBJ

    ldr rbx,dobj

    dlevent(rbx)
    xchg rbx,rax
    dlclose(rax)
    mov eax,ebx
    ret

dlmodal endp

    end
