; RCMOVE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

define _CONIO_RETRO_COLORS
include conio.inc

define AT ((BLUE shl 4) or WHITE)

.code

_getkey proc

   .new cursor_keys[8]:byte = {
        VK_UP,      ; A
        VK_DOWN,    ; B
        VK_RIGHT,   ; C
        VK_LEFT,    ; D
        0,
        VK_END,     ; F
        0,
        VK_HOME     ; H
        }

    .whiled ( _getch() != -1 )

        .if ( eax != VK_ESCAPE )

            .return

        .elseif ( _kbhit() == 0 )

            .return(VK_ESCAPE)
        .endif

        .switch _getch()

        .case 'O'

            .switch _getch()
            .case 'P': .return VK_F1
            .case 'Q': .return VK_F2
            .case 'R': .return VK_F3
            .case 'S': .return VK_F4
            .endsw
            .endc

        .case '['

            .switch _getch()
            .case 'A'
            .case 'B'
            .case 'C'
            .case 'D'
            .case 'F'
            .case 'H'
                sub eax,'A'
                mov al,cursor_keys[rax]
               .return
            .endsw
        .endsw
        _kbflush()
    .endw
    ret

_getkey endp


main proc

   .new rc:TRECT = { 10, 5, 60, 14 }
   .new cr:TRECT = {  0, 0, 60, 14 }
   .new p:PCHAR_INFO = _rcalloc(rc, 0)

    mov rdi,p
    mov eax,(AT shl 16) or ' '
    mov ecx,60*14
    rep stosd

    _rcframe(rc, cr, p, BOX_DOUBLE, 0)
    _rcputs(rc, p, 2, 2, 0, "Use Left, Right, Up, or Down to Move")
    _rcxchg(rc, p)

    mov rcx,_console
    mov cr,[rcx].TCLASS.rc
    _scputa(0, 0, cr.col, 0xF0)
    mov dil,cr.col
    shr dil,1
    sub dil,12
    _scputs(dil, 0, "Virtual Terminal Sample")


    .while 1
        .switch _getkey()
        .case 0x0A
        .case VK_ESCAPE
            .break
        .case VK_LEFT
            mov rc,_rcmovel(rc, p)
           .endc
        .case VK_RIGHT
            mov rc,_rcmover(rc, p)
           .endc
        .case VK_UP
            mov rc,_rcmoveu(rc, p)
           .endc
        .case VK_DOWN
            mov rc,_rcmoved(rc, p)
           .endc
        .endsw
    .endw
    _rcxchg(rc, p)
    .return(0)
main endp

    end
