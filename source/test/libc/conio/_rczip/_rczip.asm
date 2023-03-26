; _RCZIP.ASM--
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

   .new rc:TRECT = { 10, 5, 60, 24 }
   .new b1:TRECT = {  0, 0, 60, 24 }
   .new p:PCHAR_INFO = _rcalloc(rc, 0)
   .new z:PCHAR_INFO = _rcalloc(rc, 0)

    mov rdi,p
    mov eax,(AT shl 16) or ' '
    mov ecx,60*24
    rep stosd

    _rcframe(rc, b1, p, BOX_DOUBLE, 0)
    _rcputf(rc, p, 2, 2, 0, "Window size:    %6d byte", 60*24*4)
    _rcxchg(rc, p)
    _getch()
    _rcxchg(rc, p)
    .new size:int_t = _rczip(rc, z, p)
    _rcunzip(rc, p, z)
    _rcputf(rc, p, 2, 3, 0, "Compresed size: %6d byte", size)
    _rcxchg(rc, p)
    _getch()
    _rcxchg(rc, p)
    .return(0)

_tmain endp

    end
