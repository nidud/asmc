; DLMODAL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .code

dlmodal proc dobj:ptr S_DOBJ
    dlevent(dobj)
    dlclose(dobj)
    mov eax,edx
    test eax,eax
    ret
dlmodal endp

    END
