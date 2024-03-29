; _RCMEMSIZE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; int _rcmemsize(TRECT, int);
;
include conio.inc

.code

_rcmemsize proc rc:TRECT, shade:int_t

    movzx eax,rc.col
    movzx edx,rc.row
    mov   ecx,eax
    mul   dl
    shl   eax,2

    .if ( shade )

        ; ( ( col + ( row * 2 ) - 2 ) * 4 )

        lea ecx,[rcx+rdx*2-2]
        shl ecx,2
        add eax,ecx
    .endif
    ret

_rcmemsize endp

    end
