; POINT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include gdiplus.inc

    .code

main proc

  local x       : int_t
  local y       : int_t
  local point   : Point
  local size    : Size
  local pPoint  : ptr Point
  local pSize   : ptr Size

   .new b       : Point()
   .new b       : Point(1)
   .new b       : Point(1, 2)
   .new b       : Point(x, y)
   .new b       : Point(pSize)
   .new b       : Point(pPoint)

   .new p       : ptr Point()
   .new p       : ptr Point(1)
   .new p       : ptr Point(1, 2)
   .new p       : ptr Point(x, y)
   .new p       : ptr Point(pSize)
   .new p       : ptr Point(pPoint)

    Point       ()
    Point       (1)
    Point       (1, 2)
    Point       (x, y)
    Point       (pSize)
    Point       (pPoint)

    p.Equals    (pPoint)
    ret

main endp

    end

