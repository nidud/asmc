; _RCMOVE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

define _CONIO_RETRO_COLORS
include conio.inc
include tchar.inc

define AT ((BLUE shl 4) or WHITE)

.code

_tmain proc argc:int_t, argv:array_t

   .new rc:TRECT = { 10, 5, 60, 14 }
   .new b1:TRECT = {  0, 0, 60, 14 }
   .new p:PCHAR_INFO = _rcalloc(rc, 0)

    mov rdi,p
    mov eax,(AT shl 16) or ' '
    mov ecx,60*14
    rep stosd

    _rcframe(rc, b1, p, BOX_DOUBLE, 0)
    _rcputs(rc, p, 2, 2, 0, "Use Left, Right, Up, or Down to Move")
    _rcxchg(rc, p)

    .while 1
        .switch _getch()
        .case 0x0D
        .case 0x1B
            .break
        .case 0x4B
            mov rc,_rcmovel(rc, p)
            .endc
        .case 0x4D
            mov rc,_rcmover(rc, p)
            .endc
        .case 0x48
            mov rc,_rcmoveu(rc, p)
            .endc
        .case 0x50
            mov rc,_rcmoved(rc, p)
            .endc
        .endsw
    .endw
    _rcxchg(rc, p)
    .return(0)
_tmain endp

    end
