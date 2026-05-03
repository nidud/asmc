; _RCZIP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

define _CONIO_RETRO_COLORS
include conio.inc
include tchar.inc

define AT ((BLUE shl 4) or WHITE)
define COL 60
define ROW 20

.code

_tmain proc argc:int_t, argv:array_t

   .new rc:TRECT = { 10, 2, COL, ROW }
   .new b1:TRECT = {  0, 0, COL, ROW }
   .new p:PCHAR_INFO = _rcalloc(rc, 0)
   .new z:PCHAR_INFO = _rcalloc(rc, 0)
   .new s:PCHAR_INFO = _conpush()

    mov rdi,p
    mov eax,(AT shl 16) or ' '
    mov ecx,COL*ROW
    rep stosd

    _rcframe(rc, b1, p, BOX_DOUBLE, 0)
    _rcputf(rc, p, 2, 2, 0, "Window size:    %6d byte", COL*ROW*4)
    _rcxchg(rc, p)
    _gettch()
    _rcxchg(rc, p)
    .new size:int_t = _rczip(rc, z, p, W_UNICODE)
    _rcunzip(rc, p, z, W_UNICODE)
    _rcputf(rc, p, 2, 3, 0, "Compresed size: %6d byte", size)
    _rcxchg(rc, p)
    _gettch()
    _rcxchg(rc, p)
    _conpop(s)
    .return(0)

_tmain endp

    end
