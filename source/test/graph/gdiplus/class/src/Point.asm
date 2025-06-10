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

   .new b       : Point()
   .new b       : Point(1)
   .new b       : Point(1, 2)
   .new b       : Point(x, y)
   .new b       : Point(size)
   .new b       : Point(point)
    ret

main endp

    end

