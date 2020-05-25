; GRAPHICS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include gdiplus.inc

    .code

main proc

    .new p:Graphics(NULL)

    p.Release()

;    p.FromImage(NULL)
    p.FromGraphics(NULL)

    p.SetNativeGraphics(NULL)
    p.SetStatus(0)
    p.GetNativeGraphics()
    p.GetNativePen(NULL)
    p.Flush(0)
    p.GetHDC()
    p.ReleaseHDC(NULL)
    p.SetRenderingOrigin(0, 0)
    p.GetRenderingOrigin(NULL, NULL)
    p.SetCompositingMode(0)
    p.GetCompositingMode()
    p.SetCompositingQuality(0)
    p.GetCompositingQuality()
    p.SetTextRenderingHint(0)
    p.GetTextRenderingHint()
    p.SetTextContrast(0)
    p.GetTextContrast()
    p.GetInterpolationMode()
    p.SetInterpolationMode(0)
    p.SetAbort(NULL)
    p.GetSmoothingMode()
    p.SetSmoothingMode(0)
    p.GetPixelOffsetMode()
    p.SetPixelOffsetMode(0)
    p.SetTransform(NULL)
    p.ResetTransform()
    p.MultiplyTransform(NULL, 0)
    p.TranslateTransform(0.0, 0.0, 0)
    p.ScaleTransform(0.0, 0.0, 0)
    p.RotateTransform(0.0, 0)
    p.GetTransform(NULL)
    p.SetPageUnit(0)
    p.SetPageScale(0.0)
    p.GetPageUnit()
    p.GetPageScale()
    p.GetDpiX()
    p.GetDpiY()
    p.TransformPoints(0, 0, NULL, 0)
    p.TransformPointsI(0, 0, NULL, 0)
    p.GetNearestColor(NULL)
    p.DrawLine(NULL, 0.0, 0.0, 0.0, 0.0)
    p.DrawLines(NULL, NULL, 0)
    p.DrawLineI(NULL, 0, 0, 0, 0)

    p.DrawLinesI(NULL, NULL, 0)
    p.DrawArc(NULL, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0)

    p.DrawArcI(NULL, 0, 0, 0, 0, 0.0, 0.0)

    p.DrawBezier(NULL, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0)

    p.DrawBeziers(NULL, NULL, 0)
    p.DrawBezierI(NULL, 0, 0, 0, 0, 0, 0, 0, 0)

    p.DrawBeziersI(NULL, NULL, 0)
    p.DrawRectangle(NULL, 0.0, 0.0, 0.0, 0.0)

    p.DrawRectangles(NULL, NULL, 0)
    p.DrawRectangleI(NULL, 0, 0, 0, 0)

    p.DrawRectanglesI(NULL, NULL, 0)
    p.DrawEllipse(NULL, 0.0, 0.0, 0.0, 0.0)

    p.DrawEllipseI(NULL, 0, 0, 0, 0)

    p.DrawPie(NULL, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0)

    p.DrawPieI(NULL, 0, 0, 0, 0, 0.0, 0.0)

    p.DrawPolygon(NULL, NULL, 0)
    p.DrawPolygonI(NULL, NULL, 0)
    p.DrawPath(NULL, NULL)
    p.DrawCurve(NULL, NULL, 0)
    p.DrawCurve2(NULL, NULL, 0, 0.0)
    p.DrawCurve3(NULL, NULL, 0, 0, 0, 0.0)
    p.DrawCurveI(NULL, NULL, 0)
    p.DrawCurve2I(NULL, NULL, 0, 0.0)
    p.DrawCurve3I(NULL, NULL, 0, 0, 0, 0.0)
    p.DrawClosedCurve(NULL, NULL, 0)
    p.DrawClosedCurve2(NULL, NULL, 0, 0.0)
    p.DrawClosedCurveI(NULL, NULL, 0)
    p.DrawClosedCurve2I(NULL, NULL, 0, 0.0)
    p.Clear(NULL)
    p.FillRectangle(NULL, 0.0, 0.0, 0.0, 0.0)

    p.FillRectangles(NULL, NULL, 0)
    p.FillRectangleI(NULL, 0, 0, 0, 0)

    p.FillRectanglesI(NULL, NULL, 0)
    p.FillPolygon(NULL, NULL, 0, 0)

    p.FillPolygonI(NULL, NULL, 0, 0)

    p.FillEllipse(NULL, 0.0, 0.0, 0.0, 0.0)

    p.FillEllipseI(NULL, 0, 0, 0, 0)

    p.FillPie(NULL, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0)

    p.FillPieI(NULL, 0, 0, 0, 0, 0.0, 0.0)

    p.FillPath(NULL, NULL)
    p.FillClosedCurve(NULL, NULL, 0)
    p.FillClosedCurve2(NULL, NULL, 0, 0, 0.0)
    p.FillClosedCurveI(NULL, NULL, 0)
    p.FillClosedCurve2I(NULL, NULL, 0, 0, 0.0)
    p.FillRegion(NULL, NULL)
    p.DrawString(NULL, 0, NULL, NULL, NULL, NULL)


    p.MeasureString(NULL, 0, NULL, NULL, NULL, NULL, 0, NULL)

    p.MeasureString3(NULL, 0, NULL, NULL, NULL, NULL)
    p.MeasureString4(NULL, 0, NULL, NULL, NULL)
    p.MeasureString5(NULL, 0, NULL, NULL, NULL)
    ;p.MeasureCharacterRanges(NULL, 0, NULL, NULL, NULL, 0, NULL)
    p.DrawDriverString(NULL, 0, NULL, NULL, NULL, 0, NULL)
    p.MeasureDriverString(NULL, 0, NULL, NULL, 0, NULL, NULL)
    p.DrawCachedBitmap(NULL, 0, 0)
    p.DrawImage(NULL, 0.0, 0.0)
    p.DrawImageI(NULL, 0, 0)
    p.DrawImageRect(NULL, 0.0, 0.0, 0.0, 0.0)

    p.DrawImageRectI(NULL, 0, 0, 0, 0)

    p.DrawImagePoints(NULL, NULL, 0)
    p.DrawImagePointsI(NULL, NULL, 0)
    p.DrawImagePointRect(NULL, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0)
    p.DrawImageRectRect(NULL, NULL, 0.0, 0.0, 0.0, 0.0, 0, NULL, NULL, NULL)
    p.DrawImagePointsRect(NULL, NULL, 0, 0.0, 0.0, 0.0, 0.0, 0, NULL, NULL, NULL)
    p.DrawImagePointRectI(NULL, 0, 0, 0, 0, 0, 0, 0)
    p.DrawImageRectRectI(NULL, NULL, 0, 0, 0, 0, 0, NULL, NULL, NULL)
    p.DrawImagePointsRectI(NULL, NULL, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL)
    p.DrawImageRectRect2(NULL, NULL, NULL, 0, NULL)
    p.DrawImageFX(NULL, NULL, NULL, NULL, NULL, 0)

    p.EnumerateMetafileDestPoint(NULL, NULL, 0, NULL, NULL)
    p.EnumerateMetafileDestPointI(NULL, NULL, NULL, NULL, NULL)
    p.EnumerateMetafileDestRect(NULL, NULL, NULL, NULL, NULL)
    p.EnumerateMetafileDestRectI(NULL, NULL, NULL, NULL, NULL)
    p.EnumerateMetafileDestPoints(NULL, NULL, 0, NULL, NULL, NULL)
    p.EnumerateMetafileDestPointsI(NULL, NULL, 0, NULL, NULL, NULL)
    p.EnumerateMetafileSrcRectDestPoint(NULL, NULL, NULL, 0, NULL, NULL, NULL)
    p.EnumerateMetafileSrcRectDestPointI(NULL, NULL, NULL, 0, NULL, NULL, NULL)
    p.EnumerateMetafileSrcRectDestRect(NULL, NULL, NULL, 0, NULL, NULL, NULL)
    p.EnumerateMetafileSrcRectDestRectI(NULL, NULL, NULL, 0, NULL, NULL, NULL)
    p.EnumerateMetafileSrcRectDestPoints(NULL, NULL, 0, NULL, 0, NULL, NULL, NULL)
    p.EnumerateMetafileSrcRectDestPointsI(NULL, NULL, 0, NULL, 0, NULL, NULL, NULL)

    p.SetClip(NULL, 0)
    p.SetClipRect(NULL, 0)
    p.SetClipRectI(NULL, 0)
    p.SetClipPath(NULL, 0)
    p.SetClipRegion(NULL, 0)
    p.SetClipHrgn(NULL, 0)

    p.IntersectClipRect(NULL)
    p.IntersectClipRectI(NULL)
    p.IntersectClipRegion(NULL)

    p.ExcludeClipRect(NULL)
    p.ExcludeClipRectI(NULL)
    p.ExcludeClipRegion(NULL)
    p.ResetClip()
    p.TranslateClip(0.0, 0.0)
    p.TranslateClipI(0, 0)
    p.GetClip(NULL)
    p.GetClipBounds(NULL)
    p.GetClipBoundsI(NULL)
    p.IsClipEmpty()
    p.GetVisibleClipBounds(NULL)
    p.GetVisibleClipBoundsI(NULL)
    p.IsVisibleClipEmpty()

    p.IsVisiblePointI(NULL)
    p.IsVisiblePoint2I(0, 0)
    p.IsVisibleRectI(NULL)
    p.IsVisibleRectI2(0, 0, 0, (0)
    p.IsVisiblePoint(NULL)
    p.IsVisiblePoint2(0.0, 0.0)
    p.IsVisibleRect(NULL)
    p.IsVisibleRect2(0.0, 0.0, 0.0, 0.0)

    p.Save()
    p.Restore(0)
    p.BeginContainer(NULL, NULL, 0)
    p.BeginContainerI(NULL, NULL, 0)
    p.BeginContainer2()
    p.EndContainer(0)
    p.AddMetafileComment(NULL, 0)
    p.GetHalftonePalette()
    p.GetLastStatus()
    ret

main endp

    end
