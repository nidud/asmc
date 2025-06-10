; GRAPHICSPATH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include gdiplus.inc

    .code

main proc

    local hdc:HDC
    local h:HANDLE
    local hwnd:HWND
    local pImage:ptr Image
    local pPoint:ptr Point
    local pPointF:ptr PointF
    local pRect:ptr Rect
    local pRectF:ptr RectF
    local pSize:ptr Size
    local pSizeF:ptr SizeF
    local pPen:ptr Pen
    local pGraphicsPath:ptr GraphicsPath
    local pBrush:ptr Brush
    local pRegion:ptr Region
    local pFont:ptr Font
    local pWCHAR:ptr WCHAR
    local pStringFormat:ptr StringFormat
    local pMatrix:ptr Matrix
    local pImageAttributes:ptr ImageAttributes
    local pDrawImageAbort:ptr DrawImageAbort
    local pMetafile:ptr Metafile
    local MetafileProc:EnumerateMetafileProc
    local pEffect:ptr Effect
    local hRgn:HRGN
    local pGraphics:ptr Graphics
    local pFontFamily:ptr FontFamily

    local point:Point
    local pointF:PointF
    local rect:Rect
    local rectF:RectF
    local size:Size
    local sizeF:SizeF

  .new p:GraphicsPath()

    p.Release()
    p.SetNativePath(NULL)
    p.SetStatus(0)

    p.Reset()
    p.GetFillMode()
    p.SetFillMode(0)
    p.GetPathData(NULL)
    p.StartFigure()
    p.CloseFigure()
    p.CloseAllFigures()
    p.SetMarker()
    p.ClearMarkers()
    p.Reverse()
    p.GetLastPoint(NULL)

    p.AddLine(1, 2, 3, 4)
    p.AddLine(0.0, 0.0, 0.0, 0.0)
    p.AddLine(point, point)
    p.AddLine(pointF, pointF)

    p.AddLines(pPointF, 0)
    p.AddLines(pPoint, 0)

    p.AddArc(0.0, 0.0, 0.0, 0.0, 0.0, 0.0)
    p.AddArc(0, 0, 0, 0, 0.0, 0.0)
    p.AddArc(rect, 0.0, 0.0)
    p.AddArc(rectF, 0.0, 0.0)

    p.AddBezier(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0)
    p.AddBezier(pointF, pointF, pointF, pointF)
    p.AddBeziers(pPointF, 0)
    p.AddBezier(0, 0, 0, 0, 0, 0, 0, 0)
    p.AddBezier(point, point, point, point)
    p.AddBeziers(pPoint, 0)

    p.AddCurve(pPointF, 0)
    p.AddCurve(pPointF, 0, 0.0)
    p.AddCurve(pPointF, 0, 0, 0, 0.0)
    p.AddCurve(pPoint, 0)
    p.AddCurve(pPoint, 0, 0.0)
    p.AddCurve(pPoint, 0, 0, 0, 0.0)

    p.AddClosedCurve(pPointF, 0)
    p.AddClosedCurve(pPointF, 0, 0.0)
    p.AddClosedCurve(pPoint, 0)
    p.AddClosedCurve(pPoint, 0, 0.0)

    p.AddRectangle(rectF)
    p.AddRectangles(pRectF, 0)
    p.AddRectangle(rect)
    p.AddRectangles(pRect, 0)

    p.AddEllipse(0, 0, 0, 0)
    p.AddEllipse(rect)
    p.AddEllipse(0.0, 0.0, 0.0, 0.0)
    p.AddEllipse(rectF)

    p.AddPie(0.0, 0.0, 0.0, 0.0, 0.0, 0.0)
    p.AddPie(rectF, 0.0, 0.0)
    p.AddPie(0, 0, 0, 0, 0.0, 0.0)
    p.AddPie(rect, 0.0, 0.0)

    p.AddPolygon(pPointF, 0)
    p.AddPolygon(pPoint, 0)

    p.AddPath(pGraphicsPath, 0)
    p.AddString(pWCHAR, 0, pFontFamily, 0, 0.0, pointF, pStringFormat)
    p.AddString(pWCHAR, 0, pFontFamily, 0, 0.0, point, pStringFormat)
    p.AddString(pWCHAR, 0, pFontFamily, 0, 0.0, rectF, pStringFormat)
    p.AddString(pWCHAR, 0, pFontFamily, 0, 0.0, rect, pStringFormat)

    p.Transform(NULL)
    ;p.GetBounds(pRectF, NULL, NULL)
    ;p.GetBounds(pRect, NULL, NULL)
    p.Flatten()
    p.Flatten(NULL, 0.0)
    p.Widen(NULL)
    p.Widen(NULL, NULL, 0.0)
    p.Outline()
    p.Outline(NULL, 0.0)
    p.Warp(NULL, 0, rect)
    p.Warp(NULL, 0, rect, NULL, 0, 0.0)
    p.GetPointCount()
    p.GetPathTypes(NULL, 0)
    p.GetPathPoints(pPointF, 0)
    p.GetPathPoints(pPoint, 0)
    p.GetLastStatus()
    ;p.IsVisible(0, 0, NULL)
    ;p.IsVisible(0.0, 0.0, NULL)
    ;p.IsVisible(NULL, NULL)
    ;p.IsVisible(NULL, NULL)
    ;p.IsOutlineVisible(0, 0, NULL, NULL)
    ;p.IsOutlineVisible(0.0, 0.0, NULL, NULL)
    ;p.IsOutlineVisible(NULL, NULL, NULL)
    ;p.IsOutlineVisible(NULL, NULL, NULL)
    ret

main endp

    end
