; _WSMASK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include wsub.inc

.code

_wsmask proc wp:PWSUB, mask:LPTSTR

    ldr rcx,wp
    ldr rdx,mask

    mov [rcx].WSUB.mask,rdx
    ret

_wsmask endp

    end
