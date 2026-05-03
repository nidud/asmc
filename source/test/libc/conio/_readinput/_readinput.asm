; _READINPUT.ASM--
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

   .new Input:INPUT_RECORD
   .new esc:int_t = 2
   .new rc:TRECT = { 10, 6, 40, 14 }
   .new fc:TRECT = {  0, 0, 40, 14 }
   .new p:PCHAR_INFO = _rcalloc(rc, 0)
   .new s:PCHAR_INFO = _conpush()

    mov rdi,p
    mov eax,(AT shl 16) or ' '
    mov ecx,40*14
    rep stosd
    _rcframe(rc, fc, p, BOX_SINGLE_ARC, 0)
    _rcxchg(rc, p)

    _scputs(12,  8, "_readinput(INPUT_RECORD)")
    _scputs(12, 10, ".bKeyDown")
    _scputs(12, 11, ".wRepeatCount")
    _scputs(12, 12, ".wVirtualKeyCode")
    _scputs(12, 13, ".wVirtualScanCode")
    _scputs(12, 14, ".uChar.UnicodeChar")
    _scputs(12, 15, ".dwControlKeyState")
    _scputs(12, 17, "Hit Escape two times to Quit")

    .whilesd _readinput(&Input) >= 0

        .if ( eax && Input.EventType == KEY_EVENT && Input.Event.KeyEvent.bKeyDown )

            _scputf(35, 10, "%d",   Input.Event.KeyEvent.bKeyDown          )
            _scputf(35, 11, "%d",   Input.Event.KeyEvent.wRepeatCount      )
            _scputf(35, 12, "%02X", Input.Event.KeyEvent.wVirtualKeyCode   )
            _scputf(35, 13, "%02X", Input.Event.KeyEvent.wVirtualScanCode  )
            _scputf(35, 14, "%04X", Input.Event.KeyEvent.uChar.UnicodeChar )
            _scputf(35, 15, "%04X", Input.Event.KeyEvent.dwControlKeyState )

            movzx eax,TCHAR ptr Input.Event.KeyEvent.uChar.UnicodeChar
            _scputc(40, 14, 1, ax )

            .if ( Input.Event.KeyEvent.uChar.UnicodeChar == VK_ESCAPE )

                dec esc
               .break .ifz
            .endif
        .endif
    .endw
    ;_rcxchg(rc, p)
    _conpop(s)
    .return( 0 )

_tmain endp

    end _tstart
