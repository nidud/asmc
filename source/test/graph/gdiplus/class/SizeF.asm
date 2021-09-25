; SIZEF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include gdiplus.inc

    .code

main proc

  local x       : real4
  local y       : real4
  local point   : PointF
  local size    : SizeF
  local pPoint  : ptr PointF
  local pSize   : ptr SizeF

   .new b       : SizeF()
   .new b       : SizeF(1.0)
   .new b       : SizeF(1.0, 2.0)
   .new b       : SizeF(x, y)
   .new b       : SizeF(pSize)
   .new b       : SizeF(pPoint)

   .new p       : ptr SizeF()
   .new p       : ptr SizeF(1.0)
   .new p       : ptr SizeF(1.0, 2.0)
   .new p       : ptr SizeF(x, y)
   .new p       : ptr SizeF(pSize)
   .new p       : ptr SizeF(pPoint)

    SizeF       ()
    SizeF       (1.0)
    SizeF       (1.0, 2.0)
    SizeF       (x, y)
    SizeF       (pSize)
    SizeF       (pPoint)

    b.Equals    (pPoint)

    p.Equals    (pPoint)
    ret

main endp

    end

