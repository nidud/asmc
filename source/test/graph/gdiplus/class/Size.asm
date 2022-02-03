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

   .new b       : Size()
   .new b       : Size(1)
   .new b       : Size(1, 2)
   .new b       : Size(x, y)
   .new b       : Size(size)
   .new b       : Size(point)
    ret

main endp

    end

