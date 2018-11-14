; RSMODAL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .code

rsmodal proc robj:ptr S_ROBJ
    .if rsopen(robj)
        push eax
        rsevent(robj, eax)
        pop ecx
        push eax
        dlclose(ecx)
        pop eax
    .endif
    ret
rsmodal endp

    END
