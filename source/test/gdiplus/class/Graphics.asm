; GRAPHICS.ASM--
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


    ; Graphics(HDC)
    ; Graphics(HDC, HANDLE)
    ; Graphics(HWND, BOOL = FALSE)
    ; Graphics(Image*)

    .new p:Graphics(hdc)
    .new p:Graphics(hdc, h)
    .new p:Graphics(hwnd)
    .new p:Graphics(pImage)

    p.Release()

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

    p.TransformPoints(0, 0, pPoint, 0)
    p.TransformPoints(0, 0, pPointF, 0)

    p.GetNearestColor(NULL)

    ; DrawLine(Pen*, REAL, REAL, REAL, REAL)
    ; DrawLine(Pen*, PointF*, PointF*)
    ; DrawLine(Pen*, INT, INT, INT, INT)
    ; DrawLine(Pen*, Point*, Point*)

    p.DrawLine(pPen, 0.0, 0.0, 0.0, 0.0)
    p.DrawLine(pPen, pPointF, pPointF)
    p.DrawLine(pPen, 0, 0, 0, 0)
    p.DrawLine(pPen, ebx, ebx, ebx, ebx)
    p.DrawLine(pPen, pPoint, pPoint)

    ; DrawLines(Pen*, PointF*, INT)
    ; DrawLines(Pen*, Point*, INT)

    p.DrawLines(pPen, pPointF, 0)
    p.DrawLines(pPen, pPoint, 0)

    p.DrawArc(pPen, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0)
    p.DrawArc(pPen, 0, 0, 0, 0, 0.0, 0.0)

    p.DrawBezier(pPen, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0)
    p.DrawBezier(pPen, 0, 0, 0, 0, 0, 0, 0, 0)
    p.DrawBeziers(pPen, pPointF, 0)
    p.DrawBeziers(pPen, pPoint, 0)

    p.DrawRectangle(pPen, 0.0, 0.0, 0.0, 0.0)
    p.DrawRectangle(pPen, 0, 0, 0, 0)
    p.DrawRectangles(pPen, pRectF, 0)
    p.DrawRectangles(pPen, pRect, 0)

    p.DrawEllipse(pPen, 0.0, 0.0, 0.0, 0.0)
    p.DrawEllipse(pPen, 0, 0, 0, 0)
    p.DrawPie(pPen, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0)
    p.DrawPie(pPen, 0, 0, 0, 0, 0.0, 0.0)

    p.DrawPolygon(pPen, pPointF, 0)
    p.DrawPolygon(pPen, pPoint, 0)
    p.DrawPath(pPen, pGraphicsPath)

    p.DrawCurve(pPen, pPointF, 0)
    p.DrawCurve(pPen, pPointF, 0, 0.0)
    p.DrawCurve(pPen, pPointF, 0, 0, 0, 0.0)
    p.DrawCurve(pPen, pPoint, 0)
    p.DrawCurve(pPen, pPoint, 0, 0.0)
    p.DrawCurve(pPen, pPoint, 0, 0, 0, 0.0)

    p.DrawClosedCurve(pPen, pPointF, 0)
    p.DrawClosedCurve(pPen, pPointF, 0, 0.0)
    p.DrawClosedCurve(pPen, pPoint, 0)
    p.DrawClosedCurve(pPen, pPoint, 0, 0.0)

    p.Clear(NULL)
    p.FillRectangle(pBrush, 0.0, 0.0, 0.0, 0.0)
    p.FillRectangle(pBrush, 0, 0, 0, 0)
    p.FillRectangle(pBrush, pRect)
    p.FillRectangle(pBrush, pRectF)

    p.FillRectangles(pBrush, pRectF, 0)
    p.FillRectangles(pBrush, pRect, 0)

    p.FillPolygon(pBrush, pPointF, 0, 0)
    p.FillPolygon(pBrush, pPoint, 0, 0)

    p.FillEllipse(pBrush, 0.0, 0.0, 0.0, 0.0)
    p.FillEllipse(pBrush, 0, 0, 0, 0)
    p.FillEllipse(pBrush, pRect)
    p.FillEllipse(pBrush, pRectF)

    p.FillPie(pBrush, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0)
    p.FillPie(pBrush, 0, 0, 0, 0, 0.0, 0.0)
    p.FillPie(pBrush, pRect, 0.0, 0.0)
    p.FillPie(pBrush, pRectF, 0.0, 0.0)

    p.FillPath(pBrush, pGraphicsPath)

    p.FillClosedCurve(pBrush, pPointF, 0)
    p.FillClosedCurve(pBrush, pPointF, 0, 0, 0.0)
    p.FillClosedCurve(pBrush, pPoint, 0)
    p.FillClosedCurve(pBrush, pPoint, 0, 0, 0.0)

    p.FillRegion(pBrush, pRegion)
    p.DrawString(pWCHAR, 0, pFont, pRectF, pStringFormat, pBrush)

    ; MeasureString(WCHAR*, INT, Font*, RectF*, StringFormat*, RectF*, INT* = 0, INT* = 0)
    ; MeasureString(WCHAR*, INT, Font*, SizeF*, StringFormat*, SizeF*, INT* = 0, INT* = 0)
    ; MeasureString(WCHAR*, INT, Font*, PointF*, StringFormat*, RectF*)
    ; MeasureString(WCHAR*, INT, Font*, RectF*, RectF*)

    p.MeasureString(pWCHAR, 0, pFont, pRectF, pStringFormat, pRectF, NULL, NULL)
    p.MeasureString(pWCHAR, 0, pFont, pSizeF, pStringFormat, pSizeF, NULL, NULL)
    p.MeasureString(pWCHAR, 0, pFont, pPointF, pStringFormat, pRectF)
    p.MeasureString(pWCHAR, 0, pFont, pRectF, pRectF)

    p.MeasureCharacterRanges(pWCHAR, 0, pFont, pRectF, pStringFormat, 0, pRegion)

    p.DrawDriverString(pWCHAR, 0, pFont, pBrush, pPointF, 0, pMatrix)
    p.MeasureDriverString(pWCHAR, 0, pFont, pPointF, 0, pMatrix, pRectF)
    p.DrawCachedBitmap(NULL, 0, 0)

    ; DrawImage(Image*, PointF*)
    ; DrawImage(Image*, REAL, REAL)
    ; DrawImage(Image*, RectF*)
    ; DrawImage(Image*, REAL, REAL, REAL, REAL)
    ; DrawImage(Image*, Point*)
    ; DrawImage(Image*, INT, INT)
    ; DrawImage(Image*, Rect*)
    ; DrawImage(Image*, INT, INT, INT, INT)
    ; DrawImage(Image*, PointF*, INT)
    ; DrawImage(Image*, Point*, INT)
    ; DrawImage(Image*, REAL, REAL, REAL, REAL, REAL, REAL, Unit)
    ; DrawImage(Image*, RectF*, REAL, REAL, REAL, REAL, Unit, ImageAttributes* = NULL, DrawImageAbort = NULL, VOID* = NULL)
    ; DrawImage(Image*, PointF*, INT, REAL, REAL, REAL, REAL, Unit, ImageAttributes* = NULL, DrawImageAbort = NULL, VOID* = NULL)
    ; DrawImage(Image*, INT, INT, INT, INT, INT, INT, Unit)
    ; DrawImage(Image*, Rect*, INT, INT, INT, INT, Unit, ImageAttributes* = NULL, DrawImageAbort = NULL, VOID* = NULL)
    ; DrawImage(Image*, Point*, INT, INT, INT, INT, INT, Unit, ImageAttributes* = NULL, DrawImageAbort = NULL, VOID* = NULL)
