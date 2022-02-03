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

   .new b       : PointF()
   .new b       : PointF(1.0)
   .new b       : PointF(1.0, 2.0)
   .new b       : PointF(x, y)
   .new b       : PointF(size)
   .new b       : PointF(point)
    ret

main endp

    end

