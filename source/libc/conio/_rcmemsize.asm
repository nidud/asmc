; _RCMEMSIZE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; int _rcmemsize(TRECT, int);
;
include conio.inc

.code

_rcmemsize proc rc:TRECT, flags:uint_t

    movzx eax,rc.col
    movzx edx,rc.row
    mov   ecx,eax
    mul   dl
    add   eax,eax

    .if ( flags & W_SHADE )

        ; ( ( col + ( row * 2 ) - 2 ) * n )

        lea ecx,[rcx+rdx*2-2]
        add eax,ecx
        add eax,ecx
    .endif
    .if (  flags & W_UNICODE )

        add eax,eax
    .endif
    ret

_rcmemsize endp

    end