if (GDIPVER GE 0x0110)
    ; DrawImage(Image*, RectF*, RectF*, Unit, ImageAttributes* = NULL)
    ; DrawImage(Image*, RectF*, Matrix*, Effect*, ImageAttributes*, Unit)
endif
    p.DrawImage(pImage, pPointF)
    p.DrawImage(pImage, 0.0, 0.0)
    p.DrawImage(pImage, pRectF)
    p.DrawImage(pImage, 0.0, 0.0, 0.0, 0.0)
    p.DrawImage(pImage, pPoint)
    p.DrawImage(pImage, 0, 0)
    p.DrawImage(pImage, pRect)
    p.DrawImage(pImage, 0, 0, 0, 0)
    p.DrawImage(pImage, pPointF, 0)
    p.DrawImage(pImage, pPoint, 0)
    p.DrawImage(pImage, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0)
    p.DrawImage(pImage, pRectF, 0.0, 0.0, 0.0, 0.0, 0, pImageAttributes, pDrawImageAbort, NULL)
    p.DrawImage(pImage, pPointF, 0, 0.0, 0.0, 0.0, 0.0, 0, pImageAttributes, pDrawImageAbort, NULL)
    p.DrawImage(pImage, 0, 0, 0, 0, 0, 0, 0)
    p.DrawImage(pImage, pRect, 0, 0, 0, 0, 0, pImageAttributes, pDrawImageAbort, NULL)
    p.DrawImage(pImage, pPoint, 0, 0, 0, 0, 0, 0, pImageAttributes, pDrawImageAbort, NULL)
    p.DrawImage(pImage, pRectF, pRectF, 0, pImageAttributes)
    p.DrawImage(pImage, pRectF, pMatrix, pEffect, pImageAttributes, 0)

    p.EnumerateMetafile(pMetafile, pPointF, MetafileProc, NULL, pImageAttributes)
    p.EnumerateMetafile(pMetafile, pPoint, MetafileProc, NULL, pImageAttributes)
    p.EnumerateMetafile(pMetafile, pRectF, MetafileProc, NULL, pImageAttributes)
    p.EnumerateMetafile(pMetafile, pRect, MetafileProc, NULL, pImageAttributes)
    p.EnumerateMetafile(pMetafile, pPointF, 0, MetafileProc, NULL, pImageAttributes)
    p.EnumerateMetafile(pMetafile, pPoint, 0, MetafileProc, NULL, pImageAttributes)
    p.EnumerateMetafile(pMetafile, pPointF, pRectF, 1, MetafileProc, NULL, pImageAttributes)
    p.EnumerateMetafile(pMetafile, pPoint, pRect, 1, MetafileProc, NULL, pImageAttributes)
    p.EnumerateMetafile(pMetafile, pRectF, pRectF, 1, MetafileProc, NULL, pImageAttributes)
    p.EnumerateMetafile(pMetafile, pRect, pRect, 1, MetafileProc, NULL, pImageAttributes)
    p.EnumerateMetafile(pMetafile, pPointF, 0, pRectF, 1, MetafileProc, NULL, pImageAttributes)
    p.EnumerateMetafile(pMetafile, pPoint, 0, pRect, 1, MetafileProc, NULL, pImageAttributes)

    ; SetClip(Graphics*, CombineMode = CombineModeReplace)
    ; SetClip(RectF*, CombineMode = CombineModeReplace)
    ; SetClip(Rect*, CombineMode = CombineModeReplace)
    ; SetClip(GraphicsPath*, CombineMode = CombineModeReplace)
    ; SetClip(Region*, CombineMode = CombineModeReplace)
    ; SetClip(HRGN, CombineMode = CombineModeReplace)


    p.SetClip(pGraphics, 0)
    p.SetClip(pRectF, 0)
    p.SetClip(pRect, 0)
    p.SetClip(pGraphicsPath, 0)
    p.SetClip(pRegion, 0)
    p.SetClip(hRgn, 0)

    p.IntersectClip(pRectF)
    p.IntersectClip(pRect)
    p.IntersectClip(pRegion)

    p.ExcludeClip(pRectF)
    p.ExcludeClip(pRect)
    p.ExcludeClip(pRegion)
    p.ResetClip()
    p.TranslateClip(0.0, 0.0)
    p.TranslateClip(0, 0)
    p.GetClip(NULL)
    p.GetClipBounds(pRectF)
    p.GetClipBounds(pRect)
    p.IsClipEmpty()
    p.GetVisibleClipBounds(pRectF)
    p.GetVisibleClipBounds(pRect)
    p.IsVisibleClipEmpty()

    p.IsVisible(pPoint)
    p.IsVisible(pRect)
    p.IsVisible(0, 0, 0, 0)
    p.IsVisible(pPointF)
    p.IsVisible(pRectF)
    p.IsVisible(0.0, 0.0, 0.0, 0.0)

    p.Save()
    p.Restore(0)
    p.BeginContainer(pRectF, pRectF, 0)
    p.BeginContainer(pRect, pRect, 0)
    p.BeginContainer()
    p.EndContainer(0)
    p.AddMetafileComment(NULL, 0)
    p.GetHalftonePalette()
    p.GetLastStatus()
    ret

main endp

    end
