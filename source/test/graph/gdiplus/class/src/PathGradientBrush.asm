; PATHGRADIENTBRUSH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include gdiplus.inc

    .code

main proc

    local pGraphicsPath:ptr GraphicsPath
    local pINT:ptr int_t
    local pBOOL:ptr BOOL
    local pBYTE:ptr BYTE
    local pPointF:ptr PointF
    local pPoint:ptr Point
    local pColor:ptr Color
    local argb:ARGB
    local pREAL:ptr REAL
    local pRectF:ptr RectF
    local pRect:ptr Rect
    local pMatrix:ptr Matrix
    local pointF:PointF
    local point:Point

   .new p:PathGradientBrush(pGraphicsPath)
   .new p:PathGradientBrush(pPointF, 0)
   .new p:PathGradientBrush(pPointF, 0, 0)
   .new p:PathGradientBrush(pPoint, 0)
   .new p:PathGradientBrush(pPoint, 0, 0)

    p.Release()

    p.GetCenterColor(pColor)
    p.SetCenterColor(argb)
    p.GetPointCount()
    p.GetSurroundColorCount()
    p.GetSurroundColors(pColor, pINT)
    p.SetSurroundColors(pColor, pINT)
    p.GetGraphicsPath(pGraphicsPath)
    p.SetGraphicsPath(pGraphicsPath)

    p.GetCenterPoint(pPointF)
    p.GetCenterPoint(pPoint)
    p.SetCenterPoint(pointF)
    p.SetCenterPoint(point)

    p.GetRectangle(pRectF)
    p.GetRectangle(pRect)

    p.SetGammaCorrection(0)
    p.GetGammaCorrection()
    p.GetBlendCount()
    p.GetBlend(pREAL, pREAL, 0)
    p.SetBlend(pREAL, pREAL, 0)
    p.GetInterpolationColorCount()
    p.SetInterpolationColors(pColor, pREAL, 0)
    p.GetInterpolationColors(pColor, pREAL, 0)

    p.SetBlendBellShape(0.0)
    p.SetBlendBellShape(0.0, 2.0)
    p.SetBlendTriangularShape(0.0)
    p.SetBlendTriangularShape(0.0, 2.0)

    p.GetTransform(pMatrix)
    p.SetTransform(pMatrix)
    p.ResetTransform()
    p.MultiplyTransform(pMatrix)
    p.MultiplyTransform(pMatrix, 0)
    p.TranslateTransform(0.0, 0.0)
    p.TranslateTransform(0.0, 0.0, 0)
    p.ScaleTransform(0.0, 0.0, 0)
    p.ScaleTransform(0.0, 0.0)
    p.RotateTransform(0.0)
    p.RotateTransform(0.0, 0)
    p.GetFocusScales(pREAL, pREAL)
    p.SetFocusScales(0.0, 0.0)
    p.GetWrapMode()
    p.SetWrapMode(0)
    ret

main endp

    end
