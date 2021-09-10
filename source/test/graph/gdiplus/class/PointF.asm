; POINTF.ASM--
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

   .new b       : PointF()
   .new b       : PointF(1.0)
   .new b       : PointF(1.0, 2.0)
   .new b       : PointF(x, y)
   .new b       : PointF(pSize)
   .new b       : PointF(pPoint)

   .new p       : ptr PointF()
   .new p       : ptr PointF(1.0)
   .new p       : ptr PointF(1.0, 2.0)
   .new p       : ptr PointF(x, y)
   .new p       : ptr PointF(pSize)
   .new p       : ptr PointF(pPoint)

    PointF      ()
    PointF      (1.0)
    PointF      (1.0, 2.0)
    PointF      (x, y)
    PointF      (pSize)
    PointF      (pPoint)

    b.Equals    (pPoint)
    b.radd8     (pPoint)
    b.rsub8     (pPoint)

    p.Equals    (pPoint)
    p.radd8     (pPoint)
    p.rsub8     (pPoint)
    ret

main endp

    end

