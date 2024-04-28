; DLMEMSIZE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

    assume rbx:ptr DOBJ

dlmemsize proc uses rbx dobj:PDOBJ

    ldr rbx,dobj
    _rcmemsize([rbx].rc, [rbx].flags)

    .for ( ch = [rbx].count, cl = 0, edx = 0,
           rbx = [rbx].object : cl < ch : cl++, rbx+=TOBJ )

        assume rbx:ptr TOBJ
        add dl,[rbx].count
    .endf
    shl edx,4
    add eax,edx
    ret

dlmemsize endp

    end
