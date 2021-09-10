; REGION.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include gdiplus.inc

    .code

main proc

    local hRgn:HRGN
    local pRectF:ptr RectF
    local pRect:ptr Rect
    local pGraphics:ptr Graphics
    local pGraphicsPath:ptr GraphicsPath
    local pRegion:ptr Region
    local pPoint:ptr Point
    local pPointF:ptr PointF
    local pMatrix:ptr Matrix
    local pBYTE:ptr byte
    local pUINT:ptr UINT
    local pINT:ptr SINT

    .new p:Region()
    .new p:Region(pRectF)
    .new p:Region(pRect)
    .new p:Region(pGraphicsPath)
    .new p:Region(pBYTE, 0)
    .new p:Region(hRgn)
    .new p:Region(pRegion)

    p.FromHRGN(hRgn)
    p.Release()

    p.Clone()
    p.MakeInfinite()
    p.MakeEmpty()
    p.GetDataSize()
    p.GetData(pBYTE, 0, pUINT)

    p.Intersect(pRect)
    p.Intersect(pRectF)
    p.Intersect(pGraphicsPath)
    p.Intersect(pRegion)

    p._Union(pRect)
    p._Union(pRectF)
    p._Union(pGraphicsPath)
    p._Union(pRegion)

    p._Xor(pRect)
    p._Xor(pRectF)
    p._Xor(pGraphicsPath)
    p._Xor(pRegion)

    p.Exclude(pRect)
    p.Exclude(pRectF)
    p.Exclude(pGraphicsPath)
    p.Exclude(pRegion)

    p.Complement(pRect)
    p.Complement(pRectF)
    p.Complement(pGraphicsPath)
    p.Complement(pRegion)

    p.Translate(0.0, 0.0)
    p.Translate(0, 0)
    p.Transform(pMatrix)
    p.GetBounds(pRect, pGraphics)
    p.GetBounds(pRectF, pGraphics)
    p.GetHRGN(pGraphics)
    p.IsEmpty(pGraphics)
    p.IsInfinite(pGraphics)

    p.IsVisible(0, 0)
    p.IsVisible(0, 0, pGraphics)
    p.IsVisible(pPoint)
    p.IsVisible(pPoint, pGraphics)
    p.IsVisible(0.0, 0.0)
    p.IsVisible(0.0, 0.0, pGraphics)
    p.IsVisible(pPointF)
    p.IsVisible(pPointF, pGraphics)
    p.IsVisible(0, 0, 0, 0, pGraphics)
    p.IsVisible(pRect)
    p.IsVisible(pRect, pGraphics)
    p.IsVisible(0.0, 0.0, 0.0, 0.0)
    p.IsVisible(0.0, 0.0, 0.0, 0.0, pGraphics)
    p.IsVisible(pRectF)
    p.IsVisible(pRectF, pGraphics)

    p.Equals(pRegion, pGraphics)
    p.GetRegionScansCount(pMatrix)
    p.GetRegionScans(pMatrix, pRectF, pINT)
    p.GetRegionScans(pMatrix, pRect, pINT)
    p.GetLastStatus()
    p.SetStatus()
    p.SetStatus(1)
    p.SetNativeRegion(pRegion)
    ret

main endp

    end
