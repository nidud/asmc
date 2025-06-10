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
  local size    : SizeF

   .new b       : SizeF()
   .new b       : SizeF(1.0)
   .new b       : SizeF(1.0, 2.0)
   .new b       : SizeF(x, y)
   .new b       : SizeF(xmm0, xmm1)
   .new b       : SizeF(size)
    ret

main endp

    end

