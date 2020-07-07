; SIZE.ASM--
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

   .new b       : Size()
   .new b       : Size(1)
   .new b       : Size(1, 2)
   .new b       : Size(x, y)
   .new b       : Size(pSize)
   .new b       : Size(pPoint)

   .new p       : ptr Size()
   .new p       : ptr Size(1)
   .new p       : ptr Size(1, 2)
   .new p       : ptr Size(x, y)
   .new p       : ptr Size(pSize)
   .new p       : ptr Size(pPoint)

    Size        ()
    Size        (1)
    Size        (1, 2)
    Size        (x, y)
    Size        (pSize)
    Size        (pPoint)

    b.Equals    (pPoint)
    b.radd8     (pPoint)
    b.rsub8     (pPoint)

    p.Equals    (pPoint)
    p.radd8     (pPoint)
    p.rsub8     (pPoint)
    ret

main endp

    end

