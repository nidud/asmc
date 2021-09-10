; LINEARGRADIENTBRUSH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include gdiplus.inc

;; LinearGradientBrush(PointF*, PointF*, ARGB, ARGB)
;; LinearGradientBrush(Point*, Point*, ARGB, ARGB)
;; LinearGradientBrush(RectF*, ARGB, ARGB, LinearGradientMode)
;; LinearGradientBrush(Rect*, ARGB, ARGB, LinearGradientMode)
;; LinearGradientBrush(RectF*, ARGB, ARGB, REAL, BOOL isAngleScalable = FALSE)
;; LinearGradientBrush(Rect*, ARGB, ARGB, REAL, BOOL isAngleScalable = FALSE)

    .code

main proc

    local pPointF:ptr PointF
    local pPoint:ptr Point
    local argb:ARGB
    local pRectF:ptr RectF
    local pRect:ptr Rect
    local pColor:ptr Color
    local pREAL:ptr REAL
    local pMatrix:ptr Matrix

   .new p:LinearGradientBrush(pPointF, pPointF, argb, argb)
   .new p:LinearGradientBrush(pPoint, pPoint, argb, argb)
   .new p:LinearGradientBrush(pRectF, argb, argb, 0)
   .new p:LinearGradientBrush(pRect, argb, argb, 0)
   .new p:LinearGradientBrush(pRectF, argb, argb, 0.0)
   .new p:LinearGradientBrush(pRectF, argb, argb, 0.0, 0)
   .new p:LinearGradientBrush(pRect, argb, argb, 0.0)
   .new p:LinearGradientBrush(pRect, argb, argb, 0.0, 0)


    p.Release()

    p.SetLinearColors(argb, argb)
    p.GetLinearColors(pColor)
    p.GetRectangle(pRectF)
    p.GetRectangle(pRect)
    p.SetGammaCorrection(0)
    p.GetGammaCorrection()
    p.GetBlendCount()
    p.SetBlend(pREAL, pREAL, 0)
    p.GetBlend(pREAL, pREAL, 0)
    p.GetInterpolationColorCount()
    p.SetInterpolationColors(pColor, pREAL, 0)
    p.GetInterpolationColors(pColor, pREAL, 0)
    p.SetBlendBellShape(0.0)
    p.SetBlendBellShape(0.0, 2.0)
    p.SetBlendTriangularShape(0.0)
    p.SetBlendTriangularShape(0.0, 2.0)
    p.SetTransform(pMatrix)
    p.GetTransform(pMatrix)
    p.ResetTransform()
    p.MultiplyTransform(pMatrix)
    p.MultiplyTransform(pMatrix, 0)
    p.TranslateTransform(0.0, 0.0)
    p.TranslateTransform(0.0, 0.0, 0)
    p.ScaleTransform(0.0, 0.0)
    p.ScaleTransform(0.0, 0.0, 0)
    p.RotateTransform(0.0)
    p.RotateTransform(0.0, 0)
    p.SetWrapMode(0)
    p.GetWrapMode()
    ret

main endp

    end
