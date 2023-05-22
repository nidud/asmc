; _RCSHADE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

define _CONIO_RETRO_COLORS
include conio.inc

.code

_rcshade proc uses rbx rc:TRECT, wp:PCHAR_INFO, shade:int_t

   .new b:TRECT, r:TRECT

    mov b,rc
    mov r,eax
    shr eax,16
    mov r.col,2
    dec r.row
    inc r.y
    add r.x,al
    add b.y,ah
    mov b.row,1
    add b.x,2

    movzx eax,rc.col
    mul rc.row
    lea rbx,[rax*4]
    add rbx,wp

    .if ( shade )

        _rcread(b, rbx)
        movzx eax,b.col
        _rcread(r, &[rbx+rax*4])

        movzx edx,b.col
        add dl,r.row
        add dl,r.row
        .for ( rax = rbx : edx : edx--, rax += 4 )

            mov byte ptr [rax+2],DARKGRAY
        .endf
    .endif
    _rcxchg(b, rbx)
    movzx eax,b.col
    _rcxchg(r, &[rbx+rax*4])
    ret

_rcshade endp

    end
