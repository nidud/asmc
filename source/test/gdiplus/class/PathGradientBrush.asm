; PATHGRADIENTBRUSH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include gdiplus.inc

    .code

main proc

  .new p:ptr PathGradientBrush()

    PathGradientBrush()
    p.PathGradientBrush()
    p.Release()
    p.CreatePathGradient(NULL, 0, 0)
    p.CreatePathGradientI(NULL, 0, 0)
    p.CreatePathGradientFromPath(NULL)
    p.GetCenterColor(NULL)
    p.SetCenterColor(NULL)
    p.GetPointCount()
    p.GetSurroundColorCount()
    p.GetSurroundColors(NULL, NULL)
    p.SetSurroundColors(NULL, NULL)
    p.GetGraphicsPath(NULL)
    p.SetGraphicsPath(NULL)
    p.GetCenterPoint(NULL)
    p.GetCenterPointI(NULL)
    p.SetCenterPoint(NULL)
    p.SetCenterPointI(NULL)
    p.GetRectangle(NULL)
    p.GetRectangleI(NULL)
    p.SetGammaCorrection(0)
    p.GetGammaCorrection()
    p.GetBlendCount()
    p.GetBlend(NULL, NULL, 0)
    p.SetBlend(NULL, NULL, 0)
    p.GetInterpolationColorCount()
    p.SetInterpolationColors(NULL, NULL, 0)
    p.GetInterpolationColors(NULL, 0.0, 0)
    p.SetBlendBellShape(0.0, 0.0)
    p.SetBlendTriangularShape(0.0, 0.0)
    p.GetTransform(NULL)
    p.SetTransform(NULL)
    p.ResetTransform()
    p.MultiplyTransform(NULL, 0)
    p.TranslateTransform(0.0, 0.0, 0)
    p.ScaleTransform(0.0, 0.0, 0)
    p.RotateTransform(0.0, 0)
    p.GetFocusScales(NULL, NULL)
    p.SetFocusScales(0.0, 0.0)
    p.GetWrapMode()
    p.SetWrapMode(0)
    ret

main endp

    end
