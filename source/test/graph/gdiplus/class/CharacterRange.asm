; CHARACTERRANGE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include gdiplus.inc

    .code

main proc

  .new b:CharacterRange()
  .new b:CharacterRange(1)
  .new b:CharacterRange(1, 2)
  .new b:CharacterRange(b)
    ret

main endp

    end

