; COLOR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include gdiplus.inc

    .code

main proc

  .new p:ptr Color(0)

    Color(0)
    p.Color(0)
    p.Release()
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
