; COLOR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include gdiplus.inc

    .code

main proc

  .new p:Color(0)
  .new p:Color(0, 1, 2)
  .new p:Color(0, 1, 2, 3)

    p.GetAlpha()
    p.GetA()
    p.GetRed()
    p.GetR()
    p.GetGreen()
    p.GetG()
    p.GetBlue()
    p.GetB()
    p.GetValue()
    p.SetValue(0)
    p.SetFromCOLORREF(0)
    p.ToCOLORREF()
    ret

main endp

    end
