; FLOORQF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

floorqf proc vectorcall Q:real16

    fldq()
    fstcw   [rsp]
    fclex
    mov     word ptr [rsp+4],0x0763
    fldcw   [rsp+4]
    frndint
    fclex
    fldcw   [rsp]
    fstq()
    ret

floorqf endp

    end
