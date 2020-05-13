; LINEARGRADIENTBRUSH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include gdiplus.inc

    .code

main proc

  .new p:ptr LinearGradientBrush()

    LinearGradientBrush()

    p.Release()
    p.Create(NULL, NULL, 0, 0)
    p.CreateI(NULL, NULL, 0, 0)
    p.CreateFromRect(NULL, 0, 0, 0)
    p.CreateFromRectI(NULL, 0, 0, 0)
    p.CreateFromRectWithAngle(NULL, 0, 0, 0.0, 0)
    p.CreateFromRectWithAngleI(NULL, 0, 0, 0.0, 0)
    p.SetLinearColors(0, 0)
    p.GetLinearColors(NULL)
    p.GetRectangle(NULL)
    p.GetRectangleI(NULL)
    p.SetGammaCorrection(0)
    p.GetGammaCorrection()
    p.GetBlendCount()
    p.SetBlend(NULL, NULL, 0)
    p.GetBlend(NULL, NULL, 0)
    p.GetInterpolationColorCount()
    p.SetInterpolationColors(NULL, NULL, 0)
    p.GetInterpolationColors(NULL, NULL, 0)
    p.SetBlendBellShape(0.0, 0.0)
    p.SetBlendTriangularShape(0.0, 0.0)
    p.SetTransform(NULL)
    p.GetTransform(NULL)
    p.ResetTransform()
    p.MultiplyTransform(NULL, 0)
    p.TranslateTransform(0.0, 0.0, 0)
    p.ScaleTransform(0.0, 0.0, 0)
    p.RotateTransform(0.0, 0)
    p.SetWrapMode(0)
    p.GetWrapMode()
    ret

main endp

    end
