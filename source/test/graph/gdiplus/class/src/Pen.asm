; PEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include gdiplus.inc

    .code


main proc

  .new a:Pen(Blue)
  .new b:Pen
  .new r:REAL

    a.Release()

    a.Clone(b)
    a.SetWidth(1.0)
    a.GetWidth()
    a.SetLineCap(0, 1, 2)
    a.SetStartCap(0)
    a.SetEndCap(0)
    a.SetDashCap(0)
    a.GetStartCap()
    a.GetEndCap()
    a.GetDashCap()
    a.SetLineJoin(0)
    a.GetLineJoin()
    a.SetCustomStartCap(NULL)
    a.GetCustomStartCap(NULL)
    a.SetCustomEndCap(NULL)
    a.GetCustomEndCap(NULL)
    a.SetMiterLimit(1.0)
    a.GetMiterLimit()
    a.SetAlignment(NULL)
    a.GetAlignment()
    a.SetTransform(NULL)
    a.GetTransform(NULL)
    a.ResetTransform()
    a.MultiplyTransform(NULL, 0)
    a.TranslateTransform(1.0, 2.0, 0)
    a.ScaleTransform(1.0, 2.0, 0)
    a.RotateTransform(1.0, 0)
    a.GetPenType()
    a.SetColor(NULL)
    a.SetBrush(NULL)
    a.GetColor()
    a.GetBrush()
    a.GetDashStyle()
    a.SetDashStyle(0)
    a.GetDashOffset()
    a.SetDashOffset(1.0)
    a.SetDashPattern(NULL, 0)
    a.GetDashPatternCount()
    a.GetDashPattern(NULL, 0)
    a.SetCompoundArray(&r, 0)
    a.GetCompoundArrayCount()
    a.GetCompoundArray(&r, 0)
    a.GetLastStatus()
    a.SetNativePen(&a)
    a.SetStatus(0)
    ret

main endp

    end
