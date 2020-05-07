; SOLIDBRUSH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include gdiplus.inc

    .code

main proc

  .new p:ptr SolidBrush(0)

    SolidBrush(0)
    p.SolidBrush(0)
    p.Release()
    p.GetColor(NULL)
    p.SetColor(0)
    ret

main endp

    end
