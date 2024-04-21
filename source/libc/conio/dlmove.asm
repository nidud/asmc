; DLMOVE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

dlmove proc uses rbx dobj:PDOBJ

    ldr rbx,dobj
    mov cx,[rbx].DOBJ.flag
    and ecx,W_MOVEABLE or W_ISOPEN or W_VISIBLE
    xor eax,eax

    .if ( ecx == W_MOVEABLE or W_ISOPEN or W_VISIBLE )

        .ifd mousep()

            movzx ecx,[rbx].DOBJ.flag
            rcmsmove(&[rbx].DOBJ.rc, [rbx].DOBJ.wp, ecx)
            mov eax,1
        .endif
    .endif
    ret

dlmove endp

    end
