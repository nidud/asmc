; _RCXCHG.ASM--
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

   .new rc:TRECT = { 10, 5, 40, 20 }
   .new b1:TRECT = {  0, 0, 40, 20 }
   .new b2:TRECT = {  2, 2, 36, 16 }
   .new b3:TRECT = {  4, 4, 32, 12 }
   .new b4:TRECT = {  4, 8, 32,  4 }
   .new p:PCHAR_INFO = _rcalloc(rc, 0)

    mov rdi,rax
    mov eax,(AT shl 16) or ' '
    mov ecx,40*20
    rep stosd

    _rcframe(rc, b1, p, BOX_DOUBLE, 0)
    _rcframe(rc, b2, p, BOX_SINGLE, 0)
    _rcframe(rc, b3, p, BOX_SINGLE_ARC, 0)
    _rcframe(rc, b4, p, BOX_SINGLE_HORIZONTAL, 0)
    _rcxchg(rc, p)
    _getch()

    _rcxchg(rc, p)
    _getch()
    ret

_tmain endp

    end _tstart
